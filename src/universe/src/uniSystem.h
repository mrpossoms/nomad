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

	//    ___                       _   _  
	//   | _ \_ _ ___ _ __  ___ _ _| |_(_)___ ___
	//   |  _/ '_/ _ \ '_ \/ -_) '_|  _| / -_|_-< 
	//   |_| |_| \___/ .__/\___|_|  \__|_\___/__/  
	//               |_|                        		
	vector<System*>  subSystems;
	vector<Object_t*> objects;

	char name[64];

private:
	vec3  centerOfMass;
	float radius;
};

}
