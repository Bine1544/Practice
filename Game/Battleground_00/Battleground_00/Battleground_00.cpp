// Battleground_00.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
아이템의 이름을 매크로로 지정해두었습니다.
여기에 사용될 아이템의 목록을 옮기어, PutItemInfo() 함수의 switch 문에
각 아이템의 크기 정보를 기입할 수 있습니다.
*/
#define ITEM1 1
#define ITEM2 2
#define ITEM3 3

/*
아이템의 특징을 매크로로 지정해 둔 부분입니다.
총기와 해당하는 총탄 등을 같이 스폰시키는 등으로
활용할 수 있습니다.
*/
#define FIVEMM_GUN 1
#define SEVENMM_GUN 2 
#define SHOT_GUN 3

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>    
#include <conio.h>

typedef int ITEMTYPE;
typedef int POS;

struct ITEM
{
    ITEMTYPE TYPE;

    int WIDTH;
    int HEIGHT;
    char FEATURE; // 5mm총탄과 해당하는 소총 등 연계되는 아이템 분류에 사용
};

using namespace std;
// int Random();

void PutItemInfo(ITEM* pItem);
void GenItem(POS Pos_x, POS Pos_y, int Width, int Height, ITEM item, POS ItemPos_x, POS ItemPos_y);

int main()
{
   
    int ItemAmount = 3; // 아이템 개수

    for (int i = 0; i<=ItemAmount-1; i++)
    {
        ITEM Item;
        ITEM* pItem = &Item;
        PutItemInfo(pItem);

        POS Pos_x = 0; // 직사각형의 시작점 X좌표
        POS Pos_y = 0; // 직사각형의 시작점 Y좌표
        printf_s("Item is generated ");
        GenItem(Pos_x,Pos_y,40,40,Item, rand() % 10 + 1 + Pos_x, rand() % 10 + 1 + Pos_y); // *아이템좌표 부분은 자바의 랜덤 함수로 적절히 바꿔주십시오. GenItem(직사각형의 시작x좌표, 직사각형의 시작y좌표, 직사각형의 너비, 직사각형의 높이, Item 구조체, 아이템의 x좌표, 아이템의 y좌표) 
    }
    
    return 0;
}

void PutItemInfo(ITEM* pItem)
{
    (*pItem).TYPE = rand() % 10 + 1; // = 뒷부분은 자바의 랜덤 함수로 적절히 바꿔주십시오.
    switch ((*pItem).TYPE)
    {
    case ITEM1: // 아이템별로 크기 및 특수사항 기재
        (*pItem).WIDTH = 10;
        (*pItem).HEIGHT = 10;
        // (*pItem).FEATURE = FIVEMM_GUN; 예시) 5mm 소총 혹은 총탄일경우 이런식으로 기재 
    case ITEM2: 
        (*pItem).WIDTH = 10;
        (*pItem).HEIGHT = 10;
    case ITEM3:
        (*pItem).WIDTH = 10;
        (*pItem).HEIGHT = 10;
    }
    
    return;
}

/*
int Random() // 난수를 반환하는 함수
{
    srand((unsigned int)time(NULL));
    int num(0);
    num = rand();
    return num;
}
*/

void GenItem(POS Pos_x, POS Pos_y, int Width, int Height, ITEM item, POS ItemPos_x, POS ItemPos_y)
{
    // Clipping
    if (ItemPos_y < Pos_y)
    {
        ItemPos_y = Pos_y;
    }
    else if (ItemPos_y > Pos_y + Height)
    {
        ItemPos_y = Pos_y - item.HEIGHT;
    }
    
    if (ItemPos_x < Pos_x)
    {
        ItemPos_x = Pos_x;
    }
    else if (ItemPos_x > Pos_x + Width)
    {
        ItemPos_x = Pos_x - item.WIDTH;
    }

    /*
    비트맵 렌더링 부분을 넣어주세요
    */
    if (item.FEATURE == FIVEMM_GUN)
    {
     // 5mm 탄약 같이 렌더링 
    }
    else if (item.FEATURE == SEVENMM_GUN)
    {
        // 7mm 렌더링
    }
    else if (item.FEATURE == SHOT_GUN)
    {
        // 샷건탄환 렌더링
    }
    
    printf_s("in (%d,%d), and its item number is %d.\n",ItemPos_x,ItemPos_y,item.TYPE);
    _getch();
}