#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>

struct point{

	float x, y;
//	point* crossLink;
	std::list<point>::iterator crossLink;
	bool isIntersect;
};

class polygon{
	public:	
	std::list<point> cor;	//coordinates
	int size;
	bool designate;

	polygon(const int n, int* arr){
		size = n;
		point temp;
		for(int i = 0; i < n; i++){
			temp.x = arr[2*i];
			temp.y = arr[2*i+1];
			temp.isIntersect = false;
			cor.push_back(temp);
			designate = false;
		}
	}
};

float findArea(polygon X){

	point a;
	return 1.0;
}

float det(point a, point b){

	float x1 = a.x;
	float y1 = a.y;
	float x2 = b.x;
	float y2 = b.y;

	return (x1*y2 - x2*y1);
}

float det(float x1, float x2, float y1, float y2){

	return (x1*y2 - x2*y1);
}

float cross(point a, point b){

	return (a.x*b.y - a.y*b.x);
}

point intersection(point a1, point a2, point b1, point b2){

	point temp;
	point nil;
	nil.x = nil.y = -1.0;
	
	if(a1.x == b1.x && a1.y == b1.y) return a1;
	if(a1.x == b2.x && a1.y == b2.y) return a1;
	if(a2.x == b1.x && a2.y == b1.y) return a2;
	if(a2.x == b2.x && a2.y == b2.y) return a2;

	float deta12 = det(a1, a2);
	float detb12 = det(b1, b2);
	float detax = a1.x - a2.x;
	float detay = a1.y - a2.y;
	float detbx = b1.x - b2.x;
	float detby = b1.y - b2.y;

	//int dotProduct = detax;

	float discriminant = det(detax, detay, detbx, detby);
	if (discriminant != 0){
		temp.x =  det(deta12, detb12, detax, detbx)/discriminant;
		temp.y =  det(deta12, detb12, detay, detby)/discriminant;

		float dotproduct1 = (temp.x-a1.x)*(temp.x-a2.x) + (temp.y-a1.y)*(temp.y-a2.y);
		float dotproduct2 = (temp.x-b1.x)*(temp.x-b2.x) + (temp.y-b1.y)*(temp.y-b2.y); 
		
		if(dotproduct1 <= -0 && dotproduct2 <= -0) return temp;
		
	//	else if(((temp.x == a2.x && temp.y == a2.y) ||(temp.x == b2.x && temp.y == b2.y) )&& !replace ) return temp;		//intersection-is-vertex case

		else return nil;

	}
	else{				//parallel case

		return nil;
	}
}

bool isValid(point intersect, std::list<point>::iterator Abegin, std::list<point>::iterator Aend,
						std::list<point>::iterator Bbegin, std::list<point>::iterator Bend, 
						std::list<point>::iterator itA, std::list<point>::iterator itB){

	std::list<point>::iterator itBnext = ++itB;
	std::list<point>::iterator itAnext = ++itA;
	itA--;itB--;

	point a1 = *itA;
	point a2 = *itAnext;
	point b1 = *itB;
	point b2 = *itBnext;

//	if(itA->crossLink == itB || itAnext->crossLink == itB || itA->crossLink == itBnext || itA->crossLink == itBnext) return false;

	if(intersect.x != -1){

	/*	bool inA = (intersect.x == a2.x && intersect.y == a2.y);
		bool inB = (intersect.x == b2.x && intersect.y == b2.y);
		
		bool special = false;	
		if(inA){
			++itA;++itA;
			if(itA != Aend) a2 = *itA;
			else a2 = *Abegin;
			itA--;itA--;
			special = true;
		}

		if(inB){
			++itB;++itB;
			if(itB != Bend) point b2 = *itB;
			else b2 = *Bbegin;
			itB--;itB--;
			special = true;
		}

	
		if(special == true){
			a2.x = a2.x - intersect.x;
			a2.y = a2.y - intersect.y;
			a1.x = a1.x - intersect.x;
			a1.y = a1.y - intersect.y;

			b2.x = b2.x - intersect.x;
			b2.y = b2.y - intersect.y;
			b1.x = b1.x - intersect.x;
			b1.y = b1.y - intersect.y;

			bool insideb1 = (cross(a1, b1) > 0 && cross(b1, a2) > 0)||(cross(a1, b2) < 0 && cross(b2, a2) < 0);
			bool insideb2 = (cross(a1, b2) > 0 && cross(b2, a2) > 0)||(cross(a1, b1) < 0 && cross(b1, a2) < 0);
	
			if(insideb1 || insideb2) return true;
			else return false;
		}
	*/
		return true;

	}
	else return false;
}



