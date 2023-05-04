#pragma once

template<typename T>
struct TVector2
{
	static_assert(std::is_floating_point_v<T>, "T must be floating point");

public:
	/** Vector's X component. */
	union
	{
		T x;
		T X;
	};

	/** Vector's Y component. */
	union
	{
		T y;
		T Y;
	};

	/** Global 2D zero vector constant (0,0) */
	static const TVector2 ZeroVector;

	/** Global 2D down vector constant (0,-1) */
	static const TVector2 Down;

	/** Global 2D up vector constant (0,1) */
	static const TVector2 Up;

	/**
	* Global 2D one vector (poorly named) constant (1,1).
	*
	* @note Incorrectly named "unit" vector though its magnitude/length/size is not one. Would fix, though likely used all over the world. Use `Unit45Deg` below for an actual unit vector.
	*/
	static const TVector2 UnitVector;

	/**
	* Global 2D unit vector constant along the 45 degree angle or symmetrical positive axes (sqrt(.5),sqrt(.5)) or (.707,.707). https://en.wikipedia.org/wiki/Unit_vector
	*
	* @note The `UnitVector` above is actually a value with axes of 1 rather than a magnitude of one.
	*/
	static const TVector2 Unit45Deg;

	static TVector2 Zero() { return TVector2<T>::ZeroVector; }
	static TVector2 One() { return TVector2<T>::UnitVector; }
	static TVector2 UnitX() { return TVector2(1, 0); }
	static TVector2 UnitY() { return TVector2(0, 1); }

public:

	/** Default constructor (no initialization). */
	TVector2() { }

	/**
	* Constructor using initial values for each component.
	*
	* @param InX X coordinate.
	* @param InY Y coordinate.
	*/
	TVector2(T InX, T InY);

	/**
	* Constructor initializing both components to a single T value.
	*
	* @param InF Value to set both components to.
	*/
	explicit TVector2(T InF);

public:

	/**
	* Gets the result of adding two vectors together.
	*
	* @param V The other vector to add to this.
	* @return The result of adding the vectors together.
	*/
	TVector2 operator+(const TVector2& V) const;

	/**
	* Gets the result of subtracting a vector from this one.
	*
	* @param V The other vector to subtract from this.
	* @return The result of the subtraction.
	*/
	TVector2 operator-(const TVector2& V) const;

	/**
	* Gets the result of scaling the vector (multiplying each component by a value).
	*
	* @param Scale How much to scale the vector by.
	* @return The result of scaling this vector.
	*/
	TVector2 operator*(T Scale) const;

	/**
	* Gets the result of dividing each component of the vector by a value.
	*
	* @param Scale How much to divide the vector by.
	* @return The result of division on this vector.
	*/
	TVector2 operator/(T Scale) const;

	/**
	* Gets the result of adding A to each component of the vector.
	*
	* @param A T to add to each component.
	* @return The result of adding A to each component.
	*/
	TVector2 operator+(T A) const;

	/**
	* Gets the result of subtracting A from each component of the vector.
	*
	* @param A T to subtract from each component
	* @return The result of subtracting A from each component.
	*/
	TVector2 operator-(T A) const;

	/**
	* Gets the result of component-wise multiplication of this vector by another.
	*
	* @param V The other vector to multiply this by.
	* @return The result of the multiplication.
	*/
	TVector2 operator*(const TVector2& V) const;

	/**
	* Gets the result of component-wise division of this vector by another.
	*
	* @param V The other vector to divide this by.
	* @return The result of the division.
	*/
	TVector2 operator/(const TVector2& V) const;

	/**
	* Calculates dot product of this vector and another.
	*
	* @param V The other vector.
	* @return The dot product.
	*/
	T operator|(const TVector2& V) const;

	/**
	* Calculates cross product of this vector and another.
	*
	* @param V The other vector.
	* @return The cross product.
	*/
	T operator^(const TVector2& V) const;

public:

