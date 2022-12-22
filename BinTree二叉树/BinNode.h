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
#include "../Stackջ_Vector/Stack.h"

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
	void reavLevel(VST& visit) {//������α���
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


	template <typename VST>
	void travPre(VST& visit) {//�����������
		//��������������㷨ͳһ��ڣ����֣�
		travPre_I1(this, visit);//������#1
		//travPre_I2(this, visit);//������#2
		//travPre_R(this, visit);//�ݹ��
	}
	

	//template<typename VST> void travIn(VST&){//�����������
	//	travIn_I1
	//}

};

template <typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST& visit) {//�������������������#1��
	Stack<BinNodePosi<T>> S;//����ջ
	if (x)S.push(x);//���ڵ���ջ
	while (!S.empty()) {//��ջ���֮ǰ����ѭ��
		x = S.pop();
		visit(x->data);//���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ�������Һ���
		if (HasRChild(*x))S.push(x->rc);
		if (HasLChild(*x)) S.push(x->lc);
	}
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�����������������
template <typename T, typename VST>//Ԫ�����ͣ�������
static void visitAlongVing(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>> &S) {
	while (x) {
		visit(x->data);//���ʵ�ǰ�ڵ�
		S.push(x->rc);//�Һ�����ջ�ݴ�
		x = x->lc;//�����֧����һ��
	}
}

template<typename T,typename VST>//Ԫ�����ͣ�������
void travPre_I2(BinNodePosi<T> x, VST& visit) {//��������������㷨��������#2��
	Stack<BinNodePosi<T>> S;//����ջ
	while (true) {
		visitAlongVing(x, visit, S);//�ӵ�ǰ�ڵ��������������
		if (S.empty()) break;//ֱ��ջ��
		x = S.pop();//������һ���ڵ�
	}
}

template <typename T,typename VST>//Ԫ�����ͣ�������
void travPre_R(BinNodePosi<T> x, VST& visit) {//��������������㷨���ݹ�棩
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}




template <typename T>//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongVing(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S) {
	while (x) {
		S.push(x);
		x = x->lc;//��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
	}
}

template<typename T,typename VST>//Ԫ�����ͣ�������
void travIn_I1(BinNodePosi<T> x,VST& visit) {//��������������㷨��������#1��
	Stack<BinNodePosi<T>> S;//����ջ
	while (true) {
		goAlongVing(x, S);//�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break;//ֱ�����нڵ㴦�����
		x = S.pop();
		visit(x->data);//����ջ���ڵ㲢����
		x = x->rc;//ת��������
	}
}

template <typename T, typename VST>//Ԫ�����ͣ�������
void travIn_I2(BinNodePosi<T> x, VST& visit) {//��������������㷨��������#2��
	Stack<BinNodePosi<T>> S;//����ջ
	while(true)
		if (x) {
			S.push(x);//���ڵ��ջ
			x = x->lc;//�������������
		} else if (!S.empty()) {
			x = S.pop();//��δ���ʵ�������Ƚڵ���ջ
			visit(x->data);//���ʸ����Ƚڵ�
			x = x->rc;//�������ȵ�������
		} else
			break;//�������
}

template <typename T,typename VST>//Ԫ�����ͣ�������
void travIn_I3(BinNodePosi<T> x, VST& visit) {//��������������㷨��������#3��
	bool backtrack = false;//ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O��1)�����ռ�
	while (true)
		if (!backtrack && HasLChild(*x)) {//�����������Ҳ��Ǹոջ��ݣ���
			x = x->rc;//�������������
		} else {//���򡪡�����������ոջ��ݣ��൱������������
			visit(x->data);//���ʸýڵ�
			if (HasRChild(*x)) {//�����������ǿգ���
				x = x->rc;//������������������
				backtrack = false;//���رջ��ݱ�־
			} else {//���������գ���
				if (!(x = x->succ())) break;//���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
				backtrack = true;//�����û��ݱ�־
			}
		}
}