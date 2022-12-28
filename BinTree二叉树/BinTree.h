#pragma once

#include "BinNode.h"



template <typename T> 
struct Cleaner {
	static void clean(T x) {
#ifdef _DEBUG
		static int n = 0;
		if(7 > strlen(typeid(T).name())) {//��������һ�ź��ԣ�ֻ�����������
			printf("\t<%s>[%d]=", typeid(T).name(), ++n);
			printf("%d", x);
			printf("purged\n");
		}
#endif
	}
};


template <typename T> 
struct Cleaner<T*> {
	static void clean(T* x) {//�൱�ڵݹ��
		if (x) {
			delete x;//������а���ָ�룬�ݹ��ͷ�
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
class BinTree {//������ģ����
protected:
	int _size;//��ģ
	BinNodePosi<T> _root;//���ڵ�
	virtual int updateHeight(BinNodePosi<T> x) {//���½ڵ�x�ĸ߶�
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}

	void updateHeightAbove(BinNodePosi<T> x) {//���½ڵ�x�������ȵĸ߶�
		while (x) {
			updateHeight(x);
			x = x->parent;
		}//��x������������������
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

	BinNodePosi<T> insert(T const& e) {//������ڵ�
		_size = 1;
		return _root = new BinNode<T>(e);//��e�������ڵ����յĶ�����
	}

	BinNodePosi<T> insert(T const& e, BinNodePosi<T> x) {//��������
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lc;//e����Ϊx������
	}

	BinNodePosi<T> insert(BinNodePosi<T> x, T const& e) {//�����Һ���
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rc;//e����Ϊx���Һ���
	}

	BinNodePosi<T> attach(BinTree<T>*& S, BinNodePosi<T> x) {//����������
		if (x->lc = S->_root)
			x->lc->parent = x;//����
		_size += S->_size;
		updateHeightAbove(x);//����ȫ����ģ��x�������ȵĸ߶�
		S->_root = NULL;
		S->_size = 0;
		release(S);
		S = NULL;
		return x;//�ͷ�ԭ�������ؽ���λ��
	}

	BinNodePosi<T> attach(BinNodePosi<T> x, BinTree<T>*& S) {//����������
		if (x->rc = S->_root)
			x->rc->parent = x;//����
		_size += S->_size;
		updateHeightAbove(x);//����ȫ����ģ��x�������ȵĸ߶�
		S->_root = NULL;
		S->_size = 0;
		release(S);
		S = NULL;
		return x;//�ͷ�ԭ�������ؽ���λ��
	}

	int remove(BinNodePosi<T> x) {//����ɾ����ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
		FromPaentTo(*x) = NULL;//�ж����Ը��ڵ��ָ��
		updateHeightAbove(x->parent);//�������ȵĸ߶�
		int n = removeAt(x);//ɾ������x
		_size -= n;//���¹�ģ
		return n;//����ɾ���ڵ�����
	}

	static int removeAt(BinNodePosi<T> x){//ɾ����������λ��x���Ľڵ㼰��������ر�ɾ���ڵ����ֵ
		if (!x) return 0;//�ݹ��������
		int n = 1 + removeAt(x->lc) + removeAt(x->rc);//�ݹ��ͷ���������
		release(x->data);
		release(x);//�ͷű�ժ���ڵ�
		return n;//������ɾ���ڵ�����
	}
};