	/**
	* Compares this vector against another for equality.
	*
	* @param V The vector to compare against.
	* @return true if the two vectors are equal, otherwise false.
	*/
	bool operator==(const TVector2& V) const;

	/**
	* Compares this vector against another for inequality.
	*
	* @param V The vector to compare against.
	* @return true if the two vectors are not equal, otherwise false.
	*/
	bool operator!=(const TVector2& V) const;

	/**
	* Checks whether both components of this vector are less than another.
	*
	* @param Other The vector to compare against.
	* @return true if this is the smaller vector, otherwise false.
	*/
	bool operator<(const TVector2& Other) const;

	/**
	* Checks whether both components of this vector are greater than another.
	*
	* @param Other The vector to compare against.
	* @return true if this is the larger vector, otherwise false.
	*/
	bool operator>(const TVector2& Other) const;

	/**
	* Checks whether both components of this vector are less than or equal to another.
	*
	* @param Other The vector to compare against.
	* @return true if this vector is less than or equal to the other vector, otherwise false.
	*/
	bool operator<=(const TVector2& Other) const;

	/**
	* Checks whether both components of this vector are greater than or equal to another.
	*
	* @param Other The vector to compare against.
	* @return true if this vector is greater than or equal to the other vector, otherwise false.
	*/
	bool operator>=(const TVector2& Other) const;

	/**
	* Gets a negated copy of the vector.
	*
	* @return A negated copy of the vector.
	*/
	TVector2 operator-() const;

	/**
	* Adds another vector to this.
	*
	* @param V The other vector to add.
	* @return Copy of the vector after addition.
	*/
	TVector2 operator+=(const TVector2& V);

	/**
	* Subtracts another vector from this.
	*
	* @param V The other vector to subtract.
	* @return Copy of the vector after subtraction.
	*/
	TVector2 operator-=(const TVector2& V);

	/**
	* Scales this vector.
	*
	* @param Scale The scale to multiply vector by.
	* @return Copy of the vector after scaling.
	*/
	TVector2 operator*=(T Scale);

	/**
	* Divides this vector.
	*
	* @param V What to divide vector by.
	* @return Copy of the vector after division.
	*/
	TVector2 operator/=(T V);

	/**
	* Multiplies this vector with another vector, using component-wise multiplication.
	*
	* @param V The vector to multiply with.
	* @return Copy of the vector after multiplication.
	*/
	TVector2 operator*=(const TVector2& V);

	/**
	* Divides this vector by another vector, using component-wise division.
	*
	* @param V The vector to divide by.
	* @return Copy of the vector after division.
	*/
	TVector2 operator/=(const TVector2& V);

public:

	/**
	* Calculates the dot product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The dot product.
	*/
	static T DotProduct(const TVector2& A, const TVector2& B);

	/**
	* Squared distance between two 2D points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The squared distance between two 2D points.
	*/
	static T DistSquared(const TVector2& V1, const TVector2& V2);

	/**
	* Distance between two 2D points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The distance between two 2D points.
	*/
	static T Distance(const TVector2& V1, const TVector2& V2);

	/**
	* Calculate the cross product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The cross product.
	*/
	static T CrossProduct(const TVector2& A, const TVector2& B);

	/**
	* Returns a vector with the maximum component for each dimension from the pair of vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The max vector.
	*/
	static TVector2 Max(const TVector2& A, const TVector2& B);

	/**
	* Returns a vector with the minimum component for each dimension from the pair of vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The min vector.
	*/
	static TVector2 Min(const TVector2& A, const TVector2& B);

	/**
	* Set the values of the vector directly.
	*
	* @param InX New X coordinate.
	* @param InY New Y coordinate.
	*/
	void Set(T InX, T InY);

	/**
	* Get the maximum value of the vector's components.
	*
	* @return The maximum value of the vector's components.
	*/
	T GetMax() const;

