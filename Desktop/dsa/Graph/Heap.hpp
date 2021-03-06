template <class KeyType>
class Element{

	public:
		KeyType var;
		int key;

};

template <class Type>
class Heap{

	private:
		int length, last, *position;
		Element<Type>* data;
		
		void replace(int index);
		int parent(int index);
		int leftDec(int index);
		int rightDec(int index);

	public:
		Heap(int maxElements);
		
		void insert(const Type& dat, int key);
		Type findMin();
		void removeMin(Type& x);
		
		void decreaseKey(Type dat, int newKey);

		Type returnData(int index){
			
			return data[index].var;
		}	
};

template <class Type>
Heap<Type>::Heap(int maxLength){

	last = 0;
	data = new Element<Type>[maxLength];

	position = new int[maxLength];
}

template <class Type>
void Heap<Type>::decreaseKey(Type dat, int newKey){

	int indx = position[dat];
	data[indx].key = newKey;

	while(data[parent(indx)].key < newKey && parent(indx)!=indx) replace(indx);

}

template <class Type>
Type Heap<Type>::findMin(){

	return data[0].var;
}

template <class Type>
void Heap<Type>::insert(const Type& dat, int key){
	
	data[last].key = key;
	data[last].var = dat;
	position[dat] = last;

	int up = last;
	while (up > 0) {
		if(key < data[parent(up)].key) replace(up);
		else break;
		up = parent(up);
	}

	last++;
}

template <class Type>
void Heap<Type>::removeMin(Type& x){

	int point = 0;
	x = -1;
	if(last == 0) return;
	x = findMin();

	data[0] = data[last-1];
	last--;
	
	while(rightDec(point) < last){

		if (data[point].key <= data[leftDec(point)].key && data[point].key <= data[rightDec(point)].key)
			break;

		if(data[leftDec(point)].key < data[rightDec(point)].key) {

			replace(leftDec(point));
			point = leftDec(point);
		}
	
		else if(data[leftDec(point)].key > data[rightDec(point)].key){
			replace(rightDec(point));
			point = rightDec(point);
		}
	}

	if(leftDec(point) == last-1 && data[leftDec(point)].key < data[point].key) replace(leftDec(point));
	
}

template <class Type>
void Heap<Type>::replace(int index){
	int indx = parent(index);

	position[data[index].var] = indx;
	position[data[indx].var] = index;

	Element<Type> tempT = data[indx];
	data[indx] = data[index];
	data[index] = tempT;
}

template <class Type>
int Heap<Type>::parent(int index){

	if (index != 0) return (index-1)/2;
	else return 0;
}

template <class Type>
int Heap<Type>::leftDec(int index){
	
	return (2*index+1);
}

template <class Type>
int Heap<Type>::rightDec(int index){
	
	return 2*(index+1);
}

