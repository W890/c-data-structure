#pragma once

typedef int Rank;//秩

#include "Fib.h" //引入Fib数列类
#include <algorithm>

#define DEFAULT_CAPACITY 3//默认的初始容量

template <typename T> class Vector {

protected:
	Rank _size; int _capacity; T* _elem;//规模，容量，数据区
	void copyFrom(T const* A, Rank lo, Rank hi) {//以数组区间A[lo,hi)为蓝本复制向量
		_size = 0;//分配空间，规模清零
		while (lo < hi)//A[lo,hi)内的元素逐一
			_elem[_size++] = A[lo++];//复制至_elem[0,hi - lo)
	}

	void expand() { //向量空间不足时扩容
		if (_size < _capacity) return; //尚未满员时，不必扩容
		if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;//不低于最小容量
		T* oldElem = _elem;
		_elem = new T[_capacity <<= 1];//容量加倍
		for (Rank i = 0; i < _size; i++)
			_elem[i] = oldElem[i];//复制原向量内容（T为基本类型，或已重载赋值操作符'='）
		delete[]oldElem;//释放原空间
	}

	void shrink() { //填装因子过小时压缩向量所占空间
		if (_capacity < DEFAULT_CAPACITY << 1) return;//不致收缩到DEFAULT_APACITY以下
		if (_size << 2 > _capacity)return;//以25%为界
		T* oldElem = _elem;
		_elem = new T[_capacity >>= 1];//容量减半
		for (int i = 0; i < _size; i++)
			_elem[i] = oldElem[i];//复制向量内容
		delete[]oldElem;//释放原空间
	}

	void merge(Rank lo, Rank mi, Rank hi) {//[lo,mi)和[mi,hi)各自有序，lo < mi < hi
		Rank i = 0;
		T* A = _elem + lo;//合并后的有序向量A[0, hi - lo) = _elem[lo , hi),就地
		Rank j = 0, lb = mi - lo;
		T* B = new T[lb];//前子向量B[0,lb) <-- elem[lo,mi)
		for (Rank i = 0; i < lb; i++)  B[i] = A[i];//复制自A的前缀
		Rank k = 0, lc = hi - mi;
		T* c = _elem + mi;//后子向量B[0,lb) <-- _elem[lo,mi)，就地

		while ((j < lb) && (k < lc))//反复地比较B，C的首元素
			A[i++] = (B[j] <= c[k]) ? B[j++] : c[k++];//将更小者归入A中

		while (j < lb)//若C先耗尽，则
			A[i++] = B[j++];//将B残余的后缀归入A中
		delete[] B;//释放临时空间：mergeSort()过程中，如何比曼此反复的new/delete
	}

	bool bubble(Rank lo, Rank hi) {//扫描交换
		bool sorted = true;//整体有序标志
		while (++lo < hi)//自左向右，逐一检查各队相邻元素
			if (_elem[lo - 1] > _elem[lo]) {//若逆序，则
				sorted = false;//意味着尚未整体有序，并需要
				std::swap(_elem[lo - 1], _elem[lo]);//通过交换使局部有序
			}
		return sorted;//返回有序标志
	}

public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //容量为c，规模为s，所有元素初始为v
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}

	int remove(Rank lo, Rank hi) {//删除区间[lo,hi]
		if (lo == hi) return 0;//出于效率考虑，单独处理退化情况，比如remove(0,0)
		while (hi < _size) _elem[lo++] = _elem[hi++];//[hi,_size)顺次前移hi - lo个单位
		_size = lo;//更新规模，直接丢弃尾部[lo,_size = hi)区间
		shrink();//若有必要，则缩容
		return hi - lo;//返回被删除元素的数目
	}

	T remove(Rank r) {//删除秩为r的元素 0 < r < size
		T e = _elem[r]; //备份被删除元素
		remove(r, r + 1);//调用区间删除的算法，等效于对区间[r,r + 1)的删除
		return e; //返回被删除的元素
	}

	Rank insert(Rank r, T const& e) {//assert: 0 <= r <= size
		expand();//若有必要，扩容
		for (Rank i = _size; r < i; i--)//自后向前，后继元素
			_elem[i] = _elem[i - 1];//顺次后移一个单元
		_elem[r] = e;//置入新元素
		_size++;//并更新容量
		return r;//返回秩
	}

	Rank insert(T const& e) {//默认作为末元素插入
		return insert(_size, e);
	}

	void sort(Rank lo, Rank hi) {//对[lo,hi)排序
		switch (rand() % 2) {
		case 1:bubbleSort(lo, hi); break;
		default:mergeSort(lo, hi); break;
		}
	}

	void sort() {//整体排序
		sort(0, _size);
	}
	Vector(T const* A, Rank lo, Rank hi) { // 数组区间复制
		copyFrom(A, lo, hi);
	}

	Vector(T const* A, Rank n) { //数组整体复制
		copyFrom(A, 0, n);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) { //向量区间复制
	}

	Vector(Vector<T> const& V) { //向量整体复制
		copyFrom(V._elem, 0, V._size);
	}

	~Vector() { //析构，释放内部空间
		delete[] _elem;
	}

	Rank size() const {//规模
		return _size;
	}

	bool empty() const {//判空
		return !_size;
	}

	Rank find(T const& e) const {//无序向量整体查找
		return find(e, 0, _size);
	}

	Rank find(T const& e, Rank lo, Rank hi) const {//无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1；
		//assert: 0 <= lo < hi <= _size
		while ((lo < hi--) && (e != _elem[hi]));//从后向前，顺序查找
		return hi;//若hi < lo，则意味着失败；否则hi即命中元素的秩
	}

	void TestFind(Vector<T>& V) {
		for (Rank i = 0; i < V.size(); i++) {//依此查找向量中元素，当然成功
			int e = V[i];
			printf("%d", e);
			Rank r = V.find(e);
			if (r > -1) printf(" : 发现V[%d] = %d", r, V[r]);
			else printf(" : 未发现V[%d] <> %d", r, e);
			printf("\n");
		}
	}

	//二分查找法（版本c）：在有序向量的区间[lo,hi)内查找元素e，0 <= lo <= hi <= _size
	Rank binSearch(T* A, T const& e, Rank lo, Rank hi) const {
		while (lo < hi) {//每步迭代仅需做一次比较判断，有两个分支
			Rank mi = (lo + hi) >> 1;//以中点为轴点
			(e < A[mi]) ? hi = mi : lo = mi + 1;//经比较后深入[lo,mi)或(mi,hi)
		}//成功查找不能提前终止
		return --lo;//循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
	}//有多个元素命中时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

	//Fibonacci查找算法（版本A）：在有序向量的区间[lo,hi)内查找元素e,o <= lo <= hi <= _size
	Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) const {
		Fib fib(hi - lo);//用O(log_phi(n = hi - lo))的时间创建Fib数列
		while (lo < hi) {//每步迭代可能要做两次比较判断，有三个分支
			while (hi - lo < fib.get()) fib.prev;//通过向前顺序查找（分摊O(1))
			Rank mi = lo + fib.get() - 1;//确定形如Fib(k) - 1的轴点
			if (e < A[mi]) hi = mi;//深入前半段[lo,mi)继续查找
			else if (A[mi] < e) lo = mi + 1;//深入后半段(mi,hi)继续查找
			else return mi;//在mi处命中
		}//成功查找可以提前终止
		return -1;//查找失败
	}//有多个命中元素时，不能保证返回秩最大者;失败时，简单地返回-1，而不能指示失败的位置

	Rank search(T const& e, Rank lo, Rank hi) const {//有序向量区间查找
		return binSearch(_elem, e, lo, hi);
	}

	Rank search(T const& e) const {//有序向量整体查找
		return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size);
	}

	void TestSearch(Vector<T>& V)  const {//依次查找相邻元素的均值，当然成功
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

	void bubbleSort(Rank lo, Rank hi) {//向量的起泡排序（跳跃版） //assert : 0 <= lo <hi <= size
		for (Rank last = --hi; lo < hi; hi = last)
			for (Rank i = last = lo; i < hi; i++)
				if (_elem[i] > _elem[i + 1])//若逆序，则
					std::swap(_elem[last = i], _elem[i + 1]);//经交换使局部有序
	}

	void mergeSort(Rank lo, Rank hi) {//向量归并排序
		if (hi - lo < 2) return;//单元素区间自然有序，否则。。。
		Rank mi = (lo + hi) / 2;//以中点为界
		mergeSort(lo, mi);
		mergeSort(mi, hi);//分别排序
		merge(lo, mi, hi);//归并
	}

	void unsort(Rank lo, Rank hi) {//等概率随机置乱向量区间[lo,hi)
		T* V = _elem + lo;//将子向量_elem[lo,hi)视作另一向量V[0,hi - lo)
		for (Rank i = hi - lo; i > 0; i--)//自后向前
			std::swap(V[i - 1], V[rand() % i]);//将V[i - 1]与V[0,i)中某一元素随机交换
	}

	void unsort() {//整体置乱
		unsort(0, _size);
	}

	Rank dedulicate() {//删除无序向量中重复元素（高效版）
		Rank oldSize = _size;//记录原规模
		for (Rank i = 1; i < _size; )//自前向后逐个考察_elem[1,_size)
			if (find(_elem[i], 0, i) < 0)//在前缀[0,i)中寻找与之雷同者（至多一个）
				i++;//若无雷同则继续考察其后续
			else
				remove(i);//否则删除当前元素
		return oldSize - _size;//被删除元素总数
	}

	Rank uniquify() {//有序向量重复元素剔除算法（高效版）
		Rank i = 0, j = 0;//各对互异“相邻”元素的秩
		while (++j < _size)//逐一扫描，直至末元素
			if (_elem[i] != _elem[j])//跳过雷同者
				_elem[++i] = _elem[j];//发现不同元素时，向前移至紧邻于前者右侧
		_size = ++i; shrink();//直接截除尾部多余元素
		return j - i;//向量规模变化量
	}

	T& operator[](Rank r) const {//重载下标操作符，可以类似于数组形式引用各元素
		return _elem[r];
	}

};
