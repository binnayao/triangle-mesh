#pragma once
#include "point.h"
#include <vector>
using namespace std;

class line
{
public:
	line();
	~line();

	void insertPoint(int p);//���
	int start;
	int end;
	int num;
	int type; //�������Ƹ������Ƿ�ʹ�ã�Ĭ��type=0������ʹ�ã����type=1����������ʾ�����ε�ʱ��ʹ�ã���Ҫ���ںϲ�ͬƽ���ߵ�ʱ��ʹ��
	vector<int>pointSet;//������������int,������������������
};

