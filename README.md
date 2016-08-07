# location_odom
# RosClosestLandmark

Find the closest landmark in turtlebot world by subscribing the Odometry message

cd ~/catkin_ws/src

sudo git clone https://github.com/kennedywai/location_odom.git

cd ..
    
catkin_make

cd 

roslaunch turtlebot_gazebo turtlebot_world.launch

roslaunch turtlebot_teleop keyboard_teleop.launch 

rosrun location_odom odom_sub_node
