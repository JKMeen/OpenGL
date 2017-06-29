#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {

public:
	float radius;
	vec3d center;
	vec3d velocity;
	vec3d acceleration;
	float mass;

	vec3d pVel;
	vec3d pAcc;
	bool accBackup;


	sphere() {}
	sphere(const vec3d& _center, float _radius) : center(_center), radius(_radius), accBackup(false), mass(0) {}

	void setRadius(float _radius);
	float getRadius(void);

	
	void setLocation(const vec3d& vec);
	vec3d getLocation(void);
	void moveLocation(const vec3d& displacement);

	void setVelocity(const vec3d& vec);
	vec3d getVelocity(void);

	void setAcc(vec3d acc);

	void initAcc();
	void addAcc(vec3d acc);

	void simulate(float dt);

	


	void visualize(void);
};
#endif