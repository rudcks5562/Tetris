

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>


// 전처리 구역 
#define VERTICAL_SIZE 40
#define HORIZONTAL_SIZE 29
#define SPACE 32
#define MAGIC_KEY 224
#define MENU_LIST 5
#define MENU_Y_COORD 20


enum KEYBOARD
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};





//--- cursor 
void gotoxy(int x, int y) {

    COORD Cur;// xy를 가지는 구조체 
    Cur.X = x;
    Cur.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);// 커서의 위치를 구조체의 좌표위치로 옮기며 동시에 표준입력 스트림에 접근한다.(이거쓸거야 느낌?)
}
void CursorView(char show)		//커서 숨기는 함수
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
            // 테두리 출력 완료 40*29 네모 

            gotoxy(32, 8);
            // logo print code need


            int input = 0;
            int Local_Y = 1;// select coord need
            int prev_Y = 0;
            boolean Choice_flag = false;// 스페이스 입력 이벤트 플래그 



            while (!Choice_flag) {// 키보드 입력 받아서 space로 결정하는 코드 
                Sleep(150);
                input = _getch();// 키보드 입력 받기 
                prev_Y = Local_Y;
                if (input == MAGIC_KEY) {// 얘네는 입력이 2개로 나눠서 들어온다 방향키
                   
                    switch (_getch()) {
                        
                        gotoxy(32, Local_Y + MENU_Y_COORD);
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

                if (Local_Y > MENU_LIST) {// 0~5 1: single , 2: multi, 3: option , 4: DB, ,5: EXIT 

                    Local_Y %= MENU_LIST;// 1->

                }
                else if (Local_Y < 0) {


                    Local_Y = MENU_LIST;// 5 

                }

                gotoxy(32, prev_Y+MENU_Y_COORD);
                std::cout << "   ";

                gotoxy(32, Local_Y+MENU_Y_COORD);
                std::cout << "<<"<<Local_Y;
            }
                
            

            std::cout << "SELECT CONFIRMED!";// check comp





    }





};



int main()
{

    CursorView(0);//커서 숨기는 함수 
    MainMenu menu {};




}


