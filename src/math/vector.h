#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

namespace Math
{
	typedef float vec_t;

	class CVector
	{
	public:
		// Members
		vec_t x, y, z;

		// Construction/destruction:
		CVector(void);
		CVector(vec_t X, vec_t Y, vec_t Z);
		CVector(vec_t* clr);

		// Initialization
		void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
		// TODO (Ilya): Should there be an init that takes a single float for consistency?

		// Got any nasty NAN's?
		bool IsValid() const;
		void Invalidate();

		// array access...
		vec_t operator[](int i) const;
		vec_t& operator[](int i);

		// Base address...
		vec_t* Base();
		vec_t const* Base() const;

		// Initialization methods
		void Random(vec_t minVal, vec_t maxVal);
		void Zero(); ///< zero out a CVector

		// equality
		bool operator==(const CVector& v) const;
		bool operator!=(const CVector& v) const;

		//Math operations
		void Clamp();
		CVector Clamped() const;

		const std::string& parse()
		{
			return std::string("x = ") + std::to_string(this->x) + std::string("\ty = ") + std::to_string(this->y) +
				std::string("\tz = ") + std::to_string(this->z);
		}

		// arithmetic operations
		CVector& operator+=(const CVector& v) {
			x += v.x; y += v.y; z += v.z;
			return *this;
		}

		CVector& operator-=(const CVector& v) {
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}

		CVector& operator*=(float fl) {
			x *= fl;
			y *= fl;
			z *= fl;
			return *this;
		}

		CVector& operator*=(const CVector& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		CVector& operator/=(const CVector& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}

		// this ought to be an opcode.
		CVector& operator+=(float fl) {
			x += fl;
			y += fl;
			z += fl;
			return *this;
		}

		// this ought to be an opcode.
		CVector& operator/=(float fl) {
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}
		CVector& operator-=(float fl) {
			x -= fl;
			y -= fl;
			z -= fl;
			return *this;
		}

		// negate the CVector components
		void	Negate();

		// Get the CVector's magnitude.
		vec_t	Length() const;

		// Get the CVector's magnitude squared.
		vec_t LengthSqr(void) const {
			return (x * x + y * y + z * z);
		}

		// return true if this CVector is (0,0,0) within tolerance
		bool IsZero(float tolerance = 0.01f) const {
			return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance &&
				z > -tolerance && z < tolerance);
		}

		vec_t	NormalizeInPlace();
		CVector	Normalized() const;
		bool	IsLengthGreaterThan(float val) const;
		bool	IsLengthLessThan(float val) const;

		// check if a CVector is within the box defined by two other CVectors
		bool WithinAABox(CVector const& boxmin, CVector const& boxmax);

		// Get the distance from this CVector to the other one.
		vec_t	DistTo(const CVector& vOther) const;

		// Get the distance from this CVector to the other one squared.
		// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
		// may be able to tidy this up after switching to VC7
		vec_t DistToSqr(const CVector& vOther) const {
			CVector delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;
			delta.z = z - vOther.z;

			return delta.LengthSqr();
		}

		// Copy
		void	CopyToArray(float* rgfl) const;

		// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
		// is about 12% faster than the actual CVector equation (because it's done per-component
		// rather than per-CVector).
		void	MulAdd(const CVector& a, const CVector& b, float scalar);

		// Dot product.
		vec_t	Dot(const CVector& vOther) const;

		// assignment
		CVector& operator=(const CVector& vOther);

		// 2d
		vec_t	Length2D(void) const {
			return sqrt(x * x + y * y);
		}
		vec_t	Length2DSqr(void) const;

		/// get the component of this CVector parallel to some other given CVector
		CVector  ProjectOnto(const CVector& onto);

		// copy constructors
		//	CVector(const CVector &vOther);

		// arithmetic operations
		CVector	operator-(void) const;

		CVector	operator+(const CVector& v) const;
		CVector	operator-(const CVector& v) const;
		CVector	operator*(const CVector& v) const;
		CVector	operator/(const CVector& v) const;
		CVector	operator*(float fl) const;
		CVector	operator/(float fl) const;

		// Cross product between two CVectors.
		CVector	Cross(const CVector& vOther) const;

