

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>


// 전처리 구역 
#define VERTICAL_SIZE 40// 메인메뉴 수직 사이즈
#define HORIZONTAL_SIZE 29// 메인메뉴 수평 사이즈 
#define MAGIC_KEY 224// 방향키 입력 선입력자
#define MENU_LIST 5// 메인메뉴 조작 선택자 길이

#define MENU_Y_COORD 20// 메뉴 방향키 조작 시작좌표
#define MENU_CHOICEBAR_X 60//위와같음.
#define GAME_SINGLE_X 22// 싱글플레이 콘솔 커서 시작점.
#define GAME_SINGLE_Y 1

enum KEYBOARD// 키보드 입력 224 다음에 들어오는 숫자들.
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80,
    ENTER= 13,
    SPACE=32
};
enum cmds {

    AP=500,// angle rotate 90' plus or minus 
    AD=501,
    ML=502, // move left, right, down
    MR=503,
    MD=504,
    STRIKE=505
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


// block class
class Blocks {// 제시된 블록을 가져다 쓰기위한 클래스임. 다른 기능은 필요없음.

private:
    static Blocks BlockManager;// singleton pattern
    Blocks() {};
    ~Blocks() {};
    Blocks(const Blocks& bref) {};// 상속 복사 생성 금지.
    Blocks& operator = (const Blocks & ref){};

public:
    const int Block1[4][4][4] = {
    { {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0} },
    { {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0} },
    {  {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0} },
    {  {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0} }
    };// 2*2 블록 
    const int Block2[4][4][4] = {

    { {0,0,0,0},
      {0,1,1,0},
      {0,0,1,0},
      {0,0,1,0} },//'ㄱ'

    { {0,0,0,0},
      {0,0,1,0},
      {1,1,1,0},
      {0,0,0,0} },//gun

    { {0,1,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,0,0,0} },

    { {0,0,0,0},
      {0,1,1,1},
      {0,1,0,0},
      {0,0,0,0} }

    };
    const int Block3[4][4][4] = {

    { {0,0,0,0},
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0} },//'ㅡ'

    { {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0} },

    { {0,0,0,0},
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0} },

    { {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0} }

    };// 4*1 블록 
    const int Block4[4][4][4] = {

    { {0,0,0,0},
      {0,0,1,0},
      {0,1,1,1},
      {0,0,0,0} },//'ㅗ'

    { {0,0,0,0},
      {0,0,1,0},
      {0,0,1,1},
      {0,0,1,0} },

    { {0,0,0,0},
      {0,0,0,0},
      {0,1,1,1},
      {0,0,1,0} },

    { {0,0,0,0},
      {0,0,1,0},
      {0,1,1,0},
      {0,0,1,0} }

    };// ㅗ 블록 
    const int Block5[4][4][4] = {

    { {0,0,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,0,1,0} },//'번개모양'

    { {0,0,0,0},
      {0,1,1,0},
      {1,1,0,0},
      {0,0,0,0} },

    { {0,1,0,0},
      {0,1,1,0},
      {0,0,1,0},
      {0,0,0,0} },

    { {0,0,0,0},
      {0,0,1,1},
      {0,1,1,0},
      {0,0,0,0} }

    };// 4*1 블록 
    const int Block6[4][4][4] = {// 반전 번개

 { {0,0,0,0},
   {0,0,1,0},
   {0,1,1,0},
   {0,1,0,0} },

 { {0,0,0,0},
   {1,1,0,0},
   {0,1,1,0},
   {0,0,0,0} },

 { {0,0,1,0},
   {0,1,1,0},
   {0,1,0,0},
   {0,0,0,0} },

 { {0,0,0,0},
   {0,1,1,0},
   {0,0,1,1},
   {0,0,0,0} }

    };// 4*1 블록 
    const int Block7[4][4][4] = {
{ {0,0,0,0},
  {0,1,1,0},
  {0,1,0,0},
  {0,1,0,0} },//'반전 총 모양'

{ {0,0,0,0},
  {1,1,1,0},
  {0,0,1,0},
  {0,0,0,0} },

{ {0,0,1,0},
  {0,0,1,0},
  {0,1,1,0},
  {0,0,0,0} },

{ {0,0,0,0},
  {0,1,0,0},
  {0,1,1,1},
  {0,0,0,0} }

    };

    //1: 정사각형, 2: 오른총, 3:막대 ,4:ㅗ, 5:왼편번개, 6:오른번개, 7: 왼총
    //  blocks = [rotateAngle][y][x]

    int Get_Block_One(int RotateAngle, int y, int x,int nums) {// 블록 원소별로 뽑아 추출. [0~3 : angle ][elements coord y][ele coord x ] 

        switch (nums) {

        case 1:

            return Block1[RotateAngle][y][x];

            break;
        case 2:
            return Block1[RotateAngle][y][x];
            break;

        case 3:
            return Block1[RotateAngle][y][x];
            break;
        case 4: 
            return Block1[RotateAngle][y][x];
            break;
        case 5: 
            return Block1[RotateAngle][y][x];
         break;
        case 6:
            return Block1[RotateAngle][y][x];
            break;
        case 7:
            return Block1[RotateAngle][y][x];
            break;


        }

    }

    static Blocks& GetInstance() {// singleton

        return BlockManager;


    }



};


