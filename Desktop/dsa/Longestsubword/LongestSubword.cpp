#include <iostream>
#include <vector>

int findLongestString(std::string w1, std::string w2, const int x1, const int x2){

	static std::vector< std::vector<int> > memo;
	static bool initialized = false;
	std::vector<int> nulls;

//	std::cout<<"adf"<<std::endl;

	if(!initialized){

		for(int i = 0; i < w2.length(); i++) nulls.push_back(-1);
		for(int i = 0; i < w1.length(); i++) memo.push_back(nulls);
		initialized = true;
	}

	if(memo[x1][x2] == -1){
		
		int stringlength = 0;
		int i = x1, j = x2;
		memo[x1][x2] = 0;
		while(i < w1.length() && j < w2.length()){
			if(w1[i] == w2[j]){
				i++; j++;
				stringlength++;
			}
			else break;
		}

		const int maxlength = stringlength;
		while(stringlength > 0){

			memo[x1+stringlength-1][x2+stringlength-1] = maxlength - stringlength + 1;
			stringlength--;
		}
		
	}
	int commonLength = memo[x1][x2];

	if(x1 == w1.length()-1 && x2 == w2.length()-1){
		initialized = false;
		memo.erase(memo.begin(), memo.end());
		nulls.erase(nulls.begin(), nulls.end());
	}

	return commonLength;
}


void longestCommonSubword(std::string w1, std::string w2){

	int max = 0, maxi = -1, maxj = -1;
	int longstr;
	for(int i = 0; i < w1.length(); i++){
		for(int j = 0; j < w2.length(); j++){

			longstr = findLongestString(w1, w2, i, j);

			if(max < longstr){
				max = longstr;
				maxi = i;
				maxj = j;
			}
		}
	}

	std::cout<<maxi<<" "<<maxj<<std::endl;
}


int main(){

	longestCommonSubword("bisect", "secret");
	longestCommonSubword("adfav", "casnvauifav");	


	return 0;
}
