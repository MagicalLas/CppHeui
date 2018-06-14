// CppHeui.cpp : 응용 프로그램의 진입점을 정의합니다.
//

#include "CppHeui.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	const char * filename="F:/CppHeui/main.text";
	cout << "Hello CMake." << endl;
	cout << filename << endl;	

	ifstream infile(filename, fstream::in| fstream::out);
	unsigned int h;

	infile >> hex >> h;
	cout << h;
	int a;
	cin>>a;
	return 0;
}
