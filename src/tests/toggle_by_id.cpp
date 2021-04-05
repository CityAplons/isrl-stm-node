#include "ros/ros.h"
#include "runbot_stm/relay.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "toggle_relay");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<runbot_stm::relay>("stm/relay");
  runbot_stm::relay::Request req;
  runbot_stm::relay::Response resp;

  bool statuses[7] = {false,false,false,false,false,false,false};
  int c=0;
  while(1){
    switch (c)
    {
    case 0:
        req.relay1 = !statuses[0];
        break;
    case 1:
        req.relay2 = !statuses[1];
        break;
    case 2:
        req.relay3 = !statuses[2];
        break;
    case 3:
        req.relay4 = !statuses[3];
        break;  
    case 4:
        req.relay5 = !statuses[4];
        break;    
    case 5:
        req.relay6 = !statuses[5];
        break;    
    case 6:
        req.relay7 = !statuses[6];
        break;    
    default:
        break;
    }
    c++;
    if(c>6) c = 0;
    ros::service::waitForService("stm/relay", 5);
    bool success = client.call(req,resp);
    if (success)
    {
      for (int i = 0; i<7; i++){
        statuses[i]= resp.status[i];
        if(resp.timeout[i] != 0) ROS_INFO("Timeout: [%d]", resp.timeout[i]);
      }
      
      ROS_INFO("Service called successfully");
    }
    else
    {
      ROS_ERROR("Failed to call service relay");
      return 1;
    }
    ros::Duration(3).sleep();
  }

  return 0;
}
