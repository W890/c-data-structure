#include<iostream>
using namespace std;

typedef int Rank;//��
#define DEFAULT_CAPACITY 3//Ĭ�ϵĳ�ʼ����

template <typename T> class Vector {
protected:
	Rank _size; int _capacity; T* _elem;//��ģ��������������
	void copyFrom(T const* A, Rank lo, Rank hi) {//����������A[lo,hi)Ϊ������������
		_size = 0;//����ռ䣬��ģ����
		while (lo < hi)//A[lo,hi)�ڵ�Ԫ����һ
			_elem[_size++] = A[lo++];//������_elem[0,hi - lo)
	}
public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //����Ϊc����ģΪs������Ԫ�س�ʼΪv
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}
	//Vector(T const* A, Rank lo, Rank hi) { // �������临��
	//	copyFrom(A, lo, hi);
	//}
	//Vector(T const* A, Rank n) { //�������帴��
	//	copyFrom(A, 0, n);
	//}
	//Vector(Vector<T> const& V, Rank lo, Rank hi) { //�������临��
	//}
	//Vector(Vector<T> const& V) { //�������帴��
	//	copyFrom(V._elem, 0, V._size);
	//}
	~Vector() { //�������ͷ��ڲ��ռ�
		delete[] _elem;
	}
	Rank size() const {//��ģ
		return _size;
	}
};

int main() {
	Vector<int> v1;
	Vector<int> v2(10, 5, 1);

}