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
#include "../Stack栈_Vector/Stack.h"

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
	void reavLevel(VST& visit) {//子树层次遍历
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


	template <typename VST>
	void travPre(VST& visit) {//子树先序遍历
		//二叉树先序遍历算法统一入口（三种）
		travPre_I1(this, visit);//迭代版#1
		//travPre_I2(this, visit);//迭代版#2
		//travPre_R(this, visit);//递归版
	}
	

	//template<typename VST> void travIn(VST&){//子树中序遍历
	//	travIn_I1
	//}

};

template <typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST& visit) {//子树先序遍历（迭代版#1）
	Stack<BinNodePosi<T>> S;//辅助栈
	if (x)S.push(x);//根节点入栈
	while (!S.empty()) {//在栈变空之前反复循环
		x = S.pop();
		visit(x->data);//弹出并访问当前节点，其非空孩子的入栈次序先右后左
		if (HasRChild(*x))S.push(x->rc);
		if (HasLChild(*x)) S.push(x->lc);
	}
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途结点遇到后立即访问
template <typename T, typename VST>//元素类型，操作器
static void visitAlongVing(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>> &S) {
	while (x) {
		visit(x->data);//访问当前节点
		S.push(x->rc);//右孩子入栈暂存
		x = x->lc;//沿左分支深入一层
	}
}

template<typename T,typename VST>//元素类型，操作器
void travPre_I2(BinNodePosi<T> x, VST& visit) {//二叉树先序遍历算法（迭代版#2）
	Stack<BinNodePosi<T>> S;//辅助栈
	while (true) {
		visitAlongVing(x, visit, S);//从当前节点出发，逐批访问
		if (S.empty()) break;//直到栈空
		x = S.pop();//弹出下一批节点
	}
}

template <typename T,typename VST>//元素类型，操作器
void travPre_R(BinNodePosi<T> x, VST& visit) {//二叉树先序遍历算法（递归版）
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}




template <typename T>//从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongVing(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S) {
	while (x) {
		S.push(x);
		x = x->lc;//当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
	}
}

template<typename T,typename VST>//元素类型，操作器
void travIn_I1(BinNodePosi<T> x,VST& visit) {//二叉树中序遍历算法（迭代版#1）
	Stack<BinNodePosi<T>> S;//辅助栈
	while (true) {
		goAlongVing(x, S);//从当前节点出发，逐批入栈
		if (S.empty()) break;//直至所有节点处理完毕
		x = S.pop();
		visit(x->data);//弹出栈顶节点并访问
		x = x->rc;//转向右子树
	}
}

template <typename T, typename VST>//元素类型，操作器
void travIn_I2(BinNodePosi<T> x, VST& visit) {//二叉树中序遍历算法（迭代版#2）
	Stack<BinNodePosi<T>> S;//辅助栈
	while(true)
		if (x) {
			S.push(x);//根节点进栈
			x = x->lc;//深入遍历左子树
		} else if (!S.empty()) {
			x = S.pop();//尚未访问的最低祖先节点退栈
			visit(x->data);//访问该祖先节点
			x = x->rc;//遍历祖先的右子树
		} else
			break;//遍历完成
}

template <typename T,typename VST>//元素类型，操作器
void travIn_I3(BinNodePosi<T> x, VST& visit) {//二叉树中序遍历算法（迭代版#3）
	bool backtrack = false;//前一步是否刚从左子树回溯——省去栈，仅O（1)辅助空间
	while (true)
		if (!backtrack && HasLChild(*x)) {//若有左子树且不是刚刚回溯，则
			x = x->rc;//深入遍历左子树
		} else {//否则——无左子树或刚刚回溯（相当于无左子树）
			visit(x->data);//访问该节点
			if (HasRChild(*x)) {//若其右子树非空，则
				x = x->rc;//深入右子树继续遍历
				backtrack = false;//并关闭回溯标志
			} else {//若右子树空，则
				if (!(x = x->succ())) break;//回溯（含抵达末节点时的退出返回）
				backtrack = true;//并设置回溯标志
			}
		}
}