#ifndef TEMPLATE_ASRV_H
#define TEMPLATE_ASRV_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <action_vision/msg_templateAction.h>

class template_class {

protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<action_vision::msg_templateAction> as_;
    std::string action_name_;
    action_vision::msg_templateFeedback feedback_;
    action_vision::msg_templateResult result_;

public:
    // constructor
    template_class(std::string ASRV_name);
    
    //deconstructor
    ~template_class(void);
    
    //action callback
    void executeCB(const action_vision::msg_templateGoalConstPtr &goal);

private:
    //class specific functions     
    
};

#endif //TEMPLATE_ASRV_H
