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


/*DSA*/#define HeightUpdated(x) /*高度更新常规条件*/ \
/*DSA*/        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件

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
	

	template<typename VST> void travIn(VST& visit){//子树中序遍历
		travIn_I1(this, visit);//迭代版#1
		//travIn_I2(this, visit);//迭代版#2
		//travIn_I3(this, visit);//迭代版#3
		//travIn_I1(this, visit);//迭代版#4
		//travIn_R(this, visit);//递归版
	}


	template <typename VST>
	void travPost(VST& visit) {//子树后序遍历
		travPost_I(this, visit);//迭代版
		//travPost_R(this, visit);//递归版
	}


	//比较器，判等器
	bool operator<(BinNode const& bn) {//小于
		return data < bn.data;
	}

	bool operator==(BinNode const& bn) {//等于
		return data == bn.data;
	}

	BinNodePosi<T> zig() {//顺时针旋转
		BinNodePosi<T> lChild = lc;
		lChild->parent = this->parent;
		if (lChild->parent)
			((this == lChild->parent->rc) ? lChild->parent->rc : lChild->parent->lc) = lChild;
		lc = lChild->rc;
		if (lc) lc->parent = this;
		//update heights()
		height = 1 + max(stature(lc), stature(rc));
		lChild->height = 1 + max(stature(lChild->lc), stature(lChild->rc));
		for (BinNodePosi<T> x = lChild->parent; x; x = x->parent)
			if (HeightUpdated(*x))
				break;
			else {
				x->height = 1 + max(stature(x->lc), stature(x->rc));
			}
		return lChild;
	}

	BinNodePosi<T> zag() {//逆时针旋转
		BinNodePosi<T> rChild = rc;
		rChild->parent = this->parent;
		if (rChild->parent)
			((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
		rc = rChild->lc;
		if (rc) rc->parent = this;
		rChild->lc = this;
		this->parent = rChild;
		//update heights
		height = 1 + max(stature(lc), stature(rc));
		rChild->height = 1 + max(stature(rChild->lc), stature(rChild->rc));
		for (BinNodePosi<T> x = rChild->parent; x; x = x->parent)
			if (HeightUpdated(*x))
				break;
			else
				x->height = 1 + max(stature(x->lc), stature(x->rc));
		return rChild;
	}

	//BinNodePosi<T> balance() {//完全平衡化
	//	
	//}

	//BinNodePosi<T> imitate(const BinNodePosi<T> ){//临摹
	//
	//}
};


/***********************二叉树先序遍历算法travPre*************************/
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
/*******************************************************************************************************/


/************************二叉树中序遍历travIn************************/
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

template <typename T,typename VST>//元素类型，操作器
void treaIn_I4(BinNodePosi<T> x, VST& visit) {//二叉树中序遍历（迭代版#4）
	while (true)
		if (HasLChild(*x))//若有左子树，则
			x = x->lc;//深入遍历左子树
		else {//否则
			visit(x->data);//访问当前节点，并
			while (!HasRChild(*x))//不断地在无右分支处
				if (!(x = x->succ())) return;//回溯至直接后继（在没有后继的末节点处，直接退出）
				else visit(x->data);//访问新的当前节点
			x = x->rc;//（直至有右分支处）转向非空的右子树
		}
}

template <typename T, typename VST>//元素类型，操作器
void travIn_R(BinNodePosi<T> x, VST& visit) {//二叉树中序遍历算法（递归版）
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}
/*****************************************************************************************************************/


/***********************************二叉树后序遍历算法travPost***************************/
template <typename T>//在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S) {//沿途所遇节点依次入栈
	while(BinNodePosi<T> x = S.top())//自顶而下，反复检查当前节点（即栈顶）
		if (HasLChild(*x)) {//尽可能向左
			if (HasRChild(*x)) S.push(x->rc);//若有右孩子，优先入栈
			S.push(x->lc);//然后才转至左孩子
		} else//实在不得已
			S.push(x->rc);//才向右
		S.pop();//返回之前，弹出栈顶的空节点
}

template <typename T,typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit) {//二叉树的后序遍历（迭代版）
	Stack<BinNodePosi<T>> S;//辅助栈
	if (x) S.push(x);//根节点入栈
	while (!S.empty()) {//x始终为当前节点
		if (S.top() != x->parent)//若栈顶非x之父（而为右兄）
			gotoLeftmostLeaf(S);//则在其右兄子树找到HLVFL（相当于递归深入）
		x = S.pop();
		visit(x->data);//弹出栈顶（即前一节点的后继），并访问
	}
}

template <typename T, typename VST>//元素类型，操作器
void travPost_R(BinNodePosi<T> x, VST& visit) {//二叉树后序遍历算法（递归版）
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}
/********************************************************************************************************/



