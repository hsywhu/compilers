#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* P[100];
char* Vt = "abcdefghijklmnopqrstuvwxyz0123456789!=()*/";
char formalVt[100];
char Vn[100];
char G[100];
char inputP[100];
int P_length=0;
int left;
int right;

void getP(){	//��ȡ����ʽ��P��Vn
	printf("�������ķ�:\n");
	gets_s(G);

	printf("������Vn:\n");
	gets_s(Vn);
	int i, j;
	for (i = 0, j = 0; Vn[i] != '\0'; i++)
	{
		if (Vn[i] != ',')
			Vn[j++] = Vn[i];
	}
	Vn[j] = '\0';

	printf("���������ʽ����:\n");
	gets_s(inputP);

	char* delim = ",";
	char* pa = strtok(inputP,delim);
	while (pa != NULL){
		P[P_length] = pa;
		P_length++;
		pa = strtok(NULL, delim);
	}
}

void position(char* P){		//��ȡ����ʽ����ߺ��ұߵ�λ��
	int m;
	for (m = 0; m < strlen(P); m++){
		if (P[m] == ':')
			break;
	}
	left = m - 1;
	right = m + 3;
}

int contants(char* V, char P){		//�ж��ַ��Ƿ������ַ���
	for (int i=0; i < strlen(V); i++){
		if (V[i] == P)
			return 1;
	}
	return 0;
}

int type0(char** P){
	for (int i = 0; i < P_length; i++){
		position(P[i]);
		for (int j = right; j < strlen(P[i]); j++){
			if (contants(Vn, P[i][j]) == 1 || contants(Vt, P[i][j])==1){
				for (int h = 0; h <= left; h++){
					if (contants(Vn, P[i][h]) == 1 || contants(Vt, P[i][h]) == 1){}
					else{ return 0; }
				}
			}
			else{ return 0; }
		}
	}
	return 1;
}

int type1(char** P){
	int flag = 0;	//�жϲ���ʽ����Ƿ��з��ս��
	for (int i = 0; i < P_length; i++){
		position(P[i]);
		int right_length = strlen(P[i]) - right;
		int left_length = left + 1;
		if (right_length >= left_length && left_length >= 1){
			for (int j = 0; j <= left; j++){
				if (contants(Vn, P[i][j])){
					flag = 1;
					break;
				}
			}
			if (flag != 1){
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	return 1;
}

int type2(char** P){
	for (int i = 0; i < P_length; i++){
		position(P[i]);
		if (left == 0 && contants(Vn, P[i][left])){
			for (int j = right; j < strlen(P[i]); j++){
				if (contants(Vn, P[i][j]) == 1 || contants(Vt, P[i][j]) == 1){}
				else{ return 0; }
			}
		}
		else{ return 0; }
	}
	return 1;
}

int type3(char** P){
	for (int i = 0; i < P_length; i++){
		position(P[i]);
		int right1 = right + 1;
		if (left == 0 && contants(Vn, P[i][left])){
			int right_length = strlen(P[i]) - right;
			if (right_length == 1 || right_length == 2){
				if (right_length == 1 && contants(Vt, P[i][right])){}
				else if (right_length == 2 && contants(Vt, P[i][right]) && contants(Vn, P[i][right1])){}
				else{ return 0; }
			}
			else{ return 0; }
		}
		else{ return 0; }
	}
	return 1;
}

void formalOUT(){
	printf("�ķ�%s=({",G);
	for (int i = 0; i < strlen(Vn); i++){
		printf("%c", Vn[i]);
		if (i != (strlen(Vn) - 1)){
			printf(",");
		}
	}
	printf("},{");
	int j = 0;
	for (int k = 0; k < P_length; k++){
		for (int i = 0; i < strlen(P[k]); i++){
			if (P[k][i] != ':' && P[k][i] != '=' && P[k][i] != ',' && contants(formalVt, P[k][i]) == 0 && contants(Vn, P[k][i]) == 0){
				formalVt[j] = P[k][i];
				j++;
			}
		}
	}
	for (int i = 0; i < strlen(formalVt); i++){
		printf("%c", formalVt[i]);
		if (i != (strlen(formalVt) - 1)){
			printf(",");
		}
	}
	printf("},P,");
	int m;
	for (m = 0; m < strlen(G); m++){
		if (G[m] == '[')
			break;
	}
	char S = G[m + 1];
	printf("%c)\n", S);
}

int main(void){
	getP();
	if (type3(P) == 1){
		printf("���ķ���Chomsky3���ķ�\n");
	}
	else if (type2(P) == 1){
		printf("���ķ���Chomsky2���ķ�\n");
	}
	else if (type1(P) == 1){
		printf("���ķ���Chomsky1���ķ�\n");
	}
	else if (type0(P) == 1){
		printf("���ķ���Chomsky0���ķ�\n");
	}
	else{
		printf("���ķ��������κ�һ���ķ�����\n");
	}
	formalOUT();
	system("PAUSE");
	return 0;
}