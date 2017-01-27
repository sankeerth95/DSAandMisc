#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

template <class Type>
class ListNode{
//	friend class List;
	public:	
	ListNode(){}

//	private:
	Type data;
	ListNode<Type>* link, *crossLink, *linkPrev;
	float res;
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

	void addElement(Type dat, float w, ListNode<Type>* x = 0){

		ListNode<Type>* l = new ListNode<Type>();
		l->data = dat;
		l->res = w;
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

typedef unordered_map<string, float> resistance;
resistance weight;

void insert_to_map(int u, int v, float R){

	string x = to_string(u) + "," + to_string(v);
	string y = to_string(v) + "," + to_string(u);
	
	weight[x] = R;
	weight[y] = R;
}

float get_from_map(int u, int v){

	string x = to_string(u) + "," + to_string(v);
	if(weight.find(x) != weight.end()) return weight[x];
	else return -1;
}

void erase_from_map(int u, int v){

	string x = to_string(u) + "," + to_string(v);
	string y = to_string(v) + "," + to_string(u);
	weight.erase(x);
	weight.erase(y);
}

class Network{

	private:
		List<int>* nodes;
		int n;

	public:
		Network(const int vertices = 0){
			n = vertices;
			nodes = new List<int>[n];
		}

		void insertBiEdge(int u, int v, float w = -1.0f){

			if(get_from_map(u, v) == -1.0f){
				nodes[u].addElement(v, w);
				nodes[v].addElement(u, w);
				insert_to_map(u, v, w);

				nodes[u].lastNode()->crossLink = nodes[v].lastNode();
				nodes[v].lastNode()->crossLink = nodes[u].lastNode();
			}

			else{
				float w1 = get_from_map(u, v);
				insert_to_map(u, v, (w1*w/(w1+w)));
			}
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
			printList();
			int* K = new int[n]; int sPoint = 0;
			for(int i = 0; i < n; i++){
				if(i !=start && i != end && nodes[i].firstNode() != 0){
					if(nodes[i].firstNode()->link != 0){
						if(nodes[i].firstNode()->link->link == 0) K[sPoint++] = i;
					}
					else {
						int temp = nodes[i].firstNode()->data;
						nodes[temp].removeLink(nodes[i].firstNode()->crossLink);
						nodes[i].removeLink(nodes[i].firstNode());					
					}
				}
			}
			
			while(sPoint != 0){	

				int v = K[--sPoint];
				int nbr1 = nodes[v].firstNode()->data;
				int nbr2 = nodes[v].firstNode()->link->data;

				float R = get_from_map(v, nbr1) + get_from_map(v, nbr2);

				erase_from_map(v, nbr1);
				erase_from_map(v, nbr2);
				
				nodes[nbr1].removeLink(nodes[v].firstNode()->crossLink);
				nodes[nbr2].removeLink(nodes[v].firstNode()->link->crossLink);
				nodes[v].removeLink(nodes[v].firstNode());
				nodes[v].removeLink(nodes[v].firstNode());
				
				if(get_from_map(nbr1, nbr2) == -1) insertBiEdge(nbr1, nbr2, R);

				else{
					float R1 = get_from_map(nbr1, nbr2);
					insert_to_map(nbr1, nbr2, R1*R/(R1 + R));
					
					if(nbr1 != start && nbr1 != end)
						if(nodes[nbr1].firstNode()->link->link == 0) K[sPoint++] = nbr1;
					if(nbr2 != start && nbr2 != end)
						if(nodes[nbr2].firstNode()->link->link == 0) K[sPoint++] = nbr2;
				}
			}
		printList();

			if(nodes[start].firstNode()->link == 0 && nodes[end].firstNode()->link == 0){

				if (nodes[start].firstNode()->data == end && nodes[end].firstNode()->data == start) return true;
			}
			return false;
		}

		void printWeight(int start, int end){
			cout << fixed << setprecision(2) << get_from_map(start, end) <<endl;
		}

		bool reduceWheatstone(int start, int end){

			float RX = -1;
			if (get_from_map(start, end) != -1){
				RX = get_from_map(start, end);
				erase_from_map(start, end);
				for(ListNode<int>* a = nodes[start].firstNode(); a != 0; a = a->link){
				if(a->data == end){
					nodes[end].removeLink(a->crossLink);
					nodes[start].removeLink(a);
					}
				}
			}	

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
					detect = detectWheatstone(i, adj, j); if(detect == true) detectFinal = true;
					if(x == 0 && detect == true) deltaY(i, adj[j%3], adj[(j+1)%3], adj[(j+2)%3]);
				}
			}

			if(RX != -1) insertBiEdge(start, end, RX);
			
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

			float R12 = get_from_map(n1, n2);
			float Ran1 = get_from_map(n1, a1);
			float Ran2 = get_from_map(n2, a1);
			
			erase_from_map(a1, n2);
			
			insert_to_map(n1, a1, Ran1*Ran2/(Ran1+Ran2+R12));
			insert_to_map(n1, a2, (R12*Ran1/(Ran1+Ran2+R12) + get_from_map(n1, a2)));
			insert_to_map(n2, n1, R12*Ran2/(Ran1+Ran2+R12));				
				
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
		if(!n.reduceWheatstone(start, end)) break;
	}
	n.printWeight(start, end);

	return 0;
}
