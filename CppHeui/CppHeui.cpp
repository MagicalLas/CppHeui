// CppHeui.cpp : 응용 프로그램의 진입점을 정의합니다.
//

#include "CppHeui.h"
#include <vector>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//wchar to int
//int is method
auto strokeCount(wchar_t s) ->int{
	switch (s)
	{

	case L'ㄱ':
	case L'ㄴ':
	case L'ㅅ':
		return 2;

	case L'ㄷ':
	case L'ㅈ':
	case L'ㅋ':
		return 3;

	case L'ㅁ':
	case L'ㅂ':
	case L'ㅊ':
	case L'ㅌ':
	case L'ㅍ':
	case L'ㄲ':
	case L'ㄳ':
	case L'ㅆ':
		return 4;

	case L'ㄵ':
	case L'ㄹ':
	case L'ㄶ':
		return 5;

	case L'ㅄ':
		return 6;

	case L'ㄺ':
		return 7;

	case L'ㅀ':
		return 8;

	case L'ㄻ':
	case L'ㄼ':
		return 9;

	default:
		break;
	}
	return -1;
}

//wchar to int
auto stackIndices(wchar_t & s) -> int{
	switch (s)
	{
	case L' ':
		return 0;
	case L'ㄱ':
		return 1;
	case L'ㄴ':
		return 2;
	case L'ㄷ':
		return 3;
	case L'ㄹ':
		return 4;
	case L'ㅁ':
		return 5;
	case L'ㅂ':
		return 6;
	case L'ㅅ':
		return 7;
	case L'ㅈ':
		return 8;
	case L'ㅊ':
		return 9;
	case L'ㅋ':
		return 10;
	case L'ㅌ':
		return 11;
	case L'ㅍ':
		return 12;
	case L'ㄲ':
		return 13;
	case L'ㄳ':
		return 14;
	case L'ㄵ':
		return 15;
	case L'ㄶ':
		return 16;
	case L'ㄺ':
		return 17;
	case L'ㄻ':
		return 18;
	case L'ㄼ':
		return 19;
	case L'ㄽ':
		return 20;
	case L'ㄾ':
		return 21;
	case L'ㄿ':
		return 22;
	case L'ㅄ':
		return 23;
	case L'ㅆ':
		return 24;
	default:
		break;
	}
	return -1;
}

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

struct Char
{
	wchar_t Lead;
	wchar_t Vowel;
	wchar_t Tail;
	bool border;
	auto print() -> void {
		if (!border)
			wcout << Lead << " : " << Vowel << " : " << Tail << endl;
		else {
			cout << "Border" << endl;
		}
	}
};

struct Printable
{
	virtual auto toString()->string = 0;
};
struct State : Printable
{
	int cx;
	int cy;
	State() {
		cx = 0;
		cy = 0;
	}
	auto toString() -> string override {
		return "STATE : " + to_string(cx) + ", " + to_string(cy);
	}
};
struct CodeInterpreter
{
	stack<int> storage;
	auto run(Char code, State& state) -> void{

		
	}
	auto analyseHead(wchar_t head) -> bool {
		switch (head)
		{
		case L'ㅎ':
			exit(0);
			break;
		case L'ㄷ': {
			auto a = storage.top();
			storage.pop();
			auto b = storage.top();
			storage.pop();
			storage.push(a + b);
		}
		default:
			break;
		}
		return true;
	}
	auto analyseMiddle(wchar_t middle, State& state) -> bool{
		switch (middle)
		{
		case L'ㅏ':
			state.cx += 1;
			break;
		case L'ㅑ':
			state.cx += 2;
			break;
		case L'ㅓ':
			state.cx -= 1;
			break;
		case L'ㅕ':
			state.cx -= 2;
			break;
		case L'ㅗ':
			state.cy += 1;
			break;
		case L'ㅛ':
			state.cy += 2;
			break;
		case L'ㅜ':
			state.cy -= 1;
			break;
		case L'ㅠ':
			state.cy -= 1;
			break;
		case L'ㅢ':
			break;
		case L'ㅡ':
			break;
		case L'ㅣ':
			break;
		default:
			break;
		}
		return true;
	}
};
auto print(Printable* object) -> void {
	cout<<object->toString()<<endl;
}
template<class T>
class TD;

auto wcharToChar(wchar_t word) -> Char& {

	Char w;
	w.border = false;
	if (word == '\n')
		w.border = true;
	w.Lead = wcHead[(word - 0xAC00) / (21 * 28)];
	w.Vowel = wcMid[(word - 0xAC00) % (21 * 28) / 28];
	w.Tail = wcTail[(word - 0xAC00) % 28];

	return w;
};

auto init()-> void {
	cout << "Start of Programs" << endl;
	setlocale(LC_ALL, "Korean");
};

int main()
{
	init();
	CodeInterpreter interpre;
	State st;
	interpre.analyseMiddle(L'ㅏ', st);
	interpre.analyseHead(L'ㅎ', st);
	interpre.analyseMiddle(L'ㅠ', st);
	interpre.analyseMiddle(L'ㅜ', st);

	print(&st);

	string s;
	cin >> s;
	return 0;
}
