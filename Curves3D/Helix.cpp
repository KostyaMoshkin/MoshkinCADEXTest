#include "pch.h"
#include "Helix.h"

#define PI 3.1415926

namespace Curves
{
	Helix::Helix(double r_, double s_)
		: m_fRadius(r_), m_fStep(s_)
	{
	}

	const Point3D Helix::getPoint(double parametr_) const
	{
		return Point3D(cos(parametr_) * m_fRadius, sin(parametr_) * m_fRadius, m_fStep * parametr_ / (2 * PI));
	}

	const Point3D Helix::getDerivative(double parametr_) const
	{
		return Point3D(-1.0 * sin(parametr_) * m_fRadius, cos(parametr_) * m_fRadius, m_fStep / (2 * PI));
	}
}