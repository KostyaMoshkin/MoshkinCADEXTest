#pragma once

#ifdef CURVES3D_EXPORTS
#define CURVES3D_API __declspec(dllexport)
#else
#define CURVES3D_API __declspec(dllimport)
#endif

namespace Curves
{
	struct CURVES3D_API Point3D
	{
		double x;
		double y;
		double z;

		Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
	};

	class CURVES3D_API Curves3D {
	public:
		Curves3D(void) = default;

	public:
		virtual Point3D getPoint(double parametr_) = 0;
		virtual Point3D getDerivative(double parametr_) = 0;
	};
}