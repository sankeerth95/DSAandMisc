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

