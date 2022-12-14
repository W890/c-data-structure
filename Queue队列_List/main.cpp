#include <iostream>
using namespace std;


#include "../List列表/List.h"//以List为基类

template <typename T> class Queue :public List<T> {//队列模板类（继承List原有接口
public://size(), empty()以及其他开放接口都可以直接使用

	void enqueue(T const& e) {//入队：尾部插入
		List<T>::insertAsLast(e);
	}

	T dequeue() {//出队：首部删除
		return List<T>::remove(List<T>::first());
	}

	T& front() {//队首
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