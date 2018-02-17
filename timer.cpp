#include <time.h>
#include "timer.h"
#include "graphics.h"
#include "title.h"

namespace Mytimer
{
//length line - 25 pixels
//width line - 5 pixels
	position l1={0x15,	0x09,	0x2C,	0x0E};
	position l2={0x2F,	0x10,	0x34,	0x28};
	position l3={0x2F,	0x31,	0x34,	0x49};
	position l4={0x15,	0x4B,	0x2C,	0x50};
	position l5={0x0D,	0x31,	0x12,	0x49};
	position l6={0x0D,	0x10,	0x12,	0x28};
	position l7={0x15,	0x2A,	0x2C,	0x2F};

//CLASS "timerDisplay"
	//constructors
	timerDisplay::timerDisplay(void):
		digit_0("1111110"),
		digit_1("0110000"),
		digit_2("1101101"),
		digit_3("1111001"),
		digit_4("0110011"),
		digit_5("1011011"),
		digit_6("1011111"),
		digit_7("1110000"),
		digit_8("1111111"),
		digit_9("1111011")
	{
		//printf("\a");
		initgraph();
	}

	timerDisplay::timerDisplay(bool setting=false)
	{
		if (setting) {
			digit_0="0000000010101001000100100010010001001010100000000";
			digit_1="0000000000001000010100000010000001000000100000000";
			digit_2="0000000010101000000100101010010000001010100000000";
			digit_3="0000000010101000000100101010000001001010100000000";
			digit_4="0000000010001001000100101010000001000000100000000";
			digit_5="0000000010101001000000101010000001001010100000000";
			digit_6="0000000010101001000000101010010001001010100000000";
			digit_7="0000000010101000000100000010000001000000100000000";
			digit_8="0000000010101001000100101010010001001010100000000";
			digit_9="0000000010101001000100101010000001001010100000000";
		}
	}

	timerDisplay::timerTitle::timerTitle(void):indexTitle(0)
	{
		Title1.posX=0x0C; Title1.number=FIRST;  Title1.name=TitleClock;
		Title2.posX=0x16; Title2.number=SECOND; Title2.name=TitleAlarm_clock;
		Title3.posX=0x24; Title3.number=THIRD;  Title3.name=TitleStopwatch;
		Title4.posX=0x32; Title4.number=FOURTH; Title4.name=TitleCountdown;

		const size_t size(4);
		ARRAY=new Title[size];
		*ARRAY=Title1; ARRAY++;
		*ARRAY=Title2; ARRAY++;
		*ARRAY=Title3; ARRAY++;
		*ARRAY=Title4; ARRAY++;
		ARRAY=ARRAY-size;
	}

	timerDisplay::timerTitleButton::timerTitleButton(void)
	{
	}

	std::ostream& operator<<(std::ostream& os, const timerDisplay::timerTitleButton& ott)
	{
		return os<<ott.title;
	}

	//Recursive function used to launch "drawTitle(ARRAY, indexTitle)" a four times, analogue loop in this case. Call in "drawTitle()".
	timerDisplay::timerTitle& timerDisplay::timerTitle::operator=(timerTitle& objTitle)
	{
		objTitle.indexTitle++;
		if (objTitle.indexTitle<=4) {
			drawTitle(ARRAY, indexTitle);
			*this=objTitle;
		} else {
			objTitle.indexTitle=0;
			return *this;
		}
	}

	//Variable "*title" gets value of the argument. Call in "drawTitleButton()".
	timerDisplay::timerTitleButton& timerDisplay::timerTitleButton::operator=(const char *title)
	{
		timerTitleButton objTitleButton;
		objTitleButton.title=title;
		*this=objTitleButton;
		return *this;
	}

	//Method of printing texts: часы, будильник, секундомер, обратный отсчет.
	void timerDisplay::drawTitle()
	{
		timerTitle objTitle;
		objTitle=objTitle;
		return;
	}

