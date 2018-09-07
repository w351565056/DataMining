//---------------------------------------------------------------------------

#include <vcl.h>
#include <algorithm>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include<vector>
using namespace std;
#pragma hdrstop

#include "Unit4.h"
#include "Unit3.h"
#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
        max_length=0;
        address_of_x=0;
        address_of_y=0;
        TXT2 = "";

}
	int next[8][2]={{-1,1}, //右上
                	{0,1},//右
                        {1,1}, //右下
                        {1,0},//下
                        {1,-1},//左下
                        {0,-1},//左
                        {-1,-1},//左上
                        {-1,0}};//上
int count1=0,maxx=0,final=0;
/*vector<int> sum;
vector<int> regist_x;
vector<int> regist_y;*/
int *regist_x = (int *)malloc(sizeof(int)*200000);
int *regist_y = (int *)malloc(sizeof(int)*200000);
int *sum = (int *)malloc(sizeof(int)*200000);
void __fastcall TForm4::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        GetCursorPos(&mouse_start);
        mouse_is_down = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        GetCursorPos(&mouse_end);
        int x_move = mouse_end.x-mouse_start.x;
        int y_move = mouse_end.y-mouse_start.y;
//*******************对自己图片位置的更改************************
        Image1->Left += x_move;
        Image1->Top += y_move;
        if(Image1->Left>0) Image1->Left = 0;
        if(Image1->Top>0) Image1->Top = 0;
        if(Image1->Left<(ScrollBox1->Width-Image1->Width))
        Image1->Left = (ScrollBox1->Width-Image1->Width);
        if(Image1->Top<(ScrollBox1->Height-Image1->Height))
        Image1->Top = (ScrollBox1->Height-Image1->Height);
//*******************对另一个图片位置的更改**********************
        Form3->Image1->Left += x_move;
        Form3->Image1->Top += y_move;
        if(Form3->Image1->Left>0) Form3->Image1->Left = 0;
        if(Form3->Image1->Top>0) Form3->Image1->Top = 0;
        if(Form3->Image1->Left<(Form3->ScrollBox1->Width - Form3->Image1->Width))
        Form3->Image1->Left = (Form3->ScrollBox1->Width - Form3->Image1->Width);
        if(Form3->Image1->Top<(Form3->ScrollBox1->Height - Form3->Image1->Height))
        Form3->Image1->Top = (Form3->ScrollBox1->Height - Form3->Image1->Height);
        mouse_is_down = 0;
