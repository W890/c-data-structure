#pragma once

#include <iostream>

#include <cstdio>

#include<cstring>

#define QUEEN_MAX 20

typedef enum {
	Continuous, Step
}RunMode;


extern RunMode runMode;//����ģʽ
extern int nSolu;//�������
extern int nCheck;//���Ե��ܴ���


struct Queen {//�ʺ���
	int x, y;//�ʺ��������ϵ�λ������

	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator==(Queen const& q) const {//�����еȲ��������Լ�ⲻͬ�ʺ�֮����ܵĳ�ͻ
		return (x == q.x)//�г�ͻ����һ�����ʵ���ᷢ����ʡ�ԣ�
			|| (y == q.y)//�г�ͻ
			|| (x + y == q.x + q.y)//�����Խ��߳�ͻ
			|| (x - y == q.x - q.y);//�ط��Խ��߳�ͻ
	}

	bool operator != (Queen const& q) const {//���ز��Ȳ�����
		return !(*this == q);
	}

};


int nCheck = 0;
int nSolu = 0;

void placeQueens(int N) {//N�ʺ��㷨�������棩��������̽/���ݵĲ��ԣ�����ջ��¼���ҵĽ��
	Stack<Queen> solu;//��ţ����֣����ջ
	Queen q(0, 0);//��ԭ��λ�ó���

	do {//������̽������
		if (N <= solu.size() || N <= q.y) {//���ѳ��У���
			q = solu.pop();
			q.y++;//����һ�У���������̽��һ��
		} else {//������̽��һ��
			while ((q.y < N) && (0 <= solu.find(q))) {//ͨ�������лʺ�ıȶ�
				q.y++;
				nCheck++;//�����ҵ��ɰڷ���һ�ʺ����
			}
			if (N > q.y) {//�����ڿɰڷŵ��У���
				solu.push(q);//���ϵ�ǰ�ʺ󣬲�
				if (N <= solu.size())//�����ֽ��ѳ�Ϊȫ�ֽ⣬��ͨ��ȫ�ֱ���nSolu����
					nSolu++;
				q.x++;
				q.y = 0;//ת����һ�У��ӵ�0�п�ʼ����̽��һ�ʺ�
			}
		}
	} while ((0 < q.x) || (q.y < N));//���з�֧���ѻ���ٻ��ֽ֮�󣬽����㷨
}


