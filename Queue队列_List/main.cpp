#include <iostream>
using namespace std;


#include "../List列表/List.h"//以List为基类

template <typename T> class Queue :public List<T> {//队列模板类（继承List原有接口
public://size(), empty()以及其他开放接口都可以直接使用

	void enqueue(T const& e) {//入队：尾部插入
		List<T>::insertAsLast(e);
	}

	T dequeue() {//出队：首部删除
		return List<T>::remove(List<T>::first());
	}

	T& front() {//队首
		return List<T>::first()->data;
	}
};


struct Customer {//顾客类：所属窗口（队列）、服务时长
	int window;
	unsigned int time;
};

int bestWindow(Queue<Customer> windows[], int nWin) {//为新到顾客确定最佳队列
	int minSize = windows[0].size(), optiWin = 0;//最优队列（窗口）

	for (int i = 1;i < nWin;i++) //在所有窗口中
		if (minSize > windows[i].size()) {//挑选出
			minSize = windows[i].size();//最短队列
			optiWin = i;
		}

	return optiWin;
}



void simulate(int nWin, int servTime) {//按指定窗口数、服务总时间模拟银行业务
	Queue<Customer>* windows = new Queue<Customer>[nWin];//为每一个窗口哦创建一个队列

	for (int now = 0; now < servTime; now++) {//在下班之前，每隔一个单位时间
		if (rand() % (1 + nWin)) {//新顾客以 nWin / (nWin + 1) 的概率到达
			Customer c;
			c.time = 1 + rand() % 98;//新顾客到达，服务时长随机确定
			c.window = bestWindow(windows, nWin);//找出最佳（最短）的服务窗口
			windows[c.window].enqueue(c);//新顾客加入对应的队列
		}
		for (int i = 0; i < nWin; i++)//分别检查
			if (!windows[i].empty())//各非空队列
				if (--windows[i].front().time <= 0)//队首顾客的服务时长减少一个单位
					windows[i].dequeue();//服务完毕的顾客出列，由后继顾客接替
	}
	delete[]windows;//释放所有队列（此前，~List()会自动清空队列
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
	printf("\n\n最佳窗口：%d", bestWindow(win, 5));
}