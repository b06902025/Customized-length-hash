#include <iostream>
#include <cstring>
using namespace std;

const unsigned int L = 500;
const unsigned int K = 23;
const unsigned int RMAX = 100007;
unsigned int R;
unsigned int S;

int ROOTKEY[256] = {
	52,	49,	25,	4,	10,	40,	14,	60,	41,	34,	8,	63,	46,	29,	19,	63,
	2,	17,	1,	37,	1,	52,	22,	2,	22,	46,	35,	33,	20,	57,	19,	4,
	9,	0,	3,	47,	51,	35,	55,	20,	34,	38,	38,	43,	7,	34,	17,	43,
	59,	35,	31,	49,	23,	59,	3,	10,	10,	57,	22,	42,	1,	58,	23,	46,
	30,	56,	29,	21,	42,	62,	38,	22,	10,	23,	30,	49,	61,	50,	60,	50,
	1,	3,	39,	60,	44,	41,	56,	2,	3,	7,	17,	56,	16,	58,	18,	51,
	55,	15,	15,	42,	62,	24,	52,	19,	6,	43,	3,	8,	20,	51,	37,	20,
	36,	24,	61,	7,	18,	1,	57,	30,	47,	61,	30,	56,	55,	23,	27,	18,
	17,	60,	46,	48,	49,	35,	29,	54,	28,	62,	15,	45,	56,	40,	9,	1,
	1,	49,	97,	25,	55,	28,	3,	54,	18,	39,	32,	57,	3,	52,	27,	8,
	43,	42,	31,	37,	7,	57,	60,	28,	41,	18,	0,	40,	4,	23,	44,	59,
	27,	38,	21,	15,	9,	44,	15,	30,	61,	41,	50,	56,	8,	43,	43,	44,
	7,	27,	63,	45,	29,	9,	59,	58,	34,	6,	4,	30,	49,	3,	42,	44,
	46,	9,	62,	1,	42,	46,	9,	37,	49,	39,	31,	32,	22,	10,	59,	31,
	35,	50,	22,	12,	28,	28,	20,	5,	2,	17,	39,	16,	0,	61,	24,	56,
	40,	48,	37,	59,	34,	13,	60,	9,	30,	15,	15,	43,	40,	20,	56,	4
};

int PI_TRANS[4][4] = {
	{3, 1, 4, 1},
	{5, 9, 2, 6},
	{5, 3, 5, 8},
	{9, 7, 9, 3},
};

void printInHex(unsigned char* str, long long len){
	for(int i=0;i<len;i++){
		printf("%.2x", str[i] & 0xff);
	}
}

void addROOTKEY(unsigned char* stringA, long long len){
	for(int i=0;i<=(len-1)/256+1;i++){
		for(int j=0;j<256;j++){
			stringA[i*256+j] += ROOTKEY[j];
		}
		if(i == (len-1)/256+1)stringA[i*256+256] = '\0';
	}
}

void getR(unsigned char* stringA, long long len){
	R = 0;
	for(int i=0;i<len;i++){
		R += ROOTKEY[(stringA[i]+i)%256] * stringA[i] + i % K*L;
		R %= RMAX;
	}
}

void multipleByMatrix(unsigned char* str, long long len){
	unsigned char tmp[4][4];
	unsigned char newtmp[4][4];
	for(int i=0;i<len/16;i++){
		for(int ja=0;ja<4;ja++){
			for(int jb=0;jb<4;jb++){
				tmp[ja][jb] = str[i*16+ja*4+jb];
			}
		}

		for(int ka=0;ka<4;ka++){
			for(int kb=0;kb<4;kb++){
				newtmp[ka][kb] = 0;
				for(int s=0;s<4;s++){
					newtmp[ka][kb] += PI_TRANS[ka][s]*tmp[s][kb];
				}
			}
		}

		for(int ja=0;ja<4;ja++){
			for(int jb=0;jb<4;jb++){
				str[i*16+ja*4+jb] = newtmp[ja][jb];
			}
		}
	}
}

unsigned int rolling(unsigned int nx, unsigned int seed, unsigned long long maxvalue, int step){
	nx += 1e6+1e4+31771;
	step += 131; step *= 17; step %= 131; step += 1;
	nx *= nx+step; nx += seed*1023/97;
	nx /= 97; 
	nx *= seed+step; nx += 19; nx *= 3+step;
	nx += seed/7/13/step; nx += nx/7/step/13;
	nx += seed/step; nx += step;
	nx %= maxvalue;
}

unsigned char stringB[K][L+1];
unsigned char stringA[131073];

void PLF1(unsigned char* origin_string, unsigned char *hashvalue, long long len){
	
	for(int i=0;i<K;i++){
		hashvalue[i] = 0;
	}

	for(int i=0;i<len;i++){
		stringA[i] = origin_string[i];
	}
	addROOTKEY(stringA, len);	len = ((len-1)/256+1)*256;
	getR(stringA, len);
	int nx = rolling(0, R, len, stringA[0]);
	for(int i=0;i<K;i++){
		for(int j=0;j<L;j++){
			stringB[i][j] = ((stringA[nx]*2)+71+stringA[nx]*stringA[nx])%256;
			nx = rolling(nx, R, len, stringA[nx]);
		}
	}
	S = rolling(nx, R, K, stringB[0][0]);
	for(int i=0;i<K;i++){
		multipleByMatrix(stringB[S], L);
		for(int j=0;j<L;j++){
			hashvalue[(i+j)%K] += stringB[S][j];
			hashvalue[(i+j)%K] %= 256;
		}
		S = rolling(S, R, K, stringB[S][0]);
	}
}