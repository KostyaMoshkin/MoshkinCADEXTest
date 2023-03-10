#include "pch.h"
#include "Ellipse.h"

namespace Curves
{
	Ellipse::Ellipse(double r1_, double r2_)
		: m_fRadius1(r1_), m_fRadius2(r2_)
	{
	}

	const Point3D Ellipse::getPoint(double parametr_) const
	{
		return Point3D(cos(parametr_) * m_fRadius1, sin(parametr_) * m_fRadius2, 0);
	}

	const Point3D Ellipse::getDerivative(double parametr_) const
	{
		return Point3D(-1.0 * sin(parametr_) * m_fRadius1, cos(parametr_) * m_fRadius2, 0);
	}
}