#include "uniSystem.h"

using namespace uni;

System::System()
{
	static const char* undiscovered = "Undiscovered System";

	int len = strlen(undiscovered);
	memcpy(name, undiscovered, len);
}

System::System(const char* path)
{
	char lastWd[MAXPATHLEN];
	assert(getwd(lastWd));
	assert(chdir(path));

	{
		int fd = open(".system", O_RDONLY | O_TRUNC | O_CREAT);
		uint64_t objectCount = 0;		

		// load stuff

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
