#include <ros/ros.h>
#include <ros/console.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <turtlesim/Pose.h>
#include <oxford_gps_eth/pos_info.h>
#include <oxford_gps_eth/pos_xy.h>
#include "showpath/geo.h"
#include <iostream>

#include <pcl_ros/point_cloud.h> //可直接将pcl::PointCloud<T>发布出去，不需要转化
//#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/radius_outlier_removal.h>   //半径滤波器头文件

#include <sensor_msgs/PointCloud2.h>

#include <Eigen/Dense>

//添加
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/common/transforms.h>
using namespace Eigen;
using namespace std;

Eigen::Matrix4f transform_cloud;

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    _init = false;
    path_pub = nh.advertise<nav_msgs::Path>("path", 1, true);

    path_sub = nh.subscribe("/gps/pos", 1000, &SubscribeAndPublish::callback, this);
    pub_cloud = nh.advertise<sensor_msgs::PointCloud2>("pub_cloud", 1); //话题名
	  sub_cloud = nh.subscribe<sensor_msgs::PointCloud2>("/map/map/velodyne_points", 1,&SubscribeAndPublish:: imcoming_cloud,this);                    
  }

  void callback(const oxford_gps_eth::pos_info &msg)
  {
    if (!_init)
    {
      origin_llt.lat = msg.latitude;
      origin_llt.lon = msg.longitude;
      origin_llt.alt = msg.altitude;
      _init = true;
      return;
    }
    pos_xyz Pos;
    cout << "get llt data" << endl;
    Pos = CTr::geodetic_to_enu(msg.latitude, msg.longitude, msg.altitude, origin_llt.lat, origin_llt.lon, origin_llt.alt);

    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.pose.position.x = Pos.x;
    this_pose_stamped.pose.position.y = Pos.y;
    this_pose_stamped.pose.position.y = Pos.y;

    geometry_msgs::Quaternion goal_quat= tf::createQuaternionMsgFromYaw(msg.heading);
    /*
    geometry_msgs::Quaternion goal_quat; //= tf::createQuaternionMsgFromYaw(msg.heading);
    this_pose_stamped.pose.orientation.x = msg.x;
    this_pose_stamped.pose.orientation.y = msg.y;
    this_pose_stamped.pose.orientation.z = msg.z;
    this_pose_stamped.pose.orientation.w = msg.w;
    */
    transform_cloud(0,3)=this_pose_stamped.pose.position.x;
    transform_cloud(1,3)=this_pose_stamped.pose.position.y;
    transform_cloud(2,3)=this_pose_stamped.pose.position.z;
    transform_cloud(3,3)=1.0;
    transform_cloud(3,0)=0;
    transform_cloud(3,1)=0;
    transform_cloud(3,2)=0;

    Quaterniond quat_tmp=Quaterniond( msg.x, msg.y, msg.z, msg.w);
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix=quat_tmp.toRotationMatrix();
    for(int i=0;i<3;++i)
    {
      for(int j=0;j<3;++j)
      transform_cloud(i,j)=float(rotation_matrix(i,j));
    }
    //transform_cloud.block(0,0,2,2)=rotation_matrix;



    current_time = ros::Time::now();
    this_pose_stamped.header.stamp = current_time;
    this_pose_stamped.header.frame_id = "odom";

    path.header.stamp = current_time;
    path.header.frame_id = "odom";
    path.poses.push_back(this_pose_stamped);

    path_pub.publish(path);
  }

  void imcoming_cloud(const sensor_msgs::PointCloud2ConstPtr &msg)
  {
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_rear(new pcl::PointCloud<pcl::PointXYZI>);//得到的点云
    pcl::fromROSMsg(*msg, *cloud_rear); //sensor_msgs::PointCloud2格式转化成
    pcl::transformPointCloud(*cloud_rear, *cloud_rear, transform_cloud);
    sensor_msgs::PointCloud2 roimsg;
    pcl::toROSMsg(*cloud_rear, roimsg);
    roimsg.header.frame_id = "odom";
    pub_cloud.publish(roimsg);
  
  }

private:
  ros::NodeHandle nh;
  ros::Publisher path_pub;
  ros::Subscriber path_sub;
  ros::Publisher pub_cloud;
  ros::Subscriber sub_cloud;
  ros::Time current_time;
  nav_msgs::Path path;
  pos_llt origin_llt; //存储第一个经纬度
  bool _init;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "showpath");
  SubscribeAndPublish SAPObject;
  /*测试坐标转换代码
  pos_xyz tmp = CTr::geodetic_to_enu(51.5, 130.5, 30.4, 31, 121, 10);
  cout << "xyz " << tmp.x << " " << tmp.y << " " << tmp.z << endl;
  pos_llt pllt =CTr:: enu_to_geodetic(656669.5379845105, 2256542.7338064048, -449961.0296980934, 31, 121, 10);
  cout << "llt " << pllt.lat << " " << pllt.lon << " " << pllt.alt << endl;
  */
  ros::spin();
  return 0;
}
