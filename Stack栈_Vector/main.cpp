#define _CRT_SECURE_NO_WARNINGS


#include "../Vector向量/Vector.h"//以向量为基类，派生出栈模板类


template <typename T>
class Stack : public Vector<T> {//将向量的首/末端作为栈底/顶

public://size(), empty()以及其他开放接口，都可以使用
	void push(T const& e) {//入栈：等效于将新元素作为向量的末元素插入
		Vector<T>::insert(e);
	}

	T pop() {//出栈：等效于删除向量的末元素
		return Vector<T>::remove(this->size() - 1);
	}

	T& top() {//取顶：直接返回向量的末元素
		return(*this)[Vector<T>::size() - 1];
	}
};

#include <iostream>

void convert(Stack<char>& S, _int64 n, int base) {//十进制数n到base进制的转换（递归）
	//base进制位
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (0 < n) { //尚有余数之前，不断
		convert(S, n / base, base);//通过递归得到所有更高位
		S.push(digit[n % base]);//输出低位
	}
}//新进制下由高到低的各数位，自顶而下保存于栈S中

void trim(const char exp[], int& lo, int& hi) {  //删除表达式exp[lo, hi]不含括号的最长前缀、后缀
	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))//查找第一个和
		lo++;

	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))//最后一个括号
		hi--;
}

int divide(const char exp[], int lo, int hi) { //切分表达式exp[lo, hi]，使exp匹配仅当前的匹配
	int mi = lo;
	int crc = 1;  //crc为[lo, mi]范围内左、右括号之差
	while ((0 < crc) && (++mi < hi)) {//逐个检查各字符，直到左右括号数目相等，或者越界
		if (exp[mi] == '(')
			crc--;
		if (exp[mi] == '(') //左右括号分别计算
			crc++;
	}

	return mi;
}

//bool paren(const char exp[], int lo, int hi) {//检查表达式exp[ho, hi]是否括号匹配（递归）
//	trim(exp, lo, hi);
//	if (lo > hi) return true;//清除不含括号的前缀、后缀
//	if (exp[lo] != '(') return false;//首字符非左括号，一定不匹配
//	if (exp[hi] != ')') return false;//末字符非右括号，一定不匹配
//	int mi = divide(exp, lo, hi);//确定适当的切分点
//	if (mi > hi) return false;//切分点不合法，意味着局部以致整体不匹配
//
//	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi); //分别检查左右子表达式
//}

bool paren(const char exp[], int lo, int hi) {//表达式括号匹配检查，可以兼顾三种符号（迭代）
	Stack<char> S;//使用栈记录已发现但尚未匹配的左括号
	for (int i = 0; exp[i]; i++)//逐一检查当前字符
		switch (exp[i]) {//左括号直接进栈；右括号若与栈顶匹配，则表达式必不匹配
		case '(':
		case'[':
		case'{':S.push(exp[i]); break;
		case ')':if ((S.empty()) || ('(' != S.pop())) return false; break;
		case ']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case '}':if ((S.empty()) || ('(' != S.pop())) return false; break;
		default://非括号字符一律省略
			break;
		}

	return S.empty();//整个表达式扫描过后，栈中若仍残留（左）括号，则不匹配；否则（栈空）匹配
}

#include "RPN.h"

int main()
{
	using namespace std;

	Stack<int> S1;
	for (int i = 1; i <= 5; i++) {
		S1.push(i);
	}
	for (int i = 0; i < 5; i++) {
		printf("%d ", S1[i]);
	}
	printf("\nS1size:%d\n", S1.size());
	for (int i = S1.size(); i >= 4; i--) {
		S1.pop();
	}
	//S1.pop();
	printf("S1size:%d\n", S1.size());
	printf("\n");
	for (int i = 0; i < S1.size(); i++) {
		printf("%d ", S1[i]);
	}

	//表达式测试
	char m1[]="(1+2)/(1+2)*2";
	char* RPN1 = new char[1];
	RPN1[0] = '\0';
	float r1 = evaluate(m1, RPN1);
	printf("\n\nr1的值为：%.1f\n\n", r1);

	char m2[] = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";
	char* RPN2 = new char[1];
	RPN2[0] = '\0';
	float r2 = evaluate(m2, RPN2);
	printf("r2的值为：%.1f\n\n", r2);
}
