#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#ifdef __linux
#include <sys/time.h>
#endif

using namespace cv;
using namespace std;

int main()
{
#ifdef __linux
  struct timeval t1,t2;
  double d1,sum=0,avgFPS;
  int x=0;
#endif
  VideoCapture cam0(0);
  Mat image0;
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
    if(!cam0.isOpened())
    {
      printf("No camera!\n");
      return -1;
    }
    cam0.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cam0.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    char k;
    while(1)
    {
#ifdef __linux
      gettimeofday(&t1,NULL);
#endif
      cam0.read(image0);
      imshow("Webcam",image0);
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
              cfgFP=fopen("camcfg.ini","w");
              fprintf(cfgFP,"%d",i);
              fclose(cfgFP);
              return 0;
          }
      }
#ifdef __linux
      gettimeofday(&t2,NULL);
      d1 = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/1E+6;
      sum = sum + d1;
      x++;
      if(x==60)
      {
        avgFPS = 60.0/sum;
        printf("Average FPS: %lf\n",avgFPS);
        x=0;
        sum=0;
      }
#endif
    }
}
