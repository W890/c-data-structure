#pragma once

#if defined(DSA_REDBLACK)
#define stature(p) ((p)?(p)->height:0)
#else
#define stature(p) ((p)?(p)->height:-1)
#endif

//BinNode状态与性质的判断
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) (HasLChild(x) || HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))//同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))


//与BinNode具有特点关系的节点及指针
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc) //兄弟
#define uncle(x) (sibling((x)->parent)) //叔叔
#define FromPaentTo(x) (IsRoot(x) ? _root:(IsLChild(x) ? (x).parent->lc:(x).parent->rc))//来自父亲的引用


#include "../Queue队列_List/queue.h"

typedef enum {
	RB_RED, RB_BLACK
}RBColor;//节点颜色

template <typename T> 
struct BinNode;

template <typename T> 
using BinNodePosi = BinNode<T>*;//节点位置

template <typename T> 
struct BinNode {
	T data;
	BinNodePosi<T> parent, lc, rc;//父节点及左、右孩子
	int height;//高度（通用）
	int npl;//Null Path Length （左式堆，也可以用height代替）
	RBColor color;//颜色（红黑树）

	//构造函数
	BinNode():parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}

	BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

	//操作接口
	int size() {//统计当前节点后代总数，即以其为根的子树规模
		int s = 1;//计入本身
		if (lc)s += lc->size();//递归计入左子树规模
		if (rc)s += rc->size();//递归计入右子树规模
		return s;
	}

	BinNodePosi<T> insertAsLC(T const& e) {//将e作为当前节点的左孩子插入二叉树
		return lc = new BinNode(e, this);
	}

	BinNodePosi<T> insertAsRC(T const& e) {//将e作为当前节点的右孩子插入二叉树
		return rc = new BinNode(e, this);
	}

	BinNodePosi<T> succ() {//去当前节点的直接后继
		BinNodePosi<T> s = this;//记录后继的临时变量
		if (rc) {//若有右孩子，则直接后继必在右子树中，具体地就是
			s = rc;//右子树中
			while (HasLChild(*s))s = s->lc;//最靠左（最小）的节点
		} else {//否则，直接后继影视“将当前节点包含于其左子树中的最低祖先”，具体地就是
			while (IsRChild(*s))s = s->parent;//逆向地沿右向分支，不断朝左上方移动
			s = s->parent;//最后再朝右上方移动一小步，即抵达直接后继（如果存在）
		}
		return s;
	}

	template <typename VST> 
	void reavLevel(VST& visit) {//二叉树层次遍历算法
		Queue<BinNodePosi<T>> Q;//辅助队列
		Q.enqueue(this);//根节点入列
		while (!Q.empty()) {//在队列再次变空之前，反复迭代
			BinNodePosi<T>x = Q.dequeue();
			visit(x->data);//取出队首节点并访问
			if (HasLChild(*x))
				Q.enqueue(x->lc);//左孩子入队
			if (HasRChild(*x))
				Q.enqueue(x->rc);//右孩子入队
		}
	}

};



