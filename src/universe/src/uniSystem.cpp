#include "uniSystem.h"

using namespace uni;

System::System()
{
	static const char* undiscovered = "Undiscovered System";

	int len = strlen(undiscovered);
	memcpy(name, undiscovered, len);

	NEW_UUID(hash);
}
//-----------------------------------------------------------------------
System::System(const char* path)
{
	char lastWd[MAXPATHLEN];

	assert(getwd(lastWd)); // store the last working directory
	assert(chdir(path));   // switch to the system's working directory
	
	strcpy(sysPath, path);

	{
		int fd = open(".system", O_RDONLY);
		uint64_t objectCount = 0;

		// load stuff
		read(fd, hash, UUID_LEN);
		read(fd, name, sizeof(name));

		read(fd, &objectCount, sizeof(uint64_t));
		for(;objectCount--;){
			Object_t* obj = (Object_t*)malloc(sizeof(Object_t));
			read(fd, obj, sizeof(Object_t));
			objects.push_back(obj);
		}

		close(fd);
	}

	chdir(lastWd);
}
//-----------------------------------------------------------------------
size_t System::write(const char* path)
{
	char lastWd[MAXPATHLEN];
	char sysWd[MAXPATHLEN];
	size_t bytes = 0;

	assert(getwd(lastWd));
	sprintf(sysWd, "%s/sys%16s", path, hash);

	// switch to the system directory. if that fails
	// then try to create it.
	if(chdir(sysWd)){
		assert(mkdir(sysWd, 0666));
		chdir(sysWd);
	}

	int fd = open(".system", O_WRONLY | O_TRUNC | O_CREAT);

	bytes += ::write(fd, hash, UUID_LEN);
	bytes += ::write(fd, name, sizeof(name));

	return bytes;
}
//-----------------------------------------------------------------------
void System::hashAt(vec3 position, char hash[17])
{
	float x = position[0] / (float)scaleDivisor;
	float y = position[1] / (float)scaleDivisor;
	char ofi[8];
	
	((float*)ofi)[0] = x;
	((float*)ofi)[1] = y;

	sprintf(
		hash, "%02x%02x%02x%02x-%02x%02x%02x%02x",
		ofi[0], ofi[1], ofi[2], ofi[3],
		ofi[4], ofi[5], ofi[6], ofi[7]
	);
}
//-----------------------------------------------------------------------
int System::loadObjectsAt(vec3 position)
{
	char objFilePath[MAXPATHLEN], locHash[17];
	char lastWd[MAXPATHLEN];

	hashAt(position, locHash);
	sprintf(objFilePath, "%s/o%s", sysPath, locHash);

	uint32_t count = 0;
	DIR* dir = opendir(objFilePath);
	struct dirent* ep = NULL;

	if(!dir) return -1;
	
	getwd(lastWd);
	chdir(objFilePath);

	while((ep = readdir(dir))){
		if(ep->d_name[0] == '.') continue;
		++count;
		
		if(count > objects.size()){
			objects.push_back((Object_t*)malloc(sizeof(Object_t)));
		}
	
		int fd = open(ep->d_name, O_RDONLY);
		read(fd, objects[count], sizeof(Object_t));
		close(fd);
	}

	closedir(dir);
	chdir(lastWd);

	// clean up slots for extra objects
	while(objects.size() > count){
		free(objects[objects.size()]);
		objects.pop_back();
	}

	return 0;
}
//-----------------------------------------------------------------------
int System::saveObjects()
{
	char objFilePath[MAXPATHLEN], locHash[17];
	char lastWd[MAXPATHLEN];
	int savedObjects = 0;

	getwd(lastWd);
	chdir(sysPath);

	for(int i = objects.size(); i--;){
		hashAt(objects[i]->position, locHash);
		if(mkdir(locHash, 0666) && errno != EEXIST){
			errno = 0;
			continue;
		}

		sprintf(objFilePath, "%s/%16s", locHash, objects[i]->hash);
		int fd = open(objFilePath, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		objects[i]->write(fd);
		close(fd);

		++savedObjects;
	}
	
	chdir(lastWd);
	
	return savedObjects;
}
