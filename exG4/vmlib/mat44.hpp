#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
// SOLUTION_TAGS: gl-(ex-[^12]|cw-2)

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

/** Mat44f: 4x4 matrix with floats
 *
 * See vec2f.hpp for discussion. Similar to the implementation, the Mat44f is
 * intentionally kept simple and somewhat bare bones.
 *
 * The matrix is stored in row-major order (careful when passing it to OpenGL).
 *
 * The overloaded operator () allows access to individual elements. Example:
 *    Mat44f m = ...;
 *    float m12 = m(1,2);
 *    m(0,3) = 3.f;
 *
 * The matrix is arranged as:
 *
 *   ⎛ 0,0  0,1  0,2  0,3 ⎞
 *   ⎜ 1,0  1,1  1,2  1,3 ⎟
 *   ⎜ 2,0  2,1  2,2  2,3 ⎟
 *   ⎝ 3,0  3,1  3,2  3,3 ⎠
 */

struct Mat44f
{
	float v[16];

	constexpr
	float& operator() (std::size_t aI, std::size_t aJ) noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
	constexpr
	float const& operator() (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
};

// Identity matrix
constexpr Mat44f kIdentity44f = { {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
} };

// Common operators for Mat44f.
// Note that you will need to implement these yourself.

constexpr
Mat44f operator*( Mat44f const& aLeft, Mat44f const& aRight ) noexcept
{
	Mat44f C{0.f};
	for	(int i = 0; i < 4; ++i) {
		for (int j = 0 ; j < 4; ++j) {
			C(i, j) = 0.f;
			for (int k = 0 ; k < 4; ++k) {
				C(i , j) += aLeft(i, k) * aRight(k, j);
			}
		}
	}
	return C;
}

constexpr
Vec4f operator*( Mat44f const& aLeft, Vec4f const& aRight ) noexcept
{
	// NOTE: might be ineficient but it is much better to work with this
 	float temp[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float aRightArray[4] = {aRight.x, aRight.y, aRight.z, aRight.w};

	for (int i = 0; i < 4; ++i) {
		// printf("Row %d\n", i);
		for (int j = 0; j < 4; ++j) {
			// printf("(%f + %f)")
			temp[i] += aLeft(i, j) * aRightArray[j];
		}
	}

	Vec4f C{temp[0], temp[1], temp[2], temp[3]};

	return C;	
}

// Functions:

inline
Mat44f make_rotation_x( float aAngle ) noexcept
{
	Mat44f rot = kIdentity44f;
    float cosA = std::cos(aAngle);
    float sinA = std::sin(aAngle);

	rot(1, 1) = cosA;	
	rot(1, 2) = -sinA;
	rot(2, 1) = sinA;
	rot(2, 2) = cosA;

	return rot;
}


inline
Mat44f make_rotation_y( float aAngle ) noexcept
{
	Mat44f rot = kIdentity44f;
    float cosA = std::cos(aAngle);
    float sinA = std::sin(aAngle);

	rot(0, 0) = cosA;
	rot(0, 2) = sinA;
	rot(2, 0) = -sinA;
	rot(2, 2) = cosA;

	return rot;
}

inline
Mat44f make_rotation_z( float aAngle ) noexcept
{
	Mat44f rot = kIdentity44f;
    float cosA = std::cos(aAngle);
    float sinA = std::sin(aAngle);

	rot(0, 0) = cosA;
	rot(0, 1) = -sinA;
	rot(1, 0) = sinA;
	rot(1, 1) = cosA;

	return rot;
}

inline
Mat44f make_translation( Vec3f aTranslation ) noexcept
{
	Mat44f trans = kIdentity44f;

	trans(0, 3) = aTranslation.x;
	trans(1, 3) = aTranslation.y;
	trans(2, 3) = aTranslation.z;

	return trans;
}

inline
Mat44f make_scaling( float aSX, float aSY, float aSZ ) noexcept
{
	Mat44f scale = kIdentity44f;

	scale(0, 0) = aSX;
	scale(1, 1) = aSY;
	scale(2, 2) = aSZ;

	return scale;
}

inline
Mat44f make_perspective_projection( float aFovInRadians, float aAspect, float aNear, float aFar ) noexcept
{
	Mat44f projMat{0};	

	float f = 1.f / tan(aFovInRadians / 2.f);

	projMat(0, 0) = f / aAspect;
	projMat(1, 1) = f;
	projMat(2, 2) = (aFar + aNear) / (aNear - aFar);
	projMat(2, 3) = (2.f * aFar * aNear) / (aNear - aFar);
	projMat(3, 2) = -1; 
	projMat(3, 3) = 0.f;


	return projMat;
}

#endif // MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
