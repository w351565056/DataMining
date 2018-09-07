//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
        mouse_is_down = 0;
        select_time = 0;
        amount_of_yb = 0;
        t_min = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(select_time)
        {
                if(Button == mbRight)
                {
                        POINT tp = select_point.back();
                        POINT tb = select_point.front();
                        Image1->Canvas->Pen->Color = RGB(255,0,0);
                        Image1->Canvas->MoveTo(tp.x,tp.y);
                        Image1->Canvas->LineTo(tb.x,tb.y);
                        return ;
                }
                mouse_is_down = 1;
                GetCursorPos(&mouse_select);     //
                mouse_select.x = mouse_select.x-Form3->Left-3-Image1->Left;
                mouse_select.y = mouse_select.y-Form3->Top-28-Image1->Top;
                if(!select_point.empty())
                {
                        POINT tp = select_point.back();
                        Image1->Canvas->Pen->Color = RGB(255,0,0);
                        Image1->Canvas->MoveTo(tp.x,tp.y);
                        Image1->Canvas->LineTo(mouse_select.x,mouse_select.y);
                        
                //        Memo1->Lines->Append(mouse_start.x-Form3->Left-3);
                //        Memo2->Lines->Append(mouse_start.y-Form3->Top-28);
                }
                select_point.push_back(mouse_select);
                return ;
        }
        GetCursorPos(&mouse_start);
        mouse_is_down = 1;
   //     Memo1->Lines->Append(mouse_start.x);
   //     Memo2->Lines->Append(mouse_start.y);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{          
        if(select_time)
        {
                mouse_is_down = 0;
                return ;
        }
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
        Form2->Image1->Left += x_move;
        Form2->Image1->Top += y_move;
        if(Form2->Image1->Left>0) Form2->Image1->Left = 0;
        if(Form2->Image1->Top>0) Form2->Image1->Top = 0;
        if(Form2->Image1->Left<(Form2->ScrollBox1->Width - Form2->Image1->Width))
        Form2->Image1->Left = (Form2->ScrollBox1->Width - Form2->Image1->Width);
        if(Form2->Image1->Top<(Form2->ScrollBox1->Height - Form2->Image1->Height))
        Form2->Image1->Top = (Form2->ScrollBox1->Height - Form2->Image1->Height);
//*******************对另一个图片位置的更改**********************
        Form4->Image1->Left += x_move;
        Form4->Image1->Top += y_move;
        if(Form4->Image1->Left>0) Form4->Image1->Left = 0;
        if(Form4->Image1->Top>0) Form4->Image1->Top = 0;
        if(Form4->Image1->Left<(Form4->ScrollBox1->Width - Form4->Image1->Width))
        Form4->Image1->Left = (Form4->ScrollBox1->Width - Form4->Image1->Width);
        if(Form4->Image1->Top<(Form4->ScrollBox1->Height - Form4->Image1->Height))
        Form4->Image1->Top = (Form4->ScrollBox1->Height - Form4->Image1->Height);
        mouse_is_down = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if(!mouse_is_down)
        {
                
            /*    GetCursorPos(&mouse_eye);
                mouse_eye.x = mouse_eye.x-Form3->Left-3-Image1->Left;
                mouse_eye.y = mouse_eye.y-Form3->Top-28-Image1->Top; //获取本图片位置
                mouse_eye.x += Form3->Left - Image1->Left;           //移动到另一个图片
                Form2->Image1->Canvas->Pixels[mouse_eye.x][mouse_eye.y]
                =Graphics::TColor(RGB(0,255,255));            */
                return ;
        }
        if(select_time)
        {
                GetCursorPos(&mouse_select);
                mouse_select.x = mouse_select.x-Form3->Left-3-Image1->Left;
                mouse_select.y = mouse_select.y-Form3->Top-28-Image1->Top;
                if(!select_point.empty())
                {
                        POINT tp = select_point.back();
                        Image1->Canvas->Pen->Color = RGB(255,0,0);
                        Image1->Canvas->MoveTo(tp.x,tp.y);
                        Image1->Canvas->LineTo(mouse_select.x,mouse_select.y);
                        
                //        Memo1->Lines->Append(mouse_start.x-Form3->Left-3);
                //        Memo2->Lines->Append(mouse_start.y-Form3->Top-28);
                }
                select_point.push_back(mouse_select);
                return ;
        }
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
        Form2->Image1->Left += x_move;
        Form2->Image1->Top += y_move;
        if(Form2->Image1->Left>0) Form2->Image1->Left = 0;
        if(Form2->Image1->Top>0) Form2->Image1->Top = 0;
        if(Form2->Image1->Left<(Form2->ScrollBox1->Width - Form2->Image1->Width))
        Form2->Image1->Left = (Form2->ScrollBox1->Width - Form2->Image1->Width);
        if(Form2->Image1->Top<(Form2->ScrollBox1->Height - Form2->Image1->Height))
        Form2->Image1->Top = (Form2->ScrollBox1->Height - Form2->Image1->Height);
        Form2->mouse_start = Form2->mouse_end;
