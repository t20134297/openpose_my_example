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

int get_frontAndback(string direct_path)
{
    cout<<direct_path<<endl;
    const char * path;
    string stable_img_path = "/home/tcr/Market-1501-v15.09.15/bounding_box_train/0011_c6s4_002452_01.jpg";

    Mat stable_img = imread(stable_img_path);
    op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
    Mat temp_img;
    opWrapper.start();
    auto datumProcessed = opWrapper.emplaceAndPop(stable_img);


    vector<string> img_in_direct;
    img_in_direct = get_subdirect(direct_path);
    int img_num = img_in_direct.size();
     if(img_num<5)
    {
        cout<<"too few images"<<endl;
        return 0;
    }
    float num_imgremove = 0.5*img_num;
    vector<float> confidence_list;
    float temp_confidence;




    for(int i = 0; i < img_num; i = i + 1)
    {
        temp_confidence = 0;
        temp_img = imread(  img_in_direct[i]  );
//        imshow("dd",temp_img);

//         cout<<"calculate1"<<endl;
        datumProcessed = opWrapper.emplaceAndPop(temp_img);
//        imshow("ssss",datumProcessed->at(0)->cvOutputData);
//         waitKey(0);
//         cout<<"calculate2"<<endl;
        if (datumProcessed != nullptr && !datumProcessed->empty())
        {
//           cout<<datumProcessed->at(0)->poseKeypoints<<endl;
            try
            {
                temp_confidence = datumProcessed->at(0)->poseKeypoints[3*1+2] + datumProcessed->at(0)->poseKeypoints[3*2+2] + datumProcessed->at(0)->poseKeypoints[3*3+2] + datumProcessed->at(0)->poseKeypoints[3*4+2] + datumProcessed->at(0)->poseKeypoints[3*5+2]+ datumProcessed->at(0)->poseKeypoints[3*6+2]+ datumProcessed->at(0)->poseKeypoints[3*7+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2];
            }
            catch(exception &e)
            {
                cout<<"failed occured"<<endl;
                confidence_list.push_back(0);
            }
             confidence_list.push_back(temp_confidence);
        }
    }

    int temp_index;
    cout<<num_imgremove<<endl;
    for(int i=0;i<num_imgremove;i=i+1)
    {

        temp_index = 0;

        temp_confidence = confidence_list[0];

        for(int j=0;j<img_num;j=j+1)
        {
            if(confidence_list[j]>temp_confidence)
            {
                temp_confidence = confidence_list[j];
                temp_index = j;
            }
        }
        confidence_list[temp_index] = -10;
    }



    for(int i=0;i<img_num;i=i+1)
    {
//        cout<<"removing"<<endl;
        if(confidence_list[i] >  -5)
        {
            path = img_in_direct[i].data();
            if(remove(path)==0)
            {
                cout<<"remove "<<img_in_direct[i]<<"  successfully!"<<endl;
            }
        }
    }

    cout<<direct_path<<endl;
    cout<<endl<<endl<<endl;
    return 1;
}




int main()
{
    vector<string> all_direct;
    all_direct = get_subdirect("/home/tcr/small_market1501/pytorch/query");
    int direct_num = all_direct.size();
    int i = all_direct.size();
    for(int j = 0; j < i; j = j + 1)
    {
       get_frontAndback(all_direct[j]);
    }


//
//    for(int i=0;i<direct_num;i=i+1)
//    {
//        remove_poorimg(all_direct[i]);
//    }



//    vector <string> keypoints(25);
//    keypoints[0]="Nose";
//    keypoints[1]="Neck";
//    keypoints[2]="RShoulder";
//    keypoints[3]="RElbow";
//    keypoints[4]="RWrist";
//    keypoints[5]="LShoulder";
//    keypoints[6]="LElbow";
//    keypoints[7]="LWrist";
//    keypoints[8]="MidHip";
//    keypoints[9]="RHip";
//    keypoints[10]="RKnee";
//    keypoints[11]="RAnkle";
//    keypoints[12]="LHip";
//    keypoints[13]="LKnee";
//    keypoints[14]="LAnkle";
//    keypoints[15]="REye";
//    keypoints[16]="LEye";
//    keypoints[17]="REar";
//    keypoints[18]="LEar";
//    keypoints[19]="LBigToe";
//    keypoints[20]="LSmallToe";
//    keypoints[21]="LHeel";
//    keypoints[22]="RBigToe";
//    keypoints[23]="RSmallToe";
//    keypoints[24]="RHeel";
//
//    string img_path = "/home/tcr/Downloads/Market-1501-v15.09.15/query/0001_c4s6_000810_00.jpg";
//    Mat img = imread(img_path);
//    Mat temp_img;
//
//    op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
//    opWrapper.start();
//    auto datumProcessed = opWrapper.emplaceAndPop(img) ;
//    const char * path;
//    int i,img_num,keypoint_num;
//    float remove_num;
//    vector <string> files;
//    files = get_subdirect("/home/tcr/Downloads/openpose-master/0002");
//    img_num = files.size();
//    remove_num = 0.7* img_num;
//
//    vector<float> confidence_list;
//    float temp_confidence;
//
//    for(i=0;i<img_num;i=i+1)
//    {
//        temp_confidence = 0;
//        temp_img = imread(files[i]);
//        datumProcessed = opWrapper.emplaceAndPop(temp_img);
//        temp_confidence = datumProcessed->at(0)->poseKeypoints[3*1+2] + datumProcessed->at(0)->poseKeypoints[3*2+2] + datumProcessed->at(0)->poseKeypoints[3*3+2] + datumProcessed->at(0)->poseKeypoints[3*4+2] + datumProcessed->at(0)->poseKeypoints[3*5+2]+ datumProcessed->at(0)->poseKeypoints[3*6+2]+ datumProcessed->at(0)->poseKeypoints[3*7+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2]+ datumProcessed->at(0)->poseKeypoints[3*10+2];
//        confidence_list.push_back(temp_confidence);
//    }
//    vector<float> backup = confidence_list;
//    int temp_index,j;
//    for(i=0;i<img_num - remove_num;i=i+1)
//    {
//        temp_index = 0;
//        temp_confidence = confidence_list[0];
//        for(j=0;j<img_num;j=j+1)
//        {
//            if(confidence_list[j]>temp_confidence)
//            {
//                temp_confidence = confidence_list[j];
//                temp_index = j;
//            }
//        }
//        confidence_list[temp_index] = -10;
//    }
//
//    for(i=0;i<img_num;i=i+1)
//    {
//        if(confidence_list[i] >  -5)
//        {
//            cout<<backup[i]<<endl;
//            path = files[i].data();
//            if(remove(path)==0)
//            {
//                cout<<"remove "<<files[i]<<"  successfully!"<<endl;
//            }
//        }
//    }
    return 0;
}