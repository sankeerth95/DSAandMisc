#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

struct point{

	int x, y;
//	point* crossLink;
	bool isIntersect;
	std::list<point>::iterator crossLink;
};


class polygon{
	public:	
	std::list<point> cor;	//coordinates
	int size;
	bool designate;
	
	polygon(const int n, int* arr){
		size = n;
		point temp;
		for(int i = 0; i < n; i+=1){
			temp.x = arr[2*i];
			temp.y = arr[2*i+1];
			cor.push_back(temp);
			designate = false;
		}
	}
};

point intersection(point a1, point a2, point b1, point b2){

	point temp;
	point one;
	one.x = 1; one.y =1;

	//temp.x = det(a1, one)/;		//put clever formula(derived)

	
	return temp;
}

bool isValid(point intersect){

	if(intersect.x != -1) return true;
	else return false;
}


void findOverlapPoly(polygon A, polygon B){ //, std::vector<point>& overlapped){

	std::list<point>::iterator itA, itB, itAnext, itBnext;
	itAnext = A.cor.begin();
	itA = itAnext++;
	itBnext = B.cor.begin();
	itB = itBnext++;

	for(; itAnext != A.cor.end(); itA++){
		itAnext++;
		for(; itBnext != B.cor.end(); itB++){
			itBnext++;
			point intersect = intersection(*itA, *(itAnext), *itB, *(itBnext));
			if(isValid(intersect)){
				A.cor.insert(itA, intersect);
				B.cor.insert(itB, intersect);
				itA->crossLink = itB;
				itB->crossLink = itA;
			}
		}
	}
/*
	std::list<point>::iterator next, start;
	for(itA = A.cor.begin(); (itA+1) != A.cor.end(); itA++){

		if(itA->isIntersect){
			itB = itA->crossLink;
			float y0 = (itA+1)->y - itA->y;			// source of segmentation error
			float x0 = (itA+1)->x - itA->x;
			
			float y1 = (itB+1)->y - itA->y;			// source of segmentation error
			float x1 = (itB+1)->x - itA->x;

			if(y0*x1 - x0*y1 < 0){				//if clockwise
				next = itB+1;
				start = itB;
			}		
			else{ 
				next = itA+1;
				start = itA;
			}
			break;
		}
	}
	
	//bool inside;

	std::list<point> overlapped;
	overlapped.push_back(*start);

	std::list<point>::iterator it = next;
	while(it != start){
		overlapped.push_back(*it);
		if((++it)->isIntersect) it = it->crossLink;		//segmentation warning
	}

*/
}



bool isBadPoly(int* arr, int j){
	return false;
}


int main(){
	
	std::ifstream inFile;
	inFile.open("input.txt");

	if(inFile.fail()){
		std::cout<<"Error Opening File"<< std::endl;	
	}

	int n, i = 0;

	inFile >> n;
	
	std::vector<polygon> p;
	polygon* tmp;
	std::string line;
	while(std::getline(inFile, line)){

		std::istringstream iss(line);
		int j = 0, arr[40];
		while(iss >> arr[j]) j++;
		
		if(j%2 == 0 && !isBadPoly(arr, j)){
			tmp = new polygon(j/2, arr);
			p.push_back(*tmp);
			i++;
		}
	}

	n = i;

	return 0;
}
