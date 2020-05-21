# Title - Image Processing C++ Coding 


![](images/q_explainations.jpg)

Question : Let O1,O2,O3,O4,O5 be the center of the coins in the above image.
 	   Let C be the intersection of the line joining l1[O1-O4] & l2[O3-O5],

           Compute the distance between O2 & C.Solve the problem using C++ and OpenCV.


## Prerequisites

On Windows 

	1. OpenCV - 3.x or new version .

	2. Visual studio - 2017


On Linux 

	1.OpenCV - 3.x or above
	
	2.CMAKE - 3.5 or above

	3.GCC/G++ compiler - 6.0 or above

## Directory Structure

![](images/directory_structure.png)


## Compiling Steps

Linux :

Step-1 : Download all the prerqusites

	1.Download opencv – 3.x or new version  and extract it to some  folder in your Computer drive.
	
	Link to download:
		https://opencv.org/releases.html


	2.Install the cmake by using the below command:
		sudo apt-get install cmake
	
	3.Install the gcc/g++ compiler by using the below commands:
		sudo apt-get install gcc/g++

	4. Now follow below link for opencv installation:
		https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html

Step-2 : compile and execute the "coin_detection.cpp" src file

	1. cd ImageProcessingCoding

	2. g++ -w coin_detection.cpp -o coin `pkg-config --cflags --libs opencv`

	3. ./coin


Windows : 

Step-1: Download all the prerqusites

	1.Download and install the visual studio 2017 on window
	
	Link to downlad https://visualstudio.microsoft.com/downloads/
	
	2.Download opencv – 3.x or new version  and extract it to some  folder in your drive.
	
	Link to download https://opencv.org/releases.html
	

Step – 2 : Set up the environment paths

	1.Set the Environment path of opencv by following the below commands.
	
	2.Go to the system settings and search the word environment .
	
	3.Then system properties with advance properties option will appear and select the Environment Variables.
	
	4.Add the opencv bin ( D:/opencv/build/x64/vc14/bin ) path to the path variable and save it.
	

Step - 3 : Compile and execute the coin_detection.cpp source code  in visual studio

	1.Open the Visual studio and create a new c++ project .

	2.Add the  source files, along with the input image files to the created project.

	3.Then add the include and library paths of opencv to the properties of project.

	4.Click on C/C++ libraries and add the opencv include directory path on general settings

	5.Click on linker and add the opencv library path  and give the name of the opencv lib name opencv_world341d.lib and save it.

	6.Build the project and excute it.

## Results/Output

Following is the output image for reference.

![](images/cimg.jpg)

![](images/output.png)

Distance between intersection point (C) and Coin O1 centre Point (p1) = 1235.54


## Methodology for Solution

1. INPUT IMAGE READING.
2. IMAGE PRE-PROCESSING ~ FOR COIN DETECTION
3. FIND CENTER OF COINS AND DRAW LINE.
4. FIND LINE EQUATION.
5. INTERSECTION POINT OF LINES.
6. DISTANCE BETWEEN INTERSECTION POINT AND COIN1 CENTER.
7. DISPLAY AND SAVE RESULT