void printPolygon(polygon p){

	std::list<point>::iterator it;

	for(it = p.cor.begin(); it != p.cor.end(); it++)
	std::cout<<"Polygon: "<<"("<<it->x<<", "<<it->y<<")\t"<< it->isIntersect <<std::endl;
	std::cout<<std::endl;
}

void printPolygon(std::list<point> p){

	std::list<point>::iterator it;

	for(it = p.begin(); it != p.end(); it++)
	std::cout<<"Polygon: "<<"("<<it->x<<", "<<it->y<<")\t"<< it->isIntersect <<std::endl;
	std::cout<<std::endl;

}

float dist(point A, point B){

	float xdist = A.x - B.x;
	float ydist = A.y - B.y;

	if(xdist < 0) xdist = -xdist;
	if(ydist < 0) ydist = -ydist;

	return xdist + ydist;

}

void findOverlapPoly(polygon A, polygon B){ //, std::vector<point>& overlapped){

	std::list<point>::iterator itA, itB, itAnext, itBnext, itAprev, itBprev, itAc, itBc, itAcnext,itBcnext;
	
	std::list<point> overlapped;

	A.cor.push_back(*(A.cor.begin()));
	B.cor.push_back(*(B.cor.begin()));

	polygon Acopy = A, Bcopy = B;
	itAcnext = ++Acopy.cor.begin();	
//	itAcnext = ++itAc;
//	itBcnext = ++itBc;


	itAnext = A.cor.begin();
	itA = itAnext++;
	for(; itAnext != A.cor.end(); itA++){

		itBnext = B.cor.begin();
		itB = itBnext++;

		itBcnext = Bcopy.cor.begin();

		//itBcnext++;
		for(; itBnext != B.cor.end(); itB++){

			itBcnext++;
			while(itBcnext->isIntersect) {itBcnext++; std::cout<<"itBcnext changed to"<<std::endl;}
			std::cout<<"itBcnext: "<<"("<< (itBcnext)->x <<", "<<(itBcnext)->y<<")" <<std::endl;
			std::cout<<itBcnext->isIntersect<<std::endl;

			std::cout<<"Points Considered: A-> "<<"("<<itA->x<<", "<<itA->y<<") AND "<<"("<<itAnext->x<<", "<<itAnext->y<<")"<<std::endl;
			std::cout<<"Points Considered: B-> "<<"("<<itB->x<<", "<<itB->y<<") AND "<<"("<<itBnext->x<<", "<<itBnext->y<<")"<<std::endl;

			std::cout<<std::endl;
//			std::cout<<"("<<intersect.x<<", "<<intersect.y<<")"<<std::endl;


			point intersect = intersection(*itA, *(itAnext), *itB, *(itBnext));
			if(isValid(intersect, A.cor.begin(), A.cor.end(), B.cor.begin(), B.cor.end(), itA, itB)){		//guidance go
				
				std::cout<<"Found point between "<<std::endl;
				std::cout<<"("<<intersect.x<<", "<<intersect.y<<")"<<std::endl;

				Acopy.cor.insert(itAcnext, intersect);
				Bcopy.cor.insert(itBcnext, intersect);

				std::list<point>::iterator itAtemp = --itAcnext, itAint = itAtemp;
				std::list<point>::iterator itBtemp = --itBcnext, itBint = itBtemp;
				itAcnext++;
				itBcnext++;


				printPolygon(Bcopy);

				while(dist(*(--itAtemp), *itAcnext) < dist(*itAint ,*itAcnext)){
					Acopy.cor.insert(itAtemp, *itAint);
					Acopy.cor.erase(itAint);
					itAint = --itAtemp;
				}

				while(dist(*(--itBtemp), *itBcnext) < dist(*itBint ,*itBcnext)){

					std::cout<<"itInt: "<<"("<< itBcnext->x <<", "<<itBcnext->y<<")" <<std::endl;;
					std::cout<<"dist: "<< dist(*itBtemp, *itBcnext)<<", "<<dist(*itBint,*itBcnext)<<std::endl;
					Bcopy.cor.insert(itBtemp, *itBint);
					Bcopy.cor.erase(itBint);
					itBint = --itBtemp;
				}

				
				itAint->crossLink = itBint;
				itBint->crossLink = itAint;
				itAint->isIntersect = true;
				itBint->isIntersect = true;
				
				overlapped.push_back(intersect);
				itAprev = itA;
				itBprev = itB;

				printPolygon(Bcopy);
			//	itBnext++;itB++;

			}
			itBnext++;
			
		}

		itAnext++;
		itAcnext++;
	}

	A.cor.pop_front();
	A.cor.push_back(*(--A.cor.end()));
	A.cor.pop_back();

	B.cor.pop_front();
	B.cor.push_back(*(--B.cor.end()));
	B.cor.pop_back();

	Acopy.cor.pop_front();
	Acopy.cor.push_back(*(--A.cor.end()));
	Acopy.cor.pop_back();

	Bcopy.cor.pop_front();
	Bcopy.cor.push_back(*(--B.cor.end()));
	Bcopy.cor.pop_back();

	
	std::cout<<"Polygon A:- "<<std::endl;
	printPolygon(Acopy);
	std::cout<<"Polygon B:- "<<std::endl;
	printPolygon(Bcopy);

	std::cout<<"points of intersection: "<< std::endl;
	printPolygon(overlapped);

	std::list<point>::iterator it = A.cor.begin(), itInitial;
/*
	for(itA = A.cor.begin(); itA != A.cor.end(); itA++){
		if(itA->x < it->x) it = itA;
	}

	std::list<point>::iterator itnext;
	itnext = overlapped.begin();
	itnext++;
//	
	
	while (!overlapped.empty()){
		
		while(!it->isIntersect){
			it++;
			if(it == A.cor.end()) it = A.cor.begin();
		}

		itInitial = it;
		itInitial->crossLink->isIntersect = false;
		itInitial->isIntersect = false;
		it++;
		if(it == A.cor.end()) it = A.cor.begin();
	
		std::list<point> clip;
		clip.push_back(*itInitial);
		overlapped.pop_back();

		
		while((it->x != itInitial->x) || (it->y != itInitial->y)){
	
			clip.push_back(*it);
			//std::cout<<it->isIntersect<<std::endl;
			if(it->isIntersect){
				it->isIntersect = false;
				it = it->crossLink;
				it->isIntersect = false;
				overlapped.pop_back();
			}
			
			it++;
			if(it == A.cor.end()) it = A.cor.begin();
			if(it == B.cor.end()) it = B.cor.begin();

		}
			std::cout<<"polygon C is :-"<< std::endl;
			printPolygon(clip);
	}

*/
}

bool isBadPoly(int* arr, int len){

	if(len < 6) return true;

	for(int i = 6; i<len; i = i+2){
		
//		point intersect = 

	}

	return false;
}

int main(){

	clock_t t1,t2;

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

	std::getline(inFile, line);
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

	int iter = 1, cumulative = 0;
	for(int i = 0; i < iter; i++){
		t1 = clock();
		findOverlapPoly(p[2], p[3]);
		t2 = clock();
		cumulative = cumulative + t2-t1;
	}
    	int avg = cumulative/iter;
    	std::cout<<avg<<" microseconds"<<std::endl;


//	std::list<point>::iterator it;
//	int k = 3;
//	for(it = p[k].cor.begin(); it != p[k].cor.end(); it++){
//		std::cout<<"("<<it->x<<", "<<it->y<<")"<<std::endl;
//	}

	return 0;
}

