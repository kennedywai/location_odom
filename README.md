# location_odom
ROS Closest Landmark

Find the closest landmark in turtlebot world by subscribing the ROS Navigation Odometry message

cd ~/catkin_ws/src

sudo git clone https://github.com/kennedywai/location_odom.git

cd ..
    
catkin_make

cd 

roslaunch turtlebot_gazebo turtlebot_world.launch

roslaunch turtlebot_teleop keyboard_teleop.launch 

rosrun location_odom odom_sub_node

*****Map Building*****

roslaunch turtlebot_navigation gmapping_demo.launch

roslaunch turtlebot_rviz_launchers view_navigation.launch

rosrun map_server map_saver -f /tmp/my_map

*****Navigation*****

roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/tmp/my_map.yaml

roslaunch turtlebot_rviz_launchers view_navigation.launch --screen

