#ifndef VEC3_YMKANG
#define VEC3_YMKANG

#include <iostream>
#include <math.h>

//! 3 dimensional vector class
//!
/*!
\brief Class for 3-D vectors

- vector operations: + (add) , - (sub), * (cross), ^ (dot)
- Copyright(c) Young-Min Kang */

class vec3d {
public:
	/*! vector elements */
	float x, y, z;

	//! Constructors
	vec3d() { x = 0; y = 0; z = 0; }
	vec3d(float a, float b, float c) { x = a; y = b; z = c; }


	//! Set Elements
	void set(float a, float b, float c);

	//! Get Elements
	void get(float &a, float &b, float &c);

	//! Bracket Operators for indexing the vector elements
	float operator[](int idx) const;

	//! Negate Operator
	vec3d operator-() const;

	//! Vector Addition
	/*! vectorA + vectorB returns the addition result*/
	vec3d operator+(const vec3d& v) const;

	//! Vector Subtraction
	/*! vectorA - vectorB returns the subtraction result*/
	vec3d operator-(const vec3d& v) const;

	//! Vector - Element-wise Multiplication
	/*! vectorA * vectorB returns (A.x*B.x, A.y*B.y, A.z*B.z) */
	vec3d operator*(const vec3d& v) const;  


	//! Vector Length
	float	len(void) const;
	float   lenSquare(void) const;

	//! Vector Normalization
	/*! The vector itself is normalized, and there is no return values */
	void	normalize(void);

	//! Returns the normalized version of the vector
	/*! The vector itself is not normalized, and the length is preserved */
	vec3d	getNormalized(void) const;

	void	show(void);
};


/*! cross and dot product functions
- usage: cross|dot product = cross|dot(vector1, vector2) */

vec3d cross(vec3d v1, vec3d v2);
float dot(vec3d v1, vec3d v2);

/*! * operators */
vec3d operator*(float s, vec3d v);
vec3d operator*(vec3d v, float s);
vec3d operator/(vec3d v, float s);


/*! stream in/out */
inline std::istream& operator>>(std::istream &is, vec3d &v);
inline std::ostream& operator<<(std::ostream &os, const vec3d &v);



#endif