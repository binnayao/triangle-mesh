#include <iostream>
using namespace std;
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include "view.h"
#include <vector>

int main(int argc, char **argv)
{
	/*view a;
	a.readFile();*/
	/*vector<vector<int>> a;
	vector<int> b;
	b.push_back(1);
	a.push_back(b);
	cout << a[0].size() << endl;*/
	for (int i = 0; i < 3; i++){
		if (i == 1)
			continue;
		cout << i << endl;
	}
	return 0;
}