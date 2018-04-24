#pragma once
class point
{
public:
	point();
	~point();

	float x;
	float y;
	float z;
	int type; //点的类型，默认情况下的点的类型是0,0代表普通的点，然后1代表的是断点，2代表的是端点
};

