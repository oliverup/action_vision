#ifndef OBSERVER_ASRV_H
#define OBSERVER_ASRV_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <msgs_and_action/observerAction.h>

class Observer {

protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<msgs_and_action::observerAction> as_;
    std::string action_name_;
    msgs_and_action::observerFeedback feedback_;
    msgs_and_action::observerResult result_;

public:
    // constructor
    Observer(std::string ASRV_name);
    
    //deconstructor
    ~Observer(void);
    
    //action callback
    void executeCB(const msgs_and_action::observerGoalConstPtr &goal_);

private:
    //class specific functions     
    
};

#endif //OBSERVER_ASRV_H
