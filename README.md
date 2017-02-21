Usage:
+ Press 'C' to capture, photos will numbering automatically.
+ Press 'ESC' to exit program.

This branch is using with Raspberry PI CSI(Camera Serial Interface).

**You can't use it with normal device.**

http://yehnan.blogspot.tw/2013/05/raspberry-pi.html

This sample requires OpenCV and RaspiCam.

To install OpenCV, you can download from apt-get
```shell
sudo apt-get update
sudo apt-get install libopencv-dev
```
or download from official website and build it yourself.


Then we need RaspiCam, clone it first:
```shell
git clone https://github.com/cedricve/raspicam.git
```
and build it: (more detail please visit original author's [Github page](https://github.com/cedricve/raspicam.git))
```shell
cd raspicam
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

Finally, clone this project and checkout to this branch, and build it.

### DEMO
![Demo](http://140.127.205.188/m1045113/Easy_camera/raw/using_raspicam/IMG_002.jpg)
