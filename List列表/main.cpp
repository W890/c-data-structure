#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#include "ListNode.h"

template <typename T> class List {
	
private:
	int _size; ListNodePosi<T> header; ListNodePosi<T> trailer; //规模，头哨兵，尾哨兵
protected:
	void init() {//列表初始化，在创建列表对象时统一调用
		header = new ListNode<T>;//创建头哨兵节点
		trailer = new ListNode<T>;//创建尾哨兵节点
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0;//记录规模
	}

public:
	//构造函数
	List() { init(); } //默认
	List(List<T> const& L); //整体复制列表L
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi<T> p, int n); //复制列表中自位置p起的n项

	//析构函数
	~List() {} //释放（包含头、尾哨兵在内的）所有节点

	ListNodePosi<T> insertAsFirst(T const& e) {//将e当作首节点插入
		_size++;
		return header->insertAsSucc(e); 
	}

	ListNodePosi<T> insertAsLast(T const& e) {//将e当作末节点插入
		_size++;
		return trailer->insertAsPred(e);
	}

	ListNodePosi<T> insert(ListNodePosi<T> p, T const& e) {//e当作p的后继插入
		_size++;
		return p->insertAsSucc(e);
	}

	ListNodePosi<T> insert(T const& e, ListNodePosi<T> p) {//e当作p的前驱插入
		_size++;
		return p->insertAsPred(e);
	}
};

//template <typename T>
//void randomList(List<T>& list, int n) {
//	ListNodePosi<T> p = list.insertAsFist(rand() % (T)(n * 4));
//	for (int i = 1; i < n; i++) {
//		p = insert(p, rand() % (T)(n * 4));
//	}
//}

int main() {
	List<int> L1;
	ListNodePosi<int> p;
	p = L1.insertAsFirst(1);
	for (int i = 1; i < 5; i++) {
		L1.insert(i, p);
	}

}	