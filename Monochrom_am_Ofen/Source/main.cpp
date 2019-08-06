#include "find_ROI.h"


int main(int argc, char* argv[])
{
    Find_ROI findROI;

    AVT::VmbAPI::CameraPtr my_camera;

    findROI.is_okay = false;
    while(!findROI.is_okay)
    {
        findROI.is_okay = true;
        my_camera = findROI.getCamera();
        sleep(1);
    }

    findROI.setFeatures(my_camera);
    while(findROI.is_okay)
    {
        my_camera = findROI.getCamera(); 
        //should not be necessary, but somehow the pointer changes after editing features. still the same camera though
        cv::Mat image = findROI.getAnImage(my_camera);
        //findROI.processImage(image);
    }
    return 0;
};
