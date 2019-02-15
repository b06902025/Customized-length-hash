#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned char source[5124];
unsigned long long randomlength;
int checklength = 1;

void genRandomContent(){
	randomlength = rand()%40+16;
	for(int i=0;i<randomlength;i++){
		source[i] = rand()%255;
	}
}

bool checkResult(unsigned char* result){
	for(int i=0;i<checklength;i++){
		if(result[i] != 0)return false;
	}
	return true;
}

void printInHex(unsigned char* str, long long len);
void PLF1(unsigned char* origin_string, unsigned char *hashvalue, long long len);

int main(){
	srand(time(NULL));
	int cnt = 0, snt = 0;
	while(1){
		genRandomContent();
		unsigned char result[256];
		PLF1(source, result, randomlength);
		
		if(checkResult(result)){
			printInHex(source, randomlength); cout << " = ";
			printInHex(result, 23);
			cout << " success!\n";
			cnt++;
			cout << "success ratio:" << cnt << "/" << snt << "\n";
		}
		else{
			printInHex(result, 23); cout << " " << cnt << "/" << snt << "\r";
		}
		snt++;
	}

}