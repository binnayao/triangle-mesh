#include "line.h"


line::line()
{
	start = 0;
	end = 0;
	num = 0;
	type = 0;
}


line::~line()
{
}

void line::insertPoint(int p){
	pointSet.push_back(p);
	num++;
	start = pointSet[0];
	end = pointSet[num - 1];
}