// key reader class
class KeyManager {

public:
    int input;
    int Local_Y;// select coord need
    int Local_X;
    int prev_Y;// 숨기기 위한 좌표.
    int prev_X;
    boolean Choice_flag;// 메인메뉴 스페이스 입력 이벤트 플래그 

    KeyManager()
        :input{ 0 }, Local_Y{ MENU_Y_COORD }, Local_X{ MENU_CHOICEBAR_X }, prev_Y{ 0 }, Choice_flag{ false }, prev_X{ 0 }
    {
    }

    // 수정필요 
    void Local_Coord_init(int Select_Nums) {// 메인에서 넘어갈때 좌표 재조정.

        switch (Select_Nums)
        {
        case 1:




            break;
        case 2:

            break;

        case 3:

            break;



        }



    }

    void Listen_key_Menu() {// 

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


    int Listen_key_GamePlay() {// 수정 완료.

  
            //gotoxy(60, 30); 
            input = _getch();// 키보드 입력 받기 

          //  AP = 500,// angle rotate 90' plus or minus 
          //      AD = 501,
        //        ML = 502, // move left, right, down
         //       MR = 503,
        //        MD = 504, 스트라이크 505 

            if (input == MAGIC_KEY) {// 얘네는 입력이 2개로 나눠서 들어온다 방향키

                switch (_getch()) {
                    
                case UP: 
                    return AP;
                    break;
                case DOWN: 
                    return MD;
                    break;

                case LEFT: 
                    return ML;
                    break;
                case RIGHT: 
                    return MR;
                    break;
                }

            }
            else if (input == SPACE) {// 바로 하단에 붙이는거

               
                return STRIKE;

                // 쉐도우 상태영역으로 바로 갖다 붙이는 함수 작성 필요.

            }
            else if (input == ENTER) {// 회전 
                return AD;
            }
            
        


    }



};



class ConsoleViewManager {

public:
    int Cursor_X;// 콘솔뷰가 UI를 그릴 커서 시작점 좌표임.
    int Cursor_Y;


    ConsoleViewManager()
        :Cursor_Y{ 0 }, Cursor_X{ 0 }
    {


    }// 생성자 


