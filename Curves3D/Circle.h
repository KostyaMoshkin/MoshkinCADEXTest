#pragma once

#include "Curves3D.h"

namespace Curves
{
    class Circle;
    using CircleConstPtr = const std::shared_ptr<const Circle>;

    class CURVES3D_API Circle : public Curves3D
    {
        double m_fRadius = 0;

    public:
        Circle(double r_);
        virtual ~Circle();

    public:
        const Point3D getPoint(double parametr_) const override;
        const Point3D getDerivative(double parametr_) const override;
        
        static CircleConstPtr Create(double r_) { return std::make_shared<const Circle>(r_); }

    public:
        const double getRadius() const { return m_fRadius; }
    };
}

