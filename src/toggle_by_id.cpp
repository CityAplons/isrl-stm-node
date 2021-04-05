#include "ros/ros.h"
#include "ultrabot_stm/uvc.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "toggle_relay");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ultrabot_stm::uvc>("stm/uvc");
  ultrabot_stm::uvc::Request req;
  ultrabot_stm::uvc::Response resp;

  bool statuses[5] = {false,false,false,false,false};
  int c=0;
  while(1){
    switch (c)
    {
    case 0:
        req.left1 = !statuses[0];
        break;
    case 1:
        req.left2 = !statuses[1];
        break;
    case 2:
        req.right1 = !statuses[2];
        break;
    case 3:
        req.right2 = !statuses[3];
        break;  
    case 4:
        req.fans = !statuses[4];
        break;    
    default:
        break;
    }
    c++;
    if(c>4) c = 0;
    ros::service::waitForService("stm/uvc", 5);
    bool success = client.call(req,resp);
    if (success)
    {
      for (int i = 0; i<5; i++){
        statuses[i]= resp.status[i];
        if(resp.timeout[i] != 0) ROS_INFO("Timeout: [%d]", resp.timeout[i]);
      }
      
      ROS_INFO("Service called successfully");
    }
    else
    {
      ROS_ERROR("Failed to call service uvc");
      return 1;
    }
    ros::Duration(3).sleep();
  }

  return 0;
}
