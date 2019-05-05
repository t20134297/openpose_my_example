#include<openpose/flags.hpp>
#include<openpose/headers.hpp>
#include<vector>
#include<dirent.h>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
    vector <string> keypoints(25);
    keypoints[0]="Nose";
    keypoints[1]="Neck";
    keypoints[2]="RShoulder";
    keypoints[3]="RElbow";
    keypoints[4]="RWrist";
    keypoints[5]="LShoulder";
    keypoints[6]="LElbow";
    keypoints[7]="LWrist";
    keypoints[8]="MidHip";
    keypoints[9]="RHip";
    keypoints[10]="RKnee";
    keypoints[11]="RAnkle";
    keypoints[12]="LHip";
    keypoints[13]="LKnee";
    keypoints[14]="LAnkle";
    keypoints[15]="REye";
    keypoints[16]="LEye";
    keypoints[17]="REar";
    keypoints[18]="LEar";
    keypoints[19]="LBigToe";
    keypoints[20]="LSmallToe";
    keypoints[21]="LHeel";
    keypoints[22]="RBigToe";
    keypoints[23]="RSmallToe";
    keypoints[24]="RHeel";



    string img_path = "/home/tcr/Desktop/hezhao.jpg";   //timg.jpeg  sss.png  hezhao.jpg
    Mat img = imread(img_path);
	imshow("sss",img);
waitKey(0);

    op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
    opWrapper.start();
    auto datumProcessed = opWrapper.emplaceAndPop(img) ;
//    imshow("label",datumProcessed->at(0)->cvOutputData);
//    imshow("window",img);
    float temp_confidence;
    if (datumProcessed != nullptr && !datumProcessed->empty())
    {
	
        //cout<<datumProcessed->at(0)->poseKeypoints<<endl;
	cout<<datumProcessed->size()<<endl;
    cout<<datumProcessed->at(0)->poseKeypoints<<endl;

    try
    {
        cout<<datumProcessed->at(0)->poseKeypoints[3*1+2]<<endl;
    }catch( exception & e)
    {
        cout<<"error occured"<<endl;
        return 0;
    }

//        temp_confidence = datumProcessed->at(0)->poseKeypoints[3*1+2] + datumProcessed->at(0)->poseKeypoints[3*2+2] + datumProcessed->at(0)->poseKeypoints[3*3+2] + datumProcessed->at(0)->poseKeypoints[3*4+2] + datumProcessed->at(0)->poseKeypoints[3*5+2]+ datumProcessed->at(0)->poseKeypoints[3*6+2]+ datumProcessed->at(0)->poseKeypoints[3*7+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2];
//        cout<<temp_confidence<<endl;
    }
    else
    {
        cout<<"no people"<<endl;
    }
    cout<<"sssssssssssssssssssssssssssss"<<endl;
    return 0;
}
