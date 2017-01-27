#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>
#include <time.h>
#include <iomanip>

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
		
		else return nil;

	}
	else{				//parallel case

		float par1 = a1.x - b1.x;
		float par2 = a1.y - b1.y;
	/*	if(det(par1, detax, par2, detay) == 0){
			if(dist(a1, b1) + dist(a1, b2) == dist(b1, b2) || dist(a2, b1) + dist(a2, b2) == dist(b1, b2)){
				
			}
			if(dist(a1, b1) + dist(a1, b2) == dist(b1, b2)){
				if(dist(a2, b1) + dist(a2, b2) == dist(b1, b2) && dist(a2, b1) > dist(a1, b1)) return a2;
				else return a1;
			}
		}*/
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

bool findOverlapPoly(polygon A, polygon B){ //, std::vector<point>& overlapped){

	std::list<point>::iterator itA, itB, itAnext, itBnext, itAprev, itBprev, itAc, itBc, itAcnext,itBcnext;

	std::list<point> overlapped;

	A.cor.push_back(*(A.cor.begin()));
	B.cor.push_back(*(B.cor.begin()));

	return true;
}

float centroidDist(polygon A, polygon B){

	std::list<point>::iterator it;
	int lengthA = 0, lengthB = 0;
	float Axcentroid = 0, Aycentroid = 0, Bxcentroid = 0, Bycentroid = 0;
	for(it = A.cor.begin(); it != A.cor.end(); it++){
		lengthA++;
		Axcentroid = Axcentroid + it->x;
		Aycentroid = Aycentroid + it->y;
	}

	for(it = B.cor.begin(); it != B.cor.end(); it++){
		lengthB++;
		Bxcentroid = Bxcentroid + it->x;
		Bycentroid = Bycentroid + it->y;
	}

	Axcentroid = Axcentroid/lengthA;
	Aycentroid = Aycentroid/lengthA;
	Bxcentroid = Bxcentroid/lengthB;
	Bycentroid = Bycentroid/lengthB;

	return sqrt(pow(Axcentroid-Bxcentroid, 2) + pow(Aycentroid-Bycentroid, 2));
}

float findMin(float a, float b){

	if (b == -1 || a < b) return a;
	else return b;
}


bool isBadPoly(int* arr, int len){

//std::cout<<"called"<<std::endl;
	if(len < 6 || len > 40 || len%2 != 0) return true;
//std::cout<<len<<std::endl;

	
	point p1, p2, p3, p4;

	for(int i = 4; i < len; i += 2){

		int j;

		p3.x = arr[i];
		p3.y = arr[i+1];
		if(i != len-2){
			p4.x = arr[i+2];
			p4.y = arr[i+3];
			j = 0;
		}
		else {p4.x = arr[0]; p4.y = arr[1]; j = 2;}		
		for(; j < i-2; j+=2){
			p1.x = arr[j];
			p1.y = arr[j+1];
			p2.x = arr[j+2];
			p2.y = arr[j+3];
			
			if(p3.x < 0 || p3.y < 0 || p4.x < 0 || p4.y < 0) return true; 
//			std::cout<<"("<< i<<", "<<j<<std::endl;
			point intersect = intersection(p1, p2, p3, p4);
			if(intersect.x != -1) return true;
		}
	}
//std::cout<<"dsv"<<std::endl;
	return false;
}

int main(){

//	std::cout<<"BAD "<< 3 <<std::endl;
//	return 0;
	clock_t t1,t2;
	
	std::ifstream inFile;
	inFile.open("input2.txt");

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
		int j = 0, arr[400];
		while(iss >> arr[j]) j++;

		if(!isBadPoly(arr, j)){
			tmp = new polygon(j/2, arr);
			p.push_back(*tmp);
			i++;
		}
		else break;
	}

	if(n != i){
		i++;
		std::cout<<"BAD "<<i<<std::endl;
		return 0;
	}

	int iter = 1, cumulative = 0;
	float distance[n];
	std::fill_n(distance, n,  -1);

	distance[0] = 0;
	for(int g = 0; g < n; g++){
		for(int h = 0; h < g; h++){

			if(findOverlapPoly(p[g], p[h])){

				distance[g] = findMin(distance[h] + centroidDist(p[h], p[g]), distance[g]);
			}
		}
		if(distance[g] == -1){
			std::cout<<"DISCONNECTED "<< ++g <<std::endl;
			return 0;
		}
	}

	std::cout<<"CONNECTED"<<std::endl;
	for(int g = 1; g < n; g++){
		std::cout << std::fixed << std::setprecision(2) << distance[g] <<std::endl;
	}

    //	int avg = cumulative/iter;
  //  	std::cout<<avg<<" microseconds"<<std::endl;
//	std::cout<<value<<std::endl;


	t1 = clock();
	t2 = clock();
	cumulative = cumulative + t2-t1;


//	std::list<point>::iterator it;
//	int k = 3;
//	for(it = p[k].cor.begin(); it != p[k].cor.end(); it++){
//		std::cout<<"("<<it->x<<", "<<it->y<<")"<<std::endl;
//	}

	return 0;
}
