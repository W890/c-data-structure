#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<limits.h>
#include<math.h>
//int main() {
//	//打印1——10数字
//	int d = 1;
//	do {
//		printf("%d ", d);
//		d = d + 1; //d++
//		//循环体
//	} while (d <= 10);//循环条件
//	//1,0
//
//	printf("\n");
//	int w = 1;
//	while (w <= 10) {//判断真假。0/1
//		printf("%d ", w);
//		w++; //w = w + 1;
//	}
//
//	printf("\n");
//	for (int f = 1;f <= 10 ; f++) {
//		printf("%d ", f);
//	}
//
//	//打印乘法表
//	printf("\n\n");
//	for (int i = 1; i <= 9; i++) {//1 x 1 = 1 
//		for (int j = 1; j <= i; j++) {
//			printf("%d x %d = %-2d ", j, i, i * j);
//		}
//		printf("\n");
//	}
//	//1 x 1 = 1
//	//1 x 2 = 2 2 x 2 = 4
//	//1 x 3 = 3 2 x 3 = 6 3 x 3 = 9
//
//	printf("\n\n");
//	int i = 1;
//	while (i <= 9) {
//		int j = 1;
//		while (j <= i) {
//			printf("%d x %d = %-2d ", i, j ,i * j);
//			j++;
//		}
//		i++;
//		printf("\n");
//	}
//
//	printf("\n\n");
//	int n = 1;
//	do {
//		int m = 1;
//		do {
//			printf("%d x %d = %-2d ", m, n, m * n);
//			m++;
//		} while (m <= n);
//		printf("\n");
//		n++;
//	} while (n <=9);
//
//}


//进制转换

//int 整型
//无符号整型：表示0和正数的整数(unsigned)
//有符号整型：表示0 和正负数的整数(signed)
//sizeof
//int , char 
//int main() {
//	printf("sizeof(int) = %u\n", (unsigned)sizeof(int));
//	printf("sizeof(char) = %u\n", (unsigned)sizeof(char)); //char 的sizeof永远为1；
//	//long int (简写为long)
//	printf("sizeof(long) = %u\n", (unsigned)sizeof(long));
//	printf("sizeof(long long int) = %u\n", (unsigned)sizeof(long long int));
//	printf("sizeof(short) = %u\n", (unsigned)sizeof(short));
//
//	//<limits.h>  MAX,MIN
//
//	printf("\n");
//	puts("该环境下字符型，整型数值的范围：");
//	printf("int        :%d~%d\n", INT_MIN, INT_MAX);
//	printf("long      :%ld~%ld\n", LONG_MIN, LONG_MAX);
//	printf("short      :%d~%d\n", SHRT_MIN, SHRT_MAX);
//	printf("char      :%d~%d\n", CHAR_MIN, CHAR_MAX);
//
//	printf("unsigned char  :%d~%d\n", 0, UCHAR_MAX);
//	printf("unsigned       :%u~%u\n", 0, UINT_MAX);
//	printf("unsigned long   :%lu ~ %lu\n", 0, ULONG_MAX);
//	printf("unsigned short   :%u~%u\n", 0, USHRT_MAX);
//
//	//<<左移号 ,>>右移号
//	//二进制 0001 = 十进制 1  （<<) 《————》 二进制 0010 = 十进制 2
//	//  10 << 20  10>> 5
//
//}

//void to_bin(int num) {
//
//    // 12 
//    int temp = 0, i = 0;
//    int arr[20] = { 0 };
//    do {
//        temp = num % 2;
//        num /= 2;
//        arr[i++] = temp;
//    } while (num != 0);
//
//    for (int j = i - 1; j >= 0; j--)
//        printf("%d ", arr[j]);
//}
//
//
//int main() {
//    int m = 0;
//    printf("输入一个十进制数： ");
//    scanf("%d", &m);
//
//    to_bin(m);
//    printf("\n");
//    to_bin(m << 1);
//    printf("\n");
//    to_bin(m >>= 2);
//}
//
////浮点型  
//// float 单精度浮点型 printf("%f") scanf("%lf");
//// double 双精度浮点型 %f
//


//指针
//指针代表的是地址 
//int a = 1(0);
//int *b = a;
//int c = a;

//int main() {
//	int arr[10] = { 0 };
//	printf("%p\n", arr);
//	printf("%p\n", &arr);
//
//	int* p = arr; //赋    ==（等号）
//	printf("%p\n", p);
//
//	int a = 1; 
//	printf("%d", a);
//	printf("\n\n");
//	int c = a;
//	printf("%d", c);
//}



//void swap(int* px, int* py) {
//    int temp = *px;
//    *px = *py;
//    *py = temp;
//}
//
//void sort(int* n1, int* n2) {
//    if (*n1 > *n2)
//        swap(n1, n2);
//}
//
//int main() {
//    int na, nb;
//    puts("请输入两个整数：");
//    printf("整数A：");
//    scanf("%d", &na);
//    printf("整数B：");
//    scanf("%d", &nb);
//
//    sort(&na, &nb);
//
//    puts("将两数的值按升序排序：");
//    printf("整数A的值是%d：", na);
//    printf("整数B的值是%d: ", nb);
//
//    return 0;
//}

int main() {
	int number = 0;
	scanf("%d", &number);
	int fact = 1;
	for (int i = 1; i <= number; i++) {
		fact *= i;
	}
	printf("%d", fact);
}

//float calcu(float num1, char op, float num2) {//二元计算
//	float number = 0.0;
//	switch (op) {
//	case '+':number = num1 + num2; break;
//	case '-':number = num1 - num2; break;
//	case '*':number = num1 * num2; break;
//	case '/':number = num1 / num2; break;
//	case '^':number = pow(num1, num2); break;
//	}
//
//	return number;
//}
//
//int main() {
//	printf("%.1f\n", calcu(2 ,'+', 2));
//	printf("%.1f\n", calcu(2, '-', 2));
//	printf("%.1f\n", calcu(2, '*', 8));
//	printf("%.1f\n", calcu(2, '/', 2));
//	printf("%.1f\n", calcu(2, '^', 3));
//}
