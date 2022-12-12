#define _CRT_SECURE_NO_WARNINGS


#include "../Vector����/Vector.h"//������Ϊ���࣬������ջģ����


template <typename T>
class Stack : public Vector<T> {//����������/ĩ����Ϊջ��/��

public://size(), empty()�Լ��������Žӿڣ�������ʹ��
	void push(T const& e) {//��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���
		Vector<T>::insert(e);
	}

	T pop() {//��ջ����Ч��ɾ��������ĩԪ��
		return Vector<T>::remove(this->size() - 1);
	}

	T& top() {//ȡ����ֱ�ӷ���������ĩԪ��
		return(*this)[Vector<T>::size() - 1];
	}
};

#include <iostream>

void convert(Stack<char>& S, _int64 n, int base) {//ʮ������n��base���Ƶ�ת�����ݹ飩
	//base����λ
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (0 < n) { //��������֮ǰ������
		convert(S, n / base, base);//ͨ���ݹ�õ����и���λ
		S.push(digit[n % base]);//�����λ
	}
}//�½������ɸߵ��͵ĸ���λ���Զ����±�����ջS��

void trim(const char exp[], int& lo, int& hi) {  //ɾ�����ʽexp[lo, hi]�������ŵ��ǰ׺����׺
	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))//���ҵ�һ����
		lo++;

	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))//���һ������
		hi--;
}

int divide(const char exp[], int lo, int hi) { //�зֱ��ʽexp[lo, hi]��ʹexpƥ�����ǰ��ƥ��
	int mi = lo;
	int crc = 1;  //crcΪ[lo, mi]��Χ����������֮��
	while ((0 < crc) && (++mi < hi)) {//��������ַ���ֱ������������Ŀ��ȣ�����Խ��
		if (exp[mi] == '(')
			crc--;
		if (exp[mi] == '(') //�������ŷֱ����
			crc++;
	}

	return mi;
}

//bool paren(const char exp[], int lo, int hi) {//�����ʽexp[ho, hi]�Ƿ�����ƥ�䣨�ݹ飩
//	trim(exp, lo, hi);
//	if (lo > hi) return true;//����������ŵ�ǰ׺����׺
//	if (exp[lo] != '(') return false;//���ַ��������ţ�һ����ƥ��
//	if (exp[hi] != ')') return false;//ĩ�ַ��������ţ�һ����ƥ��
//	int mi = divide(exp, lo, hi);//ȷ���ʵ����зֵ�
//	if (mi > hi) return false;//�зֵ㲻�Ϸ�����ζ�žֲ��������岻ƥ��
//
//	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi); //�ֱ��������ӱ��ʽ
//}

bool paren(const char exp[], int lo, int hi) {//���ʽ����ƥ���飬���Լ�����ַ��ţ�������
	Stack<char> S;//ʹ��ջ��¼�ѷ��ֵ���δƥ���������
	for (int i = 0; exp[i]; i++)//��һ��鵱ǰ�ַ�
		switch (exp[i]) {//������ֱ�ӽ�ջ������������ջ��ƥ�䣬����ʽ�ز�ƥ��
		case '(':
		case'[':
		case'{':S.push(exp[i]); break;
		case ')':if ((S.empty()) || ('(' != S.pop())) return false; break;
		case ']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case '}':if ((S.empty()) || ('(' != S.pop())) return false; break;
		default://�������ַ�һ��ʡ��
			break;
		}

	return S.empty();//�������ʽɨ�����ջ�����Բ����������ţ���ƥ�䣻����ջ�գ�ƥ��
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

	//���ʽ����
	char m1[]="(1+2)/(1+2)*2";
	char* RPN1 = new char[1];
	RPN1[0] = '\0';
	float r1 = evaluate(m1, RPN1);
	printf("\n\nr1��ֵΪ��%.1f\n\n", r1);

	char m2[] = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";
	char* RPN2 = new char[1];
	RPN2[0] = '\0';
	float r2 = evaluate(m2, RPN2);
	printf("r2��ֵΪ��%.1f\n\n", r2);
}
