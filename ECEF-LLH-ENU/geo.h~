#ifndef ECEF_LLH_ENU_H
#define ECEF_LLH_ENU_H

#include <cmath>

/// @brief 地球经纬度坐标系，站心坐标系（东北天enu），ECEF坐标系转换
///
///
/// @author 古雪峰
/// @date 2020/7/30
/// @version 1.1

namespace CTr{

	extern double  a;
	extern double  b;
	extern double  f;
	extern double  e_sq;
	extern double  pi ;
	
	struct pos_xyz
	{
		double  x;
		double  y;
		double  z;
	
	};
	
	struct pos_llt
	{
		double  lat;
		double  lon;
		double  alt;
	};
	
	/// @brief WGS-84经纬度坐标系转换为ECEF坐标系
	pos_xyz  geodetic_to_ecef(lat, lon, h);
	
	/// @brief ECEF坐标系转换为站心坐标系（东北天enu）
	/// @param ECEF  ECEF坐标系下的坐标
	/// @param ENU_ref  enu坐标系的经纬度海拔原点
	/// @return enu坐标
	pos_xyz ecef_to_enu(x, y, z, lat0, lon0, h0):
	

	/// @brief enu坐标转换为ecef
	/// @param 	ENU 站心坐标系坐标（东北天）
	/// @param  ENU_ref 站心坐标的参考经纬度
	/// @return ECEF坐标
	pos_xyz pos_xyz enu_to_ecef(xEast, yNorth, zUp, lat0, lon0, h0);
	
	/// @brief ECEF坐标系转换为经纬度坐标
	pos_llt ecef_to_geodetic(x, y, z);
	pos_xyz geodetic_to_enu(lat, lon, h, lat_ref, lon_ref, h_ref);
	pos_lltenu_to_geodetic(xEast, yNorth, zUp, lat_ref, lon_ref, h_ref);
	
	double  deg2rad(double  deg){return deg/180.0*3.1415926;};
	double  rad2deg(double  rad){return rad*180.0/3.1415926;};
	
	

}//namespace



