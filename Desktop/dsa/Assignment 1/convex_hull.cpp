#include<iostream>
#include"quickSortmod.hpp"
using namespace std;

struct point{

	float x, y;
} A[8];

bool operator < (point A1, point A2){

	float y1 = A1.y;
	float y2 = A2.y;
	float x1 = A1.x;
	float x2 = A2.x;

	float c = x1*x2 + y1*y2;
	float s = x1*y2 - x2*y1;

	if(c > 0.0){
		if(s > 0.0) return true;
		else return false;
	}
	else{
		if(s > 0.0) return false;
		else return true;	
	}
}

bool valid(int i, int j){
	float y2 = A[i].y - A[j].y;
	float y1 = A[j].y - A[j-1].y;
	float x2 = A[i].x - A[j].x;
	float x1 = A[j].x - A[j-1].x;

	float c = x1*x2 + y1*y2;
	float s = x1*y2 - x2*y1;

	if(c > 0.0){
		if(s > 0.0) return false;
		else return true;
	}
	else{
		if(s > 0.0) return true;
		else return false;	
	}
}

void findLowest(const int n){
	float min = A[0].y;
	int min_index = 0;
	for(int i = 0; i < n; i++){
		if(A[i].y < min){
			min = A[i].y;
			min_index = i;
		}
	}
	point temp = A[min_index];
	A[min_index] = A[n-1];
	A[n-1] = temp;
}

void grahamScan(const int n){
	
	findLowest(n);
	quickSort<point>(A, n-1);

	int iter = 1;
	point *hullBuffer = new point[n];
	hullBuffer[0] = A[0];
	hullBuffer[1] = A[1];
	for(int i = 2; i < n-1; i++){		
		while (iter >= 0){
			if( valid(i, iter) ){
				iter++;
				hullBuffer[iter] = A[i];
				break;
			}
			iter--;
		}
	}
	hullBuffer[iter+1] = A[n-1];
	for(int i = 0; i < iter+2; i++){
		cout<<"("<<hullBuffer[i].x<<", "<<hullBuffer[i].y<<")"<<endl;
	}
}

int main(){
	
	A[0].x = 5.0; A[0].y = 1.0;
	A[1].x = 3.0; A[1].y = 4.0;
	A[2].x = 0.0; A[2].y = 2.0;
	A[3].x = 1.0; A[3].y = 1.0;
	A[4].x = 0.5; A[4].y = 5.0;
	A[5].x = 2.0; A[5].y = 0.5;
	A[6].x = 3.0; A[6].y = 3.0;
	A[7].x = 0.0; A[7].y = 0.0; 

	grahamScan(8);		
	return 0;
}
