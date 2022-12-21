#pragma once

#if defined(DSA_REDBLACK)
#define stature(p) ((p)?(p)->height:0)
#else
#define stature(p) ((p)?(p)->height:-1)
#endif

//BinNode״̬�����ʵ��ж�
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) (HasLChild(x) || HasRChild(x))//����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))//ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))


//��BinNode�����ص��ϵ�Ľڵ㼰ָ��
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc) //�ֵ�
#define uncle(x) (sibling((x)->parent)) //����
#define FromPaentTo(x) (IsRoot(x) ? _root:(IsLChild(x) ? (x).parent->lc:(x).parent->rc))//���Ը��׵�����


#include "../Queue����_List/queue.h"

typedef enum {
	RB_RED, RB_BLACK
}RBColor;//�ڵ���ɫ

template <typename T> 
struct BinNode;

template <typename T> 
using BinNodePosi = BinNode<T>*;//�ڵ�λ��

template <typename T> 
struct BinNode {
	T data;
	BinNodePosi<T> parent, lc, rc;//���ڵ㼰���Һ���
	int height;//�߶ȣ�ͨ�ã�
	int npl;//Null Path Length ����ʽ�ѣ�Ҳ������height���棩
	RBColor color;//��ɫ���������

	//���캯��
	BinNode():parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}

	BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

	//�����ӿ�
	int size() {//ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
		int s = 1;//���뱾��
		if (lc)s += lc->size();//�ݹ������������ģ
		if (rc)s += rc->size();//�ݹ������������ģ
		return s;
	}

	BinNodePosi<T> insertAsLC(T const& e) {//��e��Ϊ��ǰ�ڵ�����Ӳ��������
		return lc = new BinNode(e, this);
	}

	BinNodePosi<T> insertAsRC(T const& e) {//��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
		return rc = new BinNode(e, this);
	}

	BinNodePosi<T> succ() {//ȥ��ǰ�ڵ��ֱ�Ӻ��
		BinNodePosi<T> s = this;//��¼��̵���ʱ����
		if (rc) {//�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
			s = rc;//��������
			while (HasLChild(*s))s = s->lc;//�����С���Ľڵ�
		} else {//����ֱ�Ӻ��Ӱ�ӡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
			while (IsRChild(*s))s = s->parent;//������������֧�����ϳ����Ϸ��ƶ�
			s = s->parent;//����ٳ����Ϸ��ƶ�һС�������ִ�ֱ�Ӻ�̣�������ڣ�
		}
		return s;
	}

	template <typename VST> 
	void reavLevel(VST& visit) {//��������α����㷨
		Queue<BinNodePosi<T>> Q;//��������
		Q.enqueue(this);//���ڵ�����
		while (!Q.empty()) {//�ڶ����ٴα��֮ǰ����������
			BinNodePosi<T>x = Q.dequeue();
			visit(x->data);//ȡ�����׽ڵ㲢����
			if (HasLChild(*x))
				Q.enqueue(x->lc);//�������
			if (HasRChild(*x))
				Q.enqueue(x->rc);//�Һ������
		}
	}

};



