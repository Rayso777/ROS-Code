#include <ros/ros.h>
// PCL specific includes 。PCL 的相关的头文件
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//滤波的头文件
#include <pcl/filters/voxel_grid.h>
//申明发布器
ros::Publisher pub;
//回调函数
void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
 // 声明存储原始数据与滤波后的数据的点云的格式  
// Container for original & filtered data
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; //原始的点云的数据格式
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;//存储滤波后的数据格式
 
  // Convert to PCL data type。转化为PCL中的点云的数据格式
  pcl_conversions::toPCL(*cloud_msg, *cloud);
 
  // Perform the actual filtering进行一个滤波处理
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor; //创建滤波对象
  sor.setInputCloud (cloudPtr);  //设置输入的滤波，将需要过滤的点云给滤波对象
  sor.setLeafSize (0.1, 0.1, 0.1);  //设置滤波时创建的体素大小为1cm立方体
  sor.filter (cloud_filtered);//执行滤波处理，存储输出cloud_filtered
 
  // Convert to ROS data type。// 再将滤波后的点云的数据格式转换为ROS下的数据格式发布出去
  sensor_msgs::PointCloud2 output;//声明的输出的点云的格式
  pcl_conversions::moveFromPCL(cloud_filtered, output);//第一个参数是输入，后面的是输出
 
  // Publish the data
  pub.publish (output);
}
 
int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");//声明节点的名称
  ros::NodeHandle nh;
 
  // Create a ROS subscriber for the input point cloud
// 为接受点云数据创建一个订阅节点
  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("input", 1, cloud_cb);
 
  // Create a ROS publisher for the output point cloud
//创建ROS的发布节点
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);
 
  // Spin
// 回调
  ros::spin ();
}
