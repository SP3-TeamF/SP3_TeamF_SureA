#include "Vector2.h"
#include <cmath>
#include "MyMath.h"

Vector2::Vector2(float a, float b) :
x(a),
y(b)
{
}

Vector2::Vector2(const Vector2 &rhs) :
x(rhs.x),
y(rhs.y)
{

}

void Vector2::Set(float a, float b)
{
	x = a;
	y = b;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator-(void) const
{
	return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->x * scalar, this->y * scalar);
}

float Vector2::Length(void) const
{
	return sqrt(x * x + y * y);
}

float Vector2::Dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::Normalized(void)
{
	float L = Length();
	if (L <= Math::EPSILON && -L <= Math::EPSILON)
		throw DivideByZero();

	return Vector2(x / L, y / L);
}

ostream& operator<<(ostream& os, const Vector2& vector2)
{
    os << "[ " << vector2.x << ", " << vector2.y << " ]";
    return os;
}
