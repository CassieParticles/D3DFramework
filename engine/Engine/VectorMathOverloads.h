#pragma once
#include <DirectXMath.h>

inline DirectX::XMVECTOR operator+(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorAdd(a, b);
}

inline DirectX::XMVECTOR operator+=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a + b;
	return a;
}

inline DirectX::XMVECTOR operator-(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorSubtract(a, b);
}

inline DirectX::XMVECTOR operator-=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a - b;
	return a;
}

inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& a, const float& b)
{
	return DirectX::XMVectorScale(a, b);
}

inline DirectX::XMVECTOR operator*(const float& b, const DirectX::XMVECTOR& a)
{
	return DirectX::XMVectorScale(a, b);
}

inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorMultiply(a, b);
}

inline DirectX::XMVECTOR operator*=(DirectX::XMVECTOR& a, const float& b)
{
	a = a * b;
	return a;
}

inline DirectX::XMVECTOR operator*=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a * b;
	return a;
}

inline DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& a, const float& b)
{
	return DirectX::XMVectorScale(a, 1.f / b);
}

inline DirectX::XMVECTOR operator/(const float& b, const DirectX::XMVECTOR& a)
{
	return DirectX::XMVectorScale(a, 1.f / b);
}

inline DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorDivide(a, b);
}

inline DirectX::XMVECTOR operator/=(DirectX::XMVECTOR& a, const float& b)
{
	a = a / b;
	return a;
}

inline DirectX::XMVECTOR operator/=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a / b;
	return a;
}