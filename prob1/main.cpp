#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int a;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f=d;
	inf_int g(f);
	inf_int e("-1223123143142332131231244");

	// cin >> g ;   // not required

	a=b*c;
	// e=g/f;       // not required

	b=c-d;


	if (f==d) {
		cout << "a : " << a << endl; //~~~~~~~~55500나와야함
		cout << "b : " << b << endl; //~~~~~~~~44
		cout << "c : " << c << endl; //a에서 00뺀거
		cout << "d : " << d << endl; //~~~~~11
		cout << "e : " << e << endl;
		cout << "f : " << f << endl; //same as d
		// cout << "g : " << g << endl;
	}

	return 0;
}
