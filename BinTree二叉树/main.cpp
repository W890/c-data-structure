#include <iostream>
using namespace std;

#include "BinTree.h"

int main() {
	BinTree<int> T1;
	BinNodePosi<int> N1;
	for (int i = 1; i <= 6; i++) {
		T1.insert(i, N1);
		T1.insert(N1, i);
	}
	
}