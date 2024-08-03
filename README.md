# surveillance-app
A continuous application that monitors the presence of a water bottle. The application sends messages to the user based on the water bottle's movements. 

Camera frames are captured and digitized by the digitizer, and analyzed by the tracker, triggering control actions by the alarm module. The digitizer component of the program continually converts the video into a sequence of frames of pixels. The tracker component analyzes each frame to determine if the water bottle is present or not, and sets flags accordingly. The alarm component sends messages based on the flags it receives from the tracker. 

The application employs the pthreads library to implement producer-consumer functionality between each of the components.

## Video demo
https://youtu.be/Dup3v_lNjLI

## To run

### Software requirements:
Note: This project was built and tested on Ubuntu 24.04.

1) Install [OpenCV](https://phoenixnap.com/kb/installing-opencv-on-ubuntu)

2) Obtain a Twilio account SID and an auth token: https://www.twilio.com/docs/iam/api-keys

### Hardware requirements:
Your computer must have a webcam.


To build the project, in the project directory, run:
```rm -rf build
mkdir build
cd build
cmake ..
make
```

To run the application, navigate to `surveillance-app/build` and run:

`./CaptureFrames`
