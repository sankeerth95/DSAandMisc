template <class Type>
class ListNode{
//	friend class List;
	public:	
	ListNode(){}

//	private:
	Type data;
	ListNode<Type>* link;
};

template <class Type>
class List{

	public:
	List(){
		first = 0;
		last = 0;
		size = 0;
	}
	void addElement(Type dat, ListNode<Type>* x = 0){
	
		ListNode<Type>* l = new ListNode<Type>();
		l->data = dat;
		if(x == 0) x = last;
		if(first==0){
			first = l;
			last = l;
			size++;
			return;
		}
		l->link = x->link;
		x->link = l;
		if(l->link == 0) last = l;
		size++;
	}

	ListNode<Type>* firstNode(){
		return first;
	}
	private:
	ListNode<Type> *first, *last;
	int size;

};

template <class Type>
class ListIterator{
};