	/**
	* Get the maximum absolute value of the vector's components.
	*
	* @return The maximum absolute value of the vector's components.
	*/
	T GetAbsMax() const;

	/**
	* Get the minimum value of the vector's components.
	*
	* @return The minimum value of the vector's components.
	*/
	T GetMin() const;

	/**
	* Get the length (magnitude) of this vector.
	*
	* @return The length of this vector.
	* @see Length - This function is a synonym for Length()
	*/
	T Size() const;

	/**
	* Get the length (magnitude) of this vector.
	*
	* @return The length of this vector.
	* @see Size - This function is a synonym for Size()
	*/
	T Length() const { return Size(); }

	/**
	* Get the squared length of this vector.
	*
	* @return The squared length of this vector.
	* @see LengthSquared - This function is a synonym for LengthSquared()
	*/
	T SizeSquared() const;

	/**
	* Get the squared length of this vector.
	*
	* @return The squared length of this vector.
	* @see SizeSquared - This function is a synonym for SizeSquared()
	*/
	T SquaredLength() const { return SizeSquared(); }

	/**
	* Get the dot product of this vector against another.
	*
	* @param V2 The vector to measure dot product against.
	* @return The dot product.
	*/
	T Dot(const TVector2& V2) const;

	/*
	 * Return the Vector perpendicular to the current vector
	 *
	 */
	TVector2 Perpendicular() const;

	/**
	* Rotates around axis (0,0,1)
	*
	* @param AngleDeg Angle to rotate (in degrees)
	* @return Rotated Vector
	*/
	TVector2 GetRotated(T AngleDeg) const;

	/**
	* Normalize this vector in-place if it is large enough, set it to (0,0) otherwise.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	* @see GetSafeNormal()
	*/
	void Normalize(T Tolerance = 1.e-8f);

	TVector2<T> Normalized(T Tolerance = 1.e-8f);

	/**
	* Checks whether vector is near to zero within a specified tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if vector is in tolerance to zero, otherwise false.
	*/
	bool IsNearlyZero(T Tolerance = 1.e-8f) const;

	/**
	* Util to convert this vector into a unit direction vector and its original length.
	*
	* @param OutDir Reference passed in to store unit direction vector.
	* @param OutLength Reference passed in to store length of the vector.
	*/
	void ToDirectionAndLength(TVector2& OutDir, double& OutLength) const;
	void ToDirectionAndLength(TVector2& OutDir, float& OutLength) const;

	/**
	* Checks whether all components of the vector are exactly zero.
	*
	* @return true if vector is exactly zero, otherwise false.
	*/
	bool IsZero() const;


	/**
	* Creates a copy of this vector with both axes clamped to the given range.
	* @return New vector with clamped axes.
	*/
	TVector2 ClampAxes(T MinAxisVal, T MaxAxisVal) const;


	/**
	* Get a copy of this vector with absolute value of each component.
	*
	* @return A copy of this vector with absolute value of each component.
	*/
	TVector2 GetAbs() const;

};

/* TVector2 functions
*****************************************************************************/



template<typename T>
const TVector2<T> TVector2<T>::ZeroVector(0, 0);

template<typename T>
const TVector2<T> TVector2<T>::Down(0, -1);

template<typename T>
const TVector2<T> TVector2<T>::Up(0, 1);

template<typename T>
const TVector2<T> TVector2<T>::UnitVector(1, 1);

template<typename T>
TVector2<T>::TVector2(T InX, T InY)
	: X(InX), Y(InY)
{ }

template<typename T>
TVector2<T>::TVector2(T InF)
	: X(InF), Y(InF)
{ }


template<typename T>
TVector2<T> TVector2<T>::operator+(const TVector2& V) const
{
	return TVector2(X + V.X, Y + V.Y);
}

template<typename T>
TVector2<T> TVector2<T>::operator-(const TVector2& V) const
{
	return TVector2(X - V.X, Y - V.Y);
}

