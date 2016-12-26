#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
  VideoCapture cam0(0);
  Mat image0;
  int i=0;
  char filename[64];
    if(!cam0.isOpened())
    {
      printf("No camera!\n");
      return -1;
    }
    cam0.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cam0.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    while(1)
    {
      cam0.read(image0);
      imshow("Webcam",image0);
      switch (waitKey(1))
      {
          case 'c':
          {
            sprintf(filename,"IMG_%03d.jpg",i);
            vector<int> quality;
            quality.push_back(CV_IMWRITE_JPEG_QUALITY);
            quality.push_back(100);
            imwrite(filename,image0,quality);
            i++;
            cout << "Image " << i <<" saved!" <<endl;
            break;
          }
          case 27:
          {
              cout << "Program Exit!" <<endl;
              return 0;
          }
      }
    }
}
