#include <iostream>
#include <windows.h>
#include <map>
#include <conio.h>
#include <time.h>
#include "timer.h"
#include "colors.h"

#define _name(n) #n

#define key_left 0x4B
#define key_right 0x4D
#define key_up 0x48
#define key_down 0x50
#define key_enter 0xD
#define key_back 0x8
#define key_esc 0x1B

const int SLEEP(910);

Mytimer::timerDisplay objtD;
Mytimer::timerControl objtC;
Mytimer::timerControl::Queue q_objtC;

using namespace std;
using Mytimer::NO;
using Mytimer::YES;

void line1_link(Mytimer::flag F) {(!F)?objtD.line1(false):objtD.line1(true); return;}
void line2_link(Mytimer::flag F) {(!F)?objtD.line2(false):objtD.line2(true); return;}
void line3_link(Mytimer::flag F) {(!F)?objtD.line3(false):objtD.line3(true); return;}
void line4_link(Mytimer::flag F) {(!F)?objtD.line4(false):objtD.line4(true); return;}
void line5_link(Mytimer::flag F) {(!F)?objtD.line5(false):objtD.line5(true); return;}
void line6_link(Mytimer::flag F) {(!F)?objtD.line6(false):objtD.line6(true); return;}
void line7_link(Mytimer::flag F) {(!F)?objtD.line7(false):objtD.line7(true); return;}

void colon_link(const int x, const int y) {
	objtD.colon(x, y);
	return;
}

void (*arr_line[Mytimer::numline])(Mytimer::flag) = {
	line1_link, line2_link, line3_link, line4_link, line5_link, line6_link, line7_link
};

void (*ptr_colon)(const int x, const int y) = {
	colon_link
};

template <typename T>
void Mytimer::timerDisplay::drawDIGIT(T value, int x, int y, bool mask)
{
	value==':'?ptr_colon(x,y):NULL;

	if (value==0x3A)
		return;

	if (value==' '||value=='_'||value=='-') {
		char* v;
		if (value==' ') {
			char emptycell[]={"0000000"}; v=emptycell;
			(mask)?v="1111111":NULL;
		} else
		if (value=='_') {
			char underline[]={"0001000"}; v=underline;
			(mask)?v="1110111":NULL;
		} else
		if (value=='-') {
			char dash[]={"0000001"}; v=dash;
			(mask)?v="1111110":NULL;
		}

		position linemass[numline];
		for (int i(0); i<numline; i++)
			linemass[i]=overwritelines(i+1, x, y);

		ui i=NULL;
		while (numline-i) {
			if (v[i++]==objtD.getCH_null())
				arr_line[i-1](NO);
			else
				arr_line[i-1](YES);
		}
		objtD.overwritelinesback(linemass);
		return;
	}

	int value_digit=value;
	value>='0'&&value<='9'?value_digit-=0x30:NULL;
	position linemass[numline];
	for (int i(0); i<numline; i++)
		linemass[i]=overwritelines(i+1, x, y);

	ui i=NULL;
	while (numline-i) {
		if ((objtD.getDIGIT(value_digit)[i++])!=objtD.getCH_null())
			value>='0'&&value<='9'?arr_line[i-1](NO):arr_line[i-1](YES);
		else
			value>='0'&&value<='9'?arr_line[i-1](YES):arr_line[i-1](NO);
	}

	objtD.overwritelinesback(linemass);
	return;
}

template <typename T>
void Mytimer::timerDisplay::drawDIGIT(timerDisplay &obj, T value, int x, int y, char *sign)
{
	char asterisk=0x2A;
	int dx(1), dy(1);
	int count=NULL;
	if (sign!="DIGIT") {
		char* str;
		map<char, char*> symbol;
		symbol[':']="0000000000000000010000000000000100000000000000000";
		symbol['_']="0000000000000000000000000000000000001010100000000";
		symbol[' ']="0000000000000000000000000000000000000000000000000";
		symbol['-']="0000000000000000000000101010000000000000000000000";
		map<char, char*>::iterator it=symbol.begin();
		for (;it!=symbol.end();++it) {
			if (it->first==(char)value)
				str=it->second;
		}
		while (dy<=7) {
			setXY(x, y);
			y++;
			while (dx<=7) {
				if (sign=="COLON"&&(dx<4||dx>4)) {
					count++;
					dx++;
					continue;
				}
				if (str[count]==obj.getCH_null())
					setColor(DARK_BLUE);
				else if (str[count]==obj.getCH_one())
					setColor(CYAN);
				
				printf("%c", asterisk);
				
				count++;
				dx++;
			}
			dy++;
			dx=1;
		}
		symbol.clear();
	} else
	{
		while (dy<=7) {
			setXY(x, y);
			y++;
			while (dx<=7) {
				if ((obj.getDIGIT(value)[count])==obj.getCH_null())
					setColor(DARK_BLUE);
				else if ((obj.getDIGIT(value)[count])==obj.getCH_one())
					setColor(CYAN);
				
				printf("%c", asterisk);
				
				count++;
				dx++;
			}
			dy++;
			dx=1;
		}
	}
	
	return;
}