//*******************对另一个图片位置的更改**********************
        Form2->Image1->Left += x_move;
        Form2->Image1->Top += y_move;
        if(Form2->Image1->Left>0) Form2->Image1->Left = 0;
        if(Form2->Image1->Top>0) Form2->Image1->Top = 0;
        if(Form2->Image1->Left<(Form2->ScrollBox1->Width - Form2->Image1->Width))
        Form2->Image1->Left = (Form2->ScrollBox1->Width - Form2->Image1->Width);
        if(Form2->Image1->Top<(Form2->ScrollBox1->Height - Form2->Image1->Height))
        Form2->Image1->Top = (Form2->ScrollBox1->Height - Form2->Image1->Height);
        mouse_is_down = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if(mouse_is_down)
        {
        GetCursorPos(&mouse_end);
        int x_move = mouse_end.x-mouse_start.x;
        int y_move = mouse_end.y-mouse_start.y;
//*************************************对自己图片位置的更改***************************************
        Image1->Left += x_move;
        Image1->Top += y_move;
        if(Image1->Left>0) Image1->Left = 0;
        if(Image1->Top>0) Image1->Top = 0;
        if(Image1->Left<(ScrollBox1->Width-Image1->Width))
        Image1->Left = (ScrollBox1->Width-Image1->Width);
        if(Image1->Top<(ScrollBox1->Height-Image1->Height))
        Image1->Top = (ScrollBox1->Height-Image1->Height);
        mouse_start = mouse_end;
//************************************对另一个图片位置的更改**************************************
        Form3->Image1->Left += x_move;
        Form3->Image1->Top += y_move;
        if(Form3->Image1->Left>0) Form3->Image1->Left = 0;
        if(Form3->Image1->Top>0) Form3->Image1->Top = 0;
        if(Form3->Image1->Left<(Form3->ScrollBox1->Width - Form3->Image1->Width))
        Form3->Image1->Left = (Form3->ScrollBox1->Width - Form3->Image1->Width);
        if(Form3->Image1->Top<(Form3->ScrollBox1->Height - Form3->Image1->Height))
        Form3->Image1->Top = (Form3->ScrollBox1->Height - Form3->Image1->Height);
        Form3->mouse_start = Form3->mouse_end;
//************************************对另一个图片位置的更改**************************************
        Form2->Image1->Left += x_move;
        Form2->Image1->Top += y_move;
        if(Form2->Image1->Left>0) Form2->Image1->Left = 0;
        if(Form2->Image1->Top>0) Form2->Image1->Top = 0;
        if(Form2->Image1->Left<(Form2->ScrollBox1->Width - Form2->Image1->Width))
        Form2->Image1->Left = (Form2->ScrollBox1->Width - Form2->Image1->Width);
        if(Form2->Image1->Top<(Form2->ScrollBox1->Height - Form2->Image1->Height))
        Form2->Image1->Top = (Form2->ScrollBox1->Height - Form2->Image1->Height);
        Form2->mouse_start = Form2->mouse_end;
        }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
 void __fastcall TForm4:: find_the_line()
 {
    //显示降噪后的图片
        int i,j;
        for(i=0 ; i<HANG ; i++)
        {
                for(j=0 ; j<LIE ; j++)
                {
                        int r = Form2->ys[Form3->picture[i][j].type+1].r;
                        int g = Form2->ys[Form3->picture[i][j].type+1].g;
                        int b = Form2->ys[Form3->picture[i][j].type+1].b;
                        Form2->Image1->Canvas->Pixels[j][i]=Graphics::TColor(RGB(r,g,b));
                }
        }
        change = (int **)malloc(sizeof(int *)*5172);
        change1 = (int **)malloc(sizeof(int *)*5172);
        for(i=0 ; i<5172 ; i++)
        {
                change[i] = (int *)malloc(sizeof(int )*6573);
                change1[i] = (int *)malloc(sizeof(int )*6573);
        }
        for(i=0 ; i<Form3->HANG; i++)
        {
                for(j=0 ; j<Form3->LIE ; j++)
                {
                        change1[i][j]= Form1->check(i,j);
                        change[i][j] = 0;
                }
        }
  /*      for(int i=0 ; i<HANG*LIE ; i++)
        {
                sum.push_back(0);
                regist_x.push_back(0);
                regist_y.push_back(0);
        }   */
        for(i=0 ; i<200000 ; i++)
        {
                regist_x[i] = 0;
                regist_y[i] = 0;
                sum[i] = 0;
        }
        for(i=1;i<=HANG-2;i++)
        for(j=1;j<=LIE-2;j++) {
                        if(change1[i][j]==0) continue;
                        if(change[i][j])continue;
			count1++;//用作计数的
			regist_x[count1]=i;
			regist_y[count1]=j;
			change[i][j]=1;   //此时的change是book
			dfs(i,j);}
	for(i=1;i<=count1;i++)
		if(maxx<sum[i]){
			maxx=sum[i];
			final=i;
		}
	for(i=1;i<=HANG-2;i++)
        for(j=1;j<=LIE-2;j++)
        change[i][j]=0;       //change重置为0，在画最长的过程中依旧为book

	change[regist_x[final]][regist_y[final]]=1;
	change1[regist_x[final]][regist_y[final]]=2;     //change1=2记录的是最长的线
	redfs(regist_x[final],regist_y[final]);
        for(i=1;i<=HANG-2;i++)
                for(j=1;j<=LIE-2;j++)
                        if(change1[i][j]!=2)
                                change1[i][j]=0;
    //将最终海岸线文件显示到二进制文件里
        for(i=0;i<HANG;i++)
        {
                for(j=0;j<LIE;j++)
                {
                        if(change1[i][j]==2 )
                        {
                                Image1->Canvas->Pixels[j][i]=Graphics::TColor(RGB(0,0,0));
                                TXT2 += 1;
                        }
                        else
                        TXT2 += 0;
                }
        }
}    
int tx,ty,top=1;
//---------------------------------------------------------------------------
void __fastcall TForm4::dfs(int x,int y)
{
	//定义一个方向数组
			for(int k=0;k<=7;k++)
			{
				tx=x+next[k][0];
				ty=y+next[k][1];
				//判断是否越界
				if(tx<1||tx>HANG-1||ty<1||ty>LIE-2)
					continue;
				if(change1[tx][ty]==1&&change[tx][ty]==0)   //此时的change是book
				{

					sum[count1]++;	//将每根线的线长存到sum数组中
					change[tx][ty]=1;
 					dfs(tx,ty);
                                }
			}
			return;
}
//-------------------------------------------------------------------------------
void __fastcall TForm4:: redfs(int x,int y)
{
	//printf("i'm here");
	//定义一个方向数组
        for(int k=0;k<=7;k++)
        {

				tx=x+next[k][0];
				ty=y+next[k][1];
				//判断是否越界
				if(tx<1||tx>HANG-1||ty<1||ty>LIE-1)
					continue;
				if(change1[tx][ty]>0&&change[tx][ty]==0)   //此时的change是book
				{
					change[tx][ty]=1;
                	                change1[tx][ty]=2;
					redfs(tx,ty);
				}

        }
        return;
}

//---------------------------------------------------------------------------

