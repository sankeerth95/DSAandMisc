#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template <class Type>
class ListNode{
//	friend class List;
	public:	
	ListNode(){}

//	private:
	Type data;
	ListNode<Type>* link, *crossLink, *linkPrev;
};

template <class Type>
class List{

	public:
	List(){
		first = 0;
		last = 0;
		size = 0;
	}

	bool isEmpty(){
		if (firstNode() == 0) return true;
		else return false;
	}

	void addElement(Type dat, ListNode<Type>* x = 0){
	
		ListNode<Type>* l = new ListNode<Type>();
		l->data = dat;
		if(x == 0) x = last;
		if(first==0){
			l->linkPrev = 0;
			first = l;
			last = l;
			size++;
			return;
		}
		l->link = x->link;
		l->linkPrev = x;
		x->link = l;
		if(l->link == 0) last = l;
		size++;
	}

	void removeLink(ListNode<Type>* x){
		if(!isEmpty()){
			if(x == first && x == last){
				first = 0;
				last = 0;
			}
			else if(x == first) {

				first = x->link;
				x->link->linkPrev = 0;
				x->link = 0;
			}
			else if(x == last){
				last = x->linkPrev;
				last->link = 0;
				x->linkPrev = 0;
			}
			else{
				x->linkPrev->link = x->link;
				x->link->linkPrev = x->linkPrev;
			}	
			
		}
	}
	
	ListNode<Type>* firstNode(){
		return first;
	}

	ListNode<Type>* lastNode(){
		return last;
	}

	private:
	ListNode<Type> *first, *last;
	int size;

};

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
//printList();
			int* K = new int[n]; int sPoint = 0;
			for(int i = 0; i < n; i++){
				if(i !=start && i != end && nodes[i].firstNode() != 0){
					if(nodes[i].firstNode()->link != 0){
						if(nodes[i].firstNode()->link->link == 0) K[sPoint++] = i;
					}
				}
			}
			
			while(sPoint != 0){	

				int v = K[--sPoint];
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
				
				if(weight[nbr1][nbr2] == -1) insertBiEdge(nbr1, nbr2, R);

				else{
					float R1 = weight[nbr1][nbr2];
					weight[nbr1][nbr2] = R1*R/(R1 + R);
					weight[nbr2][nbr1] = weight[nbr1][nbr2];

					if(nbr1 != start && nbr1 != end)
						if(nodes[nbr1].firstNode()->link->link == 0) K[sPoint++] = nbr1;
					if(nbr2 != start && nbr2 != end)
						if(nodes[nbr2].firstNode()->link->link == 0) K[sPoint++] = nbr2;
				}

			}

			if(nodes[start].firstNode()->link == 0 && nodes[end].firstNode()->link == 0){

				if (nodes[start].firstNode()->data == end && nodes[end].firstNode()->data == start) return true;
			}
			
			return false;

		}

		void printWeight(int start, int end){
			cout << fixed << setprecision(2) << weight[start][end] <<endl;
		}

		bool reduceWheatstone(){

			bool detectFinal = false, detect = false;
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
					detect = detectWheatstone(i, adj, j); if(detect = true) detectFinal = true;
					if(x == 0 && detectWheatstone(i, adj, j) == true) deltaY(i, adj[j%3], adj[(j+1)%3], adj[(j+2)%3]);
				}
			}
			return detectFinal;
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

	ifstream inFile;
	inFile.open("input.txt");
	
	if(inFile.fail()){
		cerr<<"Error Opening File"<< endl;
		//abort();
	}
	
	int node_num, edges, start, end;
	inFile >> node_num >> edges >> start >> end;

	Network n(node_num);

	for(int j = 0; j < edges; j++){
		int n1, n2;	
		float R;
		inFile >> n1 >> n2 >> R;

		int node1 = n1-1, node2 = n2-1;
		n.insertBiEdge(node1, node2, R);
	}

	start--; end--;
	while(!n.reduceSeriesParallel(start, end)){
		if(!n.reduceWheatstone()) break;
	}
	n.printWeight(start, end);

	return 0;
}
