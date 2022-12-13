#pragma once


void readNumber(char*& p, Stack<float>& stk) {//将起始于p的子串解析为数值，并存入操作数栈
	stk.push((float)(*p - '0'));//当前数位对应的数值进栈

	while (isdigit(*(++p)))//只要后续还有紧邻的数字（即多位整数的情况），则
		stk.push(stk.pop() * 10 + (*p - '0'));//弹出原操作数并追加新数位后，新数值重新入栈

	if ('.' != *p) return;//此后非小数点，则意味着当前操作数解析完成

	float fraction = 1;//否则，意味着还有小数部分

	while (isdigit(*(++p)))//逐位加入
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));//小数部分
}


void append(char*& rpn, float opnd) {//将操作数接至RPN末尾
	int n = strlen(rpn);//RPN当前长度（以'\0'结尾，长度n + 1）
	char buf[64];

	if (opnd != (float)(int)opnd)
		sprintf(buf, "%.2f \0", opnd);//浮点格式，或
	else
		sprintf(buf, "%d \0", (int)opnd);//整数格式

	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //扩展空间
	strcat(rpn, buf);//RPN加长
}


void append(char*& rpn, char optr) {//将运算符接至RPN末尾
	int n = strlen(rpn);//RPN当前长度（以'\0'结尾，长度n + 1）
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3));//扩展空间
	sprintf(rpn + n, "%c ", optr);
	rpn[n + 2] = '\0'; //接入指定的运算符
}


#define N_OPTR 9//运算符总数

typedef enum {//运算符集合

	//   加， 减， 乘，  除，  乘方， 阶乘， 左括号，右括号，起始符与终止符
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;


const char pri[N_OPTR][N_OPTR] = {//运算符优先等级[栈顶][当前]
	/*                 |--------------当前运算符-------------------|      */
	/*                  +    -    *    /    ^    !    (    )    \0       */
	/* --   +  */      '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* |    -  */      '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* 栈   *  */      '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 顶   /  */      '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 运   ^  */      '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/* 算   !  */      '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/* 符   (  */      '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* |    )  */      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/* --  \0  */      '<', '<', '<', '<', '<', '<', '<', ' ', '='
};


Operator optr2rank(char op) {//由运算符转译编号
	switch (op) {
	case '+':return ADD; //加
	case '-':return SUB; //减
	case '*':return MUL; //乘
	case '/':return DIV; //除
	case '^':return POW; //乘方
	case '!':return FAC; //阶乘
	case '(':return L_P; //左括号
	case ')':return R_P; //右括号
	case '\0':return EOE; //起始符与终止符
	default:exit(-1);//未知运算符
	}
}


char orderBetween(char op1, char op2) {//比较两个运算符之间的优先级
	return pri[optr2rank(op1)][optr2rank(op2)];
}


int factorial(float number) {//求阶乘运算
	int fact = 1;
	for (int i = 1; i <= number; i++) {
		fact *= i;
	}
	return fact;
}


float calcu(char op, float num) {//一元计算
	return (float)factorial(num);
}

#include <math.h>

float calcu(float num1, char op, float num2) {//二元计算
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


float evaluate(char* S, char*& RPN) {//对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
	Stack<float> opnd;//运算数栈
	Stack<char> optr;//运算符栈
	optr.push('\0');//尾哨兵'\0'也作为头哨兵首先入栈

	while (!optr.empty()) {//在运算符栈非空之前，逐个处理表达式中各字符
		if (isdigit(*S)) {//若当前字符为操作数，则
			readNumber(S, opnd);
			append(RPN, opnd.top());//读入操作数，并将其接至RPN末尾
		} else {//若当前字符为运算符，则
			switch (orderBetween(optr.top(), *S)) {//视其与栈顶运算符之间优先级高低分处理
			case '<': optr.push(*S); //栈顶运算符优先级更低时，计算推迟，当前运算符进栈
				S++;
				break;
			case '=': optr.pop();//优先级相等（当前运算符为右括号或者尾部哨兵'\0')时，脱括号并接收下一个字符
				S++;
				break;
			case '>':
			{//栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
				char op = optr.pop();
				append(RPN, op);//栈顶运算符出栈并续接至RPN末尾
				if ('!' == op) {//若属于一元运算符
					float pOpnd = opnd.pop();//只需读取出一个操作数，并
					opnd.push(calcu(op, pOpnd));//实施一元计算，结果入栈
				} else {//对于其他（二元）运算符
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();//取出后、前操作数
					opnd.push(calcu(pOpnd1, op, pOpnd2));//实施二元计算，结果入栈
				}
				break;
			}
			default:exit(-1);//逢语法错误，不做处理直接退出
			}
		} //switch
	}//while
	return opnd.pop();//弹出并返回最后的计算结果
}
