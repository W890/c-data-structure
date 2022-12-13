#pragma once


void readNumber(char*& p, Stack<float>& stk) {//����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
	stk.push((float)(*p - '0'));//��ǰ��λ��Ӧ����ֵ��ջ

	while (isdigit(*(++p)))//ֻҪ�������н��ڵ����֣�����λ���������������
		stk.push(stk.pop() * 10 + (*p - '0'));//����ԭ��������׷������λ������ֵ������ջ

	if ('.' != *p) return;//�˺��С���㣬����ζ�ŵ�ǰ�������������

	float fraction = 1;//������ζ�Ż���С������

	while (isdigit(*(++p)))//��λ����
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));//С������
}


void append(char*& rpn, float opnd) {//������������RPNĩβ
	int n = strlen(rpn);//RPN��ǰ���ȣ���'\0'��β������n + 1��
	char buf[64];

	if (opnd != (float)(int)opnd)
		sprintf(buf, "%.2f \0", opnd);//�����ʽ����
	else
		sprintf(buf, "%d \0", (int)opnd);//������ʽ

	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //��չ�ռ�
	strcat(rpn, buf);//RPN�ӳ�
}


void append(char*& rpn, char optr) {//�����������RPNĩβ
	int n = strlen(rpn);//RPN��ǰ���ȣ���'\0'��β������n + 1��
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3));//��չ�ռ�
	sprintf(rpn + n, "%c ", optr);
	rpn[n + 2] = '\0'; //����ָ���������
}


#define N_OPTR 9//���������

typedef enum {//���������

	//   �ӣ� ���� �ˣ�  ����  �˷��� �׳ˣ� �����ţ������ţ���ʼ������ֹ��
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;


const char pri[N_OPTR][N_OPTR] = {//��������ȵȼ�[ջ��][��ǰ]
	/*                 |--------------��ǰ�����-------------------|      */
	/*                  +    -    *    /    ^    !    (    )    \0       */
	/* --   +  */      '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* |    -  */      '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* ջ   *  */      '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* ��   /  */      '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* ��   ^  */      '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/* ��   !  */      '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/* ��   (  */      '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* |    )  */      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/* --  \0  */      '<', '<', '<', '<', '<', '<', '<', ' ', '='
};


Operator optr2rank(char op) {//�������ת����
	switch (op) {
	case '+':return ADD; //��
	case '-':return SUB; //��
	case '*':return MUL; //��
	case '/':return DIV; //��
	case '^':return POW; //�˷�
	case '!':return FAC; //�׳�
	case '(':return L_P; //������
	case ')':return R_P; //������
	case '\0':return EOE; //��ʼ������ֹ��
	default:exit(-1);//δ֪�����
	}
}


char orderBetween(char op1, char op2) {//�Ƚ����������֮������ȼ�
	return pri[optr2rank(op1)][optr2rank(op2)];
}


int factorial(float number) {//��׳�����
	int fact = 1;
	for (int i = 1; i <= number; i++) {
		fact *= i;
	}
	return fact;
}


float calcu(char op, float num) {//һԪ����
	return (float)factorial(num);
}

#include <math.h>

float calcu(float num1, char op, float num2) {//��Ԫ����
	float number = 0.0;
	switch (op) {
	case '+':number = num1 + num2; break;
	case '-':number = num1 - num2; break;
	case '*':number = num1 * num2; break;
	case '/':number = num1 / num2; break;
	case '^':number = pow(num1, num2); break;
	}

	return number;
}


float evaluate(char* S, char*& RPN) {//�ԣ����޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN
	Stack<float> opnd;//������ջ
	Stack<char> optr;//�����ջ
	optr.push('\0');//β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ

	while (!optr.empty()) {//�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
		if (isdigit(*S)) {//����ǰ�ַ�Ϊ����������
			readNumber(S, opnd);
			append(RPN, opnd.top());//��������������������RPNĩβ
		} else {//����ǰ�ַ�Ϊ���������
			switch (orderBetween(optr.top(), *S)) {//������ջ�������֮�����ȼ��ߵͷִ���
			case '<': optr.push(*S); //ջ����������ȼ�����ʱ�������Ƴ٣���ǰ�������ջ
				S++;
				break;
			case '=': optr.pop();//���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0')ʱ�������Ų�������һ���ַ�
				S++;
				break;
			case '>':
			{//ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop();
				append(RPN, op);//ջ���������ջ��������RPNĩβ
				if ('!' == op) {//������һԪ�����
					float pOpnd = opnd.pop();//ֻ���ȡ��һ������������
					opnd.push(calcu(op, pOpnd));//ʵʩһԪ���㣬�����ջ
				} else {//������������Ԫ�������
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();//ȡ����ǰ������
					opnd.push(calcu(pOpnd1, op, pOpnd2));//ʵʩ��Ԫ���㣬�����ջ
				}
				break;
			}
			default:exit(-1);//���﷨���󣬲�������ֱ���˳�
			}
		} //switch
	}//while
	return opnd.pop();//�������������ļ�����
}
