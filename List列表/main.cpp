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

	int clear() {//����б�
		int oldSize = _size;
		while (0 < _size)
			remove(header->succ);//����ɾ���׽ڵ㣬ֱ���б���
		return oldSize;
	}

	List<T> copyNodes(ListNodePosi<T> p, int n) {//�����б�����λ��p���n��
		init();//����ͷ��β�ڱ��ڵ㲢����ʼ��
		while (n--) {
			insertAsLast(p->data);
			p = p->succ;//������p��n��������Ϊĩ�ڵ����
		}
	}

	//�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
	ListNodePosi<T> merge(ListNodePosi<T> p, int n ,List<T>& L, ListNodePosi<T> q, int m) {//�鲢
		//mergeSort()����ʱ��this == &L && rank(p) + n = rank(q)
		ListNodePosi<T> pp = p->pred;//�鲢֮��p���ܲ���ָ���׽ڵ㣬��Ҫ�ȼ��䣬�Ա��ڷ���ǰ����
		while ((0 <m)&&(q != p))//q��δ���磨����mergeSort()���У�pҲ��δ���磩֮ǰ
			if ((0 < n) && (p->data <= q->data)) {//��p��δ������v(p) <= v(p),��
				p = p->succ;
				n--;          //pֱ�Ӻ��ƣ���ɹ���
			} else {//���򣬽�qת����p֮ǰ������ɹ���
				insert(L.remove((q = q->succ)->pred), p);
				m--;
			}
		return pp->succ;//�����׽ڵ�λ��
	}

	void mergeSort(ListNodePosi<T>& p, int n) {//�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
		if (n < 2) return;//��������Χ���㹻С����ֱ�ӷ��أ����򡣡���
		int m = n >> 1;//���е�Ϊ��
		ListNodePosi<T> q = p;
		for (int i = 0; i < m; i++)
			q = q->succ;//�ҵ������б����
		mergeSort(p, m);//ǰ��
		mergeSort(q, n - m);//�����б�ֱ�����
		p = merge(p, m, * this, q, n - m);//�鲢
		//mergeSort()����ʱ��this == &L && rank(p) + n = rank(q)
	}

public:
	//���캯��
	List() { init(); } //Ĭ��
	List(List<T> const& L); //���帴���б�L
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNodePosi<T> p, int n); //�����б�����λ��p���n��

	//��������
	~List() {} //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�

	Rank size() const {//��ģ
		return _size;
	}

	bool empty() const {//�п�
		return _size <= 0;
	}

	List operator[] (Rank r) const {//�����±��������ͨ���б���ȷ��ʣ�Ч�ʵͣ�
		ListNodePosi<T> p = first(); //�׽ڵ����
		while (0 < r--) p = p->succ;//˳����r���ڵ����
		return p->data; //Ŀ��ڵ㣬������������Ԫ��
	}

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const {//�����������
		while (0 < n--) //��0 <= n <= rank(p) < _size)����p�������n��ǰ������������
			if (e == (p = p->pred)->data) return p;//����ȶԣ�ֱ�����л�ΧԽ��
		return NULL;//pԽ����߽���ζ�������ڲ���e������ʧ��
	}//ʧ��ʱ������NULL

	ListNodePosi<T> find(T const& e) const {//�����б����
		return find(e, _size, trailer);
	}

	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const {//�����������
		do {
			p = p->pred; n--; //��������
		} while ((-1 < n) && (e < p->data));//����Ƚϣ�ֱ�����л�Խ��
		return p;//���ز�����ֹ��λ��
	}

	ListNodePosi<T> search(T const& e) const {//�����б����
		return search(e, _size, trailer);
	}

	ListNodePosi<T> first() const {//�׽ڵ�λ��
		return header->succ;
	}

	ListNodePosi<T> last() const {
		return trailer->pred;
	}

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

	T remove(ListNodePosi<T> p) {//ɾ���Ϸ����ڵ�p����������ֵ
		T e = p->data;//���ݱ�ɾ��Ԫ��
		p->pred->succ = p->succ;//���
		p->succ->pred = p->pred;//ǰ��
		delete p;//�ͷŽڵ�
		_size--;//���¹�ģ
		return e;//���ر��ݵ���ֵ
	}

	void merge(List<T>& L) {//ȫ�б�鲢
		merge(header->succ, _size, L, L.header->succ, L._size);
	}

	void sort(ListNodePosi<T> p, int n) {//�б���������
		mergeSort(p, n);
	}

	int deduplicate() {//����ȥ��
		int oldSize = _size;
		ListNodePosi<T> p = first();
		for (Rank r = 0; p != trailer; p = p->succ)
			if (ListNodePosi<T> q = find(p->data, r, p))
				remove(q);//��ʱq��p����ͬ����ɾ��ǰ�߸�Ϊ����
			else r++;//rΪ����ǰ׺�ĳ���
		return oldSize - _size;//ɾ��Ԫ������
	}

	int uniquify() {//����ȥ��         �����޳��ظ�Ԫ�أ�Ч�ʸ�
		if (_size < 2)  return 0;//ƽ���б���Ȼ���ظ�
		int oldSize = _size;//��¼ԭ��ģ
		ListNodePosi<T> p = first();
		ListNodePosi<T> q;//pΪ��������㣬qΪ����
		while (trailer != (q = p->succ))//�����������ڵĽڵ�ԣ�p��q��
			if (p->data != q->data) p = q;//�����죬��ת����һ����
			else remove(q);//������ͬ����ɾ������
		return oldSize - _size;//�б��ģ�仯��������ɾ��Ԫ������
	}

	void sort() {//�б���������
		sort(first(), _size);
	}

	void print() const {
		ListNodePosi<T> m = header->succ;
		printf("[ ");
		while (m != trailer) {
			printf("%d, ", m->data);
			m = m->succ;
		}
		printf("]");
	}
	
};

