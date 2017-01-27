//implementation of a graph without using a hashmap, i.e, the vertex names 
//are integers numbered as 0, 1, 2, ...n-1.
//An array (hashmap between 0-n to integers) is used instead
#include<iostream>
#include "List.hpp"
#include "Queue.hpp"
#include "Heap.hpp"

class Graph{

	private:
		List<int>* headNodes;
		int n, count;
		int *pre, *post, *parent, *levels, *low;
		bool *visited;
		bool oddCycles;
		
		int **weight;

		bool checkConnected(int u, int v){
			for(ListNode<int>* x = headNodes[u].firstNode(); x!=0; x = x->link){
				if(x->data == v) return true;
			}
			return false;
		}

	public:
		Graph(const int vertices = 0){
			n = vertices;
			count = 0;
			oddCycles = false;

			weight = new int*[n];
			
			for(int i = 0; i < n; i++){
				weight[i] = new int[n];
			}		

			headNodes = new List<int>[n];
			visited = new bool[n];
			for(int i = 1; i < n; i++){
				visited[i] = false;
			}
			levels = new int[n];
			for(int i = 0; i < n; i++){
				levels[i] = -1;
			}

			parent = new int[n];
			pre = new int[n];
			post = new int[n];
			low = new int[n];
			for(int i = 0; i < n; i++){
				low[i] = 2*n+1;
			}
		}

		void insertVertex(int v){
			if(v >= n){ List<int>* p = headNodes + n;
				p = new List<int>[v-n+1];
			}
			else return;
		}

		void insertEdge(int u, int v, int w = -1){
			headNodes[u].addElement(v);
			weight[u][v] = w;
		}
		
		void insertBiEdge(int u, int v, int w = -1){
			insertEdge(u, v, w);
			insertEdge(v, u, w);
		}
		

	//	void deleteVertex(vertex v);
	//	void deleteEdge(vertex u, vertex v);
	//	bool isEmpty();

	//	List<Vertex> adjacent(vertex v);
	
		void dfs(const int s){
			std::cout<< s<< std::endl;
			visited[s] = true;
			pre[s] = count;
			low[s] = pre[s];
			for(ListNode<int>* x = headNodes[s].firstNode(); x != 0; x = x->link){
				if(visited[x->data] == false){
					count++;
					parent[x->data] = s;
					dfs(x->data);
				}
				if(low[x->data] < low[s]) low[s] = low[x->data];
			}
			post[s] = count;count++;
		}
		
		void displayPre(){
			for(int i = 0; i < n; i++) std::cout<<pre[i]<<" ";
			std::cout<<std::endl;
		}
		void displayPost(){
			for(int i = 0; i < n; i++) std::cout<<post[i]<<" ";
			std::cout<<std::endl;
		}

		void bfs(const int s){
			Queue<int> q(n);
			levels[s] = 0;
			q.enqueue(s);
			int node_num;
			
			while(!q.isEmpty()){
				
				q.dequeue(node_num);
				ListNode<int>* iter;
				for(iter = headNodes[node_num].firstNode();iter != 0;iter = iter->link){
					if(levels[iter->data] == -1){
						levels[iter->data] = levels[node_num] + 1;
						q.enqueue(iter->data);
						parent[iter->data] = node_num;
					}
					else if(levels[iter->data] == levels[node_num]){
						oddCycles = true;
					}
				}
			}

		}
		
		bool checkBipartite(){
			if(oddCycles == true) return false;
			else return true;
		}

		void displayLevels(){
			for(int i = 0; i < n; i++) std::cout<<levels[i]<<" ";

			std::cout<<std::endl;
		}

		void dijkstra(const int s){
		
			int* distance = new int[n];
			for(int i = 0; i < n; i++) distance[i] = -1;
			distance[s] = 0;
			int node_min;
			Heap<int> h(n);
			
			h.insert(s, 0);
						
			for(int i = 0; i < n; i++){
				
				h.removeMin(node_min);
				
				if(node_min == -1) return;
				visited[node_min] = true;
				ListNode<int>* adj_node;
		
				for(adj_node = headNodes[node_min].firstNode(); adj_node != 0; adj_node = adj_node->link){

					int w = weight[node_min][adj_node->data];
					if(distance[adj_node->data] > distance[node_min] + w || distance[adj_node->data] == -1){
						
						int initialDist = distance[adj_node->data];
						distance[adj_node->data] = distance[node_min] + w;
						
			std::cout<<node_min<<"       "<<distance[adj_node->data]<<"      "<< adj_node->data<<std::endl;

						if(initialDist != -1){
							h.decreaseKey(adj_node->data, distance[adj_node->data]);
						}
						else h.insert(adj_node->data, distance[adj_node->data]);
					}
				}
			}
		
		}
};

