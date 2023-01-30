#pragma once

#ifdef CURVES3D_EXPORTS
#define CURVES3D_API __declspec(dllexport)
#else
#define CURVES3D_API __declspec(dllimport)
#endif

#include <memory>

namespace Curves
{
	struct CURVES3D_API Point3D
	{
		double x;
		double y;
		double z;

		Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
	};

	class Curves3D;
	using Curves3DConstPtr = std::shared_ptr<const Curves3D>;

	class CURVES3D_API Curves3D {
	public:
		Curves3D(void) = default;
		virtual ~Curves3D(void) = default;

	public:
		virtual const Point3D getPoint(double parametr_) const = 0;
		virtual const Point3D getDerivative(double parametr_) const = 0;
	};
}