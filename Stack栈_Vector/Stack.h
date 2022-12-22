#pragma once

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



