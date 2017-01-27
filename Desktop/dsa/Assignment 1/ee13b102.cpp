#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>
#include <iomanip>

struct pair{

	float x, y;
};

struct point{

	int x, y;

};

class polygon{
	public:
	std::list<point> cor;	//coordinates

	polygon(const int n, int* arr){

		point temp;
		for(int i = 0; i < n; i++){
			temp.x = arr[2*i];
			temp.y = arr[2*i+1];
			cor.push_back(temp);
			
		}
	}
};

int det(point a, point b){

	int x1 = a.x;
	int y1 = a.y;
	int x2 = b.x;
	int y2 = b.y;

	return (x1*y2 - x2*y1);
}

float det(pair a, pair b){

	int x1 = a.x;
	int y1 = a.y;
	int x2 = b.x;
	int y2 = b.y;

	return (x1*y2 - x2*y1);
}

int det(int x1, int x2, int y1, int y2){

	return (x1*y2 - x2*y1);
}

pair intersection(point a1, point a2, point b1, point b2){

	pair temp;
	pair nil;
	nil.x = nil.y = -1;

	int deta12 = det(a1, a2);
	int detb12 = det(b1, b2);
	int detax = a1.x - a2.x;
	int detay = a1.y - a2.y;
	int detbx = b1.x - b2.x;
	int detby = b1.y - b2.y;

	int discriminant = det(detax, detay, detbx, detby);

	if (discriminant != 0){

		pair temp1, temp2;
		temp1.x = a1.x; temp1.y = a1.y;
		temp2.x = a2.x; temp2.y = a2.y;
		if(a1.x == b1.x && a1.y == b1.y) return temp1;
		if(a1.x == b2.x && a1.y == b2.y) return temp1;
		if(a2.x == b1.x && a2.y == b1.y) return temp2;
		if(a2.x == b2.x && a2.y == b2.y) return temp2;
	
		temp.x =  (float)det(deta12, detb12, detax, detbx)/discriminant;
		temp.y =  (float)det(deta12, detb12, detay, detby)/discriminant;

		float dotproduct1 = (temp.x-a1.x)*(temp.x-a2.x) + (temp.y-a1.y)*(temp.y-a2.y);
		float dotproduct2 = (temp.x-b1.x)*(temp.x-b2.x) + (temp.y-b1.y)*(temp.y-b2.y); 
		
		if(dotproduct1 <= -0 && dotproduct2 <= -0) return temp;

		else return nil;
	}
	return nil;
}

bool isInside(point K, polygon A){

	point a1, a2;
	a2.x = K.x; a2.y = K.y;
	a1.x = -1; a1.y = K.y;
	int count = 0;
	std::list<point>::iterator itA, itAnext;
//	A.cor.push_back(*(A.cor.begin()));

	float prev;
	bool oncomingFlag = false;

	itAnext = A.cor.begin();
	itA = itAnext++;

	for(; itAnext != A.cor.end(); itA++){

		if(itA->y == K.y && itAnext->y == K.y &&((itA->x <= K.x && itAnext->x >= K.x)||(itA->x >= K.x && itAnext->x <= K.x))) return false;
		pair cuts = intersection(*itA, *itAnext, a1, a2);
		if(cuts.y > -0.5){

			if(itA->y == K.y || itAnext->y == K.y) count++;
			if(K.x == cuts.x) return false;
			count+=2;
		}
		itAnext++;
	}

	if(count%4 == 2) return true;

	return false;
}

void printPolygon(polygon p){

	std::list<point>::iterator it;

	for(it = p.cor.begin(); it != p.cor.end(); it++)
	std::cout<<"Polygon: "<<"("<<it->x<<", "<<it->y<<")\t" <<std::endl;
	std::cout<<std::endl;
}

void printPolygon(std::list<point> p){

	std::list<point>::iterator it;

	for(it = p.begin(); it != p.end(); it++)
	std::cout<<"Polygon: "<<"("<<it->x<<", "<<it->y<<")\t"<<std::endl;
	std::cout<<std::endl;

}

int cross(point a, point b){

	return (a.x*b.y - a.y*b.x);
}


