

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>


// 전처리 구역 
#define VERTICAL_SIZE 40// 메인메뉴 수직 사이즈
#define HORIZONTAL_SIZE 29// 메인메뉴 수평 사이즈 
#define SPACE 32// 스페이스 입력시 들어오는 숫자
#define MAGIC_KEY 224// 방향키 입력 선입력자
#define MENU_LIST 5// 메인메뉴 조작 선택자 길이
#define MENU_Y_COORD 20// 메뉴 방향키 조작 시작좌표
#define MENU_CHOICEBAR_X 60//위와같음.

enum KEYBOARD// 키보드 입력 224 다음에 들어오는 숫자들.
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};





//--- cursor 관련 
void gotoxy(int x, int y) {

    COORD Cur;// xy를 가지는 구조체 
    Cur.X = x;
    Cur.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);// 커서의 위치를 구조체의 좌표위치로 옮기며 동시에 표준입력 스트림에 접근한다.(이거쓸거야 느낌?)
}
void CursorView(char show)		//커서 깜박이는거 숨기는 함수
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}


class MainMenu {

    public:
        MainMenu() {// 생성자.
            gotoxy(0, 0);
            MakeLine();
            Show_User_Choice();
            Make_Logo();
            Show_User_Choice();
            Wait_Keyboard_Input();

            std::cout << "SELECT CONFIRMED!";// check comp TEST CODE!!

    }




















        void MakeLine() {// 메인화면 테두리 작성 함수.
            std::cout << "┏";
            int vt_size = VERTICAL_SIZE;
            int hz_size = HORIZONTAL_SIZE;

            for (int i = 1; i < vt_size; i++) {
                gotoxy(2 * i, 0);
                std::cout << "━" ;
            }
            gotoxy(vt_size * 2, 0);
            std::cout << "┓";
            
            for (int i = 1; i < hz_size; i++)
            {
                gotoxy(2 * vt_size, i);
                std::cout << "┃";
            }
            gotoxy(vt_size * 2, hz_size);
            printf("┛");

            for (int i = 1; i < vt_size; i++)
            {
                gotoxy(2 * i, hz_size);
                std::cout << "━";
            }


            gotoxy(0, hz_size);
            printf("┗");
            for (int i = 1; i < hz_size; i++)
            {
                gotoxy(0, i);
                std::cout << "┃";
            }
            // 테두리 출력 완료 80*29 네모 




    }


    void Show_User_Choice() {// 유저가 선택할 버튼 출력 추후 문자열 길이에 맞춰서 << 출력하도록 개선해야할듯.0325

        int Local_X = MENU_CHOICEBAR_X-40;
        int Local_Y = MENU_Y_COORD+1;

        gotoxy(Local_X, Local_Y);

        std::cout << "1. G A M E   S T A R T (SINGLE PLAY) ";
        gotoxy(Local_X, Local_Y+1);
        std::cout << "2. G A M E   S T A R T (MULTI PLAY) ";
        gotoxy(Local_X, Local_Y + 2);
        std::cout << "3. S H O W     S C O R E  R A N K I N G";
        gotoxy(Local_X, Local_Y + 3);
        std::cout << "4.G A M E     S E T T I N G  ";
        gotoxy(Local_X, Local_Y + 4);
        std::cout << "5. E X I T   G A M E ";
        gotoxy(Local_X, Local_Y + 5);


    }
    void Make_Logo() {// 영문 테트리스 로고 메인에 출력
        int Logo_Start_Y = 1;
        int Logo_Start_X = 12;
        gotoxy(Logo_Start_X, Logo_Start_Y);
        // logo print code needㅇ

        std::cout << "@@@@@@@   @@@@@@@   @@@@@@@   @@@@@@@    @@@@@   @@@@@@@@";
        gotoxy(Logo_Start_X, Logo_Start_Y + 1);
        std::cout << "   @      @            @      @     @      @     @       ";
        gotoxy(Logo_Start_X, Logo_Start_Y + 2);
        std::cout << "   @      @            @      @    @       @     @       ";
        gotoxy(Logo_Start_X, Logo_Start_Y + 3);
        std::cout << "   @      @@@@@@@      @      @@@@@        @     @@@@@@@@";
        gotoxy(Logo_Start_X, Logo_Start_Y + 4);
        std::cout << "   @      @            @      @    @       @            @";
        gotoxy(Logo_Start_X, Logo_Start_Y + 5);
        std::cout << "   @      @            @      @     @      @            @";
        gotoxy(Logo_Start_X, Logo_Start_Y + 6);
        std::cout << "   @      @@@@@@@      @      @      @   @@@@@   @@@@@@@@";

    }
    
    void Wait_Keyboard_Input() {


        int input = 0;
        int Local_Y = MENU_Y_COORD;// select coord need
        int Local_X = MENU_CHOICEBAR_X;
        int prev_Y = 0;
        boolean Choice_flag = false;// 스페이스 입력 이벤트 플래그 

        while (!Choice_flag) {// 키보드 입력 받아서 space로 결정하는 코드 
            Sleep(150);
            input = _getch();// 키보드 입력 받기 
            prev_Y = Local_Y;
            if (input == MAGIC_KEY) {// 얘네는 입력이 2개로 나눠서 들어온다 방향키

                switch (_getch()) {

                    gotoxy(Local_X, Local_Y + MENU_Y_COORD);
                    std::cout << "    ";

                case UP: Local_Y--;
                    break;
                case DOWN: Local_Y++;
                    break;


                }

            }
            else if (input == SPACE) {

                gotoxy(20, 20);// TEST CODE
                Choice_flag = true;


            }

            if (Local_Y > MENU_LIST) {// 0~5 1: single , 2: multi, 3: rank , 4: option, ,5: EXIT 

                Local_Y %= MENU_LIST;// 1->

            }
            else if (Local_Y <= 0) {


                Local_Y = MENU_LIST;// 5 

            }

            gotoxy(Local_X, prev_Y + MENU_Y_COORD);
            std::cout << "           ";

            gotoxy(Local_X, Local_Y + MENU_Y_COORD);
            std::cout << "<< 선택됨";
        }







    }

    






};



int main()
{

    CursorView(0);//커서 숨기는 함수 
    MainMenu menu {};




}


