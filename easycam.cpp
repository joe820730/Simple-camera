#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

using namespace cv;
using namespace std;

int main()
{
  raspicam::RaspiCam_Cv PICam;
//  VideoCapture cam0(0);
  Mat image0;
  PICam.set(CV_CAP_PROP_FORMAT, CV_8UC1);
  int i=-1;
  FILE *cfgFP;
  char filename[64];
  char cfgfile[64];
  cfgFP=fopen("camcfg.ini","r");
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
//    cam0.set(CV_CAP_PROP_FRAME_WIDTH,640);
//    cam0.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    while(1)
    {
//      cam0.read(image0);
      PICam.grab();
      PICam.retrieve(image0);
      imshow("Webcam",image0);
      switch (waitKey(1))
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
              cfgFP=fopen("camcfg.ini","w");
              fprintf(cfgFP,"%d",i);
              fclose(cfgFP);
              return 0;
          }
      }
    }
}
