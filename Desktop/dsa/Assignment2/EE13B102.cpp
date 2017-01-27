#include <iostream>
#include <fstream>

int main(){

	std::ifstream inFile;

	inFile.open("input.txt");
	
	int msgNo, expectFrameNo;
	inFile >> msgNo >> expectFrameNo;

	int m[128], k = 0;
	std::fill_n(m, 128, 0);
	m[127]++;

	for(int i = 0; i < msgNo; i++){

		int frameStart, length;
		inFile >> frameStart >> length;

		for(int j = 0; j < length; j++) m[(frameStart+j)%128]++;

		if(frameStart + length > 128) k++;

	}

	int maxm = m[0];
	for(int i = 0; i < 128; i++){

		if(maxm < m[i]) maxm = m[i];

	}
	
	int minFrameNo = maxm;
	if(maxm < k+1) minFrameNo = k+1;

	if(minFrameNo <= expectFrameNo) std::cout<<"PASS"<<std::endl;
	else std::cout<<"FAIL"<<std::endl;



	return 0;
}
