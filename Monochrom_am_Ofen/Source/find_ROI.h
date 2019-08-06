#ifndef FIND_ROI
#define FIND_ROI

#include <iostream>
#include <stdio.h>
#include <yaml-cpp/yaml.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "VimbaCPP/Include/VimbaCPP.h"

class Find_ROI
{
    public:
        Find_ROI();
        ~Find_ROI();
        AVT::VmbAPI::CameraPtr getCamera();
        //find the connected Camera and return a pointer to it

        void setFeatures(AVT::VmbAPI::CameraPtr);
        //loads all features saved in the Config file and sets them on the current Camera

        cv::Mat getAnImage(AVT::VmbAPI::CameraPtr);
        //records one frame of the Camera. Saves it and returns it

        void processImage(cv::Mat);

        bool is_okay;
        //catch failures

    private:
        AVT::VmbAPI::VimbaSystem &system_ = AVT::VmbAPI::VimbaSystem::GetInstance();
        

};

#endif //DEFINE FIND_ROI.H
