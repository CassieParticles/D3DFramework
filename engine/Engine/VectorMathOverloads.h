#pragma once
#include <DirectXMath.h>

DirectX::XMVECTOR operator+(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorAdd(a, b);
}

DirectX::XMVECTOR operator+=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a + b;
	return a;
}

DirectX::XMVECTOR operator-(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorSubtract(a, b);
}

DirectX::XMVECTOR operator-=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a - b;
	return a;
}

DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& a, const float& b)
{
	return DirectX::XMVectorScale(a, b);
}

DirectX::XMVECTOR operator*( const float& b,const DirectX::XMVECTOR& a)
{
	return DirectX::XMVectorScale(a, b);
}

DirectX::XMVECTOR operator*(DirectX::XMVECTOR& a, const float& b)
{
	a = DirectX::XMVectorScale(a, b);
	return a;
}

DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorMultiply(a, b);
}

DirectX::XMVECTOR operator*=(DirectX::XMVECTOR& a, const float& b)
{
	a = a * b;
	return a;
}

DirectX::XMVECTOR operator*=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a * b;
	return a;
}

DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& a, const float& b)
{
	return DirectX::XMVectorScale(a, 1.f / b);
}

DirectX::XMVECTOR operator/(const float& b, const DirectX::XMVECTOR& a)
{
	return DirectX::XMVectorScale(a, 1.f / b);
}

DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	return DirectX::XMVectorDivide(a, b);
}

DirectX::XMVECTOR operator/=(DirectX::XMVECTOR& a, const float& b)
{
	a = a / b;
	return a;
}

DirectX::XMVECTOR operator/=(DirectX::XMVECTOR& a, const DirectX::XMVECTOR& b)
{
	a = a / b;
	return a;
}