#include <ros/ros.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/client/simple_action_client.h>

#include <msgs_and_action/observerAction.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "tester_client");

    actionlib::SimpleActionClient<msgs_and_action::observerAction> ac_("ObserverAction", true);

    ROS_INFO("Waiting for action server to start.");
    ac_.waitForServer();
    
    ROS_INFO("Action server started, sending goal.");
    
    msgs_and_action::observerGoal goal_;
    goal_.goal = "hello im the goal";
    ac_.sendGoal(goal_);
    
    bool finished_before_timeout = ac_.waitForResult(ros::Duration(30.0));
    
    if (finished_before_timeout) {
        actionlib::SimpleClientGoalState state = ac_.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }else {
        ROS_INFO("Action did not finish before timeout (30sec) ");
    }
    
    return 0;
}

