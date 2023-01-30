#pragma once

#include "Curves3D.h"

namespace Curves

{
    class Helix;
    using HelixConstPtr = const std::shared_ptr<const Helix>;

    class CURVES3D_API Helix : public Curves3D
    {
        double m_fRadius = 0;
        double m_fStep = 0;

    public:
        Helix(double r_, double s_);

        static HelixConstPtr Create(double r1_, double s_) { return std::make_shared<const Helix>(r1_, s_); }

    public:
        const Point3D getPoint(double parametr_) const override;
        const Point3D getDerivative(double parametr_) const override;
    };
}
