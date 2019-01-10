#include <iostream>
#include "LRULinkV2.h"

using namespace std;

bool isEqual(int a, int b){
	return a == b;
}

int main()
{
	LRULink<int> *lruLink = new LRULink<int>(3);
	int in;
	while (cin >> in)
	{
		cout << "get" << in << endl;
		lruLink->add(in, isEqual);
		cout << "after get" << endl;
		lruLink->printAll();
	}
	return 0;
}