template<typename T>
TVector2<T> TVector2<T>::operator*(T Scale) const
{
	return TVector2(X * Scale, Y * Scale);
}

template<typename T>
TVector2<T> TVector2<T>::operator/(T Scale) const
{
	const T RScale = 1.f / Scale;
	return TVector2(X * RScale, Y * RScale);
}

template<typename T>
TVector2<T> TVector2<T>::operator+(T A) const
{
	return TVector2(X + A, Y + A);
}

template<typename T>
TVector2<T> TVector2<T>::operator-(T A) const
{
	return TVector2(X - A, Y - A);
}

template<typename T>
TVector2<T> TVector2<T>::operator*(const TVector2& V) const
{
	return TVector2(X * V.X, Y * V.Y);
}

template<typename T>
TVector2<T> TVector2<T>::operator/(const TVector2& V) const
{
	return TVector2(X / V.X, Y / V.Y);
}

template<typename T>
T TVector2<T>::operator|(const TVector2& V) const
{
	return X * V.X + Y * V.Y;
}

template<typename T>
T TVector2<T>::operator^(const TVector2& V) const
{
	return X * V.Y - Y * V.X;
}

template<typename T>
T TVector2<T>::DotProduct(const TVector2& A, const TVector2& B)
{
	return A | B;
}

template<typename T>
T TVector2<T>::DistSquared(const TVector2& V1, const TVector2& V2)
{
	return Square(V2.X - V1.X) + Square(V2.Y - V1.Y);
}

template<typename T>
T TVector2<T>::Distance(const TVector2& V1, const TVector2& V2)
{
	return sqrt(TVector2<T>::DistSquared(V1, V2));
}

template<typename T>
T TVector2<T>::CrossProduct(const TVector2& A, const TVector2& B)
{
	return A ^ B;
}

template<typename T>
TVector2<T> TVector2<T>::Max(const TVector2& A, const TVector2& B)
{
	return TVector2(max(A.X, B.X), max(A.Y, B.Y));
}

template<typename T>
TVector2<T> TVector2<T>::Min(const TVector2& A, const TVector2& B)
{
	return TVector2(min(A.X, B.X), min(A.Y, B.Y));
}

template<typename T>
bool TVector2<T>::operator==(const TVector2& V) const
{
	return X == V.X && Y == V.Y;
}

template<typename T>
bool TVector2<T>::operator!=(const TVector2& V) const
{
	return X != V.X || Y != V.Y;
}

template<typename T>
bool TVector2<T>::operator<(const TVector2& Other) const
{
	return X < Other.X&& Y < Other.Y;
}

template<typename T>
bool TVector2<T>::operator>(const TVector2& Other) const
{
	return X > Other.X && Y > Other.Y;
}

template<typename T>
bool TVector2<T>::operator<=(const TVector2& Other) const
{
	return X <= Other.X && Y <= Other.Y;
}

template<typename T>
bool TVector2<T>::operator>=(const TVector2& Other) const
{
	return X >= Other.X && Y >= Other.Y;
}

template<typename T>
TVector2<T> TVector2<T>::operator-() const
{
	return TVector2(-X, -Y);
}

template<typename T>
TVector2<T> TVector2<T>::operator+=(const TVector2& V)
{
	X += V.X; Y += V.Y;
	return *this;
}

template<typename T>
TVector2<T> TVector2<T>::operator-=(const TVector2& V)
{
	X -= V.X; Y -= V.Y;
	return *this;
}

template<typename T>
TVector2<T> TVector2<T>::operator*=(T Scale)
{
	X *= Scale; Y *= Scale;
	return *this;
}

template<typename T>
TVector2<T> TVector2<T>::operator/=(T V)
{
	const T RV = 1.f / V;
	X *= RV; Y *= RV;
	return *this;
}

