#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int Rank;
typedef int T;

typedef struct Vector{
	Rank _size;
	int _capacity;
	T* _elem;
}Vector;

Vector vectorCreate(int c)
{
	Vector v;
	v._capacity = c;
	v._size = 0;
	v._elem = malloc(c * sizeof(T));
	return v;
}

//Vector ins;

Rank insert(Vector*ins, Rank r, const e) {
	for (Rank i = ins->_size; r < i; i--) 
		ins->_elem[i] = ins->_elem[i - 1];
	ins->_elem[r] = e; ins->_size++;
	return r;
}

int main() {
	Vector ins = vectorCreate(3);
	

	int v1 = insert(&ins, 0, 1);
	printf("%d ", v1);

}