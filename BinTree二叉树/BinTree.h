#pragma once

#include "BinNode.h"

template <typename T>
class BinTree {//二叉树模板类
protected:
	int _size;//规模
	BinNodePosi<T> _root;//根节点
	virtual int updateHeight(BinNodePosi<T> x) {

	}

public:
	BinTree() :_size(0), _root(NULL) {}//构造函数

	~BinTree() { if (0 < _size) remove(_root); } //析构函数

	int size() const {//规模
		return _size;
	}

	bool empty() const {//判空
		return !_root;
	}

	BinNodePosi<T> root() {//树根
		return _root;
	}

	BinNodePosi<T> insert(T const& ) {//插入根节点
		
	}
};
