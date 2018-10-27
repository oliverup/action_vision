#include <templates/template_ASRV.h> 

template_class::template_class(std::string ASRV_name):
    as_(nh_, ASRV_name, boost::bind(&template_class::executeCB, this, _1), false), action_name_(ASRV_name) {
    as_.start();
    }
    
template_class::~template_class() {};

void template_class::executeCB(const action_vision::msg_templateGoalConstPtr &goal) {
    
    ros::Rate r(1); //?
    bool success = true;
    
    ROS_INFO("this is the goal: %s", goal->goal.c_str());
    
    //do some stuff with the goal->goal you got by the client and publish your feedback
    feedback_.feedback.clear();
    feedback_.feedback.push_back(goal->goal);
    
    as_.publishFeedback(feedback_); //feedback is published on topic /action_vision/feedback
    
    // constantly check if client cancelled the action
    if (as_.isPreemptRequested() || !ros::ok()) {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        //break;
        } 
    
    
    
    
    if (success) {
        result_.result = feedback_.feedback.back(); //assign whatever the result should be (here latest feedback)
        ROS_INFO("%s : Succeeded", action_name_.c_str());
        as_.setSucceeded(result_);
    }
    
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "template_action_name");
    
    template_class action_vision("template_action_name");
    ros::spin();
    
    return 0;
}

