cmake_minimum_required(VERSION 2.8.3)
project(action_vision)
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
)

add_action_files(
  DIRECTORY action
  FILES msg_template.action
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

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(template_ASRV
  src/templates/template_ASRV.cpp
  include/templates/template_ASRV.h
)

target_link_libraries(template_ASRV
  ${catkin_LIBRARIES}
)

add_executable(template_ACL
  src/templates/template_ACL.cpp
)

target_link_libraries(template_ACL
  ${catkin_LIBRARIES}
)

