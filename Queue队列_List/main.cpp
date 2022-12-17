#include <iostream>
using namespace std;


#include "../List�б�/List.h"//��ListΪ����

template <typename T> class Queue :public List<T> {//����ģ���ࣨ�̳�Listԭ�нӿ�
public://size(), empty()�Լ��������Žӿڶ�����ֱ��ʹ��

	void enqueue(T const& e) {//��ӣ�β������
		List<T>::insertAsLast(e);
	}

	T dequeue() {//���ӣ��ײ�ɾ��
		return List<T>::remove(List<T>::first());
	}

	T& front() {//����
		return List<T>::first()->data;
	}
};


struct Customer {//�˿��ࣺ�������ڣ����У�������ʱ��
	int window;
	unsigned int time;
};

int bestWindow(Queue<Customer> windows[], int nWin) {//Ϊ�µ��˿�ȷ����Ѷ���
	int minSize = windows[0].size(), optiWin = 0;//���Ŷ��У����ڣ�

	for (int i = 1;i < nWin;i++) //�����д�����
		if (minSize > windows[i].size()) {//��ѡ��
			minSize = windows[i].size();//��̶���
			optiWin = i;
		}

	return optiWin;
}



void simulate(int nWin, int servTime) {//��ָ����������������ʱ��ģ������ҵ��
	Queue<Customer>* windows = new Queue<Customer>[nWin];//Ϊÿһ������Ŷ����һ������

	for (int now = 0; now < servTime; now++) {//���°�֮ǰ��ÿ��һ����λʱ��
		if (rand() % (1 + nWin)) {//�¹˿��� nWin / (nWin + 1) �ĸ��ʵ���
			Customer c;
			c.time = 1 + rand() % 98;//�¹˿͵������ʱ�����ȷ��
			c.window = bestWindow(windows, nWin);//�ҳ���ѣ���̣��ķ��񴰿�
			windows[c.window].enqueue(c);//�¹˿ͼ����Ӧ�Ķ���
		}
		for (int i = 0; i < nWin; i++)//�ֱ���
			if (!windows[i].empty())//���ǿն���
				if (--windows[i].front().time <= 0)//���׹˿͵ķ���ʱ������һ����λ
					windows[i].dequeue();//������ϵĹ˿ͳ��У��ɺ�̹˿ͽ���
	}
	delete[]windows;//�ͷ����ж��У���ǰ��~List()���Զ���ն���
}



int main() {
	Queue<int> Q1;
	for (int i = 1; i <= 6; i++) {
		Q1.enqueue(i);
	}
	Q1.print();
	printf("\n");
	for (int i = 1; i <= 3; i++) {
		Q1.dequeue();
	}
	Q1.print();

	Queue<Customer> win[20];
	printf("\n\n��Ѵ��ڣ�%d", bestWindow(win, 5));
}