template<typename T>
TVector2<T> TVector2<T>::operator*=(const TVector2& V)
{
	X *= V.X; Y *= V.Y;
	return *this;
}

template<typename T>
TVector2<T> TVector2<T>::operator/=(const TVector2& V)
{
	X /= V.X; Y /= V.Y;
	return *this;
}

template<typename T>
void TVector2<T>::Set(T InX, T InY)
{
	X = InX;
	Y = InY;
}

template<typename T>
T TVector2<T>::GetMax() const
{
	return max(X, Y);
}

template<typename T>
T TVector2<T>::GetAbsMax() const
{
	return max(abs(X), abs(Y));
}

template<typename T>
T TVector2<T>::GetMin() const
{
	return min(X, Y);
}

template<typename T>
T TVector2<T>::Size() const
{
	return sqrt(X * X + Y * Y);
}

template<typename T>
T TVector2<T>::SizeSquared() const
{
	return X * X + Y * Y;
}

template<typename T>
T TVector2<T>::Dot(const TVector2& V2) const
{
	return X * V2.X + Y * V2.Y;
}

template<typename T>
TVector2<T> TVector2<T>::Perpendicular() const
{
	return { -Y, X };
}

template<typename T>
TVector2<T> TVector2<T>::GetRotated(const T AngleDeg) const
{
	// Based on FVector::RotateAngleAxis with Axis(0,0,1)
	T S, C;
	SinCos(&S, &C, DegreesToRadians(AngleDeg));

	const T OMC = 1.0f - C;

	return TVector2(
		C * X - S * Y,
		S * X + C * Y);
}


template<typename T>
void TVector2<T>::Normalize(T Tolerance)
{
	const T SquareSum = X * X + Y * Y;
	if (SquareSum > Tolerance)
	{
		const T Scale = InvSqrt<T>(SquareSum);
		X *= Scale;
		Y *= Scale;
		return;
	}
	X = 0.0f;
	Y = 0.0f;
}

template<typename T>
TVector2<T> TVector2<T>::Normalized(T Tolerance)
{
	const T SquareSum = X * X + Y * Y;
	if (SquareSum > Tolerance)
	{
		const T Scale = InvSqrt<T>(SquareSum);
		return { X * Scale, Y * Scale };
	}
	return { 0.0, 0.0 };
}

template<typename T>
void TVector2<T>::ToDirectionAndLength(TVector2& OutDir, double& OutLength) const
{
	OutLength = Size();
	if (OutLength > 1.e-8f)
	{
		T OneOverLength = 1.0f / OutLength;
		OutDir = TVector2(X * OneOverLength, Y * OneOverLength);
	}
	else
	{
		OutDir = TVector2<T>::ZeroVector;
	}
}

template<typename T>
void TVector2<T>::ToDirectionAndLength(TVector2& OutDir, float& OutLength) const
{
	OutLength = Size();
	if (OutLength > 1.e-8f)
	{
		float OneOverLength = 1.0f / OutLength;
		OutDir = TVector2(X * OneOverLength, Y * OneOverLength);
	}
	else
	{
		OutDir = TVector2<T>::ZeroVector;
	}
}

template<typename T>
bool TVector2<T>::IsNearlyZero(T Tolerance) const
{
	return	abs(X) <= Tolerance
		&& abs(Y) <= Tolerance;
}

template<typename T>
bool TVector2<T>::IsZero() const
{
	return X == 0.f && Y == 0.f;
}


template<typename T>
TVector2<T> TVector2<T>::ClampAxes(T MinAxisVal, T MaxAxisVal) const
{
	return TVector2(Clamp(X, MinAxisVal, MaxAxisVal), Clamp(Y, MinAxisVal, MaxAxisVal));
}


template<typename T>
TVector2<T> TVector2<T>::GetAbs() const
{
	return TVector2(abs(X), abs(Y));
}

using FVector2 = TVector2<float>;