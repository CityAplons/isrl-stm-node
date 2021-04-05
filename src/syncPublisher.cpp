#include "ros/ros.h"
#include "std_msgs/Empty.h"

/**
 * This node helps STM to determine if ROS currently connected to it.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "sync_stm_node");
  ros::NodeHandle n;
  ros::Publisher sync_pub = n.advertise<std_msgs::Empty>("stm/sync", 10);
  ros::Rate loop_rate(20);

  std_msgs::Empty msg;

  while (ros::ok())
  {
    sync_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}