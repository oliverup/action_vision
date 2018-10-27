cmake_minimum_required(VERSION 2.8.3)
project(observer)
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
  msgs_and_action
)

#add_message_files(
#)

#add_action_files(
#)

#generate_messages(
#  DEPENDENCIES
#  actionlib_msgs
#  std_msgs
#)

catkin_package(
  CATKIN_DEPENDS 
  actionlib_msgs
  msgs_and_action
  message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(observer_ASRV
  src/observer_ASRV.cpp
  include/observer_ASRV.h
)

add_dependencies(observer_ASRV ${catkin_EXPORTED_TARGETS})

target_link_libraries(observer_ASRV
  ${catkin_LIBRARIES}
)

