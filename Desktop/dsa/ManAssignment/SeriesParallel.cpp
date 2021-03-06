#include <iostream>
#include "List.hpp"
#include "Stack.hpp"
using namespace std;

class Network{


	private:
		List<int>* nodes;
		int n;
		float **weight;

	public:
		Network(const int vertices = 0){
			n = vertices;

			weight = new float*[n];
			for(int i = 0; i < n; i++){
				weight[i] = new float[n];
				std::fill_n(weight[i], n, -1);
			}
			
			nodes = new List<int>[n];
		}

		void insertBiEdge(int u, int v, float w = -1.0){
			nodes[u].addElement(v);
			weight[u][v] = w;
			nodes[v].addElement(u);
			weight[v][u] = w;

			nodes[u].lastNode()->crossLink = nodes[v].lastNode();
			nodes[v].lastNode()->crossLink = nodes[u].lastNode();
		}

		void printList(){
				for(int i = 0; i < n; i++){
					cout<<i<<" :- ";
					for(ListNode<int>* a = nodes[i].firstNode(); a != 0; a = a->link){
						cout<<a->data<<" ";
					}
					cout<<endl;
				}
				cout<<endl;
		}

		bool reduceSeriesParallel(int start, int end){
		
			Stack<int> K(n);
			for(int i = 0; i < n; i++){
				if(i !=start && i != end)
					if(nodes[i].firstNode() != 0){
						if(nodes[i].firstNode()->link != 0){
						if(nodes[i].firstNode()->link->link == 0) K.push(i);
						}
					}	
			}
	printList();
			while(!K.isEmpty()){
				
				int v;
				K.pop(v);cout<<v<<endl;
				int nbr1 = nodes[v].firstNode()->data;
				int nbr2 = nodes[v].firstNode()->link->data;

				float R = weight[nbr1][v] + weight[nbr2][v];

				weight[nbr1][v] = -1;
				weight[nbr2][v] = -1;
				weight[v][nbr1] = -1;
				weight[v][nbr2] = -1;
				
				nodes[nbr1].removeLink(nodes[v].firstNode()->crossLink);

				nodes[nbr2].removeLink(nodes[v].firstNode()->link->crossLink);
				nodes[v].removeLink(nodes[v].firstNode());
				nodes[v].removeLink(nodes[v].firstNode());
				
				
				cout<<nbr1<<"   and    "<<nbr2<<"    "<<weight[nbr1][nbr2]<<endl;
				if(weight[nbr1][nbr2] == -1) insertBiEdge(nbr1, nbr2, R);
			
				else{
					float R1 = weight[nbr1][nbr2];
					weight[nbr1][nbr2] = R1*R/(R1 + R);
					weight[nbr2][nbr1] = weight[nbr1][nbr2];

					if(nbr1 != start && nbr1 != end)
						if(nodes[nbr1].firstNode()->link->link == 0) K.push(nbr1);
					if(nbr2 != start && nbr2 != end)
						if(nodes[nbr2].firstNode()->link->link == 0) K.push(nbr2);
				}

			}
			cout<<"weight[start][end]: "<<weight[start][end]<<endl;
			printList();
			return true;
		}

		bool reduceWheatstone(){

			for(int i = 0; i < n; i++){

				int adj[3], j;
				std::fill_n(adj, 3, -1);
				if(nodes[i].firstNode() != 0){
					adj[0] = nodes[i].firstNode()->data;
					if(nodes[i].firstNode()->link != 0){
						adj[1] = nodes[i].firstNode()->link->data;
						if(nodes[i].firstNode()->link->link != 0){
							adj[2] = nodes[i].firstNode()->link->link->data;
						}
					}
				}
				if(adj[2] != -1){
					ListNode<int>* x = nodes[i].firstNode()->link->link->link;
					if(x == 0 && detectWheatstone(i, adj, j) == true) deltaY(i, adj[j%3], adj[(j+1)%3], adj[(j+2)%3]);
				}
			}
		}

		bool detectWheatstone(int i, int* adj, int &j){
			for(j = 0; j < 3; j++){
				ListNode<int>* x = nodes[adj[j]].firstNode();
				if(x->data == i||x->data == adj[(j+1)%3]||x->data == adj[(j+2)%3]){
					if(x->link ==0) continue;x = x->link;
					if(x->data == i||x->data == adj[(j+1)%3]||x->data == adj[(j+2)%3]){	
						if(x->link == 0) continue;						
						x = x->link;
						if(x->data == i||x->data == adj[(j+1)%3]||x->data == adj[(j+2)%3]){	
							if(x->link == 0) return true;
						}
					}
				}				
			}
			return false;
		}

		void deltaY(int n1, int n2, int a1, int a2){
			ListNode<int>* x;
			for(x = nodes[n2].firstNode(); x != 0; x = x->link){
				if(x->data == a1) break;
			}

			nodes[n2].removeLink(x);
			nodes[a1].removeLink(x->crossLink);
			

			float R12 = weight[n1][n2];
			float Ran1 = weight[n1][a1];
			float Ran2 = weight[n2][a1];
			//cout<<weight[n1][a2]<<endl;
			weight[a1][n2] = -1;
			weight[n2][a1] = -1;
			
			float R = R12*Ran1*Ran2/(Ran1+Ran2+R12);
			weight[a1][n1] = weight[n1][a1] = R/R12;
			weight[a2][n1] = weight[n1][a2] = R/Ran2 + weight[n1][a2];
			weight[n1][n2] = weight[n2][n1] = R/Ran1;								
		}
};

int main(){

	Network n(10);

	n.insertBiEdge(0, 1, 100);
	n.insertBiEdge(1, 2, 200);
	n.insertBiEdge(1, 3, 200);
	n.insertBiEdge(2, 3, 200);
	n.insertBiEdge(2, 4, 200);
	n.insertBiEdge(3, 4, 200);
	n.insertBiEdge(4, 5, 100);
	n.insertBiEdge(5, 8, 100);
	n.insertBiEdge(5, 6, 100);
	n.insertBiEdge(6, 7, 100);
	n.insertBiEdge(9, 6, 100);
	n.insertBiEdge(9, 7, 100);
	n.insertBiEdge(0, 9, 100);

	bool x = n.reduceSeriesParallel(0, 8);
	n.reduceWheatstone();
	x = n.reduceSeriesParallel(0, 8);
	
	return 0;
}
