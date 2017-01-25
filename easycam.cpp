#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#ifdef TEST
#include <sys/time.h>
#endif
#define IMG_H 480
#define IMG_W 640

using namespace cv;
using namespace std;

int main()
{
  raspicam::RaspiCam_Cv PICam;  //PI camera object.
#ifdef TEST
  struct timeval t1,t2;
  double d1;
#endif
//  VideoCapture cam0(0); //OpenCV with USB Camera init.
  Mat image0;  //OpenCV Mat space.
  /* PI camera setting */  //same as OpenCV
  PICam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
  PICam.set(CV_CAP_PROP_FRAME_WIDTH, IMG_W);
  PICam.set(CV_CAP_PROP_FRAME_HEIGHT, IMG_H);
  PICam.set(CV_CAP_PROP_FPS,60);

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

  char k;
#ifdef TEST
  gettimeofday(&t1,NULL);
  for(int i=0;i<900;i++)
#else
  while(1)
#endif
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
#ifndef TEST
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
#endif
  }
#ifdef TEST
  gettimeofday(&t2,NULL);
  d1 = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/1E+6;
  cout << "Time cost: " << d1 << endl;
#endif
  PICam.release();  //Release camera.
}
