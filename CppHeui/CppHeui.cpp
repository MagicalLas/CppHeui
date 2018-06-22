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
	auto print() noexcept -> void {
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
	auto toString() noexcept -> string override {
		return "STATE : " + to_string(cx) + ", " + to_string(cy);
	}
};
struct CodeInterpreter
{
	stack<int> storage;

	auto stackCheck() -> bool {
		if (storage.size() < 2) {
			cout << "Memory Was Not Enough" << endl;
		}
		return (storage.size() < 2);
	}
	auto stackCal(int(*f)(int a, int b)) -> void {
		if (stackCheck())
			return;
		auto a = storage.top();
		storage.pop();
		auto b = storage.top();
		storage.pop();
		cout << a << ":" << b << endl;
		storage.push(f(a,b));
	}
	//ㅂ명령 도움 함수.
	auto stackInput(wchar_t data)-> void {
		if (data == L'ㅇ')
		{
			int inputData=0;
			cin >> inputData;
			storage.push(inputData);
		}
		else if (data == L'ㅎ')
		{
			wchar_t inputData;
			wcin >> inputData;
			storage.push(inputData);
		}
		else if (data == L'ㅃ')
		{
			storage.push(storage.top());
		}
		else {
			storage.push(stackIndices(data));
		}

	}
	auto stackOut(wchar_t data) -> void {
		if (data == L'ㅇ')
		{
			cout << storage.top();
		}
		if (data == L'ㅎ')
		{
			wcout << (wchar_t)storage.top();
		}
		storage.pop();
	}
	//명령 실행 코드
	auto run(Char code, State& state) -> void{

		
	}
	//첫소리 분석 코드
	auto analyseHead(Char code) noexcept -> bool {
		switch (code.Lead)
		{
		case L'ㅎ':
			exit(0);
			break;
		case L'ㄷ': {
			stackCal([](int a, int b) -> int {
				return a + b;
			});
			break;
		}
		case L'ㄸ': {
			stackCal([](int a, int b) -> int {
				return a * b; 
			});
			break;
		}
		case L'ㅌ': {
			stackCal([](int a, int b) -> int {
				return a - b;
			});
			break;
		}
		case L'ㄴ':
			stackCal([](int a, int b) -> int {
				return a / b;
			});
			break;
		case L'ㅂ':
			stackInput(code.Tail);
			break;
		case L'ㅁ':
			stackOut(code.Tail);
			break;

		case L'ㅃ':
			stackInput(code.Lead);
			break;
		default:
			break;
		}
		return true;
	}
	//모음 분석 함수
	auto analyseMiddle(wchar_t middle, State& state) -> bool {
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
auto print(Printable* object) noexcept -> void {
	cout << object->toString() << endl;
}

template<class T>
class TD;

auto wcharToChar(wchar_t word) noexcept -> Char& {

	Char w;
	w.border = false;
	if (word == '\n')
		w.border = true;
	w.Lead = wcHead[(word - 0xAC00) / (21 * 28)];
	w.Vowel = wcMid[(word - 0xAC00) % (21 * 28) / 28];
	w.Tail = wcTail[(word - 0xAC00) % 28];

	return w;
};

auto init() noexcept -> void {
	cout << "Start of Programs" << endl;
	setlocale(LC_ALL, "Korean");
};

int main()
{
	init();
	CodeInterpreter interpre;
	State st;
	interpre.analyseHead(wcharToChar(L'밤'));
	interpre.analyseHead(wcharToChar(L'밣'));
	interpre.analyseHead(wcharToChar(L'따'));
	interpre.analyseHead(wcharToChar(L'빠'));
	interpre.analyseHead(wcharToChar(L'밣'));
	interpre.analyseHead(wcharToChar(L'밟'));

	interpre.analyseHead(wcharToChar(L'맣'));
	interpre.analyseHead(wcharToChar(L'맣'));
	interpre.analyseHead(wcharToChar(L'맣'));
	interpre.analyseHead(wcharToChar(L'맣'));
	interpre.analyseHead(wcharToChar(L'맣'));
	interpre.analyseHead(wcharToChar(L'맣'));

	print(&st);
	

	string s;
	cin >> s;
	return 0;
}