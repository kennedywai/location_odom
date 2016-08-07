#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "location_odom/LandmarkDistance.h"

#include <math.h>
#include <vector>
#include <string>

//using namespace std;
using std::vector;
using std::string;
using location_odom::LandmarkDistance;


class Landmark{
  public:
  Landmark(string name, double x, double y):name(name), x(x), y(y){
  }
  string name;
  double x;
  double y;
};

class LandmarkMonitor{
  public:
  LandmarkMonitor(): landmarks_(){
   InitLandmarks();
  }
  void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  double x = msg->pose.pose.position.x;
  double y = msg->pose.pose.position.y;
  LandmarkDistance ld = FindClosest(x, y);
  //ROS_INFO("x= %f, y=%f",x,y);
  ROS_INFO("name: %s, d: %f", ld.name.c_str(),ld.distance);
  }

  private:
  vector<Landmark> landmarks_;

  LandmarkDistance FindClosest(double x, double y){
  LandmarkDistance result;
  result.distance = -1;// distance can never be negative
  
  for(int i = 0; i< landmarks_.size(); i++){
  const Landmark& landmark = landmarks_[i];
  double x_distance = landmark.x - x;
  double y_distance = landmark.y - y;
  double distance = sqrt((x_distance*x_distance) + (y_distance*y_distance));
  	
  if (result.distance < 0 || distance < result.distance){
   result.name = landmark.name;
   result.distance = distance;
   }
  }
   return result;
  }

  void InitLandmarks(){
   landmarks_.push_back(Landmark("Cube", 0.31, -0.99));
   landmarks_.push_back(Landmark("Dumpster", 0.11, -2.42));
   landmarks_.push_back(Landmark("Cylinder", -1.14, -2.88));
   landmarks_.push_back(Landmark("Barrier", -2.59, -0.83));
   landmarks_.push_back(Landmark("Bookshelf", -0.09, 0.53));
  }	
};


/*
void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  double x = msg->pose.pose.position.x;
  double y = msg->pose.pose.position.y;
  //LandmarkDistance ld = FindClosest(x, y);
  ROS_INFO("x= %f, y=%f",x,y);
  //ROS_INFO("name: %s, d: %f", ld.name.c_str(),ld.distance);
  }
*/

int main(int argc,char** argv){
  ros::init(argc, argv, "location_odom");
  ros::NodeHandle nh;
  LandmarkMonitor landmark_monitor;
  ros::Subscriber sub = nh.subscribe("odom", 10, &LandmarkMonitor::OdomCallback, &landmark_monitor);
  //ros::Subscriber sub = nh.subscribe("odom", 10, OdomCallback);
  ros::spin();
  return 0;
}
