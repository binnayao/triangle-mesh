#include "view.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream> 
#include <iomanip>
view::view()
{
}


view::~view()
{
}

void view::readFile()
{
	char buff[256];
	ifstream in("4.txt");
	if (!in.is_open())
	{
		cout << "read file , ERROR !!";
		exit(1);
	}

	while (!in.eof())
	{
		line l; //����һ����
		in.getline(buff, 100);
		stringstream str1;
		str1.str(buff);
		int lineSerial, lineNum;
		str1 >> lineSerial >> lineNum;
		for (int i = 0; i < lineNum; i++)
		{
			point point;
			in.getline(buff, 100);
			stringstream str2;
			str2.str(buff);
			float x, y, z;
			str2 >> x >> y >> z;
			point.x = x;
			point.y = y;
			point.z = z;
			point_set.push_back(point);//��ŵ�����point_set����
			l.insertPoint(point_set.size() - 1);//��һ�����ϵĵ�������±�ŵ��ߵĶ������棬Ȼ����߷ŵ��ߵ���������
		}
		line_set.push_back(l);//����������
	}
	//cout <<setiosflags(ios::fixed)<<setprecision(6) << point_set[139].x << point_set[139].y << point_set[139].z;//float�ľ��Ȳ��䣿ֻ����ʾ��ʱ��Ĭ����ʾ6����Ч���֣�
	/*for (int j = 0; j < line_set[1].pointSet.size(); j++)
	{
		cout << line_set[1].pointSet[j] << endl;
	}*/

	//���y������ͬ�ģ���ô��һ�·��������ж�
}

void view::linePointSort()
{
	bool exchange;
	//ʹ�ô�boolean��ð������
	for (int i = 0; i<line_set.size(); i++)
	{
		for (int j = 0; j<line_set[i].pointSet.size() - 1; j++)
		{
			exchange = false;
			for (int k = 0; k<line_set[i].pointSet.size() - 1 - j; k++)
			{
				if (point_set[line_set[i].pointSet[k]].x > point_set[line_set[i].pointSet[k + 1]].x)
				{
					exchange = true;
					swap(line_set[i].pointSet[k],line_set[i].pointSet[k + 1]);
				}
			}
			if (exchange == false)
				break;
		}
		line_set[i].start = line_set[i].pointSet[0];
		line_set[i].end = line_set[i].pointSet[line_set[i].num - 1];
		point_set[line_set[i].start].type = 1; //�ȸ�������������ߵĶ˵�ĵ����������Ϊ1�������ٺϲ��ߣ��ϲ����֮�󣬸��ϲ���������ö˵�����Ϊ2
		point_set[line_set[i].end].type = 1;
	}
}

void view::linecombine()
{
	//����һ��������������ͬһƽ����ߣ�Ȼ�����Щ������
	vector<vector<int>> a;
	for (int i = 0; i < line_set.size(); i++)
	{	
		vector<int> b;
		if (line_set[i].type == 1)
			continue;
		b.push_back(i);
		for (int j = i + 1; j<line_set.size(); j++)
		{
			//�����ж�y����ȵ������˵��������������ͬ�����ϵģ���Ҫ���������ߺϲ���type�Ĵ��ڿ��Բ����ߴ��������Ƴ�
			if (point_set[line_set[i].start].y == point_set[line_set[j].start].y && line_set[j].type != 1)
			{
				b.push_back(j);
				line_set[j].type = 1;//�������߶�����Ϊ1,�Ժ����ж���
			}
		}
		a.push_back(b);//��һ��ͬһƬ����߷����������b,��ȫ�����ߵ���Ϸ���a��
	}
	
	bool exchange;
	for (int m = 0; m < a.size(); m++)
	{	
		if (a[m].size() == 1)//���ֻ��һ���ߣ��Ͳ���Ҫ����������ѭ��
			continue;
		for (int n = 0; n < a[m].size()-1; n++){
			exchange = false;
			for (int l = 0; n < a[m].size() - 1 - n; l++){
				if (point_set[line_set[l].start].x > point_set[line_set[l+1].start].x)
				{
					exchange = true;
					swap(a[n][l],a[n][l+1]);
				}
			}
			if (exchange == false)
				break;
		}
	}
	//������������֮��vector<verctor<int>> a����ĵ��ǰ���x�Ĵ�С��������ģ�Ȼ�������˳�򣬸�line_set��������

	for (int x = 0; x < a.size(); x++)
	{
		if (a[x].size() != 1){
			for (int y = 1; y < a[x].size(); y++){
				for (int z = 0; z<line_set[a[x][y]].pointSet.size(); z++)
				{
					line_set[a[x][0]].insertPoint(line_set[a[x][y]].pointSet[z]);
				}
			}
		}
		line_set[a[x][0]].start = line_set[a[x][0]].pointSet[0];
		line_set[a[x][0]].end = line_set[a[x][0]].pointSet[line_set[a[x][0]].num - 1];
		point_set[line_set[a[x][0]].start].type = 2; //������ֻ��һ���ߵ�����������ߵĿ�ʼ�ͽ�β��type����2���Ƕ˵�
		point_set[line_set[a[x][0]].end].type = 2;
	}
	//�������Ѿ��������ˣ�����type Ϊ0�Ķ�����Ҫ�������ߵ�
	//Ȼ��ÿ�����������������������ɵģ��Ѿ�����x�ķ����С����������
	//�����ߵĶ˵���type=1��type=2�Ƕϵ�

}