cmake_minimum_required(VERSION 2.8.3)
project(msgs_and_action)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  actionlib_msgs
  std_msgs
  geometry_msgs
  sensor_msgs
  message_generation
  actionlib
)

add_message_files(
  DIRECTORY msg
)

add_action_files(
  DIRECTORY action
  FILES observer.action
)

generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS 
  actionlib_msgs
  message_runtime
)

