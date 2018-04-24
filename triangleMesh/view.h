#pragma once
#include <vector>
using namespace std;
#include "point.h"
#include "line.h"

class view
{
public:
	view();
	~view();

	void readFile(); //文件读取
	void linePointSort(); //线上的点进行排序
	void linecombine();//线的组合
	vector<point>point_set;//点的集合，全部的点都在存在这个向量里，用索引取值；
	vector<line>line_set;//线的集合，全部的线都存在这里，其中每一项存的是点的索引
};