int main() {
	List<int> L1;
	ListNodePosi<int> p1;
	for (int i = 1; i <= 10; i++) { p1 = L1.insertAsFirst(i); }
	if (L1.find(2) != NULL) {
		printf("yes");
	} else {
		printf("no");
	}
	printf("\n\nL1Ԫ������ǰԪ�أ�");
	L1.print(); printf("\n");
	L1.sort(); printf("L1�����Ԫ�أ�"); L1.print(); printf("\n\n");


	List<int> L2;
	ListNodePosi<int> p2;
	p2 = L2.insertAsFirst(2); p2 = L2.insert(5, p2); p2 = L2.insert(p2, 3);
	p2 = L2.insertAsLast(9); p2 = L2.insertAsLast(1); p2 = L2.insert(p2, 8);
	L2.find(5);
	printf("L2��Ԫ�أ�");
	L2.print(); printf("\n\n");

	List<int> L3;
	ListNodePosi<int> p3;
	p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(1); p3 = L3.insertAsFirst(8);  p3 = L3.insertAsFirst(5);
	p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(8); p3 = L3.insertAsFirst(6); p3 = L3.insertAsFirst(10);
	p3 = L3.insertAsFirst(6); p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(9);
	p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(8); p3 = L3.insertAsFirst(10);
	printf("L3�����б�ȥ��ǰ��Ԫ�أ�"); L3.print(); printf("\n");
	L3.deduplicate();
	printf("L3�����б�ȥ�غ��Ԫ�أ�"); L3.print(); printf("\n\n");

	List<int> L4;
	ListNodePosi<int> p4;
	for (int i = 10; i >= 0; i--) {
		p4 = L4.insertAsFirst(i); p4 = L4.insertAsFirst(i); p4 = L4.insertAsFirst(i);
	}
	printf("L4�����б�ȥ��ǰ��Ԫ�أ�"); L4.print(); printf("\n");
	L4.uniquify();
	printf("L4�����б�ȥ�غ��Ԫ�أ�"); L4.print(); printf("\n\n");

	List<int> L5;
	ListNodePosi<int> p5;
	printf("\n\n");
	for (int i = 1; i <= 10; i++) {
		p5 = L5.insertAsLast(i);
	}
	L5.print();
}