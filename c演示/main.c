#include <stdio.h>

int main() {
	int arr[10] = { 0 };
	printf("%p\n", arr);
	printf("%p\n", &arr);
	int* p = arr;
	printf("%p\n", p);
	char aee[10] = { 0 };
	printf("%p\n", aee);
	printf("%p\n", &aee);
	char* m = aee;
	printf("%p\n", m);
}