#pragma once

typedef int Rank;//��

#include "Fib.h" //����Fib������
#include <algorithm>

#define DEFAULT_CAPACITY 3//Ĭ�ϵĳ�ʼ����

template <typename T> class Vector {

protected:
	Rank _size; int _capacity; T* _elem;//��ģ��������������
	void copyFrom(T const* A, Rank lo, Rank hi) {//����������A[lo,hi)Ϊ������������
		_size = 0;//����ռ䣬��ģ����
		while (lo < hi)//A[lo,hi)�ڵ�Ԫ����һ
			_elem[_size++] = A[lo++];//������_elem[0,hi - lo)
	}

	void expand() { //�����ռ䲻��ʱ����
		if (_size < _capacity) return; //��δ��Աʱ����������
		if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;//��������С����
		T* oldElem = _elem;
		_elem = new T[_capacity <<= 1];//�����ӱ�
		for (Rank i = 0; i < _size; i++)
			_elem[i] = oldElem[i];//����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
		delete[]oldElem;//�ͷ�ԭ�ռ�
	}

	void shrink() { //��װ���ӹ�Сʱѹ��������ռ�ռ�
		if (_capacity < DEFAULT_CAPACITY << 1) return;//����������DEFAULT_APACITY����
		if (_size << 2 > _capacity)return;//��25%Ϊ��
		T* oldElem = _elem;
		_elem = new T[_capacity >>= 1];//��������
		for (int i = 0; i < _size; i++)
			_elem[i] = oldElem[i];//������������
		delete[]oldElem;//�ͷ�ԭ�ռ�
	}

	void merge(Rank lo, Rank mi, Rank hi) {//[lo,mi)��[mi,hi)��������lo < mi < hi
		Rank i = 0;
		T* A = _elem + lo;//�ϲ������������A[0, hi - lo) = _elem[lo , hi),�͵�
		Rank j = 0, lb = mi - lo;
		T* B = new T[lb];//ǰ������B[0,lb) <-- elem[lo,mi)
		for (Rank i = 0; i < lb; i++)  B[i] = A[i];//������A��ǰ׺
		Rank k = 0, lc = hi - mi;
		T* c = _elem + mi;//��������B[0,lb) <-- _elem[lo,mi)���͵�

		while ((j < lb) && (k < lc))//�����رȽ�B��C����Ԫ��
			A[i++] = (B[j] <= c[k]) ? B[j++] : c[k++];//����С�߹���A��

		while (j < lb)//��C�Ⱥľ�����
			A[i++] = B[j++];//��B����ĺ�׺����A��
		delete[] B;//�ͷ���ʱ�ռ䣺mergeSort()�����У���α����˷�����new/delete
	}

	bool bubble(Rank lo, Rank hi) {//ɨ�轻��
		bool sorted = true;//���������־
		while (++lo < hi)//�������ң���һ����������Ԫ��
			if (_elem[lo - 1] > _elem[lo]) {//��������
				sorted = false;//��ζ����δ�������򣬲���Ҫ
				std::swap(_elem[lo - 1], _elem[lo]);//ͨ������ʹ�ֲ�����
			}
		return sorted;//���������־
	}

public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //����Ϊc����ģΪs������Ԫ�س�ʼΪv
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}

	int remove(Rank lo, Rank hi) {//ɾ������[lo,hi]
		if (lo == hi) return 0;//����Ч�ʿ��ǣ����������˻����������remove(0,0)
		while (hi < _size) _elem[lo++] = _elem[hi++];//[hi,_size)˳��ǰ��hi - lo����λ
		_size = lo;//���¹�ģ��ֱ�Ӷ���β��[lo,_size = hi)����
		shrink();//���б�Ҫ��������
		return hi - lo;//���ر�ɾ��Ԫ�ص���Ŀ
	}

	T remove(Rank r) {//ɾ����Ϊr��Ԫ�� 0 < r < size
		T e = _elem[r]; //���ݱ�ɾ��Ԫ��
		remove(r, r + 1);//��������ɾ�����㷨����Ч�ڶ�����[r,r + 1)��ɾ��
		return e; //���ر�ɾ����Ԫ��
	}

	Rank insert(Rank r, T const& e) {//assert: 0 <= r <= size
		expand();//���б�Ҫ������
		for (Rank i = _size; r < i; i--)//�Ժ���ǰ�����Ԫ��
			_elem[i] = _elem[i - 1];//˳�κ���һ����Ԫ
		_elem[r] = e;//������Ԫ��
		_size++;//����������
		return r;//������
	}

	Rank insert(T const& e) {//Ĭ����ΪĩԪ�ز���
		return insert(_size, e);
	}

	void sort(Rank lo, Rank hi) {//��[lo,hi)����
		switch (rand() % 2) {
		case 1:bubbleSort(lo, hi); break;
		default:mergeSort(lo, hi); break;
		}
	}

	void sort() {//��������
		sort(0, _size);
	}
	Vector(T const* A, Rank lo, Rank hi) { // �������临��
		copyFrom(A, lo, hi);
	}

	Vector(T const* A, Rank n) { //�������帴��
		copyFrom(A, 0, n);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) { //�������临��
	}

	Vector(Vector<T> const& V) { //�������帴��
		copyFrom(V._elem, 0, V._size);
	}

	~Vector() { //�������ͷ��ڲ��ռ�
		delete[] _elem;
	}

	Rank size() const {//��ģ
		return _size;
	}

	bool empty() const {//�п�
		return !_size;
	}

	Rank find(T const& e) const {//���������������
		return find(e, 0, _size);
	}

	Rank find(T const& e, Rank lo, Rank hi) const {//����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1��
		//assert: 0 <= lo < hi <= _size
		while ((lo < hi--) && (e != _elem[hi]));//�Ӻ���ǰ��˳�����
		return hi;//��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
	}

	void TestFind(Vector<T>& V) {
		for (Rank i = 0; i < V.size(); i++) {//���˲���������Ԫ�أ���Ȼ�ɹ�
			int e = V[i];
			printf("%d", e);
			Rank r = V.find(e);
			if (r > -1) printf(" : ����V[%d] = %d", r, V[r]);
			else printf(" : δ����V[%d] <> %d", r, e);
			printf("\n");
		}
	}

	//���ֲ��ҷ����汾c��������������������[lo,hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
	Rank binSearch(T* A, T const& e, Rank lo, Rank hi) const {
		while (lo < hi) {//ÿ������������һ�αȽ��жϣ���������֧
			Rank mi = (lo + hi) >> 1;//���е�Ϊ���
			(e < A[mi]) ? hi = mi : lo = mi + 1;//���ȽϺ�����[lo,mi)��(mi,hi)
		}//�ɹ����Ҳ�����ǰ��ֹ
		return --lo;//ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
	}//�ж��Ԫ������ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��

	//Fibonacci�����㷨���汾A��������������������[lo,hi)�ڲ���Ԫ��e,o <= lo <= hi <= _size
	Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) const {
		Fib fib(hi - lo);//��O(log_phi(n = hi - lo))��ʱ�䴴��Fib����
		while (lo < hi) {//ÿ����������Ҫ�����αȽ��жϣ���������֧
			while (hi - lo < fib.get()) fib.prev;//ͨ����ǰ˳����ң���̯O(1))
			Rank mi = lo + fib.get() - 1;//ȷ������Fib(k) - 1�����
			if (e < A[mi]) hi = mi;//����ǰ���[lo,mi)��������
			else if (A[mi] < e) lo = mi + 1;//�������(mi,hi)��������
			else return mi;//��mi������
		}//�ɹ����ҿ�����ǰ��ֹ
		return -1;//����ʧ��
	}//�ж������Ԫ��ʱ�����ܱ�֤�����������;ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��

	Rank search(T const& e, Rank lo, Rank hi) const {//���������������
		return binSearch(_elem, e, lo, hi);
	}

	Rank search(T const& e) const {//���������������
		return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size);
	}

	void TestSearch(Vector<T>& V)  const {//���β�������Ԫ�صľ�ֵ����Ȼ�ɹ�
		for (Rank i = 0; i < V.size(); i++) {
			T e = V[i];
			printf("%d", e);
			printf(": by ");
			Rank r = V.search(e);
			if (V[r] == e) printf("found at rank V[%d] = %d", r, V[r]);
			else printf("found ar rank V[%d] = %d <> %d\a\a", r, V[r], e);
			printf("\n\n");
		}
	}

	void bubbleSort(Rank lo, Rank hi) {//����������������Ծ�棩 //assert : 0 <= lo <hi <= size
		for (Rank last = --hi; lo < hi; hi = last)
			for (Rank i = last = lo; i < hi; i++)
				if (_elem[i] > _elem[i + 1])//��������
					std::swap(_elem[last = i], _elem[i + 1]);//������ʹ�ֲ�����
	}

	void mergeSort(Rank lo, Rank hi) {//�����鲢����
		if (hi - lo < 2) return;//��Ԫ��������Ȼ���򣬷��򡣡���
		Rank mi = (lo + hi) / 2;//���е�Ϊ��
		mergeSort(lo, mi);
		mergeSort(mi, hi);//�ֱ�����
		merge(lo, mi, hi);//�鲢
	}

	void unsort(Rank lo, Rank hi) {//�ȸ������������������[lo,hi)
		T* V = _elem + lo;//��������_elem[lo,hi)������һ����V[0,hi - lo)
		for (Rank i = hi - lo; i > 0; i--)//�Ժ���ǰ
			std::swap(V[i - 1], V[rand() % i]);//��V[i - 1]��V[0,i)��ĳһԪ���������
	}

	void unsort() {//��������
		unsort(0, _size);
	}

	Rank dedulicate() {//ɾ�������������ظ�Ԫ�أ���Ч�棩
		Rank oldSize = _size;//��¼ԭ��ģ
		for (Rank i = 1; i < _size; )//��ǰ����������_elem[1,_size)
			if (find(_elem[i], 0, i) < 0)//��ǰ׺[0,i)��Ѱ����֮��ͬ�ߣ�����һ����
				i++;//������ͬ��������������
			else
				remove(i);//����ɾ����ǰԪ��
		return oldSize - _size;//��ɾ��Ԫ������
	}

	Rank uniquify() {//���������ظ�Ԫ���޳��㷨����Ч�棩
		Rank i = 0, j = 0;//���Ի��조���ڡ�Ԫ�ص���
		while (++j < _size)//��һɨ�裬ֱ��ĩԪ��
			if (_elem[i] != _elem[j])//������ͬ��
				_elem[++i] = _elem[j];//���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		_size = ++i; shrink();//ֱ�ӽس�β������Ԫ��
		return j - i;//������ģ�仯��
	}

	T& operator[](Rank r) const {//�����±������������������������ʽ���ø�Ԫ��
		return _elem[r];
	}

};
