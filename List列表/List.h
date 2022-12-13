#pragma once


typedef unsigned int U; //Լ��������T�����U�����ת��ΪU�������˶���

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
	ListNodePosi<T> merge(ListNodePosi<T> p, int n, List<T>& L, ListNodePosi<T> q, int m) {//�鲢
		//mergeSort()����ʱ��this == &L && rank(p) + n = rank(q)
		ListNodePosi<T> pp = p->pred;//�鲢֮��p���ܲ���ָ���׽ڵ㣬��Ҫ�ȼ��䣬�Ա��ڷ���ǰ����
		while ((0 < m) && (q != p))//q��δ���磨����mergeSort()���У�pҲ��δ���磩֮ǰ
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
		p = merge(p, m, *this, q, n - m);//�鲢
		//mergeSort()����ʱ��this == &L && rank(p) + n = rank(q)
	}

	void selectionSort(ListNodePosi<T> p, int n) {//�Դ�p��ʼ������n���ڵ�ѡ������
		ListNodePosi<T> head = p->pred, tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;//����������Ϊ(head,tail)
		while (1 < n) {//�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
			ListNodePosi<T> max = selectMax(head->succ, n);//�ҳ�����ߣ�����ʱ�������ȣ�
			insert(remove(max), tail);//����������������ĩβ����Ϊ���������µ���Ԫ�أ�
			tail = tail->pred;
			n--;
		}
	}

	void insertiionSort(ListNodePosi<T> p, int n) {//�Դ�p��ʼ������n���ڵ��������
		for (int r = 0; r < n; r++) {      //��һΪ���ڵ�
			insert(search(p->data, r, p), p->data);//�����ʵ���λ�ò�����
			p = p->succ;
			remove(p->pred);//ת����һ�ڵ�
		}
	}

	void readixSort(ListNodePosi<T> p, int n) {//�Դ�p��ʼ������n���ڵ��������
		ListNodePosi<T> head = p->pred;
		ListNodePosi<T> tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;//����������Ϊ(head, tail)
		for (U radixBit = 0x1; radixBit && (p = head); radixBit <<= 1)//���·�����
			for (int i = 0; i < n; i++)//���ݵ�ǰ����Ϊ�������нڵ�
				radixBit& U(p->succ->data) ? insert(remove(p->succ), tail) : p = p->succ;//�ּ�Ϊ��׺��1),��ǰ׺��0��
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

	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n) {//��p����n - 1��������ҳ������
		ListNodePosi<T> max = p;//������ݶ�Ϊ�׽ڵ�p
		for (ListNodePosi<T> cur = p; 1 < n; n--)
			if (!lt((cur = cur->succ)->data, max->data))//����ǰԪ�ز�С��max����
				max = cur;//�������Ԫ��λ�ü�¼
		return max;//�������ڵ�λ��
	}

	ListNodePosi<T> selectMax() {//�������
		return selectMax(header->succ, _size);
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


template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template<typename T> static bool lt(T& a, T& b) { return a < b; }



