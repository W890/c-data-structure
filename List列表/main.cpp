#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#include "ListNode.h"

template <typename T> class List {
	
private:
	int _size; ListNodePosi<T> header; ListNodePosi<T> trailer; //��ģ��ͷ�ڱ���β�ڱ�
protected:
	void init() {//�б��ʼ�����ڴ����б����ʱͳһ����
		header = new ListNode<T>;//����ͷ�ڱ��ڵ�
		trailer = new ListNode<T>;//����β�ڱ��ڵ�
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0;//��¼��ģ
	}

public:
	//���캯��
	List() { init(); } //Ĭ��
	List(List<T> const& L); //���帴���б�L
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNodePosi<T> p, int n); //�����б�����λ��p���n��

	//��������
	~List() {} //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�

	ListNodePosi<T> insertAsFirst(T const& e) {//��e�����׽ڵ����
		_size++;
		return header->insertAsSucc(e); 
	}

	ListNodePosi<T> insertAsLast(T const& e) {//��e����ĩ�ڵ����
		_size++;
		return trailer->insertAsPred(e);
	}

	ListNodePosi<T> insert(ListNodePosi<T> p, T const& e) {//e����p�ĺ�̲���
		_size++;
		return p->insertAsSucc(e);
	}

	ListNodePosi<T> insert(T const& e, ListNodePosi<T> p) {//e����p��ǰ������
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