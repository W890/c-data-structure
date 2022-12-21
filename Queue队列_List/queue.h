#pragma once


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

