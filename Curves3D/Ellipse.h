#pragma once

#include "Curves3D.h"

namespace Curves
{
    class CURVES3D_API Ellipse : public Curves3D
    {
        double m_fRadius1 = 0;
        double m_fRadius2 = 0;

    public:
        Ellipse(double r1_, double r2_);

    public:
        Point3D getPoint(double parametr_) override;
        Point3D getDerivative(double parametr_) override;
    };
}
