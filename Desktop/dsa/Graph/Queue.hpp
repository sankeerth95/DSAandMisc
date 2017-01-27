template <class Type>
class Queue{

	public:
	Queue(int maxSize = 10);

	void enqueue(const Type&);
	Type* dequeue(Type&);

	bool isFull();
	bool isEmpty();

	private:
	void queueFull();
	void queueEmpty();

	Type *array;
	int maxSize;
	int head, tail;
};

template <class Type>
Queue<Type>::Queue(int maxBagSize){

	maxSize = maxBagSize;
	array = new Type[maxSize];
	head = tail = -1;
}

template <class Type>
void Queue<Type>::enqueue(const Type& x){
	if(isFull()) queueFull();
	array[(++tail)%maxSize] = x;
}

template <class Type>
Type* Queue<Type>::dequeue(Type& x){
	if(isEmpty()) {queueEmpty(); return 0;}
	x = array[(++head)%maxSize];
	return &x;
}

template <class Type>
inline bool Queue<Type>::isFull(){
	if(tail - head == maxSize-1) return true;
	return false;
}

template <class Type>
inline bool Queue<Type>::isEmpty(){
	if(tail == head) return true;
	return false;
}

template <class Type>
void Queue<Type>::queueEmpty(){
}

template <class Type>
void Queue<Type>::queueFull(){
}

