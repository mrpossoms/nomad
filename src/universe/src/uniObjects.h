#pragma once

#include "pfx.h"
#include "data.h"

// N * KM^2 / Kg^2
#define G 6.674e-14

using namespace data;
namespace uni {

struct Object_t : Storable_t{
	//    ___                       _   _        
	//   | _ \_ _ ___ _ __  ___ _ _| |_(_)___ ___
	//   |  _/ '_/ _ \ '_ \/ -_) '_|  _| / -_|_-<
	//   |_| |_| \___/ .__/\___|_|  \__|_\___/__/
	//               |_|                         
	vec3  position; // measured in Km
	vec3  velocity; // measured in Km/s
	float mass;     // measured in Kg
	float speed;    // storage value for velo mag
	
	union P {
		struct {

		} planet;
		struct {

		} station;
		uint8_t pad[];
	};

	//    __  __     _   _            _    
	//   |  \/  |___| |_| |_  ___  __| |___
	//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
	//   |_|  |_\___|\__|_||_\___/\__,_/__/
	//                                     		
	vec3_t accTo(Object_t& obj)
	{
		float force = 0;
		vec3_t delta;
		vec3_sub(delta.v, obj.position, position);
			
		if(!delta.x && !delta.y) return delta;
		
		force = G * obj.mass * mass / vec3_mul_inner(delta.v, delta.v);
		vec3_norm(delta.v, delta.v);
		vec3_scale(delta.v, delta.v, force);

		return delta;
	};

	void update(float dt)
	{
		vec3 delta;
		vec3_scale(delta, velocity, dt);
		vec3_add(position, position, delta);
	};

	size_t write(int fd)
	{
		return ::write(fd, this, sizeof(*this));
	};
};

}
