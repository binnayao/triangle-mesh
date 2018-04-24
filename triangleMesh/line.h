#pragma once
#include "point.h"
#include <vector>
using namespace std;

class line
{
public:
	line();
	~line();

	void insertPoint(int p);//插点
	int start;
	int end;
	int num;
	int type; //用来控制该条线是否使用，默认type=0，代表使用，如果type=1，代表不在显示三角形的时候使用，主要是在合并同平面线的时候使用
	vector<int>pointSet;//向量的类型是int,用来存线向量的索引
};

