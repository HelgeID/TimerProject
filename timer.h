#include <ostream>
#pragma once

namespace t
{
	const int t(60);
	const size_t size(6);
}

namespace Mytimer
{
	typedef unsigned int ui;
	enum flag {NO, YES};
	enum md {ZERO=0, FIRST=1, SECOND=2, THIRD=3, FOURTH=4};
	enum btn {START, PAUSE, STOP, RESET};
	const int numline(7);

	struct Stack
	{
		int t_value;
		Stack* t_next;
	};

	struct position
	{
		int x1,y1;//left-top
		int x2,y2;//right-bottom
	};

	struct Time
	{
		ui seconds;
		ui minutes;
		ui hours;
	};

	class timerDisplay
	{
	private:
		const char *digit_0;
		const char *digit_1;
		const char *digit_2;
		const char *digit_3;
		const char *digit_4;
		const char *digit_5;
		const char *digit_6;
		const char *digit_7;
		const char *digit_8;
		const char *digit_9;

	public:
		timerDisplay(void);
		timerDisplay(bool);

		class timerTitle
		{
		private:
			int indexTitle;
		public:
			struct Title
			{
				int posX;
				md number;
				const char* name;
			} *ARRAY, Title1, Title2, Title3, Title4;

			timerTitle::timerTitle(void);
			timerTitle& operator=(timerTitle&);
			void drawTitle(Title[], int);
			timerTitle::~timerTitle(void);
		};

		class timerTitleButton
		{
		public:
			const char* title;
			timerTitleButton::timerTitleButton(void);
			friend std::ostream& operator<<(std::ostream&, const timerTitleButton&);
			timerTitleButton& operator=(const char*);
			void drawTitleButton(md, int, int);
			timerTitleButton::~timerTitleButton(void);
		};

		const char* takeTitleClock();
		const char* takeTitleAlarm_clock();
		const char* takeTitleStopwatch();
		const char* takeTitleCountdown();
		const char* takeTitleStart();
		const char* takeTitlePause();
		const char* takeTitleStop();
		const char* takeTitleReset();

		void drawTitle();
		void drawTitleButton();

		void triangle_up(int, int);
		void triangle_down(int, int);
		void triangle_right(int, int);
		void triangle_left(int, int);
		void _rectangle(int, int, int, int);
		void line1(bool); void line2(bool); void line3(bool);
		void line4(bool); void line5(bool); void line6(bool);
		void line7(bool);
		void colon(const int, const int);
		position overwritelines(int, int, int);
		void overwritelinesback(position (&)[numline]);

		struct valueRGBPIX
		{
			ui vRPIX;
			ui vGPIX;
			ui vBPIX;
		} v;
		void setColorPIX(ui);
		void setColorPIXnew(ui);
		ui getColorPIX(char);

		const char* getDIGIT(ui);
		const char  getCH_null() {return '0';};
		const char  getCH_one() {return '1';};

		void drawSTARTcool(int, int, const char*);
		void drawPAUSEcool(int, int, const char*);
		void drawSTOPcool(int, int, const char*);
		void drawRESETcool(int, int, const char*);

		template <typename T>
		void drawDIGIT(T, int, int, bool);
		template <typename T>
		void drawDIGIT(timerDisplay&, T, int, int, char*);

		void drawBUTTON(btn, int, int);
		void drawBUTTON(timerDisplay&, btn, int, int);
		void drawTEXT(char*, int, int);
		
		void readData();
		void printData();
		void printData(timerDisplay&);

		void input_consoleData();
		void output_consoleData();
		void output_consoleData(timerDisplay&);

		~timerDisplay(void);
	};

	class timerControl
	{
	private:
		Stack* next;
		md mode;
		Time TM, TI, TD;//Main, Increment, Decrement
		Time TA, TC;//Alarm clock, Countdown
		Time TIbuffer, TDbuffer;

		bool *activ;
		bool *activkey;
		bool clock_f;
		bool alarm_clock_f;
		bool stopwatch_f;
		bool countdown_f;

		bool selection;
		int choice1, choice2;
		int number, keynumber;

	public:
		timerControl(void);

		struct A
		{
			bool ACTIV;
			bool A_start, A_pause, A_stop, A_reset;
		} A_clock, A_alarm_clock, A_stopwatch, A_countdown;
		A *ACTIV;

		void activation(A&, const btn);
		void deactivation(A&);
		void activation(ui);
		void deactivation(ui);
		bool isActiv(ui);

		bool inputoff, emptyACf, emptyCf;
		void Inputoff(bool flag) {inputoff=flag; return;}
		bool updateFLG;
		bool& takeSelection() {return selection;}
		int& takeChoice1() {return choice1;}
		int& takeChoice2() {return choice2;}
		int& takeNumber() {return number;}
		int& takeKeyNumber() {return keynumber;}

		int& checkPoint(int &flag) {return flag;}
		bool& checkPoint(bool &flag) {return flag;}

		void checkKEY(char*);
		ui   isPressKEY();

		void setClock(const bool);
		bool getClock();
		void setAlarm_clock(const bool);
		bool getAlarm_clock();
		void setStopwatch(const bool);
		bool getStopwatch();
		void setCountdown(const bool);
		bool getCountdown();

		Time setTIME(ui);
		Time setTIME(ui, ui, ui);
		Time setTIME_null();
		int  getTIME_real(char);
		ui   getTIMEs(Time T) {return T.seconds;}
		ui   getTIMEm(Time T) {return T.minutes;}
		ui   getTIMEh(Time T) {return T.hours;}
		Time& getTIME();
		Time& getTIME(char*);
		void counting_inc();
		void counting_dec();
		void time_management();
		bool control_inputting_time(Time&);
		void move_in_time(int*, Time&);
		void move_out_time(int*, Time&);

		void setMODE(md setting) {mode=setting; return;}
		md   getMODE() {return mode;}

		void setCheck(char*);
		void setCheck_filtering();
		void setInputData();

		void Push(int);
		int Pop();

		class Queue
		{
			private:
				size_t size;
				int index;
				int *container;
			public:
				Queue();
				bool Enqueue(int);
				int Dequeue();
				int is_Queue_element(int);
				void set_Queue_element(int, int);
				~Queue();
		};
		~timerControl(void);
	};
	
	void cleaning_screen();

	void cleaning_space(int, int, int, int);
}
