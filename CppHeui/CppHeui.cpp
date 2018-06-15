// CppHeui.cpp : 응용 프로그램의 진입점을 정의합니다.
//

#include "CppHeui.h"
#include <iostream>
#include <fstream>
#include "windows.h"
#include "locale.h"
#include <string>
#include <vector>
using namespace std;
//초성 
static const wchar_t wcHead[] = { L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ',
L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ',
L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ',
L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ',
L'ㅌ', L'ㅍ', L'ㅎ' };

//중성 
static const wchar_t wcMid[] = { L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ',
L'ㅓ', L'ㅔ', L'ㅕ', L'ㅖ',
L'ㅗ', L'ㅘ', L'ㅙ', L'ㅚ',
L'ㅛ', L'ㅜ', L'ㅝ', L'ㅞ',
L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ', L'ㅣ' };

//종성 
static const wchar_t wcTail[] = { L' ', L'ㄱ', L'ㄲ', L'ㄳ',
L'ㄴ', L'ㄵ', L'ㄶ', L'ㄷ',
L'ㄹ', L'ㄺ', L'ㄻ', L'ㄼ',
L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ',
L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ',
L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ',
L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ' };
int BreakHan(wchar_t *str, wchar_t *buffer,unsigned int nSize)
{
	unsigned int pos = 0;
	while (*str != '\0')
	{
		if (*str < 256)
		{
			if (pos + 2 >= nSize - 1)
				break;

			buffer[pos] = *str;
			++pos;
		}
		else
		{
			if (pos + 4 >= nSize - 1)
				break;

			buffer[pos] = wcHead[(*str - 0xAC00) / (21 * 28)];
			buffer[pos + 1] = wcMid[(*str - 0xAC00) % (21 * 28) / 28];
			buffer[pos + 2] = wcTail[(*str - 0xAC00) % 28];
			pos += 3;
		}
		++str;
	}

	buffer[pos] = '\0';
	return pos;
}

struct Storage
{
	int Type;
	vector<int> Memory;
};
struct Machine
{
	vector<char> CodeSpace;
	Storage* CurrentStorage;
	int xpos;
	int ypos;
	int dx;
	int dy;
	bool terminated;
	int run(string code) {
	}
};
int main()
{
	const char * filename="F:/CppHeui/main.text";
	cout << "Hello CMake." << endl;
	cout << filename << endl;	

	
	string h; 
	wchar_t *str = L"Laplace Desire, 하원호, 프로그래머. 천재가 되고 싶은 사람임.";
	wchar_t buffer[10];

	BreakHan(str, buffer, sizeof buffer);
	setlocale(LC_ALL, "Korean");
	printf("%S", buffer);
	cin >> h;
	Machine machine{};
	
	return 0;
}
