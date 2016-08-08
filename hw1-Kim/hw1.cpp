/**
Name: Hyung Jin Kim
Class CSCI445 
HW1  
**/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream myfile;
	ifstream openFile; 
	openFile.open ("input.txt");
	bool init= true; 
	int width, height;
	int input;
	int labelNum=0;

	if (!openFile.is_open()){
		exit(EXIT_FAILURE);
	}

	// geting input from the file for width and height 
	openFile >> input; 
	width = input; 
	openFile >> input; 
	height= input; 
       	int array [width][height]; // input array 
	int linkarray[width][height];
	int labelarray[width][height];
	
	// initalize the 2d array's 
	for(int y=0; y<height; y++){
			cfor(int x=0; x<width ; x++){
		array[x][y]=0;
		linkarray[x][y]=0;
		labelarray[x][y]=0;
		}
	}

	// getting input from the file 
	while (!openFile.eof()){

		for(int y=0; y<height; y++){
			for(int x=0; x<width ; x++){
			 openFile>>array[x][y];
			}
		}
	}  


	//first search 
	for(int y=0; y<height; y++){
	for(int x=0; x<width; x++){

	if(array[x][y]==1){	
	        labelNum++;
		int x1= x-1;
		int y1= y-1;
		int limit = 2; 
		int tempNum=0; 
		bool found =false;
		int limitX=0;
		int limitY=0;
		int iniX =0;
		int iniY =0;

		if(x1<0)
		x1 =0;
		if(y1<0)
		y1 =0; 
		if(x1+2>width-1)
		limit =1;
		if(y1+2>height-1)	
		limit =1;

		
		limitX = x1+limit;
		limitY= y1+limit;
		iniX=x1;
		iniY=y1;

		  for(y1; y1<= limitY; y1++){
			for(x1; x1<= limitX; x1++){
				
			if(labelarray[x1][y1]!=0 && (x1 !=x || y1!=y )){
				if(!found){ //found the first negibor with label
				 labelarray[x][y]=labelarray[x1][y1];
				 found = true;
				 tempNum=labelarray[x1][y1];
				 labelNum--;
				}
				else{	
					
					if(labelarray[x1][y1] != tempNum ){
						
						int a= labelarray[x1][y1];
						if(a>tempNum)
							linkarray[a][tempNum]= tempNum; 
						if(tempNum>a){
							linkarray[tempNum][a]=a;
							tempNum=a;
 							labelarray[x][y]=a;
						}	
					
					}
						
				}
			}
			}
			x1=iniX;
		}
		if(!found){ // if no neighbor was found then assign label number 
			labelarray[x][y] = labelNum;
		}
		
	}
		
		
	}
	}// end of for loop for first pass


//second loop for linking the labels 
for(int y=0; y<height; y++){
	for(int x=0; x<width; x++){
	bool parent = false;
	 if(labelarray[x][y]!=0){
		int a=labelarray[x][y];
		while (!parent){
		
		for (int a1=0; a1< height; a1++){
			if (linkarray[a][a1]!=0){
				a = linkarray[a][a1];
				parent=false; 
				break;
			}
			else {
			parent =true;
			}
		}
		}
	labelarray[x][y]=a;
	}
	}
}

	

//writing to the file 
	myfile.open("output.txt");
	if(myfile.is_open()){
	myfile << width <<" "<<height <<"\n";
	for(int y=0; y<height; y++){
			for(int x=0; x<width ; x++){
			myfile<<labelarray[x][y]<<" ";
			}
			myfile<<"\n";
		}
	myfile.close();
	}
	else cout<< "unable  to  open  file6"<<endl;
return 0; 
}
