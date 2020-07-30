#include "ros/ros.h"
#include <nav_msgs/OccupancyGrid.h>
#include <iostream>
#include <cmath>
#include <tf2_ros/transform_listener.h>
#include <string>
#include <vector>
#include <ctime>
//PCL
#include <chrono>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/conversions.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
//Opencv

#include <pcl_ros/point_cloud.h> //可直接将pcl::PointCloud<T>发布出去，不需要转化
//#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/radius_outlier_removal.h>   //半径滤波器头文件

#include <sensor_msgs/PointCloud2.h>

#include <Eigen/Dense>

//添加
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/common/transforms.h>
#include <boost/shared_ptr.hpp>
using namespace Eigen;
using namespace std;

ros::Publisher pub;
ros::Subscriber rear_cloud;

pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);//保存所有的点云
pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_rear(new pcl::PointCloud<pcl::PointXYZI>);//得到的点云
bool cloud_in;



void imcoming_cloud(const sensor_msgs::PointCloud2ConstPtr &msg);

int main(int argc, char **argv)
{
 ros::init(argc, argv, "save_pcd_file"); //节点名
    ros::NodeHandle nh;

	cloud_in=false;
   
	    pub = nh.advertise<sensor_msgs::PointCloud2>("add_point", 1); //话题名
    pub = nh.advertise<sensor_msgs::PointCloud2>("save_pcd_file", 1); //话题名
    //rear_cloud = nh.subscribe<sensor_msgs::PointCloud2>("/laser_cloud_surround", 1, imcoming_cloud);                      //!!!!!!!!斜杠不要忘记
	rear_cloud = nh.subscribe<sensor_msgs::PointCloud2>("/registered_cloud", 1, imcoming_cloud);                      //!!!!!!!!斜杠不要忘记
    while (ros::ok())
    {
        ros::spinOnce();
		if(cloud_in)
		{
			cloud_in=false;
            static int print_time = 0;
            cout << "add point " << ++print_time << endl;

         
            *cloud += *cloud_rear;
            if(print_time==300){
            sensor_msgs::PointCloud2 roimsg;
            pcl::toROSMsg(*cloud, roimsg);
            roimsg.header.frame_id = "map";
            pub.publish(roimsg);
			}
         }
            
       
           
    }
      
    cout<<"no lidar data in,save pcd file ......"<<endl;
    pcl::PointCloud<pcl::PointXYZI> cloud_pcd; // 创建点云（不是指针）
	cloud_pcd=*cloud;
	//保存到PCD文件
	pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_pcd); //将点云保存到PCD文件中
	std::cerr << "Saved " << cloud_pcd.points.size () << " data points to test_pcd.pcd." << std::endl;

         
    return 0;
}


void imcoming_cloud(const sensor_msgs::PointCloud2ConstPtr &msg)
{
    cloud_in = true;
	Eigen::Matrix4f transform_front_left = (Eigen::Matrix4f() << 0, 0,1, 0,
											1, 0, 0, 0,
											0, 1, 0, 0,
											0, 0, 0, 1)
											   .finished();
    pcl::fromROSMsg(*msg, *cloud_rear); //sensor_msgs::PointCloud2格式转化成
    pcl::transformPointCloud(*cloud_rear, *cloud_rear, transform_front_left);
    
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloud_rear, *cloud_rear, indices);
 
}
