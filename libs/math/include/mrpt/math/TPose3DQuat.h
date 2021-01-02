/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2021, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */
#pragma once

#include <mrpt/math/TPoseOrPoint.h>

namespace mrpt::math
{
/** Lightweight 3D pose (three spatial coordinates, plus a quaternion ). Allows
 * coordinate access using [] operator.
 * \sa mrpt::poses::CPose3DQuat
 */
struct TPose3DQuat : public TPoseOrPoint,
					 public internal::ProvideStaticResize<TPose3DQuat>
{
	enum
	{
		static_size = 7
	};
	/** Translation in x,y,z */
	double x{.0}, y{.0}, z{.0};
	/** Unit quaternion part, qr,qx,qy,qz */
	double qr{1.}, qx{.0}, qy{.0}, qz{.0};

	/** Constructor from coordinates. */
	constexpr TPose3DQuat(
		double _x, double _y, double _z, double _qr, double _qx, double _qy,
		double _qz)
		: x(_x), y(_y), z(_z), qr(_qr), qx(_qx), qy(_qy), qz(_qz)
	{
	}
	/** Default fast constructor. Initializes to identity transformation. */
	TPose3DQuat() = default;
	/** Coordinate access using operator[]. Order: x,y,z,qr,qx,qy,qz */
	double& operator[](size_t i)
	{
		switch (i)
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return qr;
			case 4:
				return qx;
			case 5:
				return qy;
			case 6:
				return qz;
			default:
				throw std::out_of_range("index out of range");
		}
	}
	/** Coordinate access using operator[]. Order: x,y,z,qr,qx,qy,qz */
	constexpr double operator[](size_t i) const
	{
		switch (i)
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return qr;
			case 4:
				return qx;
			case 5:
				return qy;
			case 6:
				return qz;
			default:
				throw std::out_of_range("index out of range");
		}
	}
	/** Pose's spatial coordinates (x,y,z) norm. */
	double norm() const;
	/** Gets the pose as a vector of doubles. */
	void asVector(std::vector<double>& v) const
	{
		v.resize(7);
		for (size_t i = 0; i < 7; i++) v[i] = (*this)[i];
	}
	/** Returns a human-readable textual representation of the object as "[x y z
	 * qr qx qy qz]"
	 * \sa fromString
	 */
	void asString(std::string& s) const
	{
		s = mrpt::format("[%f %f %f %f %f %f %f]", x, y, z, qr, qx, qy, qz);
	}
	std::string asString() const
	{
		std::string s;
		asString(s);
		return s;
	}

	/** Set the current object value from a string generated by 'asString' (eg:
	 * "[0.02 1.04 -0.8 1.0 0.0 0.0 0.0]" )
	 * \sa asString
	 * \exception std::exception On invalid format
	 */
	void fromString(const std::string& s);

	static TPose3DQuat FromString(const std::string& s)
	{
		TPose3DQuat o;
		o.fromString(s);
		return o;
	}
};

}  // namespace mrpt::math

namespace mrpt::typemeta
{
// Specialization must occur in the same namespace
MRPT_DECLARE_TTYPENAME_NO_NAMESPACE(TPose3DQuat, mrpt::math)
}  // namespace mrpt::typemeta
