#pragma once

#include "Curves3D.h"

namespace Curves
{
    class Ellipse;
    using EllipseConstPtr = const std::shared_ptr<const Ellipse>;

    class CURVES3D_API Ellipse : public Curves3D
    {
        double m_fRadius1 = 0;
        double m_fRadius2 = 0;

    public:
        Ellipse(double r1_, double r2_);

        static EllipseConstPtr Create(double r1_, double r2_) { return std::make_shared<const Ellipse>(r1_, r2_); }

    public:
        const  Point3D getPoint(double parametr_) const override;
        const Point3D getDerivative(double parametr_) const override;
    };
}
