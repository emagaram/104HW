#include <fstream>
#include <iostream>
using namespace std;
int main (int argc, char* argv[]){
	int size = 0;
	ifstream iFile(argv[1]);
	ofstream oFile(argv[2]);
	iFile >> size;
	if(iFile.fail() || size==0){
		oFile << 0;
	}	
	int* numbers = new int[size];
	int outputSize;
	for (int i = 0; i < size; i++)
	{
		iFile >> numbers[i];
	}

	if(size%2==0){ //if even
		outputSize = size/2;
	}
	else{ //output array will need to have one more space for middle number
		outputSize = size/2 + 1;
	}
	int first = 0;
	int last = size - 1;
	for (int i = 0; i < outputSize; i++)
	{
		oFile << numbers[first] + numbers[last] << "\n";
		first++;
		last--;
	}
	iFile.close();
	delete[] numbers;
	
}