#include <opencv2/opencv.hpp>
#include <iostream>
#include "RangeFinder.h"

using namespace cv;
using namespace std;
int main()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Input Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	string dum;//made it a string to help prevent over-typing

	cout<<"Would you like to use the included images? Y/N: ";

	cin>>dum;
	cin.clear();
	cin.sync();

	cout<<"Press any button inside the image files to close them all."<<endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Input Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Default Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(dum=="Y"||dum=="y"){

		RangeFinder range;
		range.Begin();
		cout<<fixed<<setprecision(2)<<range.getDistance()<<" inches from the object"<<endl;

	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Default Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Dev Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	else if(dum=="z"){//Dev Mode Finds the Focal Length
		string path;
		double dist,width;
		cout<<"Please specify your path to an image include the extension: ";
		cin>>path;

		dist=-1;
		cout<<"Please enter the distance from the object in inches: ";
		while(dist<0){
			while(!(cin >> dist)){
				cin.clear();
				cin.sync();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input.  Try again: ";
				dist=-1;
				continue;
			}
			if(dist<0){
				cout<<"Positive number please: ";
			}
		}

		width=-1;

		cout<<"Please enter the actual width of the object in inches: ";
		while(width<0){
			while(!(cin >> width)){

				cin.clear();
				cin.sync();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input.  Try again: ";
				width=-1;
				continue;
			}
			if(width<0){
				cout<<"Positive number please: ";
			}
		}



		RangeFinder range(true,path,dist,width);
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Dev Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DIY Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	else{


		string path;
		double focal,width;
		cout<<"Please specify your path to an image include the extension: ";
		cin>>path;



		focal=-1;

		cout<<"Please enter the focal length (pixels per inch) used to capture the image: ";
		while(focal<0){
			while(!(cin >> focal)){//gets and validates the focal length

				cin.clear();
				cin.sync();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input.  Try again: ";
				focal=-1;
				continue;
			}
			if(focal<0){
				cout<<"Positive number please: ";
			}
		}


		width=-1;
		cout<<"Please enter the actual width of the object in inches: ";
		while(width<0){
			while(!(cin >> width)){//gets and validates the width

				cin.clear();
				cin.sync();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input.  Try again: ";
				width=-1;
				continue;
			}
			if(width<0){
				cout<<"Positive number please: ";
			}
		}


		RangeFinder range(path,focal,width);
		range.Begin();
		cout<<fixed<<setprecision(2)<<range.getDistance()<<" inches from the object"<<endl;


	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DIY Zone~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	waitKey(0);//wait for a key press to continue



	return 0;

}
