#include <iostream>
using namespace std;


#include "../List�б�/List.h"//��ListΪ����

template <typename T> class Queue :public List<T> {//����ģ���ࣨ�̳�Listԭ�нӿ�
public://size(), empty()�Լ��������Žӿڶ�����ֱ��ʹ��

	void enqueue(T const& e) {//��ӣ�β������
		List<T>::insertAsLast(e);
	}

	T dequeue() {//���ӣ��ײ�ɾ��
		return List<T>::remove(List<T>::first());
	}

	T& front() {//����
		return List<T>::first()->data;
	}
};

int main() {
	Queue<int> Q1;
	for (int i = 1; i <= 6; i++) {
		Q1.enqueue(i);
	}
	Q1.print();
	printf("\n");
	for (int i = 1; i <= 3; i++) {
		Q1.dequeue();
	}
	Q1.print();
}