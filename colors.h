#include <windows.h>
#pragma once

enum colors {
	BLACK       = 0,
	DARK_BLUE   = 1,
	DARK_GREEN  = 2,
	TEAL        = 3,
	DARK_RED    = 4,
	DARK_PURPLE = 5,
	GOLD        = 6,
	GREY        = 7,
	DARK_WHITE  = 8,
	BLUE        = 9,
	GREEN       = 10,
	CYAN        = 11,
	RED         = 12,
	PURPLE      = 13,
	YELLOW      = 14,
	WHITE       = 15
};

enum newcolors {newGREEN, newYELLOW, newRED, newCYAN};

HANDLE hConsole;

//setColor for text
void setColor(int wNewColorAttrs)
{
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, wNewColorAttrs);
	return;
}

//saveColor for text
void saveColor(WORD &wOldColorAttrs)
{
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs=csbiInfo.wAttributes;
	return;
}

//loadColor for text
void loadColor(WORD wOldColorAttrs)
{
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, wOldColorAttrs);
	return;
}

//setXY for text
void setXY(int x, int y)
{
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(hConsole, pos);
	return;
}

//functions print RGB text
typedef unsigned int ui;

class PrintText
{
public:
	HFONT hfont;
	COLORREF colorRGB;
	PrintText(int, int, char*, const ui, const ui, const ui, bool);
	void initfont(HFONT&, LONG, LONG, char*);
	void writetext(HDC, int, int, char*);
	~PrintText();
};

PrintText::PrintText(int X, int Y, char* text, const ui R, const ui G, const ui B, bool FLG):hfont(NULL)
{
	colorRGB=RGB(R, G, B);
	HDC hDC=GetWindowDC(GetConsoleWindow());
	if (FLG)
		initfont(hfont, -24, FW_NORMAL, "Lucida Handwriting");
	writetext(hDC, X, Y, text);
	ReleaseDC(GetConsoleWindow(), hDC);
}

void PrintText::initfont(HFONT& hfont, LONG lfheight, LONG lfweight, char* namefont)
{
	LOGFONT logfont;
	memset(&logfont, NULL, sizeof(logfont));
	logfont.lfHeight=lfheight;
	logfont.lfWeight=lfweight;
	strcpy(logfont.lfFaceName, namefont);
	hfont=CreateFontIndirect(&logfont);
	return;
}

void PrintText::writetext(HDC _hdc, int _X, int _Y, char* _Text)
{
	COLORREF oldcolorRGB=SetTextColor(_hdc, colorRGB);
	HFONT oldhfont=(HFONT)SelectObject(_hdc, hfont);
	SetBkMode(_hdc, 0);
	TextOut(_hdc, _X, _Y, _Text, strlen(_Text));
	SetTextColor(_hdc, oldcolorRGB);
	SelectObject(_hdc, oldhfont);
	return;
}

PrintText::~PrintText()
{
	DeleteObject(hfont);
}

//printRGBtext for text
void printRGBtext(int x, int y, char* text, const ui r, const ui g, const ui b, bool flg)
{
	PrintText objPrintText(x, y, text, r, g, b, flg);
	return;
}
