#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <queue>

int main(){

	std::ifstream inFile;
	inFile.open("adjList.txt");

	int N;
	
	std::vector<std::list<int>> adjList;
	
	std::string line;
	std::getline(inFile, line);
	std::istringstream iss(line);
	
	iss >> N;

	for(int i = 0; i < N; i++){

		std::getline(inFile, line);

		std::list<int> adjnodes;
		iss.clear();
		iss.str(line);

		int node;
		while(iss >> node) adjnodes.push_back(node);

		adjList.push_back(adjnodes);
	}


	bool bipartite = true;
	bool visited[N];
	for(int i = 0; i < N; i++) visited[i] = false;

	int s = 0;

	std::queue<int> Q;
	Q.push(s);
	visited[s] = true;
	std::list<int>::iterator it;
	int* level = new int[N]; level[s] = 0;
	while(!Q.empty()){
		int present = Q.front();
		Q.pop();

		for(it = adjList[present].begin(); it != adjList[present].end(); it++){

			if(visited[*it] == false) {Q.push(*it); visited[*it] = true; level[*it] = level[present]+1;}
			else if(levels[present]%2 == 0) bipartite = false;
		}
	}

	std::cout<<"levels:"<<std::endl;
	for(int i = 0; i < N; i++) std::cout << level[i] <<std::endl;

	std::cout<<"bipartite: "<<bipartite<<std::endl;



	return 0;
}
