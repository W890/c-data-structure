#pragma once

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



