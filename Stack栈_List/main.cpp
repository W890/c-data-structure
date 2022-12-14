#include <iostream>
using namespace std;

#include "../List�б�/List.h"//���б�Ϊ���࣬������ջģ����

template <typename T> class Stack :public List<T> {//���б����/ĩ����Ϊջ��/��
public://size(), empty()�Լ��������Žӿڣ�������ʹ��

	void push(T const& e) {//��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
		List<T>::insertAsLast(e);
	}

	T pop() {//��ջ����Ч��ɾ���б����Ԫ��
		return List<T>::remove(List<T>::last());
	}

	T& top() {//ȡ����ֱ�ӷ����б����Ԫ��
		return List<T>::last()->data;
	}
};

int main()
{
	Stack<int> S1;
	for (int i = 1; i <= 6; i++) {
		S1.push(i);
	}
	S1.print();
	printf("\n");
	for (int i = S1.size(); i >= 4; i--) {
		S1.pop();
	}
	S1.print();
}