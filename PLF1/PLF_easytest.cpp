#include <iostream>
#include <cstring>
using namespace std;

void printInHex(unsigned char* str, long long len);
void PLF1(unsigned char* origin_string, unsigned char *hashvalue, long long len);

unsigned char hashvalue[256];
unsigned char space[1];
int main(int argv, char** argc){
	if(argv < 2){
		PLF1(space, hashvalue, 0);
		printInHex(hashvalue, 23); cout << "\n";
	}else{
		PLF1((unsigned char*)argc[1], hashvalue, strlen(argc[1]));
		printInHex(hashvalue, 23); cout << "\n";
	}
}