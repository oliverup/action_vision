#include "find_ROI.h"

Find_ROI::Find_ROI(){};
Find_ROI::~Find_ROI(){};


AVT::VmbAPI::CameraPtr Find_ROI::getCamera(){
    std::string name;
    AVT::VmbAPI::CameraPtrVector cameras;
    if (VmbErrorSuccess == system_.Startup())
    {
        if (VmbErrorSuccess == system_.GetCameras(cameras))
        {
            if (cameras.size() > 0)
            {
                for (AVT::VmbAPI::CameraPtrVector::iterator iter = cameras.begin(); cameras.end() != iter; ++iter)
                {
                    if (VmbErrorSuccess == (*iter)->GetName(name))
                    {
                        std::cout << "found " << name << " Camera" << std::endl;
                        return *iter;
                    }
                }
            }else{
                std::cout << "no Cameras Connected" << std::endl;
                AVT::VmbAPI::CameraPtr empty_return;
                Find_ROI::is_okay = false;
                return empty_return;
            }
        }
        system_.Shutdown();
    }
}

void Find_ROI::setFeatures(AVT::VmbAPI::CameraPtr my_camera)
{
    if(VmbErrorSuccess == system_.Startup())
    {
        if(VmbErrorSuccess == my_camera->Open(VmbAccessModeFull))
        {
            YAML::Node config = YAML::LoadFile("../../../../Config/Camera_Features.yaml");

            AVT::VmbAPI::FeaturePtrVector features;
            std::string feature_name;
            my_camera->GetFeatures(features);
            std::cout << "--- Config ---" << std::endl;
            for(AVT::VmbAPI::FeaturePtrVector::iterator iter = features.begin(); features.end() != iter; iter++)
            {
                std::string feature_name;
                (*iter)->GetName(feature_name);
                if(config[feature_name])
                {
                    VmbFeatureDataType feature_type;
                    (*iter)->GetDataType(feature_type);
                    
                    switch(feature_type)
                    {
                    case VmbFeatureDataBool:
                        {
                            std::string written = "failed to load:  ";
                            if (VmbErrorSuccess == (*iter)->SetValue(config[feature_name].as<VmbBool_t>())) //load the predefined Configs for this feature
                            {
                                written = "loaded:  ";
                            }

                            VmbBool_t value;
                            (*iter)->GetValue( value );
                            std::cout << written << feature_name << ": " << value << "\n";
                        }
                        break;
                    case VmbFeatureDataEnum:
                        {
                            std::string written = "failed to load:  ";
                            if (VmbErrorSuccess == (*iter)->SetValue((config[feature_name].as<std::string>()).c_str())) //load the predefined Configs for this feature
                            {
                                written = "loaded:  ";
                            }
                            std::string value;
                            (*iter)->GetValue( value );
                            std::cout << written << feature_name << ": " << value << "\n";
                        }
                        break;
                    case VmbFeatureDataFloat:
                        {
                            std::string written = "failed to load:  ";
                            if (VmbErrorSuccess == (*iter)->SetValue(config[feature_name].as<double>())) //load the predefined Configs for this feature
                            {
                                written = "loaded:  ";
                            }
                            double value;
                            (*iter)->GetValue( value );
                            std::cout << written << feature_name << ": " << value << "\n";
                        }
                        break;
                    case VmbFeatureDataInt:
                        {
                            std::string written = "failed to load:  ";
                            if (VmbErrorSuccess == (*iter)->SetValue(config[feature_name].as<VmbInt64_t>())) //load the predefined Configs for this feature
                            {
                                written = "loaded:  ";
                            }
                            VmbInt64_t value;
                            (*iter)->GetValue( value );
                            std::cout << written << feature_name << ": " << value << "\n";
                        }
                        break;
                    case VmbFeatureDataString:
                        {
                            std::string written = "failed to load:  ";
                            if (VmbErrorSuccess == (*iter)->SetValue((config[feature_name].as<std::string>()).c_str())) //load the predefined Configs for this feature
                            {
                                written = "loaded:  ";
                            }
                            std::string value;
                            (*iter)->GetValue( value );
                            std::cout << written << feature_name << ": " << value << "\n";
                        }
                        break;
                    case VmbFeatureDataCommand:
                    default:
                        std::cout << feature_name << ": " << "[None]" << "\n";
                        break;
                    }
                }

            }
            std::cout << "--- Config ---" << std::endl;

        }else{std::cout << "can't open camera in setFeatures" << std::endl;}
        my_camera->Close();
    }
    system_.Shutdown();
}

