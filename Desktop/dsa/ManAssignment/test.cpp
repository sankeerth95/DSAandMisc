#include<iostream>
#include <map>
#include <utility>

using namespace std;

typedef map<string, float> resistance;

resistance m;


void insert_to_map(int u, int v, float R){

	string x; to_string(u) + "," + to_string(v);
	string y = to_string(v) + "," + to_string(u);

	m[x] = R;
	m[y] = R;
}

float get_from_map(int u, int v){

	string x = to_string(u) + "," + to_string(v);
	if(m.find(x) != m.end()) return m[x];
	else return -1;
}

void erase_from_map(int u, int v){

	string x = to_string(u) + "," + to_string(v);
	string y = to_string(v) + "," + to_string(u);
	m.erase(x);
	m.erase(y);
}


int main(){


insert_to_map(3, 4, 34);
insert_to_map(3, 4, 340);
insert_to_map(2, 4, 24);
insert_to_map(5, 4, 54);
erase_from_map(5, 4);
insert_to_map(4, 5, 3);
erase_from_map(2, 4);
insert_to_map(3, 4, 50);

float X = get_from_map(3, 4);
cout<<X<<endl;
	

	return 0;
}

//g++ -DEVAL -static -O2 -std=c++11 -o MA1 MA1.cpp
