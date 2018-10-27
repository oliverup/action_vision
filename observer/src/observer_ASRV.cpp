#include <observer_ASRV.h> 

Observer::Observer(std::string ASRV_name):
    as_(nh_, ASRV_name, boost::bind(&Observer::executeCB, this, _1), false), action_name_(ASRV_name) {
    as_.start();
    }
    
Observer::~Observer() {};

void Observer::executeCB(const msgs_and_action::observerGoalConstPtr &goal_) {
    
    ros::Rate r(1); //?
    bool success = true;
    
    ROS_INFO("this is the goal: %s", goal_->goal.c_str());

/////////////////////MAIN_CODE_START//////////////////////
    
    //do some stuff with the goal->goal you got by the client and publish your feedback
    feedback_.feedback.clear();
    feedback_.feedback.push_back(goal_->goal);
    
    as_.publishFeedback(feedback_); //feedback is published on topic /msgs_and_action/feedback
    
    // constantly check if client cancelled the action
    if (as_.isPreemptRequested() || !ros::ok()) {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        //break;
        } 

/////////////////////MAIN_CODE_END//////////////////////
    
    
    
    if (success) {
        result_.result = feedback_.feedback.back(); //assign whatever the result should be (here latest feedback)
        ROS_INFO("%s : Succeeded", action_name_.c_str());
        as_.setSucceeded(result_);
    }
    
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "ObserverAction");
    
    Observer msgs_and_action("ObserverAction");
    ros::spin();
    
    return 0;
}