cv::Mat Find_ROI::getAnImage(AVT::VmbAPI::CameraPtr my_camera)
{
    cv::Mat image_in;
    cv::Mat image_out;
    if(VmbErrorSuccess == system_.Startup())
    {
        if(VmbErrorSuccess == my_camera->Open(VmbAccessModeFull)) //TODO
        {
            AVT::VmbAPI::FramePtr frame;
            VmbFrameStatusType receive_status;
            VmbUchar_t* buffer;
            AVT::VmbAPI::FeaturePtr feature;

            VmbUint32_t frame_width;
            VmbUint32_t frame_height;
            my_camera->GetFeatureByName("ExposureTimeAbs", feature);
            YAML::Node config = YAML::LoadFile("../../../../Config/Camera_Features.yaml");
            YAML::Node test_config = YAML::LoadFile("../../../../Config/Test_Params.yaml");

            double lower_limit;
            double upper_limit;
            int number_of_images = 1;
            if(config["testing"].as<bool>() == true)
            {

                lower_limit = test_config["lower_exposure_limit"].as<double>();
                upper_limit = test_config["upper_exposure_limit"].as<double>();
                number_of_images = test_config["images_for_exposure_test"].as<int>();
            }
            for(int i=1; i<number_of_images+1; i++)
            {
                double exposure_time;
                if(config["testing"].as<bool>() == true)
                {
                    exposure_time = lower_limit + (upper_limit-lower_limit)/number_of_images *i;
                    feature->SetValue(exposure_time);
                }else{ feature->GetValue(exposure_time); }

                double wait_for_frame = 10000000000; //waits until it gets an image
                //double wait_for_frame = (exposure_time/1000.) + 250;

                my_camera->AcquireSingleImage(frame, wait_for_frame);
                frame->GetReceiveStatus(receive_status);
                if(VmbFrameStatusComplete == receive_status)
                {
                    frame->GetWidth(frame_width);
                    frame->GetHeight(frame_height);
                    frame->GetImage(buffer);

                    image_in = cv::Mat(frame_width, frame_height, CV_8UC1, buffer); 
                    std::string file_name = "../../../../Pictures/Exposure_Time_" + std::to_string((int)exposure_time) + ".jpeg";
                    std::cout << "saved an image" << std::endl;
                    cv::imwrite(file_name, image_in);
                    image_out = image_in.clone(); //just returning the image throws weird errors. so i return a clone of it.
                }else{std::cout << "did not recieve an Image in getAnImage" << std::endl;}
            }
            if(config["testing"].as<bool>() == true){Find_ROI::is_okay = false;}
        }else{std::cout << "can't open camera in getAnImage" << std::endl;}
        my_camera->Close();
    }
    system_.Shutdown();
    return image_out;
}

void Find_ROI::processImage(cv::Mat image_in)
{
    cv::Mat edges;
    cv::blur(image_in, image_in, cv::Size(5, 5), cv::Point(-1,-1) );
//    getRectSubPix(image_in, cv::Size(2000, 2000), cv::Point2f(2000, 2000), image_in);
    cv::Canny(image_in, edges, 100, 300, 5);


    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    cv::Mat image_out = cv::Mat::zeros(image_in.size(), CV_8UC1);
    int c_1 = 0;
    for(int i=0; i<contours.size(); i++)
    {
        if(contours[i].size()>100)
        {
            cv::drawContours(image_out, contours, i, cv::Scalar(255), -1);
        }
    }
//    cv::Mat element_1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11), cv::Point(1, 1));
//    cv::Mat element_2 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11), cv::Point(1, 1));
//    cv::dilate(contour_mask, contour_mask, element_1);
//    cv::erode(contour_mask, contour_mask, element_2);

//    cv::findContours(contour_mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    cv::imwrite("../../../../Pictures/processed.jpeg", image_out);
}



