#include "pfx.h"
#include "data.h"

#include "uniObjects.h"

using namespace std;

namespace uni {

class System : Object_t {
public:
	System();
	System(const char* path);
	~System();

	//    __  __     _   _            _
	//   |  \/  |___| |_| |_  ___  __| |___
	//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
	//   |_|  |_\___|\__|_||_\___/\__,_/__/
	//
	float getMass();
	float getRadius();

	size_t write(const char* path);

	void update(float dt)
	{
		for(int i = subSystems.size(); i--;){
			subSystems[i]->update(dt);
		}

		for(int i = objects.size(); i--;){
			objects[i]->update(dt);
		}
	};

	int loadObjectsAt(vec3 position);
	int saveObjects();

	//    ___                       _   _
	//   | _ \_ _ ___ _ __  ___ _ _| |_(_)___ ___
	//   |  _/ '_/ _ \ '_ \/ -_) '_|  _| / -_|_-<
	//   |_| |_| \___/ .__/\___|_|  \__|_\___/__/
	//               |_|
	vector<System*>  subSystems;
	vector<Object_t*> objects;

	char sysPath[MAXPATHLEN];
	uint8_t  name[64];
	uint8_t  hash[UUID_LEN];
	uint16_t scaleDivisor; // position scale divisor in KM

private:
	void hashAt(vec3 position, char hash[17]);

	vec3  centerOfMass;
	float radius;
};

}