bool findOverlapPoly(polygon A, polygon B){ 

	std::list<point>::iterator itA, itB, itAnext, itBnext;

	std::list<point>::iterator it, itnext, itprev;
	A.cor.push_back(*(A.cor.begin()));
	B.cor.push_back(*(B.cor.begin()));

//std::cout<<"("<<itAnext->x<<", "<<itAnext->y<<")"<<std::endl;

	itAnext = A.cor.begin();
	itA = itAnext++;
	for(; itAnext != A.cor.end(); itA++){

		itBnext = B.cor.begin();
		itB = itBnext++;

		for(; itBnext != B.cor.end(); itB++){

			pair intersect = intersection(*itA, *(itAnext), *itB, *(itBnext));
			int d1 = det(*itA, *itB) + det(*itB, *itBnext) + det(*itBnext, *itA);
			int d2 = det(*itAnext, *itB) + det(*itB, *itBnext) + det(*itBnext, *itAnext);
			int d3 = det(*itBnext, *itA) + det(*itA, *itAnext) + det(*itAnext, *itBnext);
			int d4 = det(*itB, *itA) + det(*itA, *itAnext) + det(*itAnext, *itB);

//			std::cout<<"("<<itA->x<<", "<<itA->y<<") AND ("<<itAnext->x<<", "<<itAnext->y<<")"<<std::endl;
//			std::cout<<"("<<itB->x<<", "<<itB->y<<") AND ("<<itBnext->x<<", "<<itBnext->y<<")"<<std::endl; 
//			std::cout<<d1<<" --- "<<d2<<std::endl<<std::endl;

			bool condition = (intersect.x > -0.5) && (d3 != 0) && (d4 != 0);
			if(condition && d1*d2 < 0) {return true;}	
								
			if(intersect.x > -0.5 && d1 == 0 && d2 != 0){

				if(itA->x == itB->x && itA->y == itB->y){
					if(itB != B.cor.begin()) { it = --itB; itB++; }
					else it = --(--B.cor.end());
					if(d2 < 0){//std::cout<<"FvabviabvjbviaebvoabvA"<<std::endl;
			//			std::cout<<"("<<it->x<<", "<<it->y<<")"<<std::endl;
						point it1, Anext, it2;
						it1.x = it->x - itA->x;
						it1.y = it->y - itA->y;
						Anext.x = itAnext->x - itA->x; 
						Anext.y = itAnext->y - itA->y;
						it2.x = itBnext->x - itA->x;
						it2.y = itBnext->y - itA->y; 
						
			//TO BE COMPLETED: IF ANEXT LIES IN THE MIDDLE, THEN CONSTANTS C1, C2 IN ANEXT = C1*ITB + C2*ITBNEXT ARE POSITIVE.
						bool condition2 = cross(it1, Anext) > 0;
						bool condition3 = cross(Anext, it2) > 0;
						if((cross(it1, it2) < 0) && (condition2 || condition3)) return true;
						if(cross(it1, it2) == 0) return true;
						if((cross(it1, it2) > 0) && condition2 && condition3) return true;
					}
				}
				else if(itA->x == itBnext->x && itA->y == itBnext->y){

			//	std::cout<<"avafvabeabadb"<<std::endl;
					itBnext++;
					if(itBnext != B.cor.end()) it = itBnext;
					else it = ++B.cor.begin();
					itBnext--;
					if(d2 < 0){
			//		std::cout<<"("<<it->x<<", "<<it->y<<")"<<std::endl;

						point it1, Anext, it2;
						it1.x = itB->x - itA->x;
						it1.y = itB->y - itA->y;
						Anext.x = itAnext->x - itA->x; 
						Anext.y = itAnext->y - itA->y;
						it2.x = it->x - itA->x;
						it2.y = it->y - itA->y; 

						bool condition2 = cross(it1, Anext) > 0;
						bool condition3 = cross(Anext, it2) > 0;

						if((cross(it1, it2) < 0) && (condition2 || condition3)) return true;
						if(cross(it1, it2) == 0) return true;
						if((cross(it1, it2) > 0) && condition2 && condition3) return true;
					}

				}
				else if(d2 < 0) return true;
			}

			itBnext++;
		}
		itAnext++;
	}

	
	itAnext = A.cor.begin();
	itA = itAnext++;

	bool strictCondition = true;
	for(; itAnext != A.cor.end(); itA++){

		if(!isInside(*itA, B)){ strictCondition = false; break;}
		itAnext++;
	}
	if(strictCondition) return true;

	return false;

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

bool isBadPoly(int* arr, int len){

	if(len < 6 || len > 40 || len%2 != 0) return true;

	int sum = 0;
	for(int i = 0; i < len-2; i+=2){
//		sum = sum + (arr[i+1] + arr[i+3])*(arr[i+2] - arr[i]);
		sum = sum + det(arr[i], arr[i+1], arr[i+2], arr[i+3]);
	}
	sum = sum + det(arr[len-2], arr[len-1], arr[0], arr[1]);
	if(sum > 0){return true;}

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
			pair intersect = intersection(p1, p2, p3, p4);
			if(intersect.x != -1) return true;
		}
	}


	return false;
}

