#pragma once

using Rank = int;//秩

template <typename T> 
struct ListNode;


template <typename T> 
using ListNodePosi = ListNode<T>*;//列表节点位置


template <typename T> 
struct ListNode {//列表节点模板类（以双向链表形式实现）
	//成员
	T data; ListNodePosi<T> pred; ListNodePosi<T> succ;//数值、前驱、后继
	//构造函数
	ListNode() {}//针对header和trailer的构造
	ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL):data(e), pred(p), succ(s) {}//默认构造器
	//操作接口
	ListNodePosi<T> insertAsPred(T const& e);//紧靠当前节点之前插入新节点
	ListNodePosi<T> insertAsSucc(T const& e);//紧靠当前节点之后插入新节点
};

template <typename T>//将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾结点trailer）
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi<T> x = new ListNode(e, this, succ);//创建新节点
	succ->pred = x; succ = x;//设置逆向连接
	return x;//返回新节点位置
}

template <typename T>//将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头结点header)
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi<T> x = new ListNode(e, pred, this);//创建新节点
	pred->succ = x; pred = x;//设置正向链表
	return x;//返回新节点的位置
}

