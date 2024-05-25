

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <queue>
#include <Array>

//■ ▦ ▣ 블록 글자모음.



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
    Blocks& operator = (const Blocks& ref) { return *this; };

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

    { {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0} },

    { {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0},
      {0,0,0,0} },

    { {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0} }

    };// 4*1 블록 
    const int Block4[4][4][4] = {

    { {0,0,0,0},
      {0,1,0,0},
      {1,1,1,0},
      {0,0,0,0} },//'ㅗ'

    { {0,0,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,1,0,0} },

    { {0,0,0,0},
      {0,0,0,0},
      {1,1,1,0},
      {0,1,0,0} },

    { {0,0,0,0},
      {0,1,0,0},
      {1,1,0,0},
      {0,1,0,0} }

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

        default:
            return -1;
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
    const int MAGIC_KEY ;
    const int MENU_LIST;
    const static int MENU_Y_COORD=20;
    const static int MENU_CHOICEBAR_X=60;


    boolean Choice_flag;// 메인메뉴 스페이스 입력 이벤트 플래그 

    KeyManager()
        :input{ 0 }, Local_Y{ MENU_Y_COORD }, Local_X{ MENU_CHOICEBAR_X }, prev_Y{ 0 }, Choice_flag{ false }, prev_X{ 0 }, MENU_LIST{ 5 }, MAGIC_KEY{224}
    {
    }

    // 수정필요 
    void Local_Coord_init(int Select_Nums) {// 메인에서 넘어갈때 좌표 재조정.

        switch (Select_Nums)
        {
        default:
            break;
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
            Sleep(50);
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

                default:

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




public:


    const int MENU_LIST;
    const int MENU_Y_COORD;
    const int MENU_CHOICEBAR_X;
    const int GAME_SINGLE_X;// 싱글플레이 콘솔 커서 시작점.
    const int GAME_SINGLE_Y;
    const  static int GAME_SINGLE_VSIZE=30;
    const static int GAME_SINGLE_HSIZE=20;
    const int VERTICAL_SIZE;// 메인메뉴 수직 사이즈
    const int HORIZONTAL_SIZE;// 메인메뉴 수평 사이즈 

    ConsoleViewManager()
        :MENU_LIST{ 5 }, MENU_Y_COORD{ 20 }, MENU_CHOICEBAR_X{ 60 }, GAME_SINGLE_X{ 22 }, GAME_SINGLE_Y{ 1 }, VERTICAL_SIZE{ }, HORIZONTAL_SIZE{29}
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

 


    void PlayMapShow(int (*maps)[GAME_SINGLE_HSIZE]) {// 기록배열로부터 맵 갱신 cvm이므로 그림만 그린다. 

        // 로직 
        // 게임 플레이 하다가 진행중 블록에 하단 이동에 대한 충돌이 일어남. 또는 시작 때
        // 쉐도잉 위치에 적재(1의 경우에만)
        // 배열 갱신
        // 갱신된 배열을 바탕으로 콘솔뷰 갱신***(해당 함수)
        // 다음 블록 스폰

        

        for (int i = 0; i < GAME_SINGLE_VSIZE; i++) {
            gotoxy(0, i);
            for (int j = 0; j < GAME_SINGLE_HSIZE; j++) {
                
                if (maps[i][j] == 3) {// 기본 틀

                    std::cout << "▦"; 

                }
                else if (maps[i][j] == 2) {// 누적된 블록들

                    std::cout << "▣";
                }
                else if (maps[i][j] == 4) {// shadowing 

                    std::cout << "##";

                }
                else if(maps[i][j]==0) {

                    std::cout << "  ";

                }
                else if (maps[i][j] == 1) {
                    std::cout << "■";
                }

            }


        }






    }// checked

    


};




// GameManager class

class GameManager {// 게임 관리 해주는 클래스.




    private:

        const static int GAME_SINGLE_VSIZE=30;
        const static int GAME_SINGLE_HSIZE=20;
        const int VERTICAL_SIZE;// 메인메뉴 수직 사이즈
        const int HORIZONTAL_SIZE;// 메인메뉴 수평 사이즈 
        int GameState;// 게임 진행 가능 여부 
        int map[GAME_SINGLE_VSIZE][GAME_SINGLE_HSIZE];// size 미정임 , 벡터를 쓸 이유가 없음 = 테트리스 플레이는 고정된 사각형 내부에서 진행하므로.. 

        int Score;
        int Combo; 

        KeyManager GMkm;// 게임매니저 내부의 키매니저 
        ConsoleViewManager GMcvm;// 게임매니저 내부 콘솔뷰매니저.
        struct PlayerPointer
        {
           int Cursor_X;
           int Cursor_Y;
           int BlocksNums;
           int RotateState;

           PlayerPointer& operator=(const PlayerPointer& rhs) {// 대입연산자.
               this->Cursor_X = rhs.Cursor_X;
               this->Cursor_Y = rhs.Cursor_Y;
               this->BlocksNums = rhs.BlocksNums;
               this->RotateState = rhs.RotateState;
               return *this;
        }

         } typedef pp;

        pp cur_point;

    public:





        GameManager()
            :map{}, Score{ 0 }, Combo{ 0 }, GameState{ 0 }, GMcvm{}, GMkm{}, cur_point{}, VERTICAL_SIZE{40}, HORIZONTAL_SIZE{29}
        {
            



        }// 생성자.
        bool ValidChecker(int x,int y) {// 이동 또는 회전시 기존 배열에 저장된 위치정보+ 제한선에 걸리는지 체크. (충돌체크임)  

            bool res = true;


            if (map[y + 1][x] == 2 || map[y + 1][x] == 3) {// 현재 주어진 원소에 대해 하단이 테두리나 쌓인 블록인 경우에는.

                return false;

            }

            return res;

        }
        bool CursorLimitChecker(int next_x,int next_y) {// 커서가 배열 사이즈 밖으로 나가지 못하도록 움직임 제한.

        
            if (next_x < 0 || next_x >= GAME_SINGLE_HSIZE-1 || next_y < 0 || next_y >= GAME_SINGLE_VSIZE-1) {
                return false;
           }

            return true;
        }
        bool PlaySpawnBlock(int BlockNums, int RotateState) {// 블록을 시작점에 생성하는 함수 


            Blocks& bm = Blocks::GetInstance(); 

            int StartX = 8;
            int StartY = 1;

            this->cur_point.Cursor_X = StartX;
            this->cur_point.Cursor_Y = StartY;
            this->cur_point.BlocksNums = BlockNums;
            this->cur_point.RotateState = RotateState;


            for (int i = 0; i < 4; i++) {

                for (int j = 0; j < 4; j++) {


                    int temp_res= bm.Get_Block_One(RotateState, i, j, BlockNums);
                    if (map[StartY + i][StartX + j] == 2) {
                        return false;
                    }
                    else if (map[StartY + i][StartX + j] == 0) {

                        map[StartY + i][StartX + j] = temp_res;

                    }

                }

            }

            return true;


        }
        bool PlayRotateBlock(int RotateState) {// 현위치에서 블록 회전.-> 쉐도잉과 연계되어야함.+ 이미 state는 정제되어서 제시되어야 함 gm에서 NextRotateState를 5로 나눌것(음수처리 추가).

            //기존 좌표에서 4,4 구역을 지우고 회전된 블록을 다시 출력한다. 

            Blocks& bm = Blocks::GetInstance(); 
            int temp_x = this->cur_point.Cursor_X;
            int temp_y = this->cur_point.Cursor_Y;// 로컬 좌표 가져오기
            bool flag = true;

            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(RotateState, y, x, this->cur_point.BlocksNums);

                    if (map[temp_y + y][temp_x + x] != 2 && map[temp_y + y][temp_x + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 



                    }
                    else if (elements==1&& (map[temp_y + y][temp_x + x] == 2 || map[temp_y + y][temp_x + x] == 3)) {// 2 나 3이 겹치는 곳에 블록이 생성되야한다면 
                        flag = false;
                    }


                }
            }// 변환된 값의 4*4를 유효 체크해준다. 

            if (flag == false) {
                return flag;
            }


            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    
                    if (map[temp_y + y][temp_x + x] == 1) {
                        map[temp_y + y][temp_x + x] = 0;
                    }


                }
            }// 회전 이전꺼는 지우고 


            for (int y = 0; y < 4; y++) {
               
                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(RotateState, y, x, this->cur_point.BlocksNums);

                    if (map[temp_y + y][temp_x + x] != 2&& map[temp_y + y][temp_x + x] != 3 ) {// 2,3 가 아닌 케이스들에 대하여 

                        map[temp_y + y][temp_x + x] = elements;

                    }


                }
            }// 변환된 값의 4*4를 채워준다. 
           
            this->cur_point.RotateState = RotateState;

            return true;

        }
        bool PlayMoveBlock(int Coord_x, int Coord_y) {// 방향키 입력에 따른 현 블록 위치 재지정.<여기는 cvm이기때문에 충돌처리는 gm에서 이미 거친 상태라 가정하여 출력만 한다.>


            bool flag = true;
            int temp_x = this->cur_point.Cursor_X;//이동 전의 좌표는 이곳에 저장.
            int temp_y = this->cur_point.Cursor_Y;
            Blocks& bm = Blocks::GetInstance();



            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(this->cur_point.RotateState, y, x, this->cur_point.BlocksNums);

                    if (map[Coord_y + y][Coord_x + x] != 2 && map[Coord_y + y][Coord_x + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 

                        continue;

                    }
                    else if (elements==1&&(map[Coord_y + y][Coord_x + x] == 2 || map[Coord_y + y][Coord_x + x] == 3)) {// 2 나 3이 겹치는 곳에 블록이 생성되야한다면 
                        
                        
                        
                        flag = false;
                    }


                }
            }// 변환된 값의 4*4를 유효 체크해준다. 

            if (flag == false) {
                return false;
            }
            this->cur_point.Cursor_X = Coord_x;//이동할 좌표로 바로 갱신
            this->cur_point.Cursor_Y = Coord_y;


            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {

                    if (map[temp_y + y][temp_x + x] == 1) {
                        map[temp_y + y][temp_x + x] = 0;
                    }


                }
            }// 이동 이전꺼는 지우고 

            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(this->cur_point.RotateState, y, x, this->cur_point.BlocksNums);
                   
                    if (map[this->cur_point.Cursor_Y + y][this->cur_point.Cursor_X + x] != 2 && map[this->cur_point.Cursor_Y + y][this->cur_point.Cursor_X + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 

                        map[this->cur_point.Cursor_Y + y][this->cur_point.Cursor_X + x] = elements;

                    }

                }


            }

            return true;
        }
        void PlayMoveShadow(int x_input,int y_input) {// 커서를 임시로 이분탐색을 통해 최적의 커서위치(y값:세로축)를 찾는다. 

            // 매개변수는 현재 커서의 위치.
            Blocks& bm = Blocks::GetInstance();
            
            bool pass{ true };
            pp next_point{};

            next_point = this->cur_point;// 대입

            int rec_x = x_input;// 최적 쉐도우 커서 위치 
            int rec_y = y_input;


            int left = y_input;
            int right = GAME_SINGLE_VSIZE-1-3;//Y value 
            // x좌표는 그대로 받아오고 y축 좌표는 2분탐색을 사용해 최적의 장소를 찾는다. 
            next_point.Cursor_X = x_input;

            while (left <= right) {


                int mid = (left + right) / 2;
               
                next_point.Cursor_Y = mid;
                pass = true;//블록 놓을 수 있는지 
               // std::cout << " mid= " << mid;// LOG 
        
                for (int y = 0; y < 4; y++) {

                    for (int x = 0; x < 4; x++) {
                        int elements = bm.Get_Block_One(next_point.RotateState, y, x, next_point.BlocksNums);

                            if (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 2 && map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 

                                continue;

                            }
                            else if (elements == 1 && (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] == 2 || map[next_point.Cursor_Y + y][next_point.Cursor_X + x] == 3)) {// 2 나 3이 겹치는 곳에 블록이 생성되야한다면 



                                pass = false;
                            }


                        }
                    }// 변환된 값의 4*4를 유효 체크해준다. 

                    if (!pass) {// pass가 false면 mid가 right가 되어야함
                        right = mid-1;
                    }
                    else {// pass가 true면 left= mid

                        left = mid+1;

                    }



                }
                        if (CursorLimitChecker(next_point.Cursor_X,right) == true ) {
                            rec_y = right;
                        }




            for (int y = 0; y < GAME_SINGLE_VSIZE; y++) {// 최적화 필요.. 변경이전 쉐도우 커서의 위치를 따로 저장한 후 이를 활용하도록 하자.

                for (int x = 0; x < GAME_SINGLE_HSIZE; x++) {

                    if (map[y][x] == 4) {// 쉐도우 삭제 
                        map[y][x] = 0;
                    }


                }
            }// 이동 이전꺼는 지우고 

            next_point.Cursor_Y = rec_y;

            //std::cout << "cursor coord= " << next_point.Cursor_X << next_point.Cursor_Y;

            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(next_point.RotateState, y, x, next_point.BlocksNums);

                    if (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 2 && map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 3&& map[next_point.Cursor_Y + y][next_point.Cursor_X + x]!=1) {// 2,3 가 아닌 케이스들에 대하여 
                        if (elements == 1) {
                            map[next_point.Cursor_Y + y][next_point.Cursor_X + x] = 4;
                           // std::cout << "cursor coord= " << next_point.Cursor_X+x <<" y= " << next_point.Cursor_Y+y;
                        }
                        else {
                            map[next_point.Cursor_Y + y][next_point.Cursor_X + x] = 0;
                        }
                       

                    }

                }


            }



              


        }
        void PlayRotateShadow(int x_input, int y_input) {//커서를 임시로 아래로 이동시켜 최적의 커서위치에서 쉐도우를 만든다. <로테이션 정보 변경후에 사용하도록 한다>

            Blocks& bm = Blocks::GetInstance();

            bool pass{ true };
            pp next_point{};

            next_point = (cur_point);

            int rec_x = x_input;
            int rec_y = y_input;


            int left = 1;
            int right = GAME_SINGLE_VSIZE-3-1;//Y value 

            while (left <= right) {


                int mid = (left + right) / 2;
                next_point.Cursor_X = x_input;
                next_point.Cursor_Y = mid;
                pass = true;
                
                for (int y = 0; y < 4; y++) {

                    for (int x = 0; x < 4; x++) {
                        int elements = bm.Get_Block_One(next_point.RotateState, y, x, next_point.BlocksNums);

                        if (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 2 && map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 

                            continue;

                        }
                        else if (elements == 1 && (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] == 2 || map[next_point.Cursor_Y + y][next_point.Cursor_X + x] == 3)) {// 2 나 3이 겹치는 곳에 블록이 생성되야한다면 



                            pass = false;
                        }


                    }
                }// 변환된 값의 4*4를 유효 체크해준다. 

                if (!pass) {// pass가 false면 mid가 right가 되어야함
                    right = mid-1;
                }
                else {// pass가 true면 left= mid

                    left = mid+1;
                
                }



            }
            if (CursorLimitChecker(next_point.Cursor_X, right) == true) {
                rec_y = right;
            }
            std::cout << right<<"?"<<left<<"#";

            for (int y = 0; y < GAME_SINGLE_VSIZE; y++) {// 최적화 필요.. 변경이전 쉐도우 커서의 위치를 따로 저장한 후 이를 활용하도록 하자.

                for (int x = 0; x < GAME_SINGLE_HSIZE; x++) {

                    if (map[y][x] == 4) {// 쉐도우 삭제 
                        map[y][x] = 0;
                    }


                }
            }// 회전 이전꺼는 지우고 

            next_point.Cursor_Y = rec_y;

            for (int y = 0; y < 4; y++) {

                for (int x = 0; x < 4; x++) {
                    int elements = bm.Get_Block_One(next_point.RotateState, y, x, next_point.BlocksNums);

                    if (map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 2 && map[next_point.Cursor_Y + y][next_point.Cursor_X + x] != 3) {// 2,3 가 아닌 케이스들에 대하여 
                        if (elements == 1) {
                            map[next_point.Cursor_Y + y][next_point.Cursor_X + x] = 4;
                        }
                        else {
                            map[next_point.Cursor_Y + y][next_point.Cursor_X + x] = elements;
                        }


                    }

                }


            }


        }



        void PlaySinkBlocks() {

            for (int i = 0; i < GAME_SINGLE_VSIZE; i++) {

                for (int j = 0; j < GAME_SINGLE_HSIZE; j++) {


                    if (map[i][j] == 1) {

                        map[i][j] = 2;


                    }

                }

            }



        }
        int EraseChecker(int score,int combo) {// down 함수와 연계 필요. -> 삭제후 낙하 구현필요.// 커서주위+4만 체크해보려 했으나 연쇄적으로 체크하기 위해서는 탐색이 더 나은 것 같음.

            int result = 0;
            int counter = 0;

            for (int i = 0; i < GAME_SINGLE_VSIZE; i++) {

                int cnt = 0;//2 element count
                for (int j = 0; j < GAME_SINGLE_HSIZE; j++) {

                    if (map[i][j] == 2) {
                        cnt++;
                    }


                }
                if (cnt == 18) {

                    for (int j = 1; j < GAME_SINGLE_HSIZE - 1; j++) {

                        map[i][j] = 0;
                        // 없어진 칸에 대한 물리 적용 필요. -> 최하단부터 한칸씩 하단 체크하며 이동시키기. 

                    }
                    combo++;
                    counter++;
                }


            }// checked! 
            if (counter > 0) {
                sort();
            }
   

            result = score + (combo * counter);

            return result;// 점수 반환 

        }
        void sort() {// 빈칸에 대한 이동만 진행. 

            
            std::queue<int> q;

        for (int j = 1; j < GAME_SINGLE_HSIZE - 1; j++) {// 가로축에 대해 모두 당겨주기 

            
            q.push(3);
            for (int i = GAME_SINGLE_VSIZE-1; i >0; i--) {// 기존 열의 정보를 0을 제외하고 추출
                if (map[i][j] != 0 && map[i][j] != 3)
                    q.push(map[i][j]);


            }
            

            for (int i = GAME_SINGLE_VSIZE - 1; i > 0; i--) {// 이를 놓을 장소에 모두 0으로 초기화

                if (map[i][j] == 2) {
                    map[i][j] = 0;
                }


            }

            for (int i = GAME_SINGLE_VSIZE-1; i > 0; i--) {// 그 열에 대해 압축된 정보를 집어넣기.

                if (!q.empty()) {
                    int elements= q.front();

                    (elements != 3) ? (map[i][j] = elements) : (map[i][j]=3);//?

                    q.pop();
                }
               
            }


           
         }// for end
                
            
         
        }







        void Test_Play() {// test환경 제시. 

            gotoxy(0, 0);
            GameState = 1;

            //std::cout << "▦";
            int vt_size = GAME_SINGLE_VSIZE;//30
            int hz_size = GAME_SINGLE_HSIZE;//20

            // init 
            for (int i = 0; i < vt_size; i++) {   //map의 기본 로직 - 1은 현재 움직이고 있는 블록, 2는 쌓인 상태의 블록, 3은 기본 틀,4는 쉐도잉으로 정의한다. 
                //3은 어떤 경우에도 지워지지 않고 1의 충돌지에는 4로,1이 도달시에는 2로 변환.
                // 2로 변환되며 클리어 되는 경우 물리적으로 2는 모두 충돌지점까지 낙하하도록 설계. 

                for (int j = 0; j < hz_size; j++) {

                    if (i == 0 || j == 0|| i== vt_size-1|| j==hz_size-1) {// 모든 겉테두리를 3으로 감싼 후 ▦ 로 변환할 것이다. 
                        map[i][j] = 3;
                    }
                    else {
                        map[i][j] = 0;
                    }

                }
            }

            GMcvm.PlayMapShow(this->map);


            // INIT ---









            int cur_blocknums = 3;
            int cur_rotate = 0;// 넘버링과 회전 변수에 랜덤함수 필요 ***(다음 개발일정에 주로 봐야할 곳 표시)
            
            PlaySpawnBlock(cur_blocknums, cur_rotate);//2가 없으면 그냥 뜨게 하였음. 
            PlayMoveShadow(this->cur_point.Cursor_X,this->cur_point.Cursor_Y);
            GMcvm.PlayMapShow(this->map);
            std::cout << "?";


            bool DownPossible = true;

            while (GameState==1) {// 게임진행 가능시 지속적으로 방향키 입력을 받아오도록 한다. 
                Sleep(150);// 최적화 
                 int cmd= GMkm.Listen_key_GamePlay();// 키를 읽는다 계속.

                 

                 switch (cmd) {// 입력된 키에 따른 명령 수행.
                 default:
                     break;

                 case AP:// 각도변환 ++90'

                     cur_rotate++;
                     if (cur_rotate == 4) {
                         cur_rotate = 0;
                     }
                     if (!PlayRotateBlock(cur_rotate)) {
                         cur_rotate--;
                         if (cur_rotate < 0) {
                             cur_rotate = 3;
                         }
                     }
                     PlayRotateShadow(this->cur_point.Cursor_X,this->cur_point.Cursor_Y);
                     break;

                 case AD:// 각도변환 --90'
                     cur_rotate--;
                     if (cur_rotate < 0) {
                         cur_rotate = 3;
                     }
                     if (!PlayRotateBlock(cur_rotate)) {
                         cur_rotate++;
                         if (cur_rotate == 4) {
                             cur_rotate = 0;
                         }

                     }
                     PlayRotateShadow(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                     break;

                 case ML:// 이동 왼쪽
                     if (CursorLimitChecker(this->cur_point.Cursor_X - 1, this->cur_point.Cursor_Y)) {

                         

                         PlayMoveBlock(this->cur_point.Cursor_X-1 , this->cur_point.Cursor_Y);
                         PlayMoveShadow(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                     }
                 
                     break;
                 case MR:// 이동 오른쪽
                     
                    
                     if (CursorLimitChecker(this->cur_point.Cursor_X + 1, this->cur_point.Cursor_Y)) {
                         
                         PlayMoveBlock(this->cur_point.Cursor_X+1 , this->cur_point.Cursor_Y);
                         PlayMoveShadow(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                     }
                     break;

                 case MD:// 이동 하단
                     
                     if (CursorLimitChecker(this->cur_point.Cursor_X, this->cur_point.Cursor_Y+1)) {
                         
                         if (DownPossible == false) {// 블록 지점에 대해 모두 조사하여 하단 이동 후 더이상 내려갈 곳이 없다면.(바로굳게 하려면 여기를 하단으로 내리면 된다.)


                             PlaySinkBlocks();// 이후 새로시작 해줘야된다. ***

                             int temp_score = 0;
                             do {
                                 temp_score = EraseChecker(this->Score, this->Combo);// 압축
                                 if (temp_score != this->Score) {
                                     this->Score += temp_score;
                                     this->Combo++;
                                 }


                             } while (temp_score != this->Score);


                             PlaySpawnBlock(3, 0);// TEST CODE
                             DownPossible = true;
                             break;
                         }

                         PlayMoveBlock(this->cur_point.Cursor_X, this->cur_point.Cursor_Y+1);
                         PlayMoveShadow(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                        

                         for (int i = this->cur_point.Cursor_Y; i < this->cur_point.Cursor_Y + 4; i++) {

                             for (int j = this->cur_point.Cursor_X; j < this->cur_point.Cursor_X + 4; j++) {// 4*4 구역 탐색하여 원소찾기.

                                 if (map[i][j] == 1) {

                                   //  gotoxy(50, 50);
                                    // std::cout <<" ########"<<i<< " "<<j<<" x="<< this->cur_point.Cursor_X <<" y="<< this->cur_point.Cursor_Y;-> local coord logs
                                   //  gotoxy(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                                  
                                     if (ValidChecker(j, i) == false) {// 원소가 하나라도 더이상 밑으로 내려가지 못하면 굳히기.
                                         
                                         DownPossible = false;
                                     }

                                 }

                             }



                         }



 

                     }
                     break;
                 case STRIKE:// 이동 최하단 충돌지점.
                     // shadowing need  ***(다음 개발일정에 주로 봐야할 곳 표시) - 낙하시 줄제거 잘 안됨.?

                     for (int y = 0; y < GAME_SINGLE_VSIZE; y++) {// 최적화 필요.. 변경이전 쉐도우 커서의 위치를 따로 저장한 후 이를 활용하도록 하자.

                         for (int x = 0; x < GAME_SINGLE_HSIZE; x++) {

                             if (map[y][x] == 4) {// 쉐도우 변경 
                                 map[y][x] = 2;
                             }



                         }
                     }

                     
                    // GMcvm.PlayMapShow(this->map);
                    // system("pause");// 여기서 1이 사라짐.
                     for (int y = 1; y < GAME_SINGLE_VSIZE - 1; y++) {// 최적화 필요.. 변경이전 쉐도우 커서의 위치를 따로 저장한 후 이를 활용하도록 하자.

                         for (int x = 1; x < GAME_SINGLE_HSIZE - 1; x++) {
                             if (map[y][x] == 1) {
                                 map[y][x] = 0;

                             }
                         }
                     }
                     int temp_score = 0;
                     do {
                         temp_score = EraseChecker(this->Score, this->Combo);// 압축
                         if (temp_score != this->Score) {
                             this->Score += temp_score;
                             this->Combo++;
                         }


                     } while (temp_score != this->Score);
                     /*
                     for (int y = 1; y < GAME_SINGLE_VSIZE - 1; y++) {// 최적화 필요.. 변경이전 쉐도우 커서의 위치를 따로 저장한 후 이를 활용하도록 하자.

                         for (int x = 1; x < GAME_SINGLE_HSIZE - 1; x++) {
                             if (map[y][x] == 1) {
                                 map[y][x] = 0;

                             }
                         }
                     }*/

                     PlaySpawnBlock(3, 0);// TEST CODE
                     PlayMoveShadow(this->cur_point.Cursor_X, this->cur_point.Cursor_Y);
                     DownPossible = true;

                     break;
                 }
                 
                 GMcvm.PlayMapShow(this->map);




                 // 작업 이어서 할 구간. 충돌체크랑 맵이랑 콘솔 연동하는 파트와 회전 및 방향키 작동 테스트 하면 됨. 
                 // 세부적으로는 하단에 라인 늘어나는거나 속도조절 UI는 일단 위의 것 완성하고 진행할 것. 0418 

            // 0508 블록 회전과 이동 그리고 블록 스폰 구현완료.
                // 다음에 할 일- 배열맵과 연동 및 쌓기와 충돌처리 구현. + 쉐도잉 + UI작업 strike 명령어 구현 필요. 
                 // 배열에 기록된 데이터를 기반으로 그림을 그릴지 그림을 내려가며 충돌체크를 한 후 충돌시에만 배열을 갱신할지 고민.
                 //전자는 배열이 0.15초마다 갱신되는 부하가 걸리고 후자는 블록 클래스의 4*4 크기 때문에 구현이 복잡해짐. 
                 // 후자로 진행해보고 안되면 전자로 하도록 한다. 배열에는 이미 바닥에 깔린 정보만 존재해도 무방하다. 현재 내려가고 있는 블록을 굳이 담을 필요가 없다. 

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
// 3번각도가 1번과 차이나서 공중에 뜨는듯 보인다.


int main()
{

    CursorView(0);//커서 숨기는 함수 
    //MainMenu menu {};
    
    GameManager gm{};
    gm.Test_Play();// 싱글 플레이 테스트환경 시작.




    return 0;
}


