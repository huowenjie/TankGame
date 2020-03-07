#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

namespace hwj 
{
	// 2 维向量
	template <typename T>
	class Vector2D
	{
	public:
		Vector2D() {
			mX = T();
			mY = T();
		}

		Vector2D(T x, T y) : mX(x), mY(y) {}

		Vector2D operator+(const Vector2D &vect) {
			return Vector2D(mX + vect.mX, mY + vect.mY);
		}

		friend Vector2D operator+(const Vector2D &a, const Vector2D &b) {
			return Vector2D(a.mX + b.mX, a.mY + b.mY);
		}

		Vector2D operator-(const Vector2D &vect) {
			return Vector2D(mX - vect.mX, mY - vect.mY);
		}

		friend Vector2D operator-(const Vector2D &a, const Vector2D &b) {
			return Vector2D(a.mX - b.mX, a.mY - b.mY);
		}

		Vector2D & operator+=(const Vector2D &vect) {
			mX += vect.mX;
			mY += vect.mY;
			return *this;
		}

		Vector2D & operator-=(const Vector2D &vect) {
			mX -= vect.mX;
			mY -= vect.mY;
			return *this;
		}

	public:
		T mX;
		T mY;
	};

	// 3 维向量
	template <typename T>
	class Vector3D
	{
	public:
		Vector3D() {
			mX = T();
			mY = T();
			mZ = T();
		}

		Vector3D(T x, T y, T z) : 
			mX(x), mY(y), mZ(z) {}

		Vector3D operator+(const Vector3D &vect) {
			return Vector3D(
				mX + vect.mX, 
				mY + vect.mY, 
				mZ + vect.mZ);
		}

		friend Vector3D operator+(const Vector3D &a, const Vector3D &b) {
			return Vector3D(
				a.mX + b.mX, 
				a.mY + b.mY, 
				a.mZ + b.mZ);
		}

		Vector3D operator-(const Vector3D &vect) {
			return Vector3D(
				mX - vect.mX, 
				mY - vect.mY, 
				mZ - vect.mZ);
		}

		friend Vector3D operator-(const Vector3D &a, const Vector3D &b) {
			return Vector3D(
				a.mX - b.mX, 
				a.mY - b.mY, 
				a.mZ - b.mZ);
		}

		Vector3D & operator+=(const Vector3D &vect) {
			mX += vect.mX;
			mY += vect.mY;
			mZ += vect.mZ;
			return *this;
		}

		Vector3D & operator-=(const Vector3D &vect) {
			mX -= vect.mX;
			mY -= vect.mY;
			mZ -= vect.mZ;
			return *this;
		}

	public:
		T mX;
		T mY;
		T mZ;
	};

	// 4 维度向量
	template <typename T>
	class Vector4D 
	{
	public:
		Vector4D() {
			mA = T();
			mB = T();
			mC = T();
			mD = T();
		}

		Vector4D(const Vector2D<T> &a, const Vector2D<T> &b) :
			mA(a.mX), mB(a.mY), mC(b.mX), mD(b.mY) {}

		Vector4D(T x, T y, T z, T w) :
			mA(x), mB(y), mC(z), mD(w) {}

		Vector4D operator+(const Vector4D &vect) {
			return Vector4D(
				mA + vect.mA, 
				mB + vect.mB, 
				mC + vect.mC, 
				mD + vect.mD);
		}

		friend Vector4D operator+(const Vector4D &a, const Vector4D &b) {
			return Vector4D(
				a.mA + b.mA,
				a.mB + b.mB,
				a.mC + b.mC,
				a.mD + b.mD);
		}

		Vector4D operator-(const Vector4D &vect) {
			return Vector4D(
				mA - vect.mA, 
				mB - vect.mB, 
				mC - vect.mC, 
				mD - vect.mD);
		}

		friend Vector4D operator-(const Vector4D &a, const Vector4D &b) {
			return Vector4D(
				a.mA - b.mA,
				a.mB - b.mB,
				a.mC - b.mC,
				a.mD - b.mD);
		}

		Vector4D & operator+=(const Vector4D &vect) {
			mA += vect.mA;
			mB += vect.mB;
			mC += vect.mC;
			mD += vect.mD;
			return *this;
		}

		Vector4D & operator-=(const Vector4D &vect) {
			mA -= vect.mA;
			mB -= vect.mB;
			mC -= vect.mC;
			mD -= vect.mD;
			return *this;
		}

	public:
		T mA;
		T mB;
		T mC;
		T mD;
	};
}

#endif // __GAME_MATH_H__