//************************************对另一个图片位置的更改**************************************
        Form4->Image1->Left += x_move;
        Form4->Image1->Top += y_move;
        if(Form4->Image1->Left>0) Form4->Image1->Left = 0;
        if(Form4->Image1->Top>0) Form4->Image1->Top = 0;
        if(Form4->Image1->Left<(Form4->ScrollBox1->Width - Form4->Image1->Width))
        Form4->Image1->Left = (Form4->ScrollBox1->Width - Form4->Image1->Width);
        if(Form4->Image1->Top<(Form4->ScrollBox1->Height - Form4->Image1->Height))
        Form4->Image1->Top = (Form4->ScrollBox1->Height - Form4->Image1->Height);
        Form4->mouse_start = Form4->mouse_end;
        }
}
//---------------------------------------------------------------------------
int __fastcall TForm3::pnpoly(float test_x,float test_y,int nvert)
{
        int i,j,c = 0;
        for(i=0,j=nvert-1 ; i<nvert ; j=i++)
        {
                if((select_point[i].y*1.0>test_y)!=(select_point[j].y*1.0>test_y))
                {
                        if(test_x<(select_point[j].x*1.0 - select_point[i].x*1.0)*(test_y-select_point[i].y*1.0)/(select_point[j].y*1.0-select_point[i].y*1.0)+select_point[i].x*1.0)
                        {
                                c = !c;
                        }
                }
        }
   //   Memo1->Lines->Append(nvert);
        return c;
}
void __fastcall TForm3::select_to_red()
{
        int x = select_point.size();
        int x_min=9999999;
        int y_min=9999999;
        int x_max=0;
        int y_max=0;
        for(int i=0 ; i<x ; i++)
        {
                if(select_point[i].x>x_max) x_max = select_point[i].x;
                if(select_point[i].y>y_max) y_max = select_point[i].y;
                if(select_point[i].x<x_min) x_min = select_point[i].x;
                if(select_point[i].y<y_min) y_min = select_point[i].y;
        }
        Range r;
        r.x_max = x_max;
        r.y_max = y_max;
        r.x_min = x_min;
        r.y_min = y_min;
        rg.push(r);
        int tem_xx = 0;
        for(int i=y_min ; i<=y_max ; i++)
        {
                for(int j=x_min ; j<=x_max ; j++)
                {
                        if(pnpoly(j,i,x))
                        {
                                tem_xx++;
                        }
                }
        }
        if(tem_xx + amount_of_yb >= D_YANGBEN)
        {
                Application->MessageBoxA("所选择样本数量已超过最大限制！","系统提示",MB_ICONWARNING);
                for(int i=rg.top().x_min ; i<=rg.top().x_max ; i++)
                {
                       for(int j=rg.top().y_min ; j<=rg.top().y_max ; j++)
                       {        
                                Image1->Canvas->Pixels[i][j]
                                =Graphics::TColor(RGB(picture[j][i].data[0]/t_min,picture[j][i].data[1]/t_min,picture[j][i].data[2]/t_min));
                       }
                }
                return;
        }
        for(int i=y_min ; i<=y_max ; i++)
        {
                for(int j=x_min ; j<=x_max ; j++)
                {
                        if(pnpoly(j,i,x))
                        {
                                Image1->Canvas->Pixels[j][i]
                                =Graphics::TColor(RGB(255,0,0));
                                amount_of_yb++;
                                POINT pot;
                                pot.x = j;
                                pot.y = i;
                                lucky_point.push_back(pot);
                        }
                }
        }
}

void __fastcall TForm3::back_to_photo()
{
        while(!rg.empty())
        {
                for(int i=rg.top().x_min ; i<=rg.top().x_max ; i++)
                {
                       for(int j=rg.top().y_min ; j<=rg.top().y_max ; j++)
                       {        
                                Image1->Canvas->Pixels[i][j]
                                =Graphics::TColor(RGB(picture[j][i].data[0]/t_min,picture[j][i].data[1]/t_min,picture[j][i].data[2]/t_min));
                       }
                }
                rg.pop();
        }
}
void __fastcall TForm3::go_back()
{
        int x = select_point.size();
        int x_min=9999999;
        int y_min=9999999;
        int x_max=0;
        int y_max=0;
        for(int i=0 ; i<x ; i++)
        {
                if(select_point[i].x>x_max) x_max = select_point[i].x;
                if(select_point[i].y>y_max) y_max = select_point[i].y;
                if(select_point[i].x<x_min) x_min = select_point[i].x;
                if(select_point[i].y<y_min) y_min = select_point[i].y;
        }
        for(int i=x_min ; i<=x_max ; i++)
        {
                for(int j=y_min ; j<=y_max ; j++)
                {
                        Image1->Canvas->Pixels[i][j]
                        =Graphics::TColor(RGB(picture[j][i].data[0]/t_min,picture[j][i].data[1]/t_min,picture[j][i].data[2]/t_min));
                }
        }
}
void __fastcall TForm3::write_point_to_file(String file_address)
{
        ///...////
        FILE *fp;
        fp = fopen(file_address.c_str(),"a");
     //   Memo1->SetTextBuf(file_address.c_str());
        if(fp==NULL)
        {
                Application->MessageBoxA("文件不存在","系统提示",MB_ICONWARNING);
                return ;
        }
        while(!lucky_point.empty())
        {
                int tx = lucky_point.back().x;
                int ty = lucky_point.back().y;
                for(int i=0 ; i<X_BODUAN ; i++)
                {
                /*Memo1->Lines->Append("ok!");
                Memo2->Lines->Append("ok!"); */
                        fprintf(fp,"%d" ,picture[ty][tx].data[i]);
                        if(i<X_BODUAN-1)
                        fprintf(fp," ");
                }
                lucky_point.pop_back();
                if(!lucky_point.empty())
                fprintf(fp,"\n");
        }
}