	//Method of printing texts: запуск, приостановка, остановка, сбросить.
	void timerDisplay::drawTitleButton()
	{
		timerTitleButton objTitleButtonSTART, objTitleButtonPAUSE, objTitleButtonSTOP, objTitleButtonRESET;
		objTitleButtonSTART=TitleStart;
		objTitleButtonSTART.drawTitleButton(FIRST, 0x12, 10);
		objTitleButtonPAUSE=TitlePause;
		objTitleButtonPAUSE.drawTitleButton(SECOND, 0x1b, 14);
		objTitleButtonSTOP=TitleStop;
		objTitleButtonSTOP.drawTitleButton(THIRD, 0x2a, 12);
		objTitleButtonRESET=TitleReset;
		objTitleButtonRESET.drawTitleButton(FOURTH, 0x36, 11);
		return;
	}

	//Destructors.
	timerDisplay::timerTitle::~timerTitle(void)
	{
		delete [] ARRAY;
	}

	timerDisplay::timerTitleButton::~timerTitleButton(void)
	{
	}

	const char* timerDisplay::takeTitleClock() {
		const char *Title(TitleClock);
		return Title;
	}

	const char* timerDisplay::takeTitleAlarm_clock() {
		const char *Title(TitleAlarm_clock);
		return Title;
	}

	const char* timerDisplay::takeTitleStopwatch() {
		const char *Title(TitleStopwatch);
		return Title;
	}

	const char* timerDisplay::takeTitleCountdown() {
		const char *Title(TitleCountdown);
		return Title;
	}

	const char* timerDisplay::takeTitleStart() {
		const char *Title(TitleStart);
		return Title;
	}

	const char* timerDisplay::takeTitlePause() {
		const char *Title(TitlePause);
		return Title;
	}

	const char* timerDisplay::takeTitleStop() {
		const char *Title(TitleStop);
		return Title;
	}

	const char* timerDisplay::takeTitleReset() {
		const char *Title(TitleReset);
		return Title;
	}

	//methods print for digits (mode FIRST)
	void timerDisplay::triangle_up(int tx, int ty)
	{
		int n,m,i,j;
		bool const f(true);
		for((n=(int)f)++, ++(m=n), j=(int)!f; !(n<(int)!f)&&m<t::size; n-=(int)f, m+=(int)f) {
			for(i=n; i<m+(int)f; i+=(int)f)
				if (i<=m&&i>=n)
					putpixel(tx+i, ty+j);
			j+=(int)f;
		}
		return;
	}
	void timerDisplay::triangle_down(int tx, int ty)
	{
		int n,m,i,j;
		bool const f(true);
		for(n=(int)!f, m=t::size-(int)f, j=(int)!f; !(n>m); n+=(int)f, m-=(int)f) {
			for(i=n; i<m+(int)f; i+=(int)f)
				if (i<=m&&i>=n)
					putpixel(tx+i, ty+j);
			j+=(int)f;
		}
		return;
	}
	void timerDisplay::triangle_right(int tx, int ty)
	{
		int n,m,i,j;
		bool const f(true);
		for(n=(int)!f, m=t::size-(int)f, j=(int)!f; (n<t::size/2)||(m>=(int)!f); n+=(int)f, m-=(int)f) {
			if (n<t::size/2) {
				for(i=(int)!f; i<=n; i+=(int)f)
					putpixel(tx+i, ty+j);
			}
			else 
			if (m<t::size/2) {
				for(i=(int)!f; i<=m; i+=(int)f)
					putpixel(tx+i, ty+j);
			}
			j+=(int)f;
		}
		return;
	}
	void timerDisplay::triangle_left(int tx, int ty)
	{
		int n,m,i,j;
		bool const f(true);
		for ((n=(int)f)++, m=-(t::size/2), j=(int)!f; (n>=(int)!f)||(m<t::size/2); n-=(int)f, m+=(int)f) {
			if (n>=(int)!f) {
				for(i=n; i<t::size/2; i+=(int)f)
					putpixel(tx+i, ty+j);
			}
			else
			if (m>=(int)!f) {
				for(i=m; i<t::size/2; i+=(int)f)
					putpixel(tx+i, ty+j);
			}
			j+=(int)f;
		}
		return;
	}
	void timerDisplay::_rectangle(int x1, int y1, int x2, int y2)
	{
		bool const f(true);
		for (int i(y1-(int)f); i<=y2-(int)f; i+=1)
			for (int j(x1-(int)f); j<=x2-(int)f; j+=1)
				putpixel(j, i);
		return;
	}

