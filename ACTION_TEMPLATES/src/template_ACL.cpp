#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <action_vision/msg_templateAction.h>

int main (int argc, char** argv) {
    ros::init(argc, argv, "test_actionserver");
    
    actionlib::SimpleActionClient<action_vision::msg_templateAction> ac("observerAction", true);
    
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();
    
    ROS_INFO("Action server started, sending goal.");
    
    action_vision::msg_templateGoal goal;
    goal.goal = "hello im the goal";
    ac.sendGoal(goal);
    
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
    
    if (finished_before_timeout) {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }else {
        ROS_INFO("Action did not finish before timeout (30sec) ");
    }
    
    return 0;
}
