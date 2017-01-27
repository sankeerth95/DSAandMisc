#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


int max(int i, int j){
	if(i > j) return i;
	else return j;

}

int bottom_up(std::string w1, std::string w2){

	std::vector<std::vector<int>> Opt;
	std::vector<int> temp;
	
	for(int i = 0; i < w2.length()+1; i++) temp.push_back(0);
	for(int i = 0; i < w1.length()+1; i++) Opt.push_back(temp);
	
	for(int i = 0; i < w1.length(); i++){
		for(int j = 0; j < w2.length(); j++){
			
			if(w1[i] == w2[j]) Opt[i+1][j+1] = Opt[i][j] + 1;
			else{
				Opt[i+1][j+1] = max(Opt[i+1][j], Opt[i][j+1]);
			}
		}
	}
	return Opt[w1.length()][w2.length()];
}

int top_down(std::string w1, std::string w2, int i = 0, int j = 0){

	static std::unordered_map<std::string, int> memo;
	std::unordered_map<std::string, int>::iterator it;

	if(i == w1.length() || j == w2.length()) return 0;

	std::string memij = std::to_string(i) + " " + std::to_string(j);

	if(memo.find(memij) == memo.end()){

		if(w1[i] == w2[j]) memo[memij] = 1 + top_down(w1, w2, i+1,j+1);

		else memo[memij] = max(top_down(w1, w2, i+1, j), top_down(w1, w2, i, j+1));
		
	}

	int subseq = memo[memij];
	if(i == 0 && j == 0) memo.erase(memo.begin(), memo.end());		//clean-up
	return subseq;
}

int main(){

	std::cout<<top_down("bisectvndobugnlcivhacxc", "secretagldfvnadvbiurf")<<std::endl;
	std::cout<<bottom_up("bisectvndobugnlcivhacxc", "secretagldfvnadvbiurf")<<std::endl;

	return 0;
}
