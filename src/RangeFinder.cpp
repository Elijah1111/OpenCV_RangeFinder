/*
 * RangeFinder.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: Elijah Mt. Castle
 */
#include "RangeFinder.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Constructor Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RangeFinder::RangeFinder() {//Default Constructor
	Mat src;
	src = imread("src.jpg");//read the image
	if(!src.data )//Can you read the image?
	{
		std::printf( "No image data \n" );
		std::exit(-1);
	}
	_src=src;
	_FOCAL=8377.6;// pixels/inch
	_width=30;
}



RangeFinder::RangeFinder(std::string path, double focal,double width){//Parameter Constructor
	Mat src;
	src = imread(path);//read the image
	if(!src.data )//Can you read the image?
	{
		std::printf( "No image data \n" );
		std::exit(-1);
	}

	_src=src;
	_FOCAL=focal;// pixels/inch
	_width=width;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Constructor Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



void RangeFinder::Show(Mat img,std::string title){//shows the images scaled down to load faster
	Size size(500,700);//the dst image size,e.g.100x100
	resize(img,img,size);//resize image
	imshow( title, img );
}



Mat RangeFinder::Clean(){//returns image with some thresholding and blurring
	Mat grey;


	cvtColor(_src, grey, CV_BGR2GRAY );//convert to greyscale
	threshold(grey,grey,75, 0 ,THRESH_TOZERO);//sets anything under 75 intensity to zero
	GaussianBlur( grey, grey, Size( 5, 5 ), 0, 0 );//blurs out the noise
	threshold(grey,grey,75, 0 ,THRESH_TOZERO);//re-threshold

	return grey;
}



void RangeFinder::Distance(){//finds distance

	Mat grey;
	grey=Clean();


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int maxPosn=0,minPosn=0;

	int i,j,tmp=0,cols=grey.cols,rows=grey.rows;

	int max=-256*cols,min=256*cols;//sets to be larger then max/min value * columns

	int intergal[cols+1]={0}, diffInt[cols+1];
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Find Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for(i = 2; i < cols; i++){//gets x values
		for(j = 30; j < rows; j++){//Gets y values
			tmp = (int)((grey).at<uchar>(j,i));//grabs intensity values then converts from a unsigned character array to an integer
			intergal[i] += tmp;//adds all of the pixels in the columns
		}

		diffInt[i] = intergal[i]-intergal[i-1]; //store the slope of the image. ie. the change in one row to the previous row.
	}

	for(i = 3; i < cols; i++){//Find the minimum position and the maximum position.
		tmp = diffInt[i];

		if(tmp > max){
			max=tmp;
			maxPosn=i;
		}

		if(tmp < min){
			min = tmp;
			minPosn = i;
		}
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Find Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Draw Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	rectangle(_src,
			Point(minPosn , rows/4),Point(maxPosn , rows),
			Scalar(255,0,0),10);//draws a rectangle around the object

	rectangle(grey,
			Point(minPosn,rows/4),Point(maxPosn,rows),
			Scalar(255,255,255),10);//draws a rectangle around the object

	Show(_src,"Found");//draws the source
	Show(grey,"Grey Scale Found");//draws the grey image
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Draw Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	_dist= (_FOCAL*_width) / (minPosn-maxPosn);//calculate distance

	/*	F=(P x D) / W
	 *
	 *	F = Focal length
	 *	P = Apparent width in pixels
	 *	D = Distance
	 *	W = Actual width
	 *
	 *
	 */
}



void RangeFinder::focalFind(){//finds the focal in pixels/inch

	Mat grey;
	grey=Clean();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int maxPosn=0,minPosn=0;

	int i,j,tmp=0,cols=grey.cols,rows=grey.rows;

	int max=-256*cols,min=256*cols;//sets to be larger then max/min value * columns

	int intergal[cols+1]={0}, diffInt[cols+1];
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Find Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for(i = 2; i < cols; i++){//gets x values
		for(j = 30; j < rows; j++){//Gets y values
			tmp = (int)((grey).at<uchar>(j,i));//grabs intensity values then converts from a unsigned character array to an integer
			intergal[i] += tmp;//adds all of the pixels in the columns
		}

		diffInt[i] = intergal[i]-intergal[i-1]; //store the slope of the image. ie. the change in one row to the previous row.
	}

	for(i = 3; i < cols; i++){//Find the minimum position and the maximum position.
		tmp = diffInt[i];

		if(tmp > max){
			max=tmp;
			maxPosn=i;
		}

		if(tmp < min){
			min = tmp;
			minPosn = i;
		}
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Find Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Draw Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	rectangle(_src,
			Point(minPosn , rows/4),Point(maxPosn , rows),
			Scalar(255,0,0),10);//draws a rectangle around the object

	rectangle(grey,
			Point(minPosn,rows/4),Point(maxPosn,rows),
			Scalar(255,255,255),10);//draws a rectangle around the object

	Show(_src,"Found");//draws the source
	Show(grey,"Grey Scale Found");//draws the grey image
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Draw Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	_FOCAL=((minPosn-maxPosn)*_dist)/_width;
	/*	F=(P x D) / W
	 *
	 *	F = Focal length
	 *	P = Apparent width in pixels
	 *	D = Distance
	 *	W = Actual width
	 *
	 *
	 */

	std::cout<<"FOCAL IS: "<<_FOCAL<<std::endl;
}



RangeFinder::RangeFinder(bool dev,std::string path, double dist, double width){//Dev Constructor

	std::cout<<"DEV MODE! FIND FOCAL LENGTH!"<<std::endl<<"This will have varying results use at your own risk!"<<std::endl;
	Mat src;

	src = imread(path);
	if(!src.data )//Can you read the image?
	{
		std::printf( "No image data \n" );
		std::exit(-1);
	}

	_src=src;
	_width=width;
	_dist=dist;

	focalFind();//finds the Focal in pixels/in
}



void RangeFinder::Begin(){//starts the process

	Show(_src,"Original");
	Distance();//finds the distance

}



double RangeFinder::getDistance()const{//returns distance

	return _dist;

}