	void timerDisplay::line1(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l1.x1, l1.y1, l1.x2, l1.y2);
			_rectangle(l1.x1, l1.y1, l1.x2, l1.y2);
			triangle_left(l1.x1-4, l1.y1-1);
			triangle_right(l1.x2, l1.y1-1);
		}
		return;
	}
	void timerDisplay::line2(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l2.x1, l2.y1, l2.x2, l2.y2);
			_rectangle(l2.x1, l2.y1, l2.x2, l2.y2);
			triangle_up(l2.x1-1, l2.y1-4);
			triangle_down(l2.x1-1, l2.y2);
		}
		return;
	}
	void timerDisplay::line3(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l3.x1, l3.y1, l3.x2, l3.y2);
			_rectangle(l3.x1, l3.y1, l3.x2, l3.y2);
			triangle_up(l3.x1-1, l3.y1-4);
			triangle_down(l3.x1-1, l3.y2);
		}
		return;
	}
	void timerDisplay::line4(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l4.x1, l4.y1, l4.x2, l4.y2);
			_rectangle(l4.x1, l4.y1, l4.x2, l4.y2);
			triangle_left(l4.x1-4, l4.y1-1);
			triangle_right(l4.x2, l4.y1-1);
		}
		return;
	}
	void timerDisplay::line5(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l5.x1, l5.y1, l5.x2, l5.y2);
			_rectangle(l5.x1, l5.y1, l5.x2, l5.y2);
			triangle_up(l5.x1-1, l5.y1-4);
			triangle_down(l5.x1-1, l5.y2);
		}
		return;
	}
	void timerDisplay::line6(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l6.x1, l6.y1, l6.x2, l6.y2);
			_rectangle(l6.x1, l6.y1, l6.x2, l6.y2);
			triangle_up(l6.x1-1, l6.y1-4);
			triangle_down(l6.x1-1, l6.y2);
		}
		return;
	}
	void timerDisplay::line7(bool isLineFlag) {
		if (isLineFlag) {
			//rectangle(l7.x1, l7.y1, l7.x2, l7.y2);
			_rectangle(l7.x1, l7.y1, l7.x2, l7.y2);
			triangle_left(l7.x1-4, l7.y1-1);
			triangle_right(l7.x2, l7.y1-1);
		}
		return;
	}

	void timerDisplay::colon(const int x, const int y)
	{
		int xX(x),yY(y);
		const int p(0x15);
		_rectangle(p+xX, p+yY, 2*p-0x10+xX, 2*p-0x10+yY);
		yY=yY+2*p-0x10;
		_rectangle(p+xX, p+yY, 2*p-0x10+xX, 2*p-0x10+yY);
		return;
	}

	position timerDisplay::overwritelines(int number, int x, int y)
	{
		position line, *rewrite;
		switch (number)
		{
			case 1: line=l1; rewrite=&l1; break;
			case 2: line=l2; rewrite=&l2; break;
			case 3: line=l3; rewrite=&l3; break;
			case 4: line=l4; rewrite=&l4; break;
			case 5: line=l5; rewrite=&l5; break;
			case 6: line=l6; rewrite=&l6; break;
			case 7: line=l7; rewrite=&l7; break;
			default: break;
		}
		rewrite->x1+=x;
		rewrite->y1+=y;
		rewrite->x2+=x;
		rewrite->y2+=y;
		return line;
	}

	void timerDisplay::overwritelinesback(position (&linemass)[numline])
	{
		l1=linemass[numline-7];
		l2=linemass[numline-6];
		l3=linemass[numline-5];
		l4=linemass[numline-4];
		l5=linemass[numline-3];
		l6=linemass[numline-2];
		l7=linemass[numline-1];
		return;
	}

	void timerDisplay::setColorPIX(ui color)
	{
		setcolor(color);
		if (color==8) {
			v.vRPIX=128;
			v.vGPIX=128;
			v.vBPIX=128;
		} else
		if (color==15) {
			v.vRPIX=255;
			v.vGPIX=255;
			v.vBPIX=255;
		} else
			return;
		return;
	}

	void timerDisplay::setColorPIXnew(ui color)
	{
		if (color==0) setcolorRGB(v.vRPIX=34, v.vGPIX=177, v.vBPIX=76); else
			if (color==1) setcolorRGB(v.vRPIX=255, v.vGPIX=242, v.vBPIX=0); else
				if (color==2) setcolorRGB(v.vRPIX=237, v.vGPIX=28, v.vBPIX=36); else
					if (color==3) setcolorRGB(v.vRPIX=153, v.vGPIX=217, v.vBPIX=234); else
						return;
		return;
	}

	ui timerDisplay::getColorPIX(char rgb)
	{
		if (rgb=='R')
			return v.vRPIX;
		if (rgb=='G')
			return v.vGPIX;
		if (rgb=='B')
			return v.vBPIX;

		return 0;
	}

	const char* timerDisplay::getDIGIT(ui digit)
	{
		switch (digit)
		{
			case 0:return (digit_0);
			case 1:return (digit_1);
			case 2:return (digit_2);
			case 3:return (digit_3);
			case 4:return (digit_4);
			case 5:return (digit_5);
			case 6:return (digit_6);
			case 7:return (digit_7);
			case 8:return (digit_8);
			case 9:return (digit_9);
		}
	}

	void timerDisplay::drawSTARTcool(int x, int y, const char* text=NULL)
	{
		if (text) {
			char* _text=const_cast<char*>(text);
			outtextxy(x, y, _text);
			return;
		}

		int indX(NULL), indY(NULL), counter(0);
		while (1) {
			if (!(indY<61))
				break;
			while (1) {
				putpixel(x+indX, y+indY);
				if (indX==counter)
					break;
				else
					++indX;
			}
			indY++<30?counter++:counter--;
			indX=0;
		}
		return;
	}
	
	void timerDisplay::drawPAUSEcool(int x, int y, const char* text=NULL)
	{
		if (text) {
			char* _text=const_cast<char*>(text);
			outtextxy(x, y, _text);
			return;
		}

		int indX(NULL), indY(NULL);
		while (1) {
			if (!(indY<61))
				break;
			while (1) {
				if (!(indX<24))
					break;
				if (indX<8||indX>=16)
					putpixel(x+indX, y+indY);
				++indX;
			}
			++indY;
			indX=0;
		}
		return;
	}
	
	void timerDisplay::drawSTOPcool(int x, int y, const char* text=NULL)
	{
		if (text) {
			char* _text=const_cast<char*>(text);
			outtextxy(x, y, _text);
			return;
		}

		int indX(NULL), indY(NULL);
		while (1) {
			if (!(indY<61))
				break;
			while (1) {
				if (!(indX<51))
					break;
				putpixel(x+indX, y+indY);
				++indX;
			}
			++indY;
			indX=0;
		}
		return;
	}
	
	void timerDisplay::drawRESETcool(int x, int y, const char* text=NULL)
	{
		if (text) {
			char* _text=const_cast<char*>(text);
			outtextxy(x, y, _text);
			return;
		}

		int indX(NULL),indY(NULL), counter(NULL);
		while (1) {
			if (!(indY<61))
				break;
			while (1) {
				if (!(indX<8))
					break;
				putpixel(x+indX, y+indY);
				++indX;
			}
			indX=0;
			while (1) {
				putpixel(x+indX+16, y+indY);
				if (indX==counter)
					break;
				else
					++indX;
			}
			indY++<30?counter++:counter--;
			indX=0;
		}
		return;
	}
	
	//destructor
	timerDisplay::~timerDisplay(void)
	{
	}

