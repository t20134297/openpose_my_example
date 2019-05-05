#include<openpose/flags.hpp>
#include<openpose/headers.hpp>
#include<vector>
#include<dirent.h>
#include<iostream>

using namespace std;
using namespace cv;

vector<string> get_subdirect(string path)
{
  struct dirent *ptr;
  DIR *dir;
  const char* PATH = path.c_str();
  dir = opendir(PATH);
  vector<string> files;
  while((ptr=readdir(dir))!=NULL)
  {
    if(ptr->d_name[0] == '.')
      continue;
    files.push_back(path+"/"+ptr->d_name);
  }
  return files;
}

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



    string img_path = "/home/tcr/Market-1501-v15.09.15/bounding_box_train/0011_c6s4_002452_01.jpg";
    Mat img = imread(img_path);
    Mat temp_img;

    op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
    opWrapper.start();
    auto datumProcessed = opWrapper.emplaceAndPop(img) ;
//    imshow("label",datumProcessed->at(0)->cvOutputData);
//    imshow("window",img);
    const char * path;
    int i,img_num,keypoint_num;
    float remove_num;
    vector <string> files;
    files = get_subdirect("/home/tcr/0000");
    img_num = files.size();
    remove_num = 0.7* img_num;

    if(img_num < 5)
    {
        cout<<"too few pictures"<<endl;
        return 0;
    }



    vector<float> confidence_list;
    vector<float> confidence_left;
    float temp_confidence;
    float temp_left;


    for(i=0;i<img_num;i=i+1)
    {
        temp_confidence = 0;

        temp_img = imread(files[i]);
//        imshow("original img",temp_img);
        datumProcessed = opWrapper.emplaceAndPop(temp_img);
//        imshow("keypoints",datumProcessed->at(0)->cvOutputData) ;
        temp_confidence = datumProcessed->at(0)->poseKeypoints[3*1+2] + datumProcessed->at(0)->poseKeypoints[3*2+2] + datumProcessed->at(0)->poseKeypoints[3*3+2] + datumProcessed->at(0)->poseKeypoints[3*4+2] + datumProcessed->at(0)->poseKeypoints[3*5+2]+ datumProcessed->at(0)->poseKeypoints[3*6+2]+ datumProcessed->at(0)->poseKeypoints[3*7+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2];
        confidence_list.push_back(temp_confidence);
//        for(num_keypoint=0;num_keypoint<25;num_keypoint = num_keypoint + 1 )
//        {
//            cout<<keypoints[num_keypoint] +": "<<datumProcessed->at(0)->poseKeypoints[3*num_keypoint+2]<<endl;
//        }
//        waitKey(100);
    }
    vector<float> backup = confidence_list;


    int temp_index,j;
    for(i=0;i<img_num - remove_num;i=i+1)
    {
//        cout<<endl<<endl<<endl<<endl<<endl;
//        cout<<img_num<<"img_num  "<<endl;
//        cout<<img_num-remove_num<<"  img_num-img"<<endl;
//        for(int k=0;k<img_num;k=k+1)
//        {
//            cout<<confidence_list[k]<<endl;
//        }
        temp_index = 0;
        temp_confidence = confidence_list[0];
        for(j=0;j<img_num;j=j+1)
        {
            if(confidence_list[j]>temp_confidence)
            {
                temp_confidence = confidence_list[j];
                temp_index = j;
            }
        }
        confidence_list[temp_index] = -10;
    }
//    for(i=0;i<img_num;i=i+1)
//    {
//        cout<<"lasn line"<<endl;
//        cout<<confidence_list[i]<<endl;
//        cout<<backup[i]<<endl;
//    }

    for(i=0;i<img_num;i=i+1)
    {
        if(confidence_list[i] >  -5)
        {
            cout<<backup[i]<<endl;
            path = files[i].data();
            if(remove(path)==0)
            {
                cout<<"remove "<<files[i]<<"  successfully!"<<endl;
            }
        }
    }
//    datumProcessed = opWrapper.emplaceAndPop(img1) ;
//    imshow("label1",datumProcessed->at(0)->cvOutputData);
//    imshow("window1",img);
//    waitKey(0);
//    vector<string> files;
//    files = get_subdirect("/home/tcr/Downloads/rr");
//    int i,num;
//    num = files.size();

//    for(i=0;i<num;i=i+1)
//    {
//        cout<<files[i]<<endl;
//        path = files[i].data();
//        if(remove(path)==0 )
//        {
//            cout<<"remove " +files[i] +"  successfully!";
//        }
//        else
//        {
//            cout<<"remove "+files[i]+"  failed!"<<endl;
//        }
//    }

    return 0;
}