void Mytimer::timerDisplay::drawBUTTON(btn button, int x, int y)
{
	switch (button)
	{
		case START:
			objtD.drawSTARTcool(x, y, NULL);
			objtD.drawTEXT("start", 135, 260);
			break;
		case PAUSE:
			objtD.drawPAUSEcool(x, y, NULL);
			objtD.drawTEXT("pause", 235, 260);
			break;
		case STOP:
			objtD.drawSTOPcool(x, y, NULL);
			objtD.drawTEXT("stop", 350, 260);
			break;
		case RESET:
			objtD.drawRESETcool(x, y, NULL);
			objtD.drawTEXT("reset", 440, 260);
			break;
		default: break;
	}
	return;
}

void Mytimer::timerDisplay::drawBUTTON(timerDisplay &obj, btn button, int x, int y)
{
	char *BTN;
	switch (button)
	{
		case START: BTN="1000011000111001100010000"; break;
		case PAUSE: BTN="1010010100101001010010100"; break;
		case STOP:  BTN="1111111111111111111111111"; break;
		case RESET: BTN="1010010110101111011010100"; break;
		default: break;
	}

	WORD OldColor;
	char asterisk=0x2A;
	int dx(1), dy(1);
	int count=NULL;
	saveColor(OldColor);
	if (!objtC.checkPoint(objtC.takeSelection())&&OldColor!=DARK_WHITE) {
		setColor(WHITE);
		saveColor(OldColor);
	}
	while (dy<=5) {
		setXY(x, y);
		y++;
		while (dx<=5) {
			if (BTN[count]==obj.getCH_null())
				setColor(BLACK);
			else if (BTN[count]==obj.getCH_one())
				loadColor(OldColor);
			printf("%c", asterisk);
			count++;
			dx++;
		}
		dy++;
		dx=1;
	}
	return;
}

void Mytimer::timerDisplay::timerTitle::drawTitle(Title ARRAY[], int index)
{
	setXY(ARRAY[index-1].posX, 1);
	if (objtC.checkPoint(objtC.takeChoice2())==ARRAY[index-1].number&&objtC.checkPoint(objtC.takeSelection())!=true) {
		setColor(WHITE);
		_cputs("* ");
		_cputs(ARRAY[index-1].name);
	} else {
		setColor(DARK_WHITE);
		if (!objtC.checkPoint(objtC.takeSelection())) {
			_cputs("  ");
			_cputs(ARRAY[index-1].name);
		} else
		if (objtC.checkPoint(objtC.takeChoice2())==ARRAY[index-1].number) {
			_cputs("* ");
			_cputs(ARRAY[index-1].name);
		} else
		{
			_cputs("  ");
			_cputs(ARRAY[index-1].name);
		}
	}
	return;
}

void Mytimer::timerDisplay::timerTitleButton::drawTitleButton(md number, int posX, int color)
{
	timerTitleButton objTitleButton;
	setXY(posX, 0x14);
	if (!objtC.checkPoint(objtC.takeSelection()))
		(objtC.checkPoint(objtC.takeChoice1())==number)?setColor(WHITE):setColor(DARK_WHITE);
	else
		(objtC.checkPoint(objtC.takeChoice1())==number)?setColor(color):setColor(DARK_WHITE);

	objTitleButton=*this;
	cout<<objTitleButton;
	return;
}

