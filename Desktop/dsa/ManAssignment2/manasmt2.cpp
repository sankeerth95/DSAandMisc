#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

std::vector<std::vector<int>> array;
int N;

std::unordered_map<std::string, int> memo;

int max(int a, int b){

	if(a > b) return a;
	else return b;
}

int maxCoins(int i, int j){


	std::string ij = std::to_string(i) + " " + std::to_string(j);
	if(memo.find(ij) != memo.end()) return memo[ij];

	if(array[i][j] == -1) return 0;

//		std::cout<<"SFG"<<std::endl;
	if(i == 0 && j == 0) return array[0][0];


	else if(i == 0){
		memo[ij] = array[i][j]+maxCoins(i, j-1);
		return memo[ij];
	}

	if(i%2 == 0){ 
		int x = -1;
		if(j > 0) x = maxCoins(i, j-1);
		int y = maxCoins(i-1, j);
		memo[ij] = array[i][j] + max(x, y);
		return memo[ij];
	}

	else{
		int x = -1;
		if(j < N) x = maxCoins(i, j+1);
		int y = maxCoins(i-1, j);
		memo[ij] = array[i][j] + max(x, y);
		return memo[ij];
	}
}

int bottom_up(){

	int O[N][N];

	for(int i = 0; i < N; i++){

		for(int j = 0; j < N; j++){

			if(i == 0 && j == 0) O[i][j] = array[0][0];
			else if(i%2 == 0){
				if(array[i][j] == -1) O[i][j] = 0;
				else if(i == 0) O[i][j] = array[i][j] + O[i][j-1];
				else if(j > 0) O[i][j] = array[i][j] + max(O[i][j-1], O[i-1][j]);
				else if(j == 0) O[i][j] = array[i][j] + O[i-1][j];
			}
			else{
				if(array[i][N-j-1] == -1) O[i][N-j-1] = 0;
				else if(j > 0) O[i][N-j-1] = array[i][N-j-1] + max(O[i][N-j], O[i-1][N-j-1]);
				else if(j == 0) O[i][N-j-1] = array[i][N-j-1] + O[i-1][N-j-1];
			}
		}
	}

	return O[N-1][N-1];
}


int main(){

	std::ifstream inFile;
	inFile.open("input.txt");

	inFile>>N;

	for(int i = 0; i < N; i++){

		std::vector<int> temp;
		for(int j = 0; j < N; j++){
			int coins;
			inFile>>coins;
			temp.push_back(coins);

		}
		array.push_back(temp);
	}

//	std::cout<<maxCoins(N-1, N-1)<<std::endl;
	std::cout<<bottom_up()<<std::endl;

}
