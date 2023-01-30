#include "pch.h"
#include "Circle.h"

namespace Curves
{
    Circle::Circle(double r_)
        : m_fRadius(r_)
    {
    }

    const Point3D Circle::getPoint(double parametr_) const
    {
        return Point3D(cos(parametr_) * m_fRadius, sin(parametr_) * m_fRadius, 0);
    }

    const Point3D Circle::getDerivative(double parametr_) const
    {
        return Point3D(-1.0 * sin(parametr_) * m_fRadius, cos(parametr_) * m_fRadius, 0);
    }
}