void Mytimer::timerDisplay::drawTEXT(char* text, int x, int y)
{
	if (objtC.getMODE()==FIRST) {
		const int size(4);
		struct space {
			int x1, y1, x2, y2;
		} *ptr;
		if (text==NULL) {
			ptr=new space;
			ptr->x1=0x1E;
			ptr->y1=0x0A;
			ptr->x2=0x276;
			ptr->y2=0x2D;
			cleaning_space(ptr->x1, ptr->y1, ptr->x2, ptr->y2);
			char* name[size]={_name(Clock), _name(Al Clock), _name(Stopwatch), _name(Countdown)};
			const int arrX[size]={0x20, 0x8D, 0x11D, 0x1C4};
			char cursor[]="\032";
			for (int i(0); i<size; i++) {
				setXY(arrX[i], 1);
				if (objtC.checkPoint(objtC.takeChoice2())==(i+1)&&objtC.checkPoint(objtC.takeSelection())!=true) {
					setColorPIX(WHITE);
					printRGBtext(arrX[i], 0x2A, cursor, getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
					printRGBtext(arrX[i]+15, 0x2A, name[i], getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
				}
				else {
					setColorPIX(DARK_WHITE);
					if (!objtC.checkPoint(objtC.takeSelection())) {
						printRGBtext(arrX[i], 0x2A, cursor, NULL, NULL, NULL, true);
						printRGBtext(arrX[i]+15, 0x2A, name[i], getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
					}
					else if (objtC.checkPoint(objtC.takeChoice2())==(i+1)) {
						printRGBtext(arrX[i], 0x2A, cursor, getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
						printRGBtext(arrX[i]+15, 0x2A, name[i], getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
					}
					else {
						printRGBtext(arrX[i], 0x2A, cursor, NULL, NULL, NULL, true);
						printRGBtext(arrX[i]+15, 0x2A, name[i], getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
					}
				}
			}
			delete ptr;
			return;
		}
			if (text=="start") {
				ptr=new space;
				ptr->x1=0x87; ptr->y1=0xEC; ptr->x2=0xCD; ptr->y2=0xFF;
			} else
			if (text=="pause") {
				ptr=new space;
				ptr->x1=0xEB; ptr->y1=0xEC; ptr->x2=0x13E; ptr->y2=0x105;
			} else
			if (text=="stop") {
				ptr=new space;
				ptr->x1=0x15E; ptr->y1=0xEC; ptr->x2=0x194; ptr->y2=0x105;
			} else
			if (text=="reset") {
				ptr=new space;
				ptr->x1=0x1B9; ptr->y1=0xEC; ptr->x2=0x1FC; ptr->y2=0xFF;
			} else
				ptr=new space;

			cleaning_space(ptr->x1, ptr->y1, ptr->x2, ptr->y2);
			printRGBtext(x, y, text, getColorPIX('R'), getColorPIX('G'), getColorPIX('B'), true);
			setColorPIX(DARK_WHITE);
			delete ptr;
	}
	else if (objtC.getMODE()==SECOND) {
		objtD.drawTitle();
		objtD.drawTitleButton();
	}
	return;
}

void Mytimer::timerDisplay::readData()
{
	char *str = new char[3];
	char *time_val, *time_str="smh";
	int i(0), timeinfo;
	int stopwatch_arr[3];

	if (objtC.checkPoint(objtC.takeChoice2())!=FIRST) {
		*(stopwatch_arr+0)=objtC.getTIMEs(objtC.getTIME());
		*(stopwatch_arr+1)=objtC.getTIMEm(objtC.getTIME());
		*(stopwatch_arr+2)=objtC.getTIMEh(objtC.getTIME());
	}

	while (i++<3) {
		time_val=&time_str[i-1];
		if ((objtC.checkPoint(objtC.takeChoice2())==SECOND)||
			(objtC.checkPoint(objtC.takeChoice2())==THIRD)||
			(objtC.checkPoint(objtC.takeChoice2())==FOURTH))
			timeinfo=stopwatch_arr[i-1];
		else
			timeinfo=objtC.getTIME_real(*time_val);//Choice2==1
		itoa(timeinfo, str, 10);
		if (timeinfo<10) {
			*(str+1)=*str;
			*str='0';
		}
		++str; objtC.checkPoint(objtC.takeNumber())=static_cast<int>(*str)-0x30; objtC.Push(objtC.checkPoint(objtC.takeNumber()));
		--str; objtC.checkPoint(objtC.takeNumber())=static_cast<int>(*str)-0x30; objtC.Push(objtC.checkPoint(objtC.takeNumber()));
	}
	delete [] str;
	return;
}

void Mytimer::timerDisplay::printData()
{
	WORD OldColor;
	saveColor(OldColor);
	bool coeff_f, _(true);
	int coeff(NULL), X(0x14), value;
	int radix=10;
	char buf[2];
	char *mask;
	int i(-1);
	do {
		if (!(i<0)) {
			try {
				value=objtC.Pop();
				mask=itoa(value, buf, radix);
				(coeff++%2)?coeff_f=true:coeff_f=false;
				X-=coeff_f*2;
				if ((objtC.checkPoint(objtC.takeChoice2())==SECOND&&objtC.emptyACf==false)||
					(objtC.checkPoint(objtC.takeChoice2())==FOURTH&&objtC.emptyCf==false))
				{
						setColorPIX(DARK_BLUE);
						objtD.drawDIGIT('-', X*8, 0x8*9, true);
						setColorPIX(CYAN);
						objtD.drawDIGIT('-', X*8, 0x8*9, false);
				}
				else
					(value>=0&&value<=9)?throw value:NULL;
			}
			catch (int) {
				setColorPIX(DARK_BLUE);
				objtD.drawDIGIT(*mask, X*8, 0x8*9, NULL);
				setColorPIX(CYAN);
				objtD.drawDIGIT(value, X*8, 0x8*9, NULL);
			}
			X+=_<<3;
		}
	} while (++i<t::size);

	if ((objtC.checkPoint(objtC.takeChoice2())==SECOND&&objtC.emptyACf==false)||
		(objtC.checkPoint(objtC.takeChoice2())==FOURTH&&objtC.emptyCf==false))
		setColorPIX(DARK_BLUE);

	objtD.drawDIGIT(':', 0xFA-1, 0x50, NULL);
	objtD.drawDIGIT(':', 0x16A-1, 0x50, NULL);

	if (!objtC.updateFLG) {
		loadColor(OldColor);
		return;
	}

	const int size(4);
	struct pos {
		int x,y,tx,ty;
	};
	pos pstart	= {0xA6,  0xA7, 0x91,  0xf5};
	pos ppause	= {0x104, 0xA7, 0xdc,  0xf5};
	pos pstop	= {0x163, 0xA7, 0x154, 0xf5};
	pos preset	= {0x1C7, 0xA7, 0x1b3, 0xf5};
	
	struct button {
		btn bbtn;
		pos ppos;
	} btnARR[size];
	
	btnARR[0].bbtn=START; btnARR[0].ppos=pstart;
	btnARR[1].bbtn=PAUSE; btnARR[1].ppos=ppause;
	btnARR[2].bbtn=STOP;  btnARR[2].ppos=pstop;
	btnARR[3].bbtn=RESET; btnARR[3].ppos=preset;
	
	const char *arr_keys[size];
	int index(0);
	map<const char*, newcolors> BTN;
		BTN.insert(make_pair("b1", newGREEN));	//START
		BTN.insert(make_pair("b2", newYELLOW));	//PAUSE
		BTN.insert(make_pair("b3", newRED));	//STOP
		BTN.insert(make_pair("b4", newCYAN));	//RESET
	map<const char*, newcolors>::iterator it=BTN.begin();
	while (it!=BTN.end()) {
		arr_keys[index++]=it->first;
		++it;
	}
	
	int number(objtC.checkPoint(objtC.takeChoice1()));
	while (index) {
		if (*(*(arr_keys+(--index))+1)==number+0x30)//"1"||"2"||"3"||"4" == values at the table ASCII codes (1,2,3,4 +0x30)
			setColorPIXnew(BTN[arr_keys[index]]);
	}
	if (!objtC.checkPoint(objtC.takeSelection()))
		setColorPIX(WHITE);
	switch(number)
	{
		case 1:
			objtD.drawSTARTcool(pstart.x, pstart.y, NULL);
			objtD.drawTEXT("start", 135, 260);
			break;
		case 2:
			objtD.drawPAUSEcool(ppause.x, ppause.y, NULL);
			objtD.drawTEXT("pause", 235, 260);
			break;
		case 3:
			objtD.drawSTOPcool(pstop.x, pstop.y, NULL);
			objtD.drawTEXT("stop", 350, 260);
			break;
		case 4:
			objtD.drawRESETcool(preset.x, preset.y, NULL);
			objtD.drawTEXT("reset", 440, 260);
			break;
		default: break;
	}
	
	setColorPIX(DARK_WHITE);
	for (int i(1); i<=size; i++) {
		if (objtC.checkPoint(objtC.takeChoice1())==i) 
		{
		}
		else
			drawBUTTON(btnARR[i-1].bbtn, btnARR[i-1].ppos.x, btnARR[i-1].ppos.y);
	}

	objtC.updateFLG=false;
	objtD.drawTEXT(NULL, NULL, NULL);
	loadColor(OldColor);
	return;
}

void Mytimer::timerDisplay::printData(timerDisplay &obj)
{
	WORD OldColor;
	saveColor(OldColor);
	bool coeff_f;
	int coeff(NULL);
	int X(0x12), value;
	objtD.drawDIGIT(obj, ':', 0x20, 0x6, "COLON");
	objtD.drawDIGIT(obj, ':', 0x2f, 0x6, "COLON");
	int i(-1);
	for (bool _(true);;X+=_<<3) {
		if (t::size<=++i)
			break;
		value=objtC.Pop();
		(coeff++%2)?coeff_f=true:coeff_f=false;
		X-=coeff_f;
		if (objtC.checkPoint(objtC.takeChoice2())==SECOND&&objtC.emptyACf==false)
			objtD.drawDIGIT(obj, '-', X, 0x6, "DASH"); else
		if (objtC.checkPoint(objtC.takeChoice2())==FOURTH&&objtC.emptyCf==false)
			objtD.drawDIGIT(obj, '-', X, 0x6, "DASH"); else
		{
			int j(-1);
			while (++j<10) {
				if (value==j) {
					objtD.drawDIGIT(obj, value, X, 0x6, "DIGIT");
					break;
				}
			}
		}
	}

	if (objtC.checkPoint(objtC.takeChoice1())==FIRST) {
		setColor(GREEN);
		objtD.drawBUTTON(obj, START, 0x14, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, START, 0x14, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==SECOND) {
		setColor(YELLOW);
		objtD.drawBUTTON(obj, PAUSE, 0x1f, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, PAUSE, 0x1f, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==THIRD) {
		setColor(RED);
		objtD.drawBUTTON(obj, STOP, 0x2c, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, STOP, 0x2c, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==FOURTH) {
		setColor(CYAN);
		objtD.drawBUTTON(obj, RESET, 0x38, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, RESET, 0x38, 0xe);
	}
	objtC.updateFLG=false;
	objtD.drawTEXT(NULL, NULL, NULL);
	loadColor(OldColor);
	return;
}

void Mytimer::timerDisplay::input_consoleData()
{
	//system("cls");
	const int size=6;
	int count=size;
	static int arr[size];
	static int index=NULL;
	static bool flag=false;

	bool keyEnter=(objtC.checkPoint(objtC.takeKeyNumber())==key_enter);

	if ((objtC.isActiv(2)&&objtC.A_alarm_clock.ACTIV==true)||objtC.isActiv(4)&&objtC.A_countdown.ACTIV==true) {
		for (int i(0); i<size; ++i)
			(flag==true)?q_objtC.Enqueue(arr[i]):q_objtC.Enqueue(-2);
		(flag)?flag=NO:flag=YES;
		index++;
		if (index>2) {
			if (objtC.isActiv(SECOND)) {
				arr[size-2]=arr[size-1]=0;
				objtC.setClock(!NULL);
				objtC.checkPoint(objtC.takeChoice2())=FIRST;
				objtC.move_in_time(arr, objtC.getTIME("TA"));//move in time
				if (objtC.control_inputting_time(objtC.getTIME("TA")))
					objtC.move_out_time(arr, objtC.getTIME("TA"));//move out time
				for (int i(0); i<size; ++i)
					q_objtC.Dequeue();
				for (int i(0); i<size; ++i)
					q_objtC.Enqueue(arr[i]);
			}
			else if (objtC.isActiv(FOURTH)) {
				objtC.setCountdown(!NULL);
				objtC.checkPoint(objtC.takeChoice2())=FOURTH;
				objtC.move_in_time(arr, objtC.getTIME("TC"));//move in time
				if (objtC.control_inputting_time(objtC.getTIME("TC"))) {
					objtC.move_out_time(arr, objtC.getTIME("TC"));//move out time
					for (int i(0); i<size; ++i)
						q_objtC.Dequeue();
					for (int i(0); i<size; ++i)
						q_objtC.Enqueue(arr[i]);
				}
				objtC.getTIME("TD")=objtC.getTIME("TC");//make a copy
				objtC.Inputoff(true);
			}
			index=0;
			objtC.ACTIV->ACTIV=NO;
			objtC.ACTIV=NULL;
			objtC.updateFLG=true;
		}
		objtC.checkKEY("null");
		return;
	}
	if (!flag) {
		if (objtC.getAlarm_clock())
			objtC.ACTIV=&objtC.A_alarm_clock;
		else if (objtC.getCountdown())
			objtC.ACTIV=&objtC.A_countdown;
		objtC.checkPoint(objtC.takeNumber())=-1;
		int *ptr=&*arr;
		int i(size);
		ptr+=size-1;
		while (i--) {
			*ptr=objtC.checkPoint(objtC.takeNumber());
			ptr--;
		}
		flag=true;
	}
	if (objtC.isPressKEY()==key_back)
		(index>0&&*(arr+size-1)<0)?*(arr+--index)=objtC.checkPoint(objtC.takeNumber()):*(arr+index)=objtC.checkPoint(objtC.takeNumber());
	if (objtC.isPressKEY()==key_esc) {
		if (objtC.checkPoint(objtC.takeChoice2())==SECOND)
			objtC.emptyACf=false;
		else
		if (objtC.checkPoint(objtC.takeChoice2())==FOURTH)
			objtC.emptyCf=false;

		for (int i(0); i<size; ++i)
			q_objtC.Enqueue(-1);
		flag=false;
		objtC.setClock(!NULL);
		objtC.checkPoint(objtC.takeChoice2())==FOURTH?objtC.setCheck("up"):NULL;
		index=0;
		objtC.ACTIV=NULL;
		objtC.checkKEY("null");
		return;
	}
	if (objtC.checkPoint(objtC.takeNumber())!=-1&&!keyEnter) {
		*(arr+index)=objtC.checkPoint(objtC.takeNumber());
		objtC.checkPoint(objtC.takeNumber())=-1;
	}
	else if (!objtC.checkPoint(objtC.takeNumber())&&*(arr+size-1)<0)
		*(arr+index)=objtC.checkPoint(objtC.takeNumber());

	int ind_temp=index+1;
	while (--count-index) {
		*(arr+ind_temp)=objtC.checkPoint(objtC.takeNumber());
		ind_temp++;
	}
	for (int i(0); i<size; ++i)
		q_objtC.Enqueue(arr[i]);

	if (index>0)
		(objtC.checkPoint(objtC.takeChoice2())==SECOND)?objtC.emptyACf=true:objtC.emptyCf=true;
	else {
		(objtC.checkPoint(objtC.takeChoice2())==FOURTH)?objtC.emptyCf=false:objtC.emptyACf=false;
		if (objtC.isPressKEY()==key_enter) {
			for (int i(0); i<size; ++i)
				q_objtC.Enqueue(-1);
			flag=false;
			objtC.setClock(!NULL);
			objtC.setCheck("up");
			index=0;
			objtC.ACTIV=NULL;
			objtC.checkPoint(objtC.takeKeyNumber())=key_esc;
			objtC.checkKEY("null");
			return;
		}
	}
	index=count;
	while (true) {
		if (q_objtC.is_Queue_element(index)==3) {
			index++;
			if (index==size) {
				index--;
				break;
			}
		}
		if (q_objtC.is_Queue_element(index)==2) {
			*(arr+index)=-1;
			q_objtC.set_Queue_element(index, -1);
			break;
		}
		if (q_objtC.is_Queue_element(index)==1) {
			*(arr+index)=-2;
			q_objtC.set_Queue_element(index, -2);
			break;
		}
	}
	if (objtC.isPressKEY()==key_enter) {
		(objtC.getAlarm_clock())?objtC.deactivation(1), objtC.activation(2), objtC.deactivation(3), objtC.deactivation(4):
			(objtC.getCountdown())?objtC.deactivation(1), objtC.deactivation(2), objtC.deactivation(3), objtC.activation(4):
				NULL;
		index=0;
		objtC.ACTIV->ACTIV=YES;
	}
	objtC.checkKEY("null");
	return;
}

void Mytimer::timerDisplay::output_consoleData()
{
	WORD OldColor;
	saveColor(OldColor);
	bool coeff_f, _(true);
	int coeff(NULL), X(0x14), value;
	int i(-1);

	for (int i=0; i<t::size; i++) {
		try {
			value=q_objtC.Dequeue();
			(coeff++%2)?coeff_f=true:coeff_f=false;
			X-=coeff_f*2;
			(value>=0&&value<=9)?throw value:throw static_cast<char>(value);
		}

		catch (int value) {
			char mask(static_cast<char>(value)+0x30);
			setColorPIX(DARK_BLUE);
			objtD.drawDIGIT(mask, X*8, 0x8*9, NULL);
			setColorPIX(CYAN);
			objtD.drawDIGIT(value, X*8, 0x8*9, NULL);
		}

		catch (char value) {
			setColorPIX(DARK_BLUE);
			if (value==-1) {
				objtD.drawDIGIT('_', X*8, 0x8*9, true);
				setColorPIX(CYAN);
				objtD.drawDIGIT('_', X*8, 0x8*9, false);
			}
			else {
				objtD.drawDIGIT(' ', X*8, 0x8*9, true);
				setColorPIX(CYAN);
				objtD.drawDIGIT(' ', X*8, 0x8*9, false);
			}
		}
		X+=_<<3;
	}

	objtD.drawDIGIT(':', 0xFA-1, 0x50, NULL);
	objtD.drawDIGIT(':', 0x16A-1, 0x50, NULL);

	if (!objtC.updateFLG) {
		loadColor(OldColor);
		return;
	}

	const int size(4);
	struct pos {
		int x,y,tx,ty;
	};
	pos pstart; pstart.x=0xA6; pstart.y=0xA7; pstart.tx=0x91; pstart.ty=0xf5;
	pos ppause; ppause.x=0x104; ppause.y=0xA7; ppause.tx=0xdc; ppause.ty=0xf5;
	pos pstop; pstop.x=0x163; pstop.y=0xA7; pstop.tx=0x154; pstop.ty=0xf5;
	pos preset; preset.x=0x1C7; preset.y=0xA7; preset.tx=0x1b3; preset.ty=0xf5;

	struct button {
		btn bbtn;
		pos ppos;
		newcolors nnewcolors;
	} btnARR[size];
	
	int index(0);
	btnARR[index].bbtn=START; btnARR[index].ppos=pstart; btnARR[index].nnewcolors=newGREEN; ++index;
	btnARR[index].bbtn=PAUSE; btnARR[index].ppos=ppause; btnARR[index].nnewcolors=newYELLOW; ++index;
	btnARR[index].bbtn=STOP;  btnARR[index].ppos=pstop; btnARR[index].nnewcolors=newRED; ++index;
	btnARR[index].bbtn=RESET; btnARR[index].ppos=preset; btnARR[index].nnewcolors=newCYAN; ++index;
	
	int number(objtC.checkPoint(objtC.takeChoice1()));
	while (index) {
		if (index--==number)
			setColorPIXnew(btnARR[index].nnewcolors);
	}
	
	if (!objtC.checkPoint(objtC.takeSelection()))
		setColorPIX(WHITE);
	
	switch(number)
	{
		case 1:
			objtD.drawSTARTcool(pstart.x, pstart.y, NULL);
			objtD.drawTEXT("start", 135, 260);
			break;
		case 2:
			objtD.drawPAUSEcool(ppause.x, ppause.y, NULL);
			objtD.drawTEXT("pause", 235, 260);
			break;
		case 3:
			objtD.drawSTOPcool(pstop.x, pstop.y, NULL);
			objtD.drawTEXT("stop", 350, 260);
			break;
		case 4:
			objtD.drawRESETcool(preset.x, preset.y, NULL);
			objtD.drawTEXT("reset", 440, 260);
			break;
		default: break;
	}
	
	setColorPIX(DARK_WHITE);
	for (int i(1); i<=size; i++) {
		if (objtC.checkPoint(objtC.takeChoice1())!=i)
			drawBUTTON(btnARR[i-1].bbtn, btnARR[i-1].ppos.x, btnARR[i-1].ppos.y);
	}
	
	objtC.updateFLG=false;
	objtD.drawTEXT(NULL, NULL, NULL);
	loadColor(OldColor);
	return;
}

void Mytimer::timerDisplay::output_consoleData(timerDisplay &obj)
{
	WORD OldColor;
	saveColor(OldColor);
	bool coeff_f, _(true);
	int coeff(NULL);
	int X(0x12), value(-1);
	objtD.drawDIGIT(obj, ':', 0x20, 0x6, "COLON");
	objtD.drawDIGIT(obj, ':', 0x2f, 0x6, "COLON");
	int i(-1);
	while (++i<t::size) {
		value=q_objtC.Dequeue();
		(coeff++%2)?coeff_f=true:coeff_f=false;
		X-=coeff_f;
		switch (value)
		{
			case 0: objtD.drawDIGIT(obj, 0, X, 0x6, "DIGIT"); goto exit;
			case 1: objtD.drawDIGIT(obj, 1, X, 0x6, "DIGIT"); goto exit;
			case 2: objtD.drawDIGIT(obj, 2, X, 0x6, "DIGIT"); goto exit;
			case 3: objtD.drawDIGIT(obj, 3, X, 0x6, "DIGIT"); goto exit;
			case 4: objtD.drawDIGIT(obj, 4, X, 0x6, "DIGIT"); goto exit;
			case 5: objtD.drawDIGIT(obj, 5, X, 0x6, "DIGIT"); goto exit;
			case 6: objtD.drawDIGIT(obj, 6, X, 0x6, "DIGIT"); goto exit;
			case 7: objtD.drawDIGIT(obj, 7, X, 0x6, "DIGIT"); goto exit;
			case 8: objtD.drawDIGIT(obj, 8, X, 0x6, "DIGIT"); goto exit;
			case 9: objtD.drawDIGIT(obj, 9, X, 0x6, "DIGIT"); goto exit;
			default: (value==-1)?
					objtD.drawDIGIT(obj, '_', X, 0x6, "UNDERLINE"):
					objtD.drawDIGIT(obj, ' ', X, 0x6, "EMPTYCELL"); goto exit;
		}
		exit:
		;
		X+=_<<3;
	}

	if (objtC.checkPoint(objtC.takeChoice1())==FIRST) {
		setColor(GREEN);
		objtD.drawBUTTON(obj, START, 0x14, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, START, 0x14, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==SECOND) {
		setColor(YELLOW);
		objtD.drawBUTTON(obj, PAUSE, 0x1f, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, PAUSE, 0x1f, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==THIRD) {
		setColor(RED);
		objtD.drawBUTTON(obj, STOP, 0x2c, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, STOP, 0x2c, 0xe);
	}
	if (objtC.checkPoint(objtC.takeChoice1())==FOURTH) {
		setColor(CYAN);
		objtD.drawBUTTON(obj, RESET, 0x38, 0xe);
	} else {
		setColor(DARK_WHITE);
		objtD.drawBUTTON(obj, RESET, 0x38, 0xe);
	}
	objtC.updateFLG=false;
	objtD.drawTEXT(NULL, NULL, NULL);
	loadColor(OldColor);
	return;
}

void _updFIRST(const bool flag)
{
	//FIRST as default
	system("cls");
	if (objtC.getAlarm_clock()||(objtC.getCountdown()&&!objtC.inputoff)) {
		objtD.input_consoleData();
		objtD.output_consoleData();
	} else {
		objtD.readData();
		objtD.printData();
	}
	if (flag)
		objtC.time_management();

	setXY(NULL, NULL);

//	debug information:
//	setXY(0, 15);
//	cout<<"choice1 - "<<objtC.checkPoint(objtC.takeChoice1())<<endl;
//	cout<<"choice2 - "<<objtC.checkPoint(objtC.takeChoice2())<<endl;
//	cout<<"selection - "<<objtC.checkPoint(objtC.takeSelection())<<endl;
	return;
}

void _updSECOND(const bool flag)
{
	Mytimer::timerDisplay objtD(1);//restart
	if (objtC.getAlarm_clock()||(objtC.getCountdown()&&!objtC.inputoff)) {
		objtD.input_consoleData();
		objtD.output_consoleData(objtD);
	} else {
		objtD.readData();
		objtD.printData(objtD);
	}
	if (flag)
		objtC.time_management();

	setXY(NULL, NULL);

//	debug information:
//	setXY(0, 15);
//	cout<<"choice1 - "<<objtC.checkPoint(objtC.takeChoice1())<<endl;
//	cout<<"choice2 - "<<objtC.checkPoint(objtC.takeChoice2())<<endl;
//	cout<<"selection - "<<objtC.checkPoint(objtC.takeSelection())<<endl;
	return;
}

int main(int argc, char *argv[])
{
	HANDLE hConsole;
	HWND hWnd;
	HMENU hm;
	RECT rect, pre_rect={0, 0, 0};
	locale lcl("Russian");
	locale::global(lcl);
	system("mode con cols=80 lines=25");
	system("title Timer");
	if((hWnd=GetConsoleWindow())==NULL)
		return EXIT_SUCCESS;
	hm=GetSystemMenu(hWnd, false);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND|MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND|MF_REMOVE);
	DrawMenuBar(hWnd);

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible=false;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);

	for (;;)
	{
		while (!_kbhit()) {
			(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(YES):_updSECOND(YES);
			GetWindowRect(hWnd, &rect);
			if (pre_rect.top!=rect.top||
				pre_rect.left!=rect.left||
				pre_rect.bottom!=rect.bottom||
				pre_rect.right!=rect.right)
			{
				pre_rect=rect;
				objtC.updateFLG=true;
			}
			if (
				objtC.emptyACf&&!objtC.getAlarm_clock()&&
				objtC.getTIME_real('h')==(int)objtC.getTIME("TA").hours&&
				objtC.getTIME_real('m')==(int)objtC.getTIME("TA").minutes
				)
				printf("\a\a");
			Sleep(SLEEP);
		}
		if (objtC.getAlarm_clock()||(objtC.getCountdown()&&!objtC.inputoff)) {
			objtC.checkPoint(objtC.takeKeyNumber())=_getch();
			if (objtC.checkPoint(objtC.takeKeyNumber())==key_enter) {
				objtC.updateFLG=true;
				objtC.checkPoint(objtC.takeNumber())=0;
				objtC.checkKEY("enter");
			} else
			if (objtC.checkPoint(objtC.takeKeyNumber())==key_back) {
				objtC.updateFLG=true;
				objtC.checkPoint(objtC.takeNumber())=-1;
				objtC.checkKEY("back");
			} else
			if (objtC.checkPoint(objtC.takeKeyNumber())==key_esc) {
				objtC.updateFLG=true;
				objtC.checkKEY("esc");
			} else
			{
				objtC.checkPoint(objtC.takeKeyNumber())-=0x30;
				if (objtC.checkPoint(objtC.takeKeyNumber())>=0&&objtC.checkPoint(objtC.takeKeyNumber())<=9)
					objtC.checkPoint(objtC.takeNumber())=objtC.checkPoint(objtC.takeKeyNumber());
			}
			(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO);
		} else {
			switch (_getch())
			{
				case key_left:
					objtC.setCheck("left");
					//Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO); break;
				case key_right:
					objtC.setCheck("right");
					//Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO); break;
				case key_up:
					objtC.setCheck("up");
					//Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO); break;
				case key_down:
					objtC.setCheck("down");
					//Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO); break;
				case key_enter:
					objtC.setInputData();
					//Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					(objtC.getMODE()==Mytimer::FIRST)?_updFIRST(NO):_updSECOND(NO); break;
				case key_esc:
					//exit(0);
					Mytimer::cleaning_screen();
					objtC.updateFLG=true;
					if (objtC.getMODE()==Mytimer::FIRST) {
						objtC.setMODE(Mytimer::SECOND);
						_updSECOND(NO);
					} else {
						objtC.setMODE(Mytimer::FIRST);
						_updFIRST(NO);
					}
					break;
				default: break;
			}
		}
	}

	return EXIT_SUCCESS;
}
