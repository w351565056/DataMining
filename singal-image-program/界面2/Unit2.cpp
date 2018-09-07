//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
        TXT1 = "";
        max_suggest = 0;
        amount_of_feature = 0;      
        amount_of_feature_2 = 0;
        amount_of_feature_3 = 0;
        mouse_is_down = 0;
        Height = 651;
        for(int i=0 ; i<I_D ; i++)
        {
                address[i] = "";
        }
        ys[0].r = 0; ys[0].g = 0; ys[0].b = 0;             //黑
        ys[1].r = 255; ys[1].g = 0; ys[1].b = 0;           //红
        ys[2].r = 0; ys[2].g = 255; ys[2].b = 0;           //绿
        ys[3].r = 0; ys[3].g = 0; ys[3].b = 255;           //蓝
        ys[4].r = 255; ys[4].g = 255; ys[4].b = 0;         //黄
        ys[5].r = 255; ys[5].g = 0; ys[5].b = 255;         //紫
        ys[6].r = 0; ys[6].g = 255; ys[6].b = 255;         //浅蓝
        ys[7].r = 255; ys[7].g = 192; ys[7].b = 203;       //粉色
        ys[8].r = 255; ys[8].g = 215; ys[8].b = 0;         //金黄
        ys[9].r = 138; ys[9].g = 43; ys[9].b = 226;        //紫罗兰
        ys[10].r = 255; ys[10].g = 255; ys[10].b = 255;    //白
        ys[11].r = 255; ys[11].g = 127; ys[11].b = 80;     //珊瑚红
        ys[12].r = 210; ys[12].g = 180; ys[12].b = 140;    //灰褐色

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        GetCursorPos(&mouse_start);
        mouse_is_down = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1MouseUp(TObject *Sender, TMouseButton Button,
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

void __fastcall TForm2::Image1MouseMove(TObject *Sender, TShiftState Shift,
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


void  __fastcall TForm2::change_color()
{
                Image1->Height = HANG;
                Image1->Width = LIE;
                int r=0,g=0,b=0;
                unsigned short int *data;
                data = (unsigned short int *)malloc(sizeof(int)*X);
                FILE *ffp;
                ffp = fopen(ADDRESS.c_str(),"rb");
                if(ffp==NULL)
                {
                        Memo1->Lines->Append("error!!");
                        return ;
                }
                int tp[I_D];
                for(int i=0 ; i<D ; i++)
                tp[i] = vvv[i].f.size();
          for(int ii=0 ; ii<HANG ; ii++)
          {
               for(int jj=0 ; jj<LIE ; jj++)
               {
                        int i;
                        for(i=0 ; i<D ; i++)
                	{
	                     // printf("*********************************************\n");
                              int bingo = 1;
		              for(int j=0 ; j<tp[i] ; j++)
		              {
		           //    	printf("***********%d\n",vvv[i].ff[j]);
	        	   //     	printf("fat:%d\tthin:%d\tfat_plus:%d\tthin_plus:%d\tyu:%d\n",vvv[i].f[j].fat,vvv[i].f[j].thin,vvv[i].f[j].fat_plus,vvv[i].f[j].thin_plus,vvv[i].f[j].yu);
                                        if(vvv[i].f[j].flag == -1)
                                        {
                                                if(vvv[i].ff[j]<0)
                                                {
                                                        if(Form3->picture[ii][jj].data[vvv[i].f[j].fat]<=vvv[i].f[j].yu)
                                                        continue;
                                                        else
                                                        {
                                                                bingo = 0;
                                                                break;
                                                        }
                                                }
                                                else
                                                {
                                                        if(Form3->picture[ii][jj].data[vvv[i].f[j].fat]>vvv[i].f[j].yu)
                                                        continue;
                                                        else
                                                        {
                                                                bingo = 0;
                                                                break;
                                                        }
                                                }
                                        }
                                        else if(vvv[i].f[j].flag==0)
                                        {                                
                                                if(vvv[i].ff[j]<0)
                                                {
                                                        if(Form3->picture[ii][jj].data[vvv[i].f[j].fat] - Form3->picture[ii][jj].data[vvv[i].f[j].thin]<=vvv[i].f[j].yu)
                                                        continue;
                                                        else
                                                        {
                                                                bingo = 0;
                                                                break;
                                                        }
                                                }
                                                else
                                                {
                                                        if(Form3->picture[ii][jj].data[vvv[i].f[j].fat] - Form3->picture[ii][jj].data[vvv[i].f[j].thin]>vvv[i].f[j].yu)
                                                        continue;
                                                        else
                                                        {
                                                                bingo = 0;
                                                                break;
                                                        }
                                                }
                                        }
                              }
                              if(bingo)
                              break;
                	}
                        r=ys[i+5].r;
                        g=ys[i+5].g;
                        b=ys[i+5].b;   
                        Form3->picture[ii][jj].type = i+1;
                        Image1->Canvas->Pixels[jj][ii]
                        =Graphics::TColor(RGB(r,g,b));
                        TXT1 += i;
                }
        }
        fclose(ffp);
}
void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
        if(Form2->Height == 651)
        {
                Form2->Height = 750;
                BitBtn1->Caption = "隐藏规则▲";
                BitBtn1->Top = 590+Memo1->Height;
                Memo1->Top = 600;
        }
        else
        {
                Form2->Height = 651;
                BitBtn1->Caption = "显示规则▼";
                BitBtn1->Top = 600;
                Memo1->Top = 600;
        }


}
//---------------------------------------------------------------------------
                             
void __fastcall TForm2::select_from_SQL(String str)
{
        String select_str = "select * from dbo.G_sample where 实验编号 = " + str;
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(select_str);
        ADOQuery1->Open();
        String ssr[10] = {"1","2","3","4","5","6","7","8","9","10"};
        Memo1->Clear();
        for(int i=0 ; i<D ; i++)
        {
                String s = ADOQuery1->FieldByName("rule_"+ssr[i])->Value;
                stringg[i] = s;
                address[i] = ADOQuery1->FieldByName("Ground_"+ssr[i])->Value;
                Memo1->Lines->Append(s);
        }
}

