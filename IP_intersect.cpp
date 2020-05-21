/*
Image Processing - Opencv C++ Coding 

Created on Sat July 20 10:40:32 2019

@author: Brijesh Gupta

Sample Run:
---------- 
For code compilation:-
g++ -w coin_detection.cpp -o coin `pkg-config --cflags --libs opencv`

Run the executable:-
./coin

*/


#include "opencv2/highgui/highgui.hpp"
// highgui - an interface to video and image capturing.
#include "opencv2/imgproc/imgproc.hpp"
// imgproc - An image processing module that for linear and non-linear
// image filtering, geometrical image transformations, color space conversion and so on.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
// The header files for performing input and output.
#include <vector>
// header file for vector class object
using namespace cv;
// Namespace where all the C++ OpenCV functionality resides.
using namespace std;
// For input output operations.

 
int main()
{
    Mat image,cimg,imgBlurred,imgGrayscale,thresh,erode_img,dilate_img,adp_thresh,imgBlurred2;
    //Mat object is a basic image container.Mat object for input image pre-processing 
    
    vector<Vec3f> circles; 
    int erosion_size = 1;

    Mat element = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),cv::Point(erosion_size, erosion_size) );

    
    double m1,m2,x,y,X,Y,X1,Y1,X2,Y2,X3,Y3,X4,Y4,X5,Y5,distance;
    cv::Point p1,p2,p3,p4,p5;
    
    // Co-ordintes variable for coin center detection.



    // ##################################################################################################
    //                                    STAGE 1 : IMAGE READING 
    // ##################################################################################################
    

    image=imread("input_image.jpg", IMREAD_COLOR);
    // Input image from the same folder.
    // first argument denotes the image to be loaded. 
    // second argument specifies the image format as follows:      
    // IMAGE_COLOR (>0) loads the image in the BGR format. 

    cimg = image.clone();
    // clone the image to draw output on original image


    // ###################################################################################################
    //                            Stage 2:  IMAGE PRE-PROCESSING Stage ~ FOR COIN DETECTION
    // ###################################################################################################


    GaussianBlur(image,imgBlurred,Size(9,9),2,2);
    // apply Gaussian kernel of 9x9 size to remove noise 

    cvtColor(imgBlurred,imgGrayscale,CV_BGR2GRAY);
    // convert in gray scale ( 3 channel image to single channel image) 

    threshold(imgGrayscale,thresh,81 ,255,THRESH_BINARY_INV);
    // apply binary invere thresholding for image segmentation to create binary image

    // For image segmentation erode and dilate operation : Morphological operation
    erode(thresh,erode_img,element);

    dilate(erode_img,dilate_img,element);

    adaptiveThreshold(dilate_img, adp_thresh, 255.0, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY, 15,15); 
    // Here again threshold for a small regions of the image : for coin 

    GaussianBlur(adp_thresh,imgBlurred2,Size(3,3),2,2);
    // Again blur technique to remove noise :for small black dots in foreground
    
    // Detect circles using HoughCircles transform
    HoughCircles(imgBlurred2, circles, CV_HOUGH_GRADIENT,1,555, 1, 69, 0, 0);
    // Argument 1: Input image mode
    // Argument 2: A vector that stores 3 values: x,y and r for each circle.
    // Argument 3: CV_HOUGH_GRADIENT: Detection method.
    // Argument 4: The inverse ratio of resolution.
    // Argument 5: Minimum distance between centers.
    // Argument 6: Upper threshold for Canny edge detector.
    // Argument 7: Threshold for center detection.
    // Argument 8: Minimum radius to be detected. Put zero as default
    // Argument 9: Maximum radius to be detected. Put zero as default

    cout<<"Number of Detected Coin : "<<circles.size()<<endl;
    // Get the number of coins detected.


    // ###################################################################################################
    //                        STAGE 3 : FIND CENTER OF COINS AND DRAW LINE
    // ###################################################################################################

      for( size_t i = 0; i < circles.size(); i++ )
      {
          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
          X = circles[i][0] ; Y = circles[i][1];
          // Print the detected circle co-ordinates on the console
          cout<<"circle id :"<<i+1<<endl;
          cout<<"Circle point:"<<"( "<<X<<", "<<Y<<")"<<endl;

          // Store co-ordinates of center of coin 
          if (i+1==1)
          {
            X1 = (circles[i][0]); 
            Y1 = (circles[i][1]);
            p1 = Point(X1,Y1);
          }
          else if (i+1==2)
          {
            X2 = (circles[i][0]);
            Y2 = (circles[i][1]);
            p2 = Point(X2,Y2);
          }
          else if (i+1==3)
          {
            X3 = (circles[i][0]);
            Y3 = (circles[i][1]);
            p3 = Point(X3,Y3);
          }
          else if (i+1==4)
          {
            X4 = (circles[i][0]);
            Y4 = (circles[i][1]);
            p4 = Point(X4 ,Y4);
          }
          else if (i+1==5)
          {
            X5 = (circles[i][0]);
            Y5 = (circles[i][1]);
            p5 = Point(X5,Y5);
          }

          // radius of the coin
          int radius = cvRound(circles[i][2]);
          
          // Draw the outer circle
          //circle( cimg, center, radius, Scalar(0, 255, 0), 10);
          
          // Draw the center of the circle
          circle( cimg, center, 2, Scalar(255, 255, 255), 40);
          // named the center of the circle as O1,O2,O3,O4,O5 and print on cloned input image
          putText(cimg, "O"+std::to_string(i+1) ,Point(X+50,Y+50), FONT_HERSHEY_COMPLEX, 3, Scalar(255,255,255), 3);
       }

       // Draw the line adjoining center of circle O2 and O3 , O4 and O5.
       line(cimg, p2, p3, cv::Scalar(0,255,255), 5);
       line(cimg, p4, p5, cv::Scalar(0,255,255), 5);

       
    // ########################################################################################################
    //                                 STAGE 4 : FIND LINE EQUATION 
    // ########################################################################################################

       // formula for line equation from two Coin Center co-ordinates.
       // Line equation between p2 and p3 ( Coin Center O2 and O3 ):  (y-y2) = m (x-x2)

       // where m = slope = (y3-y2)/(x3-x2)

       // calculate slope of line 
        m1 = (Y3-Y2)/(X3-X2);
        // print the slope of line between Coin2 and Coin3 on console
        cout<<"Slope-m1 of line between coins O2 and O3:"<<m1<<endl;
  
       //(y-Y2) = m1*(x-X2);
        // lIne equation
       y = ((m1*x)-(m1*X2))+Y2;  // ---->> equation(1)
       


       // Line equation between p4 and p5 ( Coin Center O4 and O5 ):  (y-y4) = m (x-x4)

       // where m = slope = (y5-y4)/(x5-x4)

       // calculate slope of line
       m2 = (Y5-Y4)/(X5-X4);
       // print the slope of line between Coin4 and Coin5 on console
       cout<<"Slope-m2 of line between coins O4 and O5: "<<m2<<endl;
       
       //(y-Y4) = m2*(x-X4);
       // line equation
       y = ((m2*x)-(m2*X4))+Y4;  //------>> equation(2)
       

    // ########################################################################################################
    //                               STAGE 5 : INTERSECTION POINT OF LINES
    // ########################################################################################################


       // calculating the intersection (x,y) of lines: eqation(1) and (2)
       //m1*x-m1*X2 +Y2 = m2*x -m2*X4 +Y4;
       //(m1-m2)*x = m1*X2 - m2*X4 -Y2 +Y4;
  
       // calculate x value. 
       x = ((m1*X2)-(m2*X4)-Y2 +Y4) / (m1-m2);
        
        // put the x value in equation(2) and find y value
       y = ((m2*x)-(m2*X4)) + Y4;
      
        
       // Now intersection point of this two line = (x,y) 
       cout<<"Intersection point of coin circle (O2-O3) and (O4-O5) - two lines is : (x,y) = "<<"("<<x<<","<<y<<")"<<endl;

       // Draw the Intersection point on the clone image for reference
       circle( cimg, Point(1089,1639), 2, Scalar(255, 255, 255), 40);
       // named intersection point as "C"
       putText(cimg, "C" ,Point(950,1600), FONT_HERSHEY_COMPLEX, 3, Scalar(255,255,255), 3);
       
      

    // #########################################################################################################
    //                           STAGE 6: DISTANCE BETWEEN INTERSECTION POINT AND COIN1 CENTER
    // ######################################################################################################### 

      
       // Now use from Pythagorean theorem for find out the distance between C ( Intersection point) and coint O1 center(p1).
      
       // p1 = (X1,Y1)  and C = (x,y)
       // distance = sqrt((x-X1)**2 + (y-Y1)**2)

       // Draw the line between intersection point and coin1 Center 
       line(cimg, p1, Point(x,y), cv::Scalar(0,255,0), 5);  
       
 
       // Calculate the  distance 
       distance = sqrt(pow(x - X1, 2) + pow(y - Y1, 2) * 1.0);
       // print the distance on console.
       cout<<"Distance between intersection point (C) and Coin1 centre Point (p1) = "<<distance<<endl;

   
    // #########################################################################################################
    //                                STAGE 7: DISPLAY AND SAVE RESULT
    // ######################################################################################################### 
       
      // Resize the image for visibility on your computer screen


      //resize(imgBlurred,imgBlurred,Size(480,640));    
      //resize(imgGrayscale,imgGrayscale,Size(480,640));
      //resize(thresh,thresh,Size(480,640));
      //resize(erode_img,erode_img,Size(480,640));
      //resize(dilate_img,dilate_img,Size(480,640));
      //resize( adp_thresh, adp_thresh,Size(480,640));
      //resize(imgBlurred2,imgBlurred2,Size(480,640));
      
      resize(cimg,cimg,Size(480,640));
     
      // Disply the image
    
      //imshow("imgBlurred",imgBlurred); 
      //imshow("imgGrayscale",imgGrayscale);
      //imshow("thresh",thresh);
      //imshow("erode_img",erode_img);
      //imshow("dilate_img ",dilate_img);
      //imshow("adp_thresh",adp_thresh);
      //imshow("imgBlurred2",imgBlurred2);
      
      imshow( "cimg",cimg );

      
      // Save the output image
      
      imwrite("cimg.jpg",cimg);
  

      waitKey(0); // Wait for infinite time for a key press.

  return 0;    // Return from main function.
}