		// Returns a CVector with the min or max in X, Y, and Z.
		CVector	Min(const CVector& vOther) const;
		CVector	Max(const CVector& vOther) const;
	};

	void CVectorCopy(const CVector& src, CVector& dst);
	float CVectorLength(const CVector& v);
	void CVectorLerp(const CVector& src1, const CVector& src2, vec_t t, CVector& dest);
	void CVectorCrossProduct(const CVector& a, const CVector& b, CVector& result);
	vec_t NormalizeCVector(CVector& v);


	class __declspec(align(16)) CVectorAligned : public CVector {
	public:
		inline CVectorAligned(void) {};
		inline CVectorAligned(vec_t X, vec_t Y, vec_t Z) {
			Init(X, Y, Z);
		}

	public:
		explicit CVectorAligned(const CVector& vOther) {
			Init(vOther.x, vOther.y, vOther.z);
		}

		CVectorAligned& operator=(const CVector& vOther) {
			Init(vOther.x, vOther.y, vOther.z);
			return *this;
		}

		//CVectorAligned& operator=(const CVectorAligned& vOther) {
		//	_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
		//	return *this;
		//}

		float w;
	};
	FORCEINLINE void VectorSubtract(const CVector& a, const CVector& b, CVector& c)
	{
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}
	FORCEINLINE void VectorAdd(const CVector& a, const CVector& b, CVector& c)
	{
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}

	struct cplane_t
	{
		Math::CVector normal;
		float dist;
		unsigned char type;			// for fast side tests
		unsigned char signbits;		// signx + (signy<<1) + (signz<<1)
		unsigned char pad[2];

		cplane_t() {}

	private:
		// No copy constructors allowed if we're in optimal mode
		cplane_t(const cplane_t& vOther);
	};

	class vec3_t {
	public:
		vec3_t();
		vec3_t(float, float, float);
		~vec3_t();

		float x, y, z;

		vec3_t& operator+=(const vec3_t& v) {
			x += v.x; y += v.y; z += v.z; return *this;
		}
		vec3_t& operator-=(const vec3_t& v) {
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}
		vec3_t& operator*=(float v) {
			x *= v; y *= v; z *= v; return *this;
		}
		vec3_t operator+(const vec3_t& v) {
			return vec3_t{ x + v.x, y + v.y, z + v.z };
		}
		vec3_t operator-(const vec3_t& v) {
			return vec3_t{ x - v.x, y - v.y, z - v.z };
		}
		vec3_t operator*(float fl) const {
			return vec3_t(x * fl, y * fl, z * fl);
		}
		vec3_t operator*(const vec3_t& v) const {
			return vec3_t(x * v.x, y * v.y, z * v.z);
		}
		vec3_t& operator/=(float fl) {
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}
		auto operator-(const vec3_t& other) const -> vec3_t {
			auto buf = *this;

			buf.x -= other.x;
			buf.y -= other.y;
			buf.z -= other.z;

			return buf;
		}

		auto operator/(float other) const {
			vec3_t vec;
			vec.x = x / other;
			vec.y = y / other;
			vec.z = z / other;
			return vec;
		}

		float& operator[](int i) {
			return ((float*)this)[i];
		}
		float operator[](int i) const {
			return ((float*)this)[i];
		}

		inline float Length2D() const {
			return sqrt((x * x) + (y * y));
		}
		void crossproduct(vec3_t v1, vec3_t v2, vec3_t cross_p) const {
			cross_p.x = (v1.y * v2.z) - (v1.z * v2.y); //i
			cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x)); //j
			cross_p.z = (v1.x * v2.y) - (v1.y * v2.x); //k
		}

		vec3_t cross(const vec3_t& vOther) const {
			vec3_t res;
			crossproduct(*this, vOther, res);
			return res;
		}

		void init(float ix, float iy, float iz);
		void clamp();
		vec3_t clamped();
		vec3_t normalized();
		float distance_to(const vec3_t& other);
		void normalize();
		float length();
		float length_sqr();
		float length_2d_sqr(void) const;
		float dot(const vec3_t other);
		float dot(const float* other);
	};

	inline vec3_t operator*(float lhs, const vec3_t& rhs) {
		return vec3_t(rhs.x * lhs, rhs.x * lhs, rhs.x * lhs);
	}
}