#pragma once


typedef unsigned int U; //约定：类型T或就是U；或可转换为U，并依此定序

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

	int clear() {//清空列表
		int oldSize = _size;
		while (0 < _size)
			remove(header->succ);//反复删除首节点，直至列表变空
		return oldSize;
	}

	List<T> copyNodes(ListNodePosi<T> p, int n) {//复制列表中自位置p起的n项
		init();//创建头，尾哨兵节点并做初始化
		while (n--) {
			insertAsLast(p->data);
			p = p->succ;//将起自p的n项依次作为末节点插入
		}
	}

	//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
	ListNodePosi<T> merge(ListNodePosi<T> p, int n, List<T>& L, ListNodePosi<T> q, int m) {//归并
		//mergeSort()调用时，this == &L && rank(p) + n = rank(q)
		ListNodePosi<T> pp = p->pred;//归并之后p可能不再指向首节点，需要先记忆，以便在返回前更新
		while ((0 < m) && (q != p))//q尚未出界（或在mergeSort()）中，p也尚未出界）之前
			if ((0 < n) && (p->data <= q->data)) {//若p尚未出界且v(p) <= v(p),则
				p = p->succ;
				n--;          //p直接后移，完成归入
			} else {//否则，将q转移至p之前，以完成归入
				insert(L.remove((q = q->succ)->pred), p);
				m--;
			}
		return pp->succ;//更新首节点位置
	}

	void mergeSort(ListNodePosi<T>& p, int n) {//列表的归并排序算法：对起始于位置p的n个元素排序
		if (n < 2) return;//若待排序范围已足够小，则直接返回，否则。。。
		int m = n >> 1;//以中点为界
		ListNodePosi<T> q = p;
		for (int i = 0; i < m; i++)
			q = q->succ;//找到后子列表起点
		mergeSort(p, m);//前、
		mergeSort(q, n - m);//后子列表分别排序
		p = merge(p, m, *this, q, n - m);//归并
		//mergeSort()调用时，this == &L && rank(p) + n = rank(q)
	}

	void selectionSort(ListNodePosi<T> p, int n) {//对从p开始连续的n个节点选择排序
		ListNodePosi<T> head = p->pred, tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;//待排序区间为(head,tail)
		while (1 < n) {//在至少还剩两个节点之前，在待排序区间内
			ListNodePosi<T> max = selectMax(head->succ, n);//找出最大者（歧义时后者优先）
			insert(remove(max), tail);//将其移至无序区间末尾（作为有序区间新的首元素）
			tail = tail->pred;
			n--;
		}
	}

	void insertiionSort(ListNodePosi<T> p, int n) {//对从p开始连续的n个节点插入排序
		for (int r = 0; r < n; r++) {      //逐一为各节点
			insert(search(p->data, r, p), p->data);//查找适当的位置并插入
			p = p->succ;
			remove(p->pred);//转向下一节点
		}
	}

	void readixSort(ListNodePosi<T> p, int n) {//对从p开始连续的n个节点基数排序
		ListNodePosi<T> head = p->pred;
		ListNodePosi<T> tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;//待排序区间为(head, tail)
		for (U radixBit = 0x1; radixBit && (p = head); radixBit <<= 1)//以下反复地
			for (int i = 0; i < n; i++)//根据当前基数为，将所有节点
				radixBit& U(p->succ->data) ? insert(remove(p->succ), tail) : p = p->succ;//分拣为后缀（1),与前缀（0）
	}

public:
	//构造函数
	List() { init(); } //默认
	List(List<T> const& L); //整体复制列表L
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi<T> p, int n); //复制列表中自位置p起的n项

	//析构函数
	~List() {} //释放（包含头、尾哨兵在内的）所有节点

	Rank size() const {//规模
		return _size;
	}

	bool empty() const {//判空
		return _size <= 0;
	}

	List operator[] (Rank r) const {//重载下标操作符，通过列表的秩访问（效率低）
		ListNodePosi<T> p = first(); //首节点出发
		while (0 < r--) p = p->succ;//顺数第r个节点就是
		return p->data; //目标节点，返回其中所存元素
	}

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const {//无序区间查找
		while (0 < n--) //（0 <= n <= rank(p) < _size)对于p的最近的n个前驱，从右向左
			if (e == (p = p->pred)->data) return p;//逐个比对，直至命中或范围越界
		return NULL;//p越出左边界意味着区间内不含e，查找失败
	}//失败时，返回NULL

	ListNodePosi<T> find(T const& e) const {//无序列表查找
		return find(e, _size, trailer);
	}

	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const {//有序区间查找
		do {
			p = p->pred; n--; //从右向左
		} while ((-1 < n) && (e < p->data));//逐个比较，直至命中或越界
		return p;//返回查找终止的位置
	}

	ListNodePosi<T> search(T const& e) const {//有序列表查找
		return search(e, _size, trailer);
	}

	ListNodePosi<T> first() const {//首节点位置
		return header->succ;
	}

	ListNodePosi<T> last() const {
		return trailer->pred;
	}

	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n) {//在p及其n - 1个后继中找出最大者
		ListNodePosi<T> max = p;//最大者暂定为首节点p
		for (ListNodePosi<T> cur = p; 1 < n; n--)
			if (!lt((cur = cur->succ)->data, max->data))//若当前元素不小于max，则
				max = cur;//更新最大元素位置记录
		return max;//返回最大节点位置
	}

	ListNodePosi<T> selectMax() {//整体最大
		return selectMax(header->succ, _size);
	}

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

	T remove(ListNodePosi<T> p) {//删除合法化节点p，返回其数值
		T e = p->data;//备份被删除元素
		p->pred->succ = p->succ;//后继
		p->succ->pred = p->pred;//前驱
		delete p;//释放节点
		_size--;//更新规模
		return e;//返回备份的数值
	}

	void merge(List<T>& L) {//全列表归并
		merge(header->succ, _size, L, L.header->succ, L._size);
	}

	void sort(ListNodePosi<T> p, int n) {//列表区间排序
		mergeSort(p, n);
	}

	int deduplicate() {//无序去重
		int oldSize = _size;
		ListNodePosi<T> p = first();
		for (Rank r = 0; p != trailer; p = p->succ)
			if (ListNodePosi<T> q = find(p->data, r, p))
				remove(q);//此时q与p有雷同，但删除前者更为简明
			else r++;//r为无重前缀的长度
		return oldSize - _size;//删除元素总数
	}

	int uniquify() {//有序去重         成批剔除重复元素，效率高
		if (_size < 2)  return 0;//平凡列表自然无重复
		int oldSize = _size;//记录原规模
		ListNodePosi<T> p = first();
		ListNodePosi<T> q;//p为各区段起点，q为其后继
		while (trailer != (q = p->succ))//反复考察相邻的节点对（p，q）
			if (p->data != q->data) p = q;//若互异，则转向下一区段
			else remove(q);//否则（雷同），删除后者
		return oldSize - _size;//列表规模变化量，即被删除元素总数
	}

	void sort() {//列表整体排序
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


template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template<typename T> static bool lt(T& a, T& b) { return a < b; }



