#include <iostream>
#include <cstring>
using namespace std;

void printInHex(unsigned char* str, long long len);
void PLF1(unsigned char* origin_string, unsigned char *hashvalue, long long len);

unsigned char hashvalue[500];
unsigned char space[1];
int main(int argv, char** argc){
	if(argv < 2){
		PLF1(space, hashvalue, 0);
		printInHex(hashvalue, 256); cout << "\n";
	}else{
		PLF1((unsigned char*)argc[1], hashvalue, strlen(argc[1]));
		printInHex(hashvalue, 256); cout << "\n";
	}
}

/*
compile with:
	g++ PLF_easytest.cpp PLF1.cpp -o easytest
execute with:
	easytest <data string>
	./easytest <datastring>
*/