    void MainLine() {// 메인화면 테두리 작성 함수.
        std::cout << "┏";
        int vt_size = VERTICAL_SIZE;
        int hz_size = HORIZONTAL_SIZE;

        for (int i = 1; i < vt_size; i++) {
            gotoxy(2 * i, 0);
            std::cout << "━";
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

    void MainChoice() {// 유저가 선택할 버튼 출력 추후 문자열 길이에 맞춰서 << 출력하도록 개선해야할듯.0325

        int Local_X = MENU_CHOICEBAR_X - 40;
        int Local_Y = MENU_Y_COORD + 1;

        gotoxy(Local_X, Local_Y);

        std::cout << "1. G A M E   S T A R T (SINGLE PLAY) ";
        gotoxy(Local_X, Local_Y + 1);
        std::cout << "2. G A M E   S T A R T (MULTI PLAY) ";
        gotoxy(Local_X, Local_Y + 2);
        std::cout << "3. S H O W     S C O R E  R A N K I N G";
        gotoxy(Local_X, Local_Y + 3);
        std::cout << "4.G A M E     S E T T I N G  ";
        gotoxy(Local_X, Local_Y + 4);
        std::cout << "5. E X I T   G A M E ";
        gotoxy(Local_X, Local_Y + 5);


    }
    void MainLogo() {// 영문 테트리스 로고 메인에 출력
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

    // 메인 콘솔 그리기 기능 끝.



    void PlayLine() {// singleplay ui 라인선 그리기



    }
    void PlayDescription() {// 싱글플레이 부가설명과 스코어 



    }
    void PlayNextBlockUI() {// 다음 블록이 오는 곳 UI만!




    }
    void PlayNextBlockChange() {// 다음 블록 도형 받아서 그리기 




    }

    void PlayShadowing() {// 쉐도잉 구현.





    }
    void PlaySpawnBlock() {// 블록 시작점에 소환.





    }
    void PlayRotateBlock() {// 현위치에서 블록 회전.-> 쉐도잉과 연계되어야함.




    }
    void PlayMoveBlock() {// 방향키 입력에 따른 현 블록 위치 재지정.



    }


    void PlayEraseRow() {// 배열 확인해서 모두 차있는 경우 지운 다음 그만큼 땡기기 + 물리 적용해 공중에 떠있는 도형 없도록 하기. 



    }



};




// GameManager class

class GameManager {// 게임 관리 해주는 클래스.

    private:
        int GamePlay_Local_X;// 진행중인 게임 테두리 내부에서 작동할 커서 좌표.
        int GamePlay_Local_Y;
        int MapStart_X;// 배열이 인식을 시작할 [0][0] 의 좌표 테스트환경 커서기준 0,0 시작함.
        int MapStart_Y;

        int GameState;// 게임 진행 가능 여부 

        int map[25][40];// size 미정임 , 벡터를 쓸 이유가 없음 = 테트리스 플레이는 고정된 사각형 내부에서 진행하므로.. 

        int Score;
        int Combo;

        KeyManager GMkm;// 게임매니저 내부의 키매니저 
        ConsoleViewManager GMcvm;// 게임매니저 내부 콘솔뷰매니저.



    public:
        GameManager()
            :GamePlay_Local_X{ 0 }, GamePlay_Local_Y{ 0 }, MapStart_X{ 40 }, MapStart_Y{ 25 }, map{}, Score{ 0 }, Combo{ 0 }, GameState{0}
        {




        }// 생성자.
        bool Valid_checker(int NextCmd) {// 이동 또는 회전시 기존 배열에 저장된 위치정보+ 제한선에 걸리는지 체크. (충돌체크임)  

            bool res = true;




            return res;

        }
        void Test_Play() {// test환경 제시. 

            gotoxy(0, 0);
            GameState = 1;

            std::cout << "┏";
            int vt_size = 25;
            int hz_size = 40;

            for (int i = 1; i < vt_size; i++) {
                gotoxy(2 * i, 0);
                std::cout << "━";
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

            // make line 


            gotoxy(22, 1);// 도형 떨어지기 좋은 좌표 이동 
            GamePlay_Local_X = GAME_SINGLE_X;
            GamePlay_Local_Y = GAME_SINGLE_Y;
           // std::cout << "here!";


            while (GameState==1) {// 게임진행 가능시 지속적으로 방향키 입력을 받아오도록 한다. 
                Sleep(150);// 최적화 
                 int cmd= GMkm.Listen_key_GamePlay();// 키를 읽는다 계속.

                 // 작업 이어서 할 구간. 충돌체크랑 맵이랑 콘솔 연동하는 파트와 회전 및 방향키 작동 테스트 하면 됨. 
                 // 세부적으로는 하단에 라인 늘어나는거나 속도조절 UI는 일단 위의 것 완성하고 진행할 것. 0418 



            }


    }







};




class MainMenu {// 메인메뉴를 위한 UI 클래스

    public:

        //KeyManager km;// test code



        MainMenu() {// 생성자.
            gotoxy(0, 0);
            //MakeLine();
            //Show_User_Choice();
            //Make_Logo();
            //Show_User_Choice();
           // km.Listen_key_Menu();

           // std::cout << "SELECT CONFIRMED!";// check comp TEST CODE!!

    }








    
    void Move_OptionView() {// lang 같은 옵션 조작 메뉴 진입.
    
    
        


    
    
    
    
    
    }





    void Move_Back_Main() {// 메인메뉴로 돌아오기.






    }
    void Exit() {// 콘솔 종료.






    }





};



int main()
{

    CursorView(0);//커서 숨기는 함수 
    //MainMenu menu {};
    
    GameManager gm{};
    gm.Test_Play();// 싱글 플레이 테스트환경 시작.




    return 0;
}


