#include<iostream>
using namespace std;

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3//默认的初始容量

template <typename T> class Vector {
protected:
	Rank _size; int _capacity; T* _elem;//规模，容量，数据区
	void copyFrom(T const* A, Rank lo, Rank hi) {//以数组区间A[lo,hi)为蓝本复制向量
		_size = 0;//分配空间，规模清零
		while (lo < hi)//A[lo,hi)内的元素逐一
			_elem[_size++] = A[lo++];//复制至_elem[0,hi - lo)
	}
public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //容量为c，规模为s，所有元素初始为v
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}
	//Vector(T const* A, Rank lo, Rank hi) { // 数组区间复制
	//	copyFrom(A, lo, hi);
	//}
	//Vector(T const* A, Rank n) { //数组整体复制
	//	copyFrom(A, 0, n);
	//}
	//Vector(Vector<T> const& V, Rank lo, Rank hi) { //向量区间复制
	//}
	//Vector(Vector<T> const& V) { //向量整体复制
	//	copyFrom(V._elem, 0, V._size);
	//}
	~Vector() { //析构，释放内部空间
		delete[] _elem;
	}
	Rank size() const {//规模
		return _size;
	}
};

int main() {
	Vector<int> v1;
	Vector<int> v2(10, 5, 1);

}