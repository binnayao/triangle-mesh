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

	void readFile(); //�ļ���ȡ
	void linePointSort(); //���ϵĵ��������
	void linecombine();//�ߵ����
	vector<point>point_set;//��ļ��ϣ�ȫ���ĵ㶼�ڴ�����������������ȡֵ��
	vector<line>line_set;//�ߵļ��ϣ�ȫ�����߶������������ÿһ�����ǵ������
};

