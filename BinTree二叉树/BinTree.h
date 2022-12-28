#pragma once

#include "BinNode.h"



template <typename T> 
struct Cleaner {
	static void clean(T x) {
#ifdef _DEBUG
		static int n = 0;
		if(7 > strlen(typeid(T).name())) {//复制类型一概忽略，只输出基本类型
			printf("\t<%s>[%d]=", typeid(T).name(), ++n);
			printf("%d", x);
			printf("purged\n");
		}
#endif
	}
};


template <typename T> 
struct Cleaner<T*> {
	static void clean(T* x) {//相当于递归基
		if (x) {
			delete x;//如果其中包含指针，递归释放
		}
#ifdef _DEBUG
		static int n = 0;
		printf("\t<%s>[%d] released\n", typeid(T*).name(), ++n);
#endif // _DEBUG

	}
};


template <typename T>
void release(T x) {
	Cleaner<T>::clean(x);
}


template <typename T>
class BinTree {//二叉树模板类
protected:
	int _size;//规模
	BinNodePosi<T> _root;//根节点
	virtual int updateHeight(BinNodePosi<T> x) {//更新节点x的高度
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}

	void updateHeightAbove(BinNodePosi<T> x) {//更新节点x及其祖先的高度
		while (x) {
			updateHeight(x);
			x = x->parent;
		}//从x出发，覆盖历代祖先
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

	BinNodePosi<T> insert(T const& e) {//插入根节点
		_size = 1;
		return _root = new BinNode<T>(e);//将e当作根节点插入空的二叉树
	}

	BinNodePosi<T> insert(T const& e, BinNodePosi<T> x) {//插入左孩子
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lc;//e插入为x的左孩子
	}

	BinNodePosi<T> insert(BinNodePosi<T> x, T const& e) {//插入右孩子
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rc;//e插入为x的右孩子
	}

	BinNodePosi<T> attach(BinTree<T>*& S, BinNodePosi<T> x) {//接入左子树
		if (x->lc = S->_root)
			x->lc->parent = x;//接入
		_size += S->_size;
		updateHeightAbove(x);//更新全树规模与x所有祖先的高度
		S->_root = NULL;
		S->_size = 0;
		release(S);
		S = NULL;
		return x;//释放原树，返回接入位置
	}

	BinNodePosi<T> attach(BinNodePosi<T> x, BinTree<T>*& S) {//接入右子树
		if (x->rc = S->_root)
			x->rc->parent = x;//接入
		_size += S->_size;
		updateHeightAbove(x);//更新全树规模与x所有祖先的高度
		S->_root = NULL;
		S->_size = 0;
		release(S);
		S = NULL;
		return x;//释放原树，返回接入位置
	}

	int remove(BinNodePosi<T> x) {//子树删除，删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
		FromPaentTo(*x) = NULL;//切断来自父节点的指针
		updateHeightAbove(x->parent);//更新祖先的高度
		int n = removeAt(x);//删除子树x
		_size -= n;//更新规模
		return n;//返回删除节点总数
	}

	static int removeAt(BinNodePosi<T> x){//删除二叉树中位置x处的节点及后代，返回被删除节点的数值
		if (!x) return 0;//递归基：空树
		int n = 1 + removeAt(x->lc) + removeAt(x->rc);//递归释放左、右子树
		release(x->data);
		release(x);//释放被摘除节点
		return n;//并返回删除节点总数
	}
};



