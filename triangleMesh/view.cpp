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
		line l; //声明一条线
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
			point_set.push_back(point);//点放到向量point_set里面
			l.insertPoint(point_set.size() - 1);//把一条线上的点的索引下标放到线的对象里面，然后把线放到线的向量里面
		}
		line_set.push_back(l);//操作对象，线
	}
	//cout <<setiosflags(ios::fixed)<<setprecision(6) << point_set[139].x << point_set[139].y << point_set[139].z;//float的精度不变？只是显示的时候默认显示6个有效数字？
	/*for (int j = 0; j < line_set[1].pointSet.size(); j++)
	{
		cout << line_set[1].pointSet[j] << endl;
	}*/

	//如果y轴是相同的，那么用一下方法进行判断
}

void view::linePointSort()
{
	bool exchange;
	//使用带boolean的冒泡排序
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
		point_set[line_set[i].start].type = 1; //先给点排序，这里给线的端点的点的类型设置为1，待会再合并线，合并完成之后，给合并完的线设置端点类型为2
		point_set[line_set[i].end].type = 1;
	}
}

void view::linecombine()
{
	//声明一个向量，用来存同一平面的线，然后给这些线排序
	vector<vector<int>> a;
	for (int i = 0; i < line_set.size(); i++)
	{	
		vector<int> b;
		if (line_set[i].type == 1)
			continue;
		b.push_back(i);
		for (int j = i + 1; j<line_set.size(); j++)
		{
			//这是判断y轴相等的情况，说明这两条线是在同个面上的，需要把这两条线合并，type的存在可以不把线从向量中移除
			if (point_set[line_set[i].start].y == point_set[line_set[j].start].y && line_set[j].type != 1)
			{
				b.push_back(j);
				line_set[j].type = 1;//后加入的线都设置为1,以后不用判断了
			}
		}
		a.push_back(b);//将一组同一片面的线放入放入向量b,把全部的线的组合放入a中
	}
	
	bool exchange;
	for (int m = 0; m < a.size(); m++)
	{	
		if (a[m].size() == 1)//如果只有一条线，就不需要排序，跳出该循环
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
	//经过上述处理之后，vector<verctor<int>> a里面的点是按照x的从小到大排序的，然后按照这个顺序，给line_set重新设置

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
		point_set[line_set[a[x][0]].start].type = 2; //这里是只有一条线的情况，这条线的开始和结尾的type就是2，是端点
		point_set[line_set[a[x][0]].end].type = 2;
	}
	//好像是已经处理完了，现在type 为0的都是需要用来画线的
	//然后每条线里面可能是有若干线组成的，已经按照x的方向从小到大排序了
	//现在线的端点是type=1；type=2是断点

}