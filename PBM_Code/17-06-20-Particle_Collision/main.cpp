#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}


class CMyWindow : public CKangGL {
public:
	sphere *sphere[3];

	CMyWindow() : CKangGL() {
		for (int i = 0; i < 3; i++) sphere[i] = addSphere();
		//CCloth* myCloth = new CCloth(100, 100, 10, 10, 1, 1.5);
		CConfetti* myCloth = new CConfetti(101, 101, 10, 10, 1, 1.5);
		addCloth(myCloth);

		addPlane(100, 100, 5);
		setCamera(15, 5, 20, 15, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {

	};

	virtual void init(void) {
		for (int i = 0; i < 3; i++){
			vec3d p(15+5*i, 1, 5);
			sphere[i]->setLocation(p);
			sphere[i]->setVelocity(vec3d(0, 0, 0));
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(1);
			sphere[i]->setColor(vec3d(rand(0.0, 1.0), rand(0.0, 1.0), rand(0.0, 1.0)));
			sphere[i]->mass = sphere[i]->getRadius();
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		if (dt > 0.01) dt = 0.01;

		int iter = 10;

		dt = dt / iter;
		for (int i = 0; i < iter; i++) {
			// 색종이
			//cloth->simulate(dt);
			// init force and set gravity
			for (int i = 0; i < cloth->nPart; i++) {
				cloth->force[i].set(0, 0, 0);
				// gravity
				cloth->force[i] = cloth->mass[i] * vec3d(0, -10.0, 0);
			}

			// spring force
			for (int i = 0; i < cloth->nSpring; i++) {
				int p1 = cloth->spring[i].i;
				int p2 = cloth->spring[i].j;
				// f1 = k * d * (p2-p1)/|p2-p1|
				// f1 = spring constant * stretched length * direction
				vec3d dir = cloth->loc[p2] - cloth->loc[p1];
				float d = dir.len() - cloth->spring[i].l0;

				vec3d f1 = cloth->spring[i].k * d * dir.getNormalized();
				cloth->force[p1] = cloth->force[p1] + f1;
				cloth->force[p2] = cloth->force[p2] - f1;
			}

			// damping for each spring
			float dampingCoeff = 0.01;
			for (int i = 0; i < cloth->nSpring; i++) {
				int p1 = cloth->spring[i].i;
				int p2 = cloth->spring[i].j;
				vec3d v1 = cloth->vel[p1];
				vec3d v2 = cloth->vel[p2];
				vec3d vRel = v1 - v2;
				vec3d dir = cloth->loc[p2] - cloth->loc[p1];
				dir.normalize();

				vec3d F_damp = -dampingCoeff * dot(vRel, dir)*dir;
				cloth->force[p1] = cloth->force[p1] + F_damp;
				cloth->force[p2] = cloth->force[p2] - F_damp;
			}


			// wind drag and lift
			static float angle = 0.0f;
			angle += 0.001;
			vec3d wind = vec3d(cos(angle) * 50, 0, sin(angle) * 50);
			//vec3d wind = vec3d(cos(angle) * 50, 10, sin(angle) * 50);
			float dragCoeff = 0.00001;
			float liftCoeff = 0.0001;
			for (int i = 0; i < cloth->nPart; i++) {
				vec3d relWind = wind + vec3d(rand() % 10 - 5, 0, 0) - cloth->vel[i]; // 속도를 빼주면 상대 바람
				vec3d windDir = relWind.getNormalized();
				float DOT = dot(relWind, cloth->normal[i]);
				vec3d dragForce = dragCoeff * fabs(DOT) * windDir;

				float sign = DOT > 0 ? 1.0 : -1.0;
				float liftMagnitude = sign * cross(relWind, cloth->normal[i]).len();
				vec3d liftForce = liftCoeff * liftMagnitude * cloth->normal[i];

				cloth->force[i] = cloth->force[i] + dragForce + liftForce;
			}

			//force[0].set(0, 0, 0);
			//force[w * (h - 1)].set(0, 0, 0);

			// integration 
			for (int i = 0; i < cloth->nPart; i++) {
				cloth->vel[i] = cloth->vel[i] + (cloth->force[i] / cloth->mass[i])*dt;
				cloth->loc[i] = cloth->loc[i] + cloth->vel[i] * dt;
				if (cloth->loc[i].y < 0) {
					cloth->loc[i].y = 0;
					cloth->vel[i] = cloth->vel[i] - cloth->vel[i] / 5;
				}
			}

			// collision Sphere
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < cloth->nPart; j++){
					// 위치
					vec3d p1 = sphere[i]->getLocation();
					vec3d p2 = cloth->loc[j];

					// 충돌 작용선의 방향
					vec3d N = (p1 - p2).getNormalized(); // 노말라이즈된 벡터 N

					// 두 구체의 거리
					float distance = (p1 - p2).len();

					// 반지름
					float r1 = sphere[i]->getRadius();
					float r2 = 0.1;

					// 질량
					float m1 = sphere[i]->mass;
					float m2 = cloth->mass[j];

					// 기존 속도 스칼라(방향)
					float v1 = dot(sphere[i]->getVelocity(), N); // dot : 내적
					float v2 = dot(cloth->vel[j], N);

					if (distance < r1 + r2 && v1 - v2 < 0){ // v1-v2 < 0 은 뚫고 들어가려고 하는 상태
						// 바뀐 속도 스칼라(방향)
						float v1new = (2.0 * m2*v2 + (m1 - m2)*v1) / (m1 + m2);
						float v2new = (2.0 * m1*v1 + (m2 - m1)*v2) / (m1 + m2);
						//sphere[i]->setVelocity(sphere[i]->getVelocity() + (v1new - v1)*N);
						// 이전에 있던 속도 v1*N을 없애고 새로운 속도 v1new*N을 더해줌
						cloth->vel[j] = cloth->vel[j] + (v2new - v2)*N;
					}
				}
			}
		}
	}


};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "Cloth Simulation");
}