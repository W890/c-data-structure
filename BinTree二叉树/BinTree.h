#pragma once

#include "BinNode.h"

template <typename T>
class BinTree {//������ģ����
protected:
	int _size;//��ģ
	BinNodePosi<T> _root;//���ڵ�
	virtual int updateHeight(BinNodePosi<T> x) {

	}

public:
	BinTree() :_size(0), _root(NULL) {}//���캯��

	~BinTree() { if (0 < _size) remove(_root); } //��������

	int size() const {//��ģ
		return _size;
	}

	bool empty() const {//�п�
		return !_root;
	}

	BinNodePosi<T> root() {//����
		return _root;
	}

	BinNodePosi<T> insert(T const& ) {//������ڵ�
		
	}
};
