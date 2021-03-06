#include <iostream>
#include <unordered_map>
#include <vector>

int min(int n1, int n2, int n3){

	int n[] = {n1, n2, n3};
	int min = n1;
	for(int i = 0; i < 3; i++){
		if(min > n[i]) min = n[i];
	}
	return min;
}

int max(int i, int j){
	if(i < j) return j;
	else return i;
}


int bottom_up(std::string w1, std::string w2){

	std::vector< std::vector<int> > Opt;
	std::vector<int> temp;

	for(int i = 0; i < w2.length()+1; i++) temp.push_back(0);
	for(int i = 0; i < w1.length()+1; i++) Opt.push_back(temp);

	for(int i = 0; i < w2.length()+1; i++) Opt[0][i] = i;
	for(int i = 0; i < w1.length()+1; i++) Opt[i][0] = i;

	for(int i = 1; i < w1.length()+1; i++){
		for(int j = 1; j < w2.length()+1; j++){
		
			if(w1[i-1] == w2[j-1]) Opt[i][j] = Opt[i-1][j-1];
			
			else Opt[i][j] = 1 + min(Opt[i-1][j], Opt[i][j-1], Opt[i-1][j-1]);
		}
	}

	return Opt[w1.length()][w2.length()];
}


int editDistTop(std::string w1,std::string w2, int i = -2, int j = -2){

	if(i == -2 && j == -2){
		i = w1.length()-1;
		j = w2.length()-1;
	}

	if(i == -1 || j == -1) return 1 + max(i, j);

	static std::unordered_map<std::string, int> memo;

	std::string ij = std::to_string(i) + " " + std::to_string(j);
	if(memo.find(ij) == memo.end()){

		if(w1[i] == w2[j]) memo[ij] = editDistTop(w1, w2, i-1, j-1);
		
		else memo[ij] = 1+min(editDistTop(w1, w2, i-1, j), editDistTop(w1, w2, i, j-1),  editDistTop(w1, w2, i-1, j-1));
	}
	
	int edits = memo[ij];
	if(i == w1.length()-1 && j == w2.length()-1) memo.erase(memo.begin(), memo.end());

	return edits;
}

int main(){

	std::cout<< editDistTop("Okay Pikachu, finish him off with your thunderbolt attack", "Venasaur, use Solar Beam!!") <<std::endl;

	std::cout<< bottom_up("Okay Pikachu, finish him off with your thunderbolt attack", "Venasaur, use Solar Beam!!") <<std::endl;

	return 0;
}