int main(){

	std::ifstream inFile;
	inFile.open("input.txt");

	if(inFile.fail()){

		return 0;
	}

	int n, i = 0;

	inFile >> n;

	if(n == 1) {std::vector<int> asd; asd[2] = 2;}

	std::vector<polygon> p;
	polygon* tmp;
	std::string line;

	std::getline(inFile, line);
	int arr[100];
	while(std::getline(inFile, line)){

		std::istringstream iss(line), isc(line);
		int j = 0;
		char ch;
		bool condit = true;
		while(isc >> ch) {if(ch != 32 && (ch <= 47 || ch >= 58)) condit = false;}
		while(iss >> arr[j]) j++;

		if(!isBadPoly(arr, j) && condit){
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

//	point a;
//	a.x = 3; a.y = 2;
//	int alp, bet;
//	alp = 0;
//	bet = 2;
//	std::cout<<findOverlapPoly(p[alp], p[bet])<<std::endl;
//	std::cout<<findOverlapPoly(p[bet], p[alp])<<std::endl;
//	std::cout<<isInside(a, p[2])<<std::endl;
//	return 0;

	float distance[n][n];

	for(int g = 0; g < n; g++){

		distance[g][g] = 0;
	}

	for(int g = 0; g < n; g++){
		for(int h = 0; h < g; h++){

			if(findOverlapPoly(p[g], p[h]) || findOverlapPoly(p[h], p[g])){

				distance[g][h] = distance[h][g] = centroidDist(p[h], p[g]);
		
			}
			else{
				distance[g][h] = distance[h][g] = -1;
			}
		}
	}

/*
	for(int g = 0; g < n; g++){
		for(int h = 0; h < n; h++){

			std::cout<<distance[g][h]<<"\t";
		
		}
		std::cout<<std::endl;
	}
*/

	float mindist[n];
	std::fill_n(mindist, n, -1);
	bool visited[n];
	std::fill_n(visited, n, false);
	mindist[0] = 0;

	for(int g = 0; g < n; g++){
		int u;
		float min = -1.0;
		for(int v = 0; v < n; v++){
			if( !visited[v] && (mindist[v] < min || min < -0.5) && mindist[v] > -0.5) {u = v; min = mindist[v];}
		}

		visited[u] = true;

		for(int h = 0; h < n; h++){
			if(distance[u][h] > -0.5 && (!visited[h])){
				if((mindist[h] < -0.5) || (mindist[h] > mindist[u] + distance[u][h])){
					mindist[h] = mindist[u] + distance[u][h];
				}
			}
		}
	}
//	for(int g = 0; g < n; g++){
//		for(int h = 0; h < n; h++) {
//			std::cout<<distance[g][h]<<"\t";
//		} std::cout<<std::endl;
//	}
	

	for(int g = 0; g < n; g++){
		if(!visited[g]){
//				std::vector<int> asd; asd[2] = 2;

			std::cout<<"DISCONNECTED "<< ++g <<std::endl;
			return 0;
		}
	}

	std::cout<<"CONNECTED"<<std::endl;
	for(int g = 1; g < n; g++){
		std::cout << std::fixed << std::setprecision(2) << mindist[g] <<std::endl;
	}

	return 0;
}

