

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

//■ ▦ 블록 글자모음.

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
    
    Blocks()
    {};
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
            return Block2[RotateAngle][y][x];
            break;

        case 3:
            return Block3[RotateAngle][y][x];
            break;
        case 4: 
            return Block4[RotateAngle][y][x];
            break;
        case 5: 
            return Block5[RotateAngle][y][x];
         break;
        case 6:
            return Block6[RotateAngle][y][x];
            break;
        case 7:
            return Block7[RotateAngle][y][x];
            break;


        }

    }

    static Blocks& GetInstance() {// singleton
        static Blocks BlockManager;// singleton pattern

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


    int Listen_key_GamePlay() {// 수정 완료. 키보드 입력을 enum의 특정 정수로 변환하여 리턴해준다.

  
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


// console drawing class
class ConsoleViewManager {



private:
    struct PlayerPointer
    {
        int Cursor_X;
        int Cursor_Y;
        int BlocksNums;
        int RotateState;

    } typedef pp;

    pp cur_point;

public:

    ConsoleViewManager()
        :cur_point{}
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

    //UI---

    void PlayLine() {// singleplay ui 라인선 그리기



    }
    void PlayDescription() {// 싱글플레이 부가설명과 스코어 그리기



    }
    void PlayNextBlockUI() {// 다음 블록이 오는 곳 UI만! 그리기

      
        


    }
    void PlayNextBlockChange() {// 다음 블록 도형 받아서 그리기 - UI안에  

        Blocks& bm = Blocks::GetInstance();//singletone used by local 



    }

    // block draw---

    void PlayShadowing() {// 쉐도잉 구현.





    }
    void PlaySpawnBlock(int BlockNums,int RotateState) {// 블록 시작점에 소환. rand 함수 활용해서 인자 넣을 것.

        this->cur_point.Cursor_X = 22;
        this->cur_point.Cursor_Y = 1;
        this->cur_point.BlocksNums = BlockNums;
        this->cur_point.RotateState = RotateState;

        Blocks& bm = Blocks::GetInstance();

        for (int y = 0; y < 4; y++) {
            gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
            for (int x = 0; x < 4; x++) {
                int elements= bm.Get_Block_One(RotateState, y, x, BlockNums);
                (elements == 1) ? std::cout << "■" : std::cout << "  ";


            }
            this->cur_point.Cursor_Y++;

        }
        this->cur_point.Cursor_X = 22;
        this->cur_point.Cursor_Y = 1;
        gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);

    }
    void PlayRotateBlock(int RotateState) {// 현위치에서 블록 회전.-> 쉐도잉과 연계되어야함.+ 이미 state는 정제되어서 제시되어야 함 gm에서 NextRotateState를 5로 나눌것(음수처리 추가).

        //기존 좌표에서 4,4 구역을 지우고 회전된 블록을 다시 출력한다. 
        
        this->cur_point.RotateState = RotateState;
        int temp_x = this->cur_point.Cursor_X;
        int temp_y = this->cur_point.Cursor_Y;


        Blocks& bm = Blocks::GetInstance();
        for (int y = 0; y < 5; y++) {
            gotoxy(temp_x, temp_y);
            for (int x = 0; x < 8; x++) {
               std::cout << "  ";
            }
            temp_y++;
        }
        gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
         temp_x = this->cur_point.Cursor_X;
         temp_y = this->cur_point.Cursor_Y;

        for (int y = 0; y < 4; y++) {
            gotoxy(temp_x, temp_y);
            for (int x = 0; x < 4; x++) {
                int elements = bm.Get_Block_One(this->cur_point.RotateState, y, x, this->cur_point.BlocksNums);
                (elements == 1) ? std::cout << "■" : std::cout << "  ";
            }
            temp_y++;

        }
        gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
    }
    void PlayMoveBlock(int Coord_x,int Coord_y) {// 방향키 입력에 따른 현 블록 위치 재지정.<여기는 cvm이기때문에 충돌처리는 gm에서 이미 거친 상태라 가정하여 출력만 한다.>



        this->cur_point.Cursor_X = Coord_x;
        this->cur_point.Cursor_Y = Coord_y;

        int temp_x = this->cur_point.Cursor_X;
        int temp_y = this->cur_point.Cursor_Y;

        Blocks& bm = Blocks::GetInstance();
        for (int y = 0; y < 5; y++) {
            gotoxy(temp_x, temp_y);
            for (int x = 0; x < 8; x++) {
                std::cout << "  ";
            }
            temp_y++;
        }
        gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
        temp_x = this->cur_point.Cursor_X;
        temp_y = this->cur_point.Cursor_Y;

        for (int y = 0; y < 4; y++) {
            gotoxy(temp_x, temp_y);
            for (int x = 0; x < 4; x++) {
                int elements = bm.Get_Block_One(this->cur_point.RotateState, y, x, this->cur_point.BlocksNums);
                (elements == 1) ? std::cout << "■" : std::cout << "  ";
            }
            temp_y++;

        }
        gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);

    }


    void PlayEraseRow() {// 배열 확인해서 모두 차있는 경우 지운 다음 그만큼 땡기기 + 물리 적용해 공중에 떠있는 도형 없도록 하기. 



    }
    void PlayMapShow() {// 기록배열로부터 맵 갱신




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
            :GamePlay_Local_X{ 0 }, GamePlay_Local_Y{ 0 }, MapStart_X{ 40 }, MapStart_Y{ 25 }, map{}, Score{ 0 }, Combo{ 0 }, GameState{ 0 }, GMcvm{}, GMkm{}
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
            int cur_blocknums = 4;
            int cur_rotate = 0;// 넘버링과 회전 변수에 랜덤함수 필요 ***(다음 개발일정에 주로 봐야할 곳 표시)
            
            GMcvm.PlaySpawnBlock(cur_blocknums, cur_rotate);// 초기진행(판단)도 구현해야함.  ***(다음 개발일정에 주로 봐야할 곳 표시)

            while (GameState==1) {// 게임진행 가능시 지속적으로 방향키 입력을 받아오도록 한다. 
                Sleep(150);// 최적화 
                 int cmd= GMkm.Listen_key_GamePlay();// 키를 읽는다 계속.
                 switch (cmd) {// 입력된 키에 따른 명령 수행.

                 case AP:// 각도변환 ++90'
                     cur_rotate++;
                     if (cur_rotate <= 4) {
                         cur_rotate = 0;
                     }
                     GMcvm.PlayRotateBlock(cur_rotate);
                     break;

                 case AD:// 각도변환 --90'
                     cur_rotate--;
                     if (cur_rotate < 0) {
                         cur_rotate = 3;
                     }
                     GMcvm.PlayRotateBlock(cur_rotate);

                     break;

                 case ML:// 이동 왼쪽
                     GamePlay_Local_X--;
                     // valid check need  ***(다음 개발일정에 주로 봐야할 곳 표시) 
                     GMcvm.PlayMoveBlock(this->GamePlay_Local_X,this->GamePlay_Local_Y);
                     break;
                 case MR:// 이동 오른쪽
                     GamePlay_Local_X++;
                     // valid check need  ***(다음 개발일정에 주로 봐야할 곳 표시)
                     GMcvm.PlayMoveBlock(this->GamePlay_Local_X, this->GamePlay_Local_Y);
                     break;

                 case MD:// 이동 하단
                     GamePlay_Local_Y++;
                     // valid check need  ***(다음 개발일정에 주로 봐야할 곳 표시)
                     GMcvm.PlayMoveBlock(this->GamePlay_Local_X, this->GamePlay_Local_Y);
                     break;
                 case STRIKE:// 이동 최하단 충돌지점.
                     // shadowing need  ***(다음 개발일정에 주로 봐야할 곳 표시)

                     break;
                 }
                 
                 




                 // 작업 이어서 할 구간. 충돌체크랑 맵이랑 콘솔 연동하는 파트와 회전 및 방향키 작동 테스트 하면 됨. 
                 // 세부적으로는 하단에 라인 늘어나는거나 속도조절 UI는 일단 위의 것 완성하고 진행할 것. 0418 

            // 0508 블록 회전과 이동 그리고 블록 스폰 구현완료.
                // 다음에 할 일- 배열맵과 연동 및 쌓기와 충돌처리 구현. + 쉐도잉 + UI작업 strike 명령어 구현 필요. 


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


