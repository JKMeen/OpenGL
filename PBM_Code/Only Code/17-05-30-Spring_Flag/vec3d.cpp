#include "vec3d.h"

/*! Sets the vector elements */
void vec3d::set(float a, float b, float c)		{ x = a; y = b; z = c; }

/*! Stores the vector elements into the given parameters */
void vec3d::get(float &a, float &b, float &c)	{ a = x; b = y; c = z; }

/*! Negate Operator
*/
vec3d vec3d::operator-() const {
	return vec3d(-x,-y,-z);
}

/*! Vector Addition
- Return: vec3d */
vec3d vec3d::operator+(const vec3d& v) const {
	return vec3d(x + v[0], y + v[1], z + v[2]);
}

/*! Vector Subtraction
- Return: vec3d */
vec3d vec3d::operator-(const vec3d& v) const {
	return vec3d(x - v[0], y - v[1], z - v[2]);
}


/*! Element-wise Multiplication
 Return: vec3d */
vec3d vec3d::operator*(const vec3d& v) const { 
	return vec3d(x*v[0], y*v[1], z*v[2]);
}



/*! [] Operator for indexing x, y, and z */
float vec3d::operator[](int idx) const {
	switch (idx) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: return 0;
	}
}

/*! Length: returns the length of the vector */
float	vec3d::len(void) const { return sqrt(x*x + y*y + z*z); }

float	vec3d::lenSquare(void) const { return x*x + y*y + z*z; }

void	vec3d::normalize(void) {
	float l = len();
	if (l == 0.0f) { x = y = z = 0.0f; return; }
	x /= l; y /= l; z /= l;
}

/*! Returns a new normalized vector with the same direction */
vec3d	vec3d::getNormalized(void) const {
	float l = len();	if (len() == 0) return vec3d(0, 0, 0);
	return vec3d(x / l, y / l, z / l);
}


void	vec3d::show(void) {
	std::cout << x << " " << y << " " << z << std::endl;
}
///////////////////////////////////////////////

/*! functions and operators for vec3d */

vec3d cross(vec3d v1, vec3d v) {
	return vec3d(v1.y*v[2] - v1.z*v[1], -v1.x*v[2] + v1.z*v[0], v1.x*v[1] - v1.y*v[0]);
}

float dot(vec3d v1, vec3d v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


//vec3d operator+(vec3d v1, vec3d v2) {
//	return vec3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
//}

//vec3d operator-(vec3d v1, vec3d v2) {
//	return vec3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
//}

vec3d operator*(float s, vec3d v) {
	return vec3d(s*v[0], s*v[1], s*v[2]);
}

vec3d operator*(vec3d v, float s) {
	return vec3d(s*v[0], s*v[1], s*v[2]);
}

vec3d operator/(vec3d v, float s) {
	return vec3d(v[0]/s, v[1]/s, v[2]/s);
}


inline std::istream& operator>>(std::istream &is, vec3d &v) {
	is >> v.x >> v.y >> v.z;
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3d &v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}