//CLASS "timerControl"

	//constructor
	timerControl::timerControl(void)
	{
		{
			const int size(4);
			int i(size);
			do {
				if (i==size)
					activ=new bool[size];
				else
				{
					*activ=false;
					activ++;
				}
			} while (i--);
			activ=activ-size;
		}
		{
			const int size(3);
			activkey=new bool[size];
			activkey[0]=false;//Enter
			activkey[1]=false;//BackSpace
			activkey[2]=false;//Esc
		}
		TM=TI=TD=setTIME_null();
		TIbuffer=setTIME(NULL);
		TDbuffer=setTIME(NULL);
		ACTIV=NULL;
		setClock(true);
		setMODE(FIRST);
		setCheck("default");
		emptyACf=false;
		emptyCf=false;
		updateFLG=true;
	}

	void timerControl::activation(A &choice, const btn button)
	{
		ACTIV=&choice;
		switch (button)
		{
			case START:
				ACTIV->A_start=YES;
				ACTIV->A_pause=NO;
				ACTIV->A_stop=NO;
				ACTIV->A_reset=NO;
				break;

			case PAUSE:
				ACTIV->A_start=NO;
				ACTIV->A_pause=YES;
				ACTIV->A_stop=NO;
				ACTIV->A_reset=NO;
				break;

			case STOP:
				ACTIV->A_start=NO;
				ACTIV->A_pause=NO;
				ACTIV->A_stop=YES;
				ACTIV->A_reset=NO;
				break;

			case RESET:
				ACTIV->A_start=NO;
				ACTIV->A_pause=NO;
				ACTIV->A_stop=NO;
				ACTIV->A_reset=YES;
				break;

			default: break;
		}
		ACTIV=NULL;
		return;
	}

	void timerControl::deactivation(A &choice)
	{
		ACTIV=&choice;
		ACTIV->A_start=NO;
		ACTIV->A_pause=NO;
		ACTIV->A_stop=NO;
		ACTIV->A_reset=NO;
		ACTIV=NULL;
		return;
	}

	void timerControl::activation(ui setting)
	{
		setting==1? *(activ+setting-1)=true:
		setting==2? *(activ+setting-1)=true:
		setting==3? *(activ+setting-1)=true:
		setting==4? *(activ+setting-1)=true:
		NULL;
		return;
	}

	void timerControl::deactivation(ui setting)
	{
		int i(0);
		restart:
		if (setting==++i)
			*(activ+i-1)=false;
		else
			if (setting>0&&setting<=4)
				goto restart;
		else
			return;
		return;
	}

	bool timerControl::isActiv(ui setting)
	{
		if (setting>0&&setting<=4) {
			if (*(activ+setting-1))
				return true;
			else
				return false;
		}
		return false;
	}

	void timerControl::checkKEY(char *setting)
	{
		setting=="null"?
			activkey[0]=0, activkey[1]=0, activkey[2]=0 :
		setting=="enter"?
			activkey[0]=1, activkey[1]=0, activkey[2]=0 :
		setting=="back"?
			activkey[0]=0, activkey[1]=1, activkey[2]=0 :
		setting=="esc"?
			activkey[0]=0, activkey[1]=0, activkey[2]=1 :
		NULL;
		return;
	}

	ui timerControl::isPressKEY()
	{
		const int size(3);
		int index(0), i(0);
		while (i<size) {
			if (activkey[i++]) {
				index=i;
				break;
			}
		}
		switch (index) {
			case 1:return (0xD);
			case 2:return (0x8);
			case 3:return (0x1B);
			default: return (0x0);
		}
		return NULL;
	}

	void timerControl::setClock(const bool setting)
	{
		clock_f=setting;
		if (setting) {
			setAlarm_clock(NULL);
			setStopwatch(NULL);
			setCountdown(NULL);
		}
		return;
	}

	bool timerControl::getClock()
	{
		return clock_f;
	}

	void timerControl::setAlarm_clock(const bool setting)
	{
		alarm_clock_f=setting;
		if (setting) {
			setClock(NULL);
			setStopwatch(NULL);
			setCountdown(NULL);
		}
		return;
	}

	bool timerControl::getAlarm_clock()
	{
		return alarm_clock_f;
	}

	void timerControl::setStopwatch(const bool setting)
	{
		stopwatch_f=setting;
		if (setting) {
			setClock(NULL);
			setAlarm_clock(NULL);
			setCountdown(NULL);
		}
		return;
	}

	bool timerControl::getStopwatch()
	{
		return stopwatch_f;
	}

	void timerControl::setCountdown(const bool setting)
	{
		countdown_f=setting;
		if (setting) {
			setClock(NULL);
			setAlarm_clock(NULL);
			setStopwatch(NULL);
		}
		return;
	}

	bool timerControl::getCountdown()
	{
		return countdown_f;
	}

	Time timerControl::setTIME(ui s)
	{
		Time t;
		t.hours=s/(t::t*t::t);
		t.minutes=s%(t::t*t::t)/t::t;
		t.seconds=s%(t::t*t::t)%t::t;
		return t;
	}

	Time timerControl::setTIME(ui h, ui m, ui s)
	{
		Time t;
		if (s>t::t) {m+=(s/t::t); s=s%t::t;}
		t.seconds=s;
		if (m>t::t) {h+=(m/t::t); m=m%t::t;}
		t.minutes=m;
		if (h>(t::t/2.5))
			t=setTIME_null();
		else
			t.hours=h;
		return t;
	}

	Time timerControl::setTIME_null()
	{
		Time t;
		t.hours=NULL;
		t.minutes=NULL;
		t.seconds=NULL;
		return t;
	}

	int timerControl::getTIME_real(char time_val)
	{
		time_t rawtime=time(NULL);
		struct tm* timeinfo;
		time (&rawtime);
		timeinfo=localtime(&rawtime);
		if (time_val=='h')
			return (timeinfo->tm_hour);
		else if (time_val=='m')
			return (timeinfo->tm_min);
		else if (time_val=='s')
			return (timeinfo->tm_sec);
		return EXIT_SUCCESS;
	}

	Time& timerControl::getTIME()
	{
		return TM;
	}

	Time& timerControl::getTIME(char *t)
	{
		char *tarr[5]={"TM", "TI", "TD", "TA", "TC"};
		int value;
		for (int i(0); i<5; i++) {
			if(tarr[i]==t) {
				value=i;
				break;
			}
		}
		switch (value)
		{
			case 0: return TM;
			case 1: return TI;
			case 2: return TD;
			case 3: return TA;
			case 4: return TC;
			default: break;
		}
		return TM;
	}

	void timerControl::counting_inc()
	{
		TI.seconds++;
		if (!(TI.seconds<t::t)) {
			TI.minutes++;
			if (!(TI.minutes<t::t)) {
				TI.hours++;
				if (!(TI.hours<t::t)) {
					TI.hours=0;
				}
				TI.minutes=0;
			}
			TI.seconds=0;
		}
		
		return;
	}

	void timerControl::counting_dec()
	{
		if (TD.hours==0&&TD.minutes==0&&TD.seconds==0)
			return;

		if (TD.seconds) {
			TD.seconds--;
			return;
		} else
			TD.seconds=t::t-1;

		if (TD.minutes) {
			TD.minutes--;
			return;
		} else
			TD.minutes=t::t-1;

		if (TD.hours) {
			TD.hours--;
			return;
		} else
			TD.hours=t::t-1;

		return;
	}

	void timerControl::time_management()
	{
		if (A_stopwatch.A_start) {
			counting_inc();
			if (checkPoint(takeChoice2())==THIRD) { TM=TI;
			}	
		} else
		if (A_stopwatch.A_pause) {
			counting_inc();
			if (checkPoint(takeChoice2())==THIRD) { TM=TIbuffer;
			}
		} else
		if (A_stopwatch.A_stop) {
			//counting_inc();
			if (checkPoint(takeChoice2())==THIRD) { TM=TIbuffer;
			}
		} else
		if (A_stopwatch.A_reset) {
			deactivation(A_stopwatch);
			TI=setTIME_null();
			if (checkPoint(takeChoice2())==THIRD) { TM=TI;
			}
		} else
		if (checkPoint(takeChoice2())==THIRD) { TM=TI;
		}

		if (A_countdown.A_start) {
			counting_dec();
			if (checkPoint(takeChoice2())==FOURTH) { TM=TD;
			}
		} else
		if (A_countdown.A_pause) {
			counting_dec();
			if (checkPoint(takeChoice2())==FOURTH) { TM=TDbuffer;
			}
		} else
		if (A_countdown.A_stop) {
			//counting_dec();
			if (checkPoint(takeChoice2())==FOURTH) { TM=TDbuffer;
			}
		} else
		if (A_countdown.A_reset) {
			deactivation(A_countdown);
			TD=setTIME_null();
			if (checkPoint(takeChoice2())==FOURTH) { TM=TD;
			}
			Inputoff(false);
		} else
		if (checkPoint(takeChoice2())==FOURTH) { TM=TD;
		}

		if (checkPoint(takeChoice2())==FIRST) {
			TM.hours=getTIME_real('h');
			TM.minutes=getTIME_real('m');
			TM.seconds=getTIME_real('s');
		} else
		if (checkPoint(takeChoice2())==SECOND) { TM=TA;
		}
		return;
	}

	bool timerControl::control_inputting_time(Time& time)
	{
		bool control=false;
		if (time.seconds>=t::t) {
			time.seconds=ui(t::t-1);
			control=true;
		}
		if (time.minutes>=t::t) {
			time.minutes=ui(t::t-1);
			control=true;
		}
		if (time.hours>=t::t/2.5) {
			time.hours=ui(t::t/2.5-1);
			control=true;
		}
		return control;
	}

	void timerControl::move_in_time(int array[], Time& time)
	{
		ui value(0);
		time.hours=array[value++]*10;
		time.hours+=array[value++];
		time.minutes=array[value++]*10;
		time.minutes+=array[value++];
		time.seconds=array[value++]*10;
		time.seconds+=array[value++];
		value=0;
		return;
	}

	void timerControl::move_out_time(int array[], Time& time)
	{
		ui value(0);
		array[value++]=time.hours/10;
		array[value++]=time.hours%10;
		array[value++]=time.minutes/10;
		array[value++]=time.minutes%10;
		array[value++]=time.seconds/10;
		array[value++]=time.seconds%10;
		value=0;
		return;
	}

	void timerControl::setCheck(char *key)
	{
		if (key=="default") {
			checkPoint(takeChoice1())=ZERO;
			checkPoint(takeChoice2())=FIRST;
		} else
		if (key=="left") {
			if (checkPoint(takeSelection()))
				(checkPoint(takeChoice1())>FIRST)?checkPoint(takeChoice1())--:checkPoint(takeChoice1())=FIRST;
			else
				(checkPoint(takeChoice2())>FIRST)?checkPoint(takeChoice2())--:checkPoint(takeChoice2())=FIRST;
		} else
		if (key=="right") {
			if (checkPoint(takeSelection()))
				(checkPoint(takeChoice1())<FOURTH)?checkPoint(takeChoice1())++:checkPoint(takeChoice1())=FOURTH;
			else
				(checkPoint(takeChoice2())<FOURTH)?checkPoint(takeChoice2())++:checkPoint(takeChoice2())=FOURTH;
		} else
		if (key=="up") {
			if (checkPoint(takeSelection())==YES)
				checkPoint(takeSelection())=NO;
		} else
		if (key=="down") {
			if (checkPoint(takeSelection())==NO)
				checkPoint(takeSelection())=YES;
		}

		setCheck_filtering();
		return;
	}

	void timerControl::setCheck_filtering()
	{
		static int PreChoice_stopwatch;
		static int PreChoice_countdown;

		if (checkPoint(takeChoice2())>SECOND&&checkPoint(takeSelection())==YES) {
			checkPoint(takeChoice2())==THIRD?PreChoice_stopwatch=checkPoint(takeChoice1()),setStopwatch(true):NULL;
			checkPoint(takeChoice2())==FOURTH?PreChoice_countdown=checkPoint(takeChoice1()),setCountdown(true):NULL;
		}
		if (checkPoint(takeChoice2())==FIRST||checkPoint(takeChoice2())==SECOND)
			checkPoint(takeChoice1())=ZERO;
		else
		if (checkPoint(takeSelection())!=YES) {
			checkPoint(takeChoice2())==THIRD?checkPoint(takeChoice1())=PreChoice_stopwatch:NULL;
			checkPoint(takeChoice2())==FOURTH?checkPoint(takeChoice1())=PreChoice_countdown:NULL;
		}

		if (checkPoint(takeSelection())==true)
			if (checkPoint(takeChoice2())==FIRST||checkPoint(takeChoice2())==SECOND)
				checkPoint(takeSelection())=NULL;

		if (checkPoint(takeChoice2())==THIRD||checkPoint(takeChoice2())==FOURTH) {
			if (takeChoice2()==THIRD)
				ACTIV=&A_stopwatch;
			else if (takeChoice2()==FOURTH)
				ACTIV=&A_countdown;

			(ACTIV->A_start)?checkPoint(takeChoice1())!=FIRST?NULL:checkPoint(takeChoice1())+=FIRST:NULL;
			(ACTIV->A_pause||ACTIV->A_stop||ACTIV->A_reset)?checkPoint(takeChoice1())>FIRST?checkPoint(takeChoice1())-=FIRST:NULL:NULL;
			(!ACTIV->A_start&&!ACTIV->A_pause&&!ACTIV->A_stop&&!ACTIV->A_reset)?checkPoint(takeChoice1())=FIRST:NULL;
			ACTIV=NULL;
		}
		return;
	}
	
	void timerControl::setInputData()
	{
		bool STOPWATCH=(checkPoint(takeChoice2())==THIRD);
		bool COUNTDOWN=(checkPoint(takeChoice2())==FOURTH);

		if (checkPoint(takeSelection())) {
			if (checkPoint(takeChoice1())==FIRST) {
				STOPWATCH?activation(A_stopwatch, START):takeChoice1()=SECOND;
				COUNTDOWN?activation(A_countdown, START):takeChoice1()=SECOND;
			} else
			if (checkPoint(takeChoice1())==SECOND) {
				STOPWATCH?activation(A_stopwatch, PAUSE),TIbuffer=TI,NULL:NULL;
				COUNTDOWN?activation(A_countdown, PAUSE),TDbuffer=TD,NULL:NULL;
				checkPoint(takeChoice1())=true;
				setCheck_filtering();
			} else
			if (checkPoint(takeChoice1())==THIRD) {
				STOPWATCH?activation(A_stopwatch, STOP),TIbuffer=TI,NULL:NULL;
				COUNTDOWN?activation(A_countdown, STOP),TDbuffer=TD,NULL:NULL;
				checkPoint(takeChoice1())=true;
				setCheck_filtering();
			} else
			if (checkPoint(takeChoice1())==FOURTH) {
				STOPWATCH?activation(A_stopwatch, RESET),TIbuffer=setTIME_null(),NULL:NULL;
				COUNTDOWN?activation(A_countdown, RESET),TDbuffer=setTIME_null(),NULL:NULL;
				checkPoint(takeChoice1())=true;
				setCheck_filtering();
			}
		} else {
			if (checkPoint(takeChoice2())==FIRST) {
				if (!getClock())
					setClock(!NULL);
			} else
			if (checkPoint(takeChoice2())==SECOND) {
				if (!getAlarm_clock())
					setAlarm_clock(!NULL);
			} else
			if (checkPoint(takeChoice2())==THIRD) {
				if (!getStopwatch())
					setStopwatch(!NULL);
			} else
			if (checkPoint(takeChoice2())==FOURTH) {
				if (!getCountdown())
					setCountdown(!NULL);
			}

			(checkPoint(takeChoice2())==THIRD)||(checkPoint(takeChoice2())==FOURTH)?setCheck("down"):NULL;
		}
		return;
	}

	//stack methods
	void timerControl::Push(int value)
	{
		Stack* digit = new Stack;
		(*digit).t_value=value;
		(*digit).t_next=next;
		next=digit;
		return;
	}

	int timerControl::Pop()
	{
		int value=next->t_value;
		Stack *digit=next;
		next=next->t_next;
		delete digit;
		return value;
	}

	//queue methods
	timerControl::Queue::Queue()
	{
		index=NULL;
		size=6;
		container=new int[size];
		for (size_t i(0); i<size; i+=1)
			container[i]=-1;
	}

	bool timerControl::Queue::Enqueue(int value)
	{
		if (index==size)
			return false;
		else {
			container[index++]=value;
			return true;
		}
	}

	int timerControl::Queue::Dequeue()
	{
		return container[size-index--];
	}

	int timerControl::Queue::is_Queue_element(int ind)
	{
		int flag;
		if (container[ind]>=0&&container[ind]<=9)
			flag=3;
		else
			(container[ind]==-1)?flag=1:flag=2;
		return flag;
	}

	void timerControl::Queue::set_Queue_element(int ind, int value)
	{
		container[ind]=value;
		return;
	}

	timerControl::Queue::~Queue()
	{
		delete [] container;
	}

	//destructor
	timerControl::~timerControl(void)
	{
		delete [] activ;
		delete [] activkey;
	}

	void cleaning_screen()
	{
		clrscr();
		return;
	}

	void cleaning_space(int x1, int y1, int x2, int y2)
	{
		int n1(x1), m1(y1), n2(x2), m2(y1);
		setcolor(0);
		while(m2<=y2) {
			line(n1, m1, n2, m2);
			m1=m1+1;
			m2=m2+1;
		}
		return;
	}
}
