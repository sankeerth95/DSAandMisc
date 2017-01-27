#include "Graph.hpp"

using namespace std;

int main(){

	Graph g(10); //= new Graph(10);
	
	g.insertBiEdge(0, 1, 10);
	g.insertBiEdge(1, 2, 6);
	g.insertBiEdge(2, 0, 80);
	g.insertBiEdge(2, 3, 70);
	g.insertBiEdge(1, 4, 20);
	g.insertBiEdge(4, 5, 50);
	g.insertBiEdge(5, 6, 5);
	g.insertBiEdge(4, 6, 10);
/*	g.insertBiEdge(5, 6);
	g.insertBiEdge(5, 8);
	g.insertBiEdge(5, 7);
	g.insertBiEdge(7, 8);
	g.insertBiEdge(8, 9);
*/	
	//g.dfs(8);
	//g.displayPre();
	//g.displayPost();

	g.dijkstra(0);
	

	return 0;
}
