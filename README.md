Usage:
+ Press 'C' to capture, photos will numbering automatically.
+ Press 'ESC' to exit program.

For Pi Camera, you can use the branch "using_raspicam", or do as follows:

1. Enable Pi camera port.
```shell
sudo raspi-config
```
Then choose "Interfacing Options", choose "Camera", and just enable it.

2. Install V4L drivers.
```shell
sudo apt-get install libv4l-dev
```

3. Reboot

4. Load v4l2 driver
``
sudo modprobe bcm2835-v4l2
``

5. (Optional) Auto load v4l driver when boot.
```shell
sudo vim /etc/modules
```
And add "bcm2835-v4l2" at the last line of file.
