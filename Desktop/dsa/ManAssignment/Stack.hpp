template <class Type>
class Stack{

	public:
	Stack(int maxSize = 10);

	void push(const Type&);
	Type* pop(Type&);

	bool isFull();
	bool isEmpty();

	private:
	void stackFull();
	void stackEmpty();

	Type *array;
	int maxSize;
	int top;
};

template <class Type>
Stack<Type>::Stack(int maxBagSize){

	maxSize = maxBagSize;
	array = new Type[maxSize];
	top = -1;
}

template <class Type>
void Stack<Type>::push(const Type& x){
	if(isFull()) stackFull();
	array[++top] = x;
}

template <class Type>
Type* Stack<Type>::pop(Type& x){
	if(isEmpty()) {stackEmpty(); return 0;}
	x = array[top--];
	return &x;
}

template <class Type>
inline bool Stack<Type>::isFull(){
	if(top == maxSize-1) return true;
	return false;
}

template <class Type>
inline bool Stack<Type>::isEmpty(){
	if(top == -1) return true;
	return false;
}

template <class Type>
void Stack<Type>::stackEmpty(){
}

template <class Type>
void Stack<Type>::stackFull(){
}



