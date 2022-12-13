#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#include "ListNode.h"

#include "List.h"


int main() {
	List<int> L1;
	ListNodePosi<int> p1;
	for (int i = 1; i <= 10; i++) { p1 = L1.insertAsFirst(i); }
	if (L1.find(2) != NULL) {
		printf("yes");
	} else {
		printf("no");
	}
	printf("\n\nL1元素排序前元素：");
	L1.print(); printf("\n");
	L1.sort(); printf("L1排序后元素："); L1.print(); printf("\n\n");


	List<int> L2;
	ListNodePosi<int> p2;
	p2 = L2.insertAsFirst(2); p2 = L2.insert(5, p2); p2 = L2.insert(p2, 3);
	p2 = L2.insertAsLast(9); p2 = L2.insertAsLast(1); p2 = L2.insert(p2, 8);
	L2.find(5);
	printf("L2的元素：");
	L2.print(); printf("\n\n");

	List<int> L3;
	ListNodePosi<int> p3;
	p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(1); p3 = L3.insertAsFirst(8);  p3 = L3.insertAsFirst(5);
	p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(8); p3 = L3.insertAsFirst(6); p3 = L3.insertAsFirst(10);
	p3 = L3.insertAsFirst(6); p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(10); p3 = L3.insertAsFirst(9);
	p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(9); p3 = L3.insertAsFirst(8); p3 = L3.insertAsFirst(10);
	printf("L3无序列表去重前的元素："); L3.print(); printf("\n");
	L3.deduplicate();
	printf("L3无序列表去重后的元素："); L3.print(); printf("\n\n");

	List<int> L4;
	ListNodePosi<int> p4;
	for (int i = 10; i >= 0; i--) {
		p4 = L4.insertAsFirst(i); p4 = L4.insertAsFirst(i); p4 = L4.insertAsFirst(i);
	}
	printf("L4有序列表去重前的元素："); L4.print(); printf("\n");
	L4.uniquify();
	printf("L4有序列表去重后的元素："); L4.print(); printf("\n\n");

	List<int> L5;
	ListNodePosi<int> p5;
	printf("\n\n");
	for (int i = 1; i <= 10; i++) {
		p5 = L5.insertAsLast(i);
	}
	L5.print();
}