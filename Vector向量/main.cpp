#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Vector.h"
using namespace std;


int main() {
	Vector<int> v1;
	Vector<int> v2;
	v1.insert(1); v1.insert(2); v1.insert(3); v1.insert(4); v1.insert(5); v1.insert(0, 6);
	cout << "v1(1)的规模是：" << v1.size() << endl;
	//cout << "v2(1)的规模是：" << v2.size() << endl;

	printf("\n");
	printf("v1向量值分别是：");
	for (int i = 0; i < v1.size(); i++) {
		printf("%d ", v1[i]);
	}
	printf("\n");

	/*printf("\n");
	int h = 0;
	printf("\n请输入要查找的值(find)：%d",h);
	scanf("%d", &h);
	if (v1.find(h,0,5) > -1) printf("存在于秩%d",v1.find(h,0,5));
	else printf("不存在\n\n");*/
	
	v1.search(4, 0, 4);
	//测试remove
	v1.remove(0);
	printf("v1remove后向量值为：");
	for (int i = 0; i < v1.size(); i++) {
		printf("%d ", v1[i]);
	}

	//测试remove,shrink
	printf("\n\n"); printf("v2 remove前：");
	for (int i = 0; i < 10; i++) {
		v2.insert(i);
		printf("%d ", v2[i]);
	}
	printf("\n"); printf("v2 remove后：");
	v2.remove(2, 10);
	for (int i = 0; i < v2.size(); i++) {
		printf("%d ", v2[i]);
	}

	//冒泡排序测试
	Vector<int> v3;
	v3.insert(6); v3.insert(1); v3.insert(3); v3.insert(9); v3.insert(4); 
	v3.insert(8); v3.insert(2); v3.insert(7); v3.insert(5); v3.insert(10);
	printf("\n\n"); printf("v3排序前：");
	for (int i = 0; i < v3.size(); i++) {
		printf("%d ", v3[i]);
	}
	v3.bubbleSort(0, v3.size());
	printf("\n"); printf("v3排序后：");
	for (int i = 0; i < v3.size(); i++) {
		printf("%d ", v3[i]);
	}

	//归并排序测试
	Vector<int> v4;
	v4.insert(10); v4.insert(9); v4.insert(5); v4.insert(2); v4.insert(7);
	v4.insert(6); v4.insert(1); v4.insert(3); v4.insert(8); v4.insert(4);
	printf("\n\n"); printf("v4排序前：");
	for (int i = 0; i < v4.size(); i++) {
		printf("%d ", v4[i]);
	}
	v4.mergeSort(0, v4.size());
	printf("\n"); printf("v4排序后：");
	for (int i = 0; i < v4.size(); i++) {
		printf("%d ", v4[i]);
	}

	//置乱
	Vector<int> v5;
	printf("\n\nv5unsort前：");
	for (int i = 0; i < 10; i++) {
		v5.insert(i);
		printf("%d ", v5[i]);
	}
	v5.unsort();
	printf("\nv5unsort后：");
	for (int i = 0; i < v5.size(); i++) {
		printf("%d ", v5[i]);
	}


	Vector<int>v6;
	v6.insert(1); v6.insert(3); v6.insert(3); v6.insert(2); v6.insert(6); v6.insert(2);
	v6.insert(6); v6.insert(1); v6.insert(7); v6.insert(2); v6.insert(8); v6.insert(3);
	printf("\n\nv6无序重复前：");
	for (int i = 0; i < v6.size(); i++) {
		printf("%d ", v6[i]);

	}printf("\nv6无序去重复后：");
	v6.dedulicate(); 
	for (int i = 0; i < v6.size(); i++) {
		printf("%d ", v6[i]);
	}

	Vector<int>v7;
	v7.insert(1); v7.insert(1); v7.insert(2); v7.insert(2); v7.insert(2); v7.insert(3);
	v7.insert(3); v7.insert(4); v7.insert(4); v7.insert(5); v7.insert(5); v7.insert(5);
	printf("\n\nv7有序重复前：");
	for (int i = 0; i < v7.size(); i++) {
		printf("%d ", v7[i]);

	}printf("\nv7有序去重复后：");
	v7.uniquify();
	for (int i = 0; i < v7.size(); i++) {
		printf("%d ", v7[i]);

	}

	{
		Vector<int> i1;
		Vector<float> f1;
	}
}