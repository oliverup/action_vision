#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <action_vision/msg_templateAction.h>

class action_visionAction {

protected:

    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<action_vision::msg_templateAction> as_;
    std::string action_name_;
    action_vision::msg_templateFeedback feedback_;
    action_vision::msg_templateResult result_;
    
public:
    action_visionAction(std::string name):
        as_(nh_, name, boost::bind(&action_visionAction::executeCB, this, _1), false), action_name_(name) {
        as_.start();
        }
    ~action_visionAction(void) {
    }
    
    void executeCB(const action_vision::msg_templateGoalConstPtr &goal) {
        ros::Rate r(1); //?
        bool success = true;
        
        //do some stuff with the goal->goal you got by the client.
        ROS_INFO("%s, ayy shits working", goal->goal.c_str());
        
        feedback_.feedback.clear();
        feedback_.feedback.push_back(goal->goal);
        
        // constantly check if client cancelled the action
        if (as_.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s: Preempted", action_name_.c_str());
            // set the action state to preempted
            as_.setPreempted();
            success = false;
            //break;
            } 
        
        
        
        as_.publishFeedback(feedback_); //feedback is published on topic /action_vision/feedback
        
        if (success) {
            result_.result = feedback_.feedback.back(); //assign whatever the result should be
            ROS_INFO("%s : Succeeded", action_name_.c_str());
            as_.setSucceeded(result_);
        }
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "action_vision");
    
    action_visionAction action_vision("action_vision");
    ros::spin();
    
    return 0;
}



