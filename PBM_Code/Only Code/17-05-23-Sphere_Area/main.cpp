#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"
#include "sphere.h"


double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

#define NSPHERES 50

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];


	float density;
	float dragCoeff;

	CMyWindow() : CKangGL() {
		for (int i = 0; i < NSPHERES; i++) sphere[i] = addSphere();
		addPlane(100, 100, 5);
		setCamera(0, 50, 50, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 1; i < NSPHERES; i++){
			vec3d p(rand(-10, 10), 0, rand(-10, 10));
			sphere[i]->setLocation(p);
			sphere[i]->setVelocity(-p);
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(rand(0.1, 1.0));
			sphere[i]->setColor(vec3d(rand(0.0, 1.0), rand(0.0, 1.0), rand(0.0, 1.0)));
			sphere[i]->mass = sphere[i]->getRadius();
		}
		sphere[0]->setLocation(vec3d(0, 0, 0));
		sphere[0]->setVelocity(vec3d(0, 0, 0));
		sphere[0]->setAcc(vec3d(0, 0, 0));
		sphere[0]->setRadius(25.0);
		sphere[0]->setColor(vec3d(1.0, 0.0, 0.0));
		sphere[0]->mass = sphere[0]->getRadius();
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		int div = 10;
		if (dt > 0.03) dt = 0.01;
		dt = dt / div;
		for (int iteration = 0; iteration < div; iteration++){ // õ���� ���� ������
			for (int i = 0; i < NSPHERES; i++) {
				if (i > 0) {
					sphere[i]->setAcc(vec3d(0, -10, 0)); // �߷�
					vec3d drag = -0.05 * sphere[i]->getVelocity(); // �׷�
					sphere[i]->addAcc(drag / sphere[i]->mass); // �׷��� ����
				}
				sphere[i]->simulate(dt);
				sphere[i]->initAcc();
			}

			float e = 0.5; // ź��

			for (int i = 1; i < NSPHERES; i++){
				vec3d p = sphere[i]->getLocation();
				float d = p.len() + sphere[i]->getRadius() - sphere[0]->getRadius();// �հ�� ��
				if (d > 0){ // �հ� �� ���� �������� 0�� �� �ȿ� �ִ� ��
					// collision handling
					vec3d N = -p.getNormalized(); // �븻������� ���� N
					vec3d newloc = p + d*N + e*d*N;
					sphere[i]->setLocation(newloc); // �� �� �� ������ ������ ���ϰԸ� ����
					vec3d v = sphere[i]->getVelocity();

					// penetrating velocity (�հ� ���� �ӵ�)
					float penetration = dot(v, N);
					if (penetration < 0) { // ������ ��쿡 �հ� ���� ��
						vec3d vp = penetration * N;
						v = v - vp - e*vp; // v-vp�� ��� ������, -e*vp�� ���ָ� ź��
						sphere[i]->setVelocity(v);
					}
				}
			}

			// collision handling
			for (int i = 1; i < NSPHERES; i++){
				for (int j = i + 1; j < NSPHERES; j++){
					// ��ġ
					vec3d p1 = sphere[i]->getLocation();
					vec3d p2 = sphere[j]->getLocation();

					// �浹 �ۿ뼱�� ����
					vec3d N = (p1 - p2).getNormalized(); // �븻������� ���� N

					// �� ��ü�� �Ÿ�
					float distance = (p1 - p2).len();

					// ������
					float r1 = sphere[i]->getRadius();
					float r2 = sphere[j]->getRadius();

					// ����
					float m1 = sphere[i]->mass;
					float m2 = sphere[j]->mass;

					// ���� �ӵ� ��Į��(����)
					float v1 = dot(sphere[i]->getVelocity(), N); // dot : ����
					float v2 = dot(sphere[j]->getVelocity(), N);

					if (distance < r1 + r2 && v1 - v2 < 0){ // v1-v2 < 0 �� �հ� ������ �ϴ� ����
						// �ٲ� �ӵ� ��Į��(����)
						float v1new = (2.0 * m2*v2 + (m1 - m2)*v1) / (m1 + m2);
						float v2new = (2.0 * m1*v1 + (m2 - m1)*v2) / (m1 + m2);
						sphere[i]->setVelocity(sphere[i]->getVelocity() + (v1new - v1)*N);
						// ������ �ִ� �ӵ� v1*N�� ���ְ� ���ο� �ӵ� v1new*N�� ������
						sphere[j]->setVelocity(sphere[j]->getVelocity() + (v2new - v2)*N);
					}
				}

			}
		}
	}
};

int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}