#pragma once

#include "Curves3D.h"

namespace Curves
{
    class CURVES3D_API Circle : public Curves3D
    {
        double m_fRadius = 0;

    public:
        Circle(double r_);
        virtual ~Circle();

    public:
        const Point3D getPoint(double parametr_) const override;
        const Point3D getDerivative(double parametr_) const override;

    public:
        const double getRadius() const { return m_fRadius; }
    };
}

