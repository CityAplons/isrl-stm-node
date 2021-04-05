#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <geometry_msgs/TransformStamped.h>
#include "sensor_msgs/Imu.h"

void rotCallback(const sensor_msgs::ImuConstPtr &msg){
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "map";
  transformStamped.child_frame_id = "stm_imu";
  transformStamped.transform.translation.x = 1;
  transformStamped.transform.translation.y = 1;
  transformStamped.transform.translation.z = 0;
  tf2::Quaternion q;
  tf2::convert(msg->orientation,q);
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "stm_imu_tf2_broadcaster");
    
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("stm/imu", 10, &rotCallback);

  ros::spin();
  return 0;
};