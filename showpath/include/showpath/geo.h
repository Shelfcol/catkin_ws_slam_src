#ifndef ECEF_LLH_ENU_H
#define ECEF_LLH_ENU_H

#include <cmath>
#include<iostream>
using namespace std;
/// @brief 地球经纬度坐标系，站心坐标系（东北天enu），ECEF坐标系转换
///
///
/// @author 古雪峰
/// @date 2020/7/30
/// @version 1.1

struct pos_xyz
{
	pos_xyz(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	pos_xyz() : x(0.0), y(0.0), z(0.0) {}

	double x;
	double y;
	double z;
};

struct pos_llt
{
	pos_llt(double _lat, double _lon, double _alt) : lat(_lat), lon(_lon), alt(_alt) {}
	pos_llt() : lat(0.0), lon(0.0), alt(0.0) {}

	double lat;
	double lon;
	double alt;
};

namespace CTr
{

	extern double a;
	extern double b;
	extern double f;
	extern double e_sq;
	extern double pi;

	/// @brief WGS-84经纬度坐标系转换为ECEF坐标系
	pos_xyz geodetic_to_ecef(double lat, double lon, double h);

	/// @brief ECEF坐标系转换为站心坐标系（东北天enu）
	/// @param ECEF  ECEF坐标系下的坐标
	/// @param ENU_ref  enu坐标系的经纬度海拔原点
	/// @return enu坐标
	pos_xyz ecef_to_enu(double x, double y, double z, double lat0, double lon0, double h0);

	/// @brief enu坐标转换为ecef
	/// @param 	ENU 站心坐标系坐标（东北天）
	/// @param  ENU_ref 站心坐标的参考经纬度
	/// @return ECEF坐标
	pos_xyz enu_to_ecef(double xEast, double yNorth, double zUp, double lat0, double lon0, double h0);

	/// @brief ECEF坐标系转换为经纬度坐标
	pos_llt ecef_to_geodetic(double x, double y, double z);
	pos_xyz geodetic_to_enu(double lat, double lon, double h, double lat_ref, double lon_ref, double h_ref);
	pos_llt enu_to_geodetic(double xEast, double yNorth, double zUp, double lat_ref, double lon_ref, double h_ref);

} // namespace CTr
#endif
