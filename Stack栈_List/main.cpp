#include <iostream>
using namespace std;

#include "../List列表/ListNode.h"

#include "../List列表/List.h"//以列表为基类，派生出栈模板类

template <typename T> class Stack :public List<T> {//将列表的首/末端作为栈顶/底
public://size(), empty()以及其他开放接口，都可以使用

	void push(T const& e) {//入栈：等效于将新元素作为列表的首元素插入
		List<T>::insertAsLast(e);
	}

	T pop() {//出栈：等效于删除列表的首元素
		return List<T>::remove(List<T>::last());
	}

	T& top() {//取顶：直接返回列表的首元素
		return List<T>::last()->data;
	}
};

int main()
{
	
}