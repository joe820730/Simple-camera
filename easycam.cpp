#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#define IMG_H 480
#define IMG_W 640

using namespace cv;
using namespace std;

int main()
{
  raspicam::RaspiCam_Cv PICam;  //PI camera object.
//  VideoCapture cam0(0); //OpenCV with USB Camera init.
  Mat image0;  //OpenCV Mat space.
  /* PI camera setting */  //same as OpenCV
  PICam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
  PICam.set(CV_CAP_PROP_FRAME_WIDTH, IMG_W);
  PICam.set(CV_CAP_PROP_FRAME_HEIGHT, IMG_H);

  int i=-1;
  FILE *cfgFP;
  char filename[64];
  const char* cfgName="camcfg.ini";
  cfgFP=fopen(cfgName,"r");
  if(cfgFP != NULL)
  {
    fscanf(cfgFP,"%d",&i);
    fclose(cfgFP);
  }
  else
  {
    printf("No config file, use default setting.\n");
  }
  if(!PICam.open())
  {
    printf("No camera!\n");
    return -1;
  }

  char k; // keyboard char
  while(1)
  {
    /*
     * In OpenCV with USB camera, we just need a line:
     * cam0.read(image0);
     * to read image from camera to cam0;
     *
     * But in RaspiCam, we need grad image,
     * and move image to cv::Mat space.
     */
    PICam.grab();   //grad image from PIcam
    PICam.retrieve(image0);  //move image to CV Mat space.
    imshow("Webcam",image0); //show image to a window.
    k = waitKey(1);
    switch (k)
    {
      case 'c':
        {
          i++;
          sprintf(filename,"IMG_%03d.jpg",i);
          vector<int> quality;
          quality.push_back(CV_IMWRITE_JPEG_QUALITY);
          quality.push_back(100);
          imwrite(filename,image0,quality);
          cout << "Image " << i <<" saved!" <<endl;
          break;
        }
      case 27:
        {
          cout << "Program Exit!" <<endl;
          cfgFP=fopen(cfgName,"w");
          fprintf(cfgFP,"%d",i);
          fclose(cfgFP);
          return 0;
        }
    }
  }
  PICam.release();  //Release camera.
}
