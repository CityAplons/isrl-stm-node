#include "ros/ros.h"
#include "ultrabot_stm/uvc.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_uvc_control_client");
  if (argc != 2)
  {
    ROS_INFO("Usage: toggle_by_id NUM[1..4]");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ultrabot_stm::uvc>("toggle_by_id");
  ultrabot_stm::uvc srv;
  switch (atoll(argv[1]))
  {
  case 1:
      srv.request.left1 = !srv.response.status[0];
      break;
  case 2:
      srv.request.left2 = !srv.response.status[1];
      break;
  case 3:
      srv.request.right1 = !srv.response.status[2];
      break;
  case 4:
      srv.request.right2 = !srv.response.status[3];
      break;  
  case 5:
      srv.request.fans = !srv.response.status[4];
      break;    
  default:
      break;
  }
  if (client.call(srv))
  {
    ROS_INFO("Service called successfully");
  }
  else
  {
    ROS_ERROR("Failed to call service uvc control");
    return 1;
  }

  return 0;
}
