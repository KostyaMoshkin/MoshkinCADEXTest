#pragma once

#include "Curves3D.h"

namespace Curves
{
    class CURVES3D_API Circle : public Curves3D
    {
        double m_fRadius = 0;

    public:
        Circle(double r_);

    public:
        Point3D getPoint(double parametr_) override;
        Point3D getDerivative(double parametr_) override;

    public:
        double getRadius() { return m_fRadius; }
    };
}

