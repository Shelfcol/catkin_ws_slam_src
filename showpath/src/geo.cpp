#include "showpath/geo.h"

/// @brief 地球经纬度坐标系，站心坐标系（东北天enu），ECEF坐标系转换
///
///
/// @author 古雪峰
/// @date 2020/7/30
/// @version 1.1

namespace CTr
{

	double a = 6378137.0;
	double b = 6356752.3142;
	double f = (a - b) / a;
	double e_sq = f * (2 - f);
	double pi = 3.14159265359;

	double deg2rad(double deg) { return deg / 180.0 * 3.1415926; };
	double rad2deg(double rad) { return rad * 180.0 / 3.1415926; };

	/// @brief WGS-84经纬度坐标系转换为ECEF坐标系
	pos_xyz geodetic_to_ecef(double lat, double lon, double h)
	{
		//(lat, lon) in degrees
		// h in meters
		double lamb = deg2rad(lat);
		double phi = deg2rad(lon);
		double s = sin(lamb);
		double N = a / sqrt(1 - e_sq * s * s);

		double sin_lambda = sin(lamb);
		double cos_lambda = cos(lamb);
		double sin_phi = sin(phi);
		double cos_phi = cos(phi);

		double x = (h + N) * cos_lambda * cos_phi;
		double y = (h + N) * cos_lambda * sin_phi;
		double z = (h + (1 - e_sq) * N) * sin_lambda;

		pos_xyz Pos = pos_xyz(x, y, z);
		return Pos;
	}

	/// @brief ECEF坐标系转换为站心坐标系（东北天enu）
	/// @param ECEF  ECEF坐标系下的坐标
	/// @param ENU_ref  enu坐标系的经纬度海拔原点
	/// @return enu坐标
	pos_xyz ecef_to_enu(double x, double y, double z, double lat0, double lon0, double h0)
	{
		double lamb = deg2rad(lat0);
		double phi = deg2rad(lon0);
		double s = sin(lamb);
		double N = a / sqrt(1 - e_sq * s * s);

		double sin_lambda = sin(lamb);
		double cos_lambda = cos(lamb);
		double sin_phi = sin(phi);
		double cos_phi = cos(phi);

		double x0 = (h0 + N) * cos_lambda * cos_phi;
		double y0 = (h0 + N) * cos_lambda * sin_phi;
		double z0 = (h0 + (1 - e_sq) * N) * sin_lambda;

		double xd = x - x0;
		double yd = y - y0;
		double zd = z - z0;

		double t = -cos_phi * xd - sin_phi * yd;

		double xEast = -sin_phi * xd + cos_phi * yd;
		double yNorth = t * sin_lambda + cos_lambda * zd;
		double zUp = cos_lambda * cos_phi * xd + cos_lambda * sin_phi * yd + sin_lambda * zd;

		pos_xyz Pos = pos_xyz(xEast, yNorth, zUp);
		return Pos;
	}

	/// @brief enu坐标转换为ecef
	/// @param 	ENU 站心坐标系坐标（东北天）
	/// @param  ENU_ref 站心坐标的参考经纬度
	/// @return ECEF坐标
	pos_xyz enu_to_ecef(double xEast, double yNorth, double zUp, double lat0, double lon0, double h0)
	{
		double lamb = deg2rad(lat0);
		double phi = deg2rad(lon0);
		double s = sin(lamb);
		double N = a / sqrt(1 - e_sq * s * s);

		double sin_lambda = sin(lamb);
		double cos_lambda = cos(lamb);
		double sin_phi = sin(phi);
		double cos_phi = cos(phi);

		double x0 = (h0 + N) * cos_lambda * cos_phi;
		double y0 = (h0 + N) * cos_lambda * sin_phi;
		double z0 = (h0 + (1 - e_sq) * N) * sin_lambda;

		double t = cos_lambda * zUp - sin_lambda * yNorth;

		double zd = sin_lambda * zUp + cos_lambda * yNorth;
		double xd = cos_phi * t - sin_phi * xEast;
		double yd = sin_phi * t + cos_phi * xEast;

		double x = xd + x0;
		double y = yd + y0;
		double z = zd + z0;

		pos_xyz Pos = pos_xyz(x, y, z);
		return Pos;
	}

	/// @brief ECEF坐标系转换为经纬度坐标
	pos_llt ecef_to_geodetic(double x, double y, double z)
	{
		// Convert from ECEF cartesian coordinates to
		// latitude, longitude and height.  WGS-84
		double x2 = x * x;
		double y2 = y * y;
		double z2 = z * z;

		double a = 6378137.0000; // earth radius in meters
		double b = 6356752.3142; // earth semiminor in meters
		double e = sqrt(1 - (b / a) * (b / a));
		double b2 = b * b;
		double e2 = e * e;
		double ep = e * (a / b);
		double r = sqrt(x2 + y2);
		double r2 = r * r;
		double E2 = a * a - b * b;
		double F = 54 * b2 * z2;
		double G = r2 + (1 - e2) * z2 - e2 * E2;
		double c = (e2 * e2 * F * r2) / (G * G * G);
		double s = pow( 1.0 + c + sqrt(c*c + 2*c) ,1.0/3.0) ;
		double P = F / (3 * pow((s + 1 / s + 1), 2) * G * G);
		double Q = sqrt(1 + 2 * e2 * e2 * P);
		double ro = -(P * e2 * r) / (1 + Q) + sqrt((a * a / 2) * (1 + 1 / Q) - (P * (1 - e2) * z2) / (Q * (1 + Q)) - P * r2 / 2);
		double tmp = (r - e2 * ro) * (r - e2 * ro);
		double U = sqrt(tmp + z2);
		double V = sqrt(tmp + (1 - e2) * z2);
		double zo = (b2 * z) / (a * V);

		double height = U * (1 - b2 / (a * V));

		double lat = atan((z + ep * ep * zo) / r);

		double temp = atan(y / x);
		double longi;
		if (x >= 0)
			longi = temp;
		else if ((x < 0) && (y >= 0))
			longi = pi + temp;
		else
			longi = temp - pi;

		double lat0 = lat / (pi / 180);
		double lon0 = longi / (pi / 180);
		double h0 = height;

		pos_llt Pos = pos_llt(lat0, lon0, h0);
		return Pos;
	}
	pos_xyz geodetic_to_enu(double lat, double lon, double h, double lat_ref, double lon_ref, double h_ref)
	{
		pos_xyz tmp = geodetic_to_ecef(lat, lon, h);

		return ecef_to_enu(tmp.x, tmp.y, tmp.z, lat_ref, lon_ref, h_ref);
	}

	pos_llt enu_to_geodetic(double xEast, double yNorth, double zUp, double lat_ref, double lon_ref, double h_ref)
	{
		pos_xyz tmp = enu_to_ecef(xEast, yNorth, zUp, lat_ref, lon_ref, h_ref);

		return ecef_to_geodetic(tmp.x, tmp.y, tmp.z);
	}

} // namespace CTr
