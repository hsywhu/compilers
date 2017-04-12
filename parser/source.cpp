#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ch[1000];	//�洢���ļ��ж��������
int p=-1;	//��¼��ȡcd��ָ��
char thisch;	//��¼��ǰ��ȡ���ַ�

int isExpression();

void getFileContent(){	//���ļ����ݶ�ȡ��������
	char temp[100];
	FILE *fp = fopen("input.txt", "r");
	if (!fp)
	{
		printf("can't open file\n");
	}
	do{
		fscanf(fp, "%s", &temp);	//���ж�������
		strcat(ch, temp);	//��һ�е����ݸ��Ƶ�ch�ַ���β��
	} while (!feof(fp));
}

int isLetter(char p){
	if ((p >= 'A'&&p <= 'Z') || (p >= 'a'&&p <= 'z'))
		return 1;
	else
		return 0;
}

int isNumber(char p){
	if (p >= '0'&&p <= '9')
		return 1;
	else
		return 0;
}

void nextp(){
	p++;
	thisch = ch[p];
}

void lastp(){
	p--;
	thisch = ch[p];
}

int isIF(){
	nextp();
	if (thisch == 'i'){
		nextp();
		if (thisch == 'f'){
			nextp();
			if (isLetter(thisch) == 0 && isNumber(thisch) == 0){
				lastp();
				return 1;
			}
			else{
				lastp();
				lastp();
				lastp();
			}
		}
		else{
			lastp();
			lastp();
		}
	}
	else{
		lastp();
	}
	return 0;
}

void error(){
	printf("ʶ���%d���ַ�ʱ���ִ���,�����ַ�Ϊ'%c'\n", p + 1, thisch);
}

int isIdentifier(){
	char idtemp[100];	//��ʱ�洢ʶ��ı�ʶ��
	strcpy(idtemp, "\0");
	int idtemplen = 0;
	nextp();
	idtemp[idtemplen] = thisch;
	idtemplen++;
	if (isLetter(thisch) == 1){
		for (;;){
			nextp();
			idtemp[idtemplen] = thisch;
			idtemplen++;
			if (!(isLetter(thisch) == 1 || isNumber(thisch) == 1)){
				idtemp[--idtemplen] = '\0';
				if (strcmp(idtemp, "if") == 0){
					lastp();
					return 0;
				}
				lastp();
				return 1;
			}
		}
	}
	else{
		error();
		return 0;
	}
}

int isUnsignedNum(){
	nextp();
	if (isNumber(thisch) == 0){
		error();
		return 0;
	}
	for (;;){
		nextp();
		if (isNumber(thisch) == 0){
			lastp();
			return 1;
		}
	}
}

int isCompare(){
	nextp();
	if (thisch == '<'){
		nextp();
		if (thisch == '='){
			return 1;
		}
		else{
			lastp();
			return 1;
		}
	}
	else if (thisch == '>'){
		nextp();
		if (thisch == '='){
			return 1;
		}
		else{
			lastp();
			return 1;
		}
	}
	else{
		error();
		return 0;
	}
}

int isFactor(){
	nextp();
	if (thisch == '('){
		int isExp = isExpression();
		//printf("exp:%d\n",isExp);
		if (isExp == 0){
			error();
			return 0;
		}
		nextp();
		if (thisch != ')'){
			error();
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		if (isNumber(thisch) == 1){
			lastp();
			if (isUnsignedNum() == 0){
				return 0;
			}
			else{
				return 1;
			}
		}
		else if (isLetter(thisch) == 1){
			lastp();
			if (isIdentifier() == 0){
				return 0;
			}
			else{
				return 1;
			}
		}
		else{
			//error();
			return 0;
		}
	}
}

int isExpression(){
	if (isFactor() == 1){
		nextp();
		if (thisch == '+' || thisch == '-' || thisch == '*' || thisch == '/'){
			if (isFactor() == 1){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			lastp();
			return 1;
		}
	}
	else{
		return 0;
	}
}

int isJudgeCondition(){
	if (isIdentifier() == 1){
		//�Ƿ��ǱȽ������
		if (isCompare() == 1){
			if (isFactor() == 1){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

int isEvaluate(){
	if (isIdentifier() == 1){
		nextp();
		if (thisch == '='){
			int isExp_eva = isExpression();
			//printf("isevaluate_exp:%d\n",isExp_eva);
			if (isExp_eva == 1){
				nextp();
				if (thisch == ';'){
					return 1;
				}
				else{
					error();
					return 0;
				}
			}
			else{
				error();
				return 0;
			}
		}
		else{
			error();
			return 0;
		}
	}
	else{
		return 0;
	}
}

int isCondition(){
	nextp();
	if (thisch == '('){
		if (isJudgeCondition() == 1){
			nextp();
			if (thisch == ')'){
				nextp();
				if (thisch == '{'){
					if (isIF() == 1){
						//��������ж�
						if (isCondition() == 0){
							error();
							return 0;
						}
						else{
							nextp();
							if (thisch == '}'){
								return 1;
							}
							else{
								error();
								return 0;
							}
						}
					}
					else{
						//��ֵ����ж�
						if (isEvaluate() == 1){
							nextp();
							//printf("thisch:%c",thisch );
							if (thisch == '}'){
								return 1;
							}
							else{
								error();
								return 0;
							}
						}
						else{
							return 0;
						}
					}
				}
				else{
					error();
					return 0;
				}
			}
			else{
				error();
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		error();
		return 0;
	}
}

void totalJudge(){
	for (;;){
		nextp();
		if (thisch == '#'){
			printf("�ó�������ȷ��\n");
			break;
		}
		else if (thisch == '\0'){
			printf("�ó���û����ֹ��\n");
			break;
		}
		else{
			lastp();
			if (isIF() == 1){
				//��������ж�
				if (isCondition() == 0){
					break;
				}
			}
			else{
				//��ֵ����ж�
				if (isEvaluate() == 0){
					break;
				}
			}
		}
	}
}

int main(void){
	getFileContent();
	totalJudge();
	system("PAUSE");
	return 0;
}