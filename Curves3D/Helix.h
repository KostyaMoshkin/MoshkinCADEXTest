#pragma once

#include "Curves3D.h"

namespace Curves
{
    class CURVES3D_API Helix : public Curves3D
    {
        double m_fRadius = 0;
        double m_fStep = 0;

    public:
        Helix(double r_, double s_);

    public:
        Point3D getPoint(double parametr_) override;
        Point3D getDerivative(double parametr_) override;
    };
}
