/*************************************************************************
> File Name: CppHeui.cpp
> Project Name: CppHeui
> Author: Wonho Ha aka Las
> Purpose: Ahuei for cpp
> Created Time: 2018/06/22
> Copyright (c) 2018, Wonho-Ha aka Las
*************************************************************************/

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
//문자열을 분해
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
//출력가능 객체
struct Printable
{
	virtual auto toString()->string = 0;
};
//현재 상태
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
	stack<int> & nowStorage;
	vector< stack<int> > otherStorage;
	auto changeStack(wchar_t index) -> void {
		auto stackIndex = stackIndices(index);
		nowStorage = otherStorage[stackIndex];
	}

	auto changeStack(wchar_t index, int data) -> void {
		auto stackIndex = stackIndices(index);
		nowStorage = otherStorage[stackIndex];
		nowStorage.push(data);
	}
	//스택에 값이 2개 이상 있는지 확인하는 함수
	auto stackCheck() -> bool {
		if (nowStorage.size() < 2) {
			cout << "Memory Was Not Enough" << endl;
		}
		return (nowStorage.size() < 2);
	}
	//스택에서 두 값을 꺼내고 계산하는 함수
	auto stackCal(int(*f)(int a, int b)) -> void {
		if (stackCheck())
			return;
		auto a = nowStorage.top();
		nowStorage.pop();
		auto b = nowStorage.top();
		nowStorage.pop();
		nowStorage.push(f(a,b));
	}
	//스택에 값을 넣기위한 함수
	auto stackInput(wchar_t data)-> void {
		if (data == L'ㅇ')
		{
			int inputData=0;
			cin >> inputData;
			nowStorage.push(inputData);
		}
		else if (data == L'ㅎ')
		{
			wchar_t inputData;
			wcin >> inputData;
			nowStorage.push(inputData);
		}
		else if (data == L'ㅃ')
		{
			nowStorage.push(nowStorage.top());
		}
		else if (data == L'ㅍ')
		{
			if (stackCheck())
				return;
			auto a = nowStorage.top();
			nowStorage.pop();
			auto b = nowStorage.top();
			nowStorage.pop();
			nowStorage.push(a);
			nowStorage.push(b);
		}
		else {
			nowStorage.push(strokeCount(data));
		}

	}
	auto stackOut(wchar_t data) -> void {
		if (data == L'ㅇ')
		{
			cout << nowStorage.top();
		}
		if (data == L'ㅎ')
		{
			wcout << (wchar_t)nowStorage.top();
		}
		nowStorage.pop();
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
		case L'ㅍ':
			stackInput(code.Lead);
			break;
		case L'ㅅ':
			changeStack(code.Tail);
			break;
		case L'ㅆ':
			auto data = nowStorage.top();
			changeStack(code.Tail, data);
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

//출력가능한 객체를 출력하는 함수
auto print(Printable* object) noexcept -> void {
	cout << object->toString() << endl;
}

//Type을 보기위한 가상객체.
template<class T>
class TD;

//wchar_T를 분해하여 Char를 생성한다.
//줄의 끝이라면('\n') border가 0이다.
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

//초기 설정을 하는 함수.
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
	interpre.analyseHead(wcharToChar(L'밤'));
	interpre.analyseHead(wcharToChar(L'밣'));
	interpre.analyseHead(wcharToChar(L'따'));
	interpre.analyseHead(wcharToChar(L'따'));


	interpre.analyseHead(wcharToChar(L'맣'));

	

	string s;
	cin >> s;
	return 0;
}