//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
#include "Unit2.h"
#include <fstream>
#include <string.h>
#include<time.h>
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Memo2->Lines->Append("asdfasdfasdf\n232323");
        Edit1->SetTextBuf("");
        Edit2->SetTextBuf("1125");
        Edit3->SetTextBuf("1996");
        ComboBox1->SetTextBuf("");
        ComboBox2->SetTextBuf("4");
       // Form1->Height = 160;
        Form1->Left = 900;
        Memo1->SetTextBuf("");
        Panel4->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(OpenDialog1->Execute())
        {
             String str;
             str=OpenDialog1->FileName;
             Edit1->SetTextBuf(str.c_str());
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        //按钮按下，主页面信息传入从页面。
        if(Edit1->Text=="" || ComboBox2->Text=="" || Edit2->Text=="" || Edit3->Text=="" || ComboBox5->Text=="")
        {
                Application->MessageBoxA("信息填写不完整，请核对后重试","系统提示",MB_ICONWARNING);
                return;                        
        }
        Form3->ADDRESS = Edit1->Text;
        Form3->HANG = Edit2->Text.ToInt();
        Form3->LIE = Edit3->Text.ToInt();
        Form3->X_BODUAN = ComboBox2->Text.ToInt();
        Form3->MODEL = ComboBox5->Text;
        Memo2->Lines->Append(Form3->ADDRESS);
        Memo2->Lines->Append(Form3->HANG);
        Memo2->Lines->Append(Form3->LIE);
        Memo2->Lines->Append(Form3->X_BODUAN);
        Memo2->Lines->Append(Form3->MODEL);
      //  Label11->Visible = true;
        Form3->show_the_picture();
        Form3->Show();
    //    Label11->Visible = false;
   /*     Form1->Left = 1069;
        Form3->Left = 215 ;
        Form1->Height=900;
        Form1->Top=142; */
        BitBtn1->Enabled = true;
        Form3->Repaint();

//------------------------------------------------------------------------------
//开始绘图

}
//---------------------------------------------------------------------------










void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{ 
        Form2->ADDRESS = Edit1->Text;
        Form2->D = ComboBox1->Text.ToInt();
        Form2->X = ComboBox2->Text.ToInt();
        Form2->AMOUNT = ComboBox3->Text.ToInt();
        Form2->HANG = Edit2->Text.ToInt();
        Form2->LIE = Edit3->Text.ToInt();
        Form2->Image1->Height = Form2->HANG;
        Form2->Image1->Width = Form2->LIE;
        char * TXT = Form2->TXT1.c_str();
        if(Form2->TXT1 != "")
        {
                for(int i=0 ; i<Form2->HANG ; i++)
                {
                        for(int j=0 ; j<Edit3->Text.ToInt() ; j++)
                        {
                                int r= Form2->ys[TXT[i*(Form2->LIE) + j]-'0'+3].r;
                                int g= Form2->ys[TXT[i*(Form2->LIE) + j]-'0'+3].g;
                                int b= Form2->ys[TXT[i*(Form2->LIE) + j]-'0'+3].b;
                                Form2->Image1->Canvas->Pixels[j][i]
                                =Graphics::TColor(RGB(r,g,b));
                        }
                }
                Memo2->SetTextBuf("OK");
                Form2->Show();
                return ;
        }
        if(Form1->ComboBox1->Text == "" || Form1->ComboBox3->Text == "")
        {
                Application->MessageBoxA("信息填写不完整，请核对后重试","系统提示",MB_ICONWARNING);
                return;
        }
        String str[I_D] = {"一","二","三","四","五","六"};
        for(int i=0 ; i<ComboBox1->Text.ToInt() ; i++)
        {
                if(Form2->address[i] == "")
                {
                     String t_sr = "第"+str[i]+"类地物样本未录入，请核对后重试";
                     Application->MessageBoxA(t_sr.c_str(),"系统提示",MB_ICONWARNING);
                     return;
                }
        }
        Label9->Visible = false;
  //      Form2->Show();
        Form2->hanshu();
        Form2->Image1->Left = Form3->Image1->Left;
        Form2->Image1->Top = Form3->Image1->Top;
        Form2->Show();
//*******************************安排所有窗口位置***********************

        Form3->Top = 33;
        Form3->Left = 69;
        Form2->Top = 33;
        Form2->Left = 789;
        Form2->Repaint();
}
//---------------------------------------------------------------------------






void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
        if(ComboBox4->Text == "")
        {
                Application->MessageBoxA("“样本选择”不能为空！","系统提示",MB_ICONWARNING);
                return ;
        }
        if(OpenDialog1->Execute())
        {
                int x = ComboBox4->Text.ToInt();
                Edit4->SetTextBuf(OpenDialog1->FileName.c_str());
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{ 
        if(Edit4->Text=="")
        {
                Application->MessageBoxA("请选择保存路径！","系统提示",MB_ICONWARNING);
                return ;
        }
        int number = ComboBox4->Text.ToInt();
        if(Form2->address[number-1]!="")
        {
                int xxx = Application->MessageBoxA("该类样本已存在，确认将其覆盖？","系统提示",MB_YESNO);
                if(xxx==7)return ;
        }
        Form2->address[number-1] = Edit4->Text;
        String str[I_D] = {"一","二","三","四","五","六"};
        String ts = "第"+str[number-1]+"类地物样本已录入!";
        Label9->SetTextBuf(ts.c_str());
        Label9->Visible = true;
        ComboBox4->SetTextBuf("");
        Edit4->SetTextBuf("");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
        Panel1->Visible = false;
        Panel4->Visible = true;
        Panel4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
        Panel1->Visible = true;
        Panel1->Enabled = true;
        Panel4->Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button4Click(TObject *Sender)
{
        if(Form3->select_time==0)
        {
                Form3->select_time = 1;
                Button4->SetTextBuf("确认选择");
                Button5->Enabled = false;
                Button6->Enabled = false;
                Label11->Enabled = false;
                Edit5->Enabled = false;
        }
        else
        {
                Form3->select_time = 0;
                Button4->SetTextBuf("选择地物");
                Form3->select_to_red();
                Form3->select_point.clear();
                Memo1->SetTextBuf(str_int(Form3->amount_of_yb).c_str());
                Button5->Enabled = true;
                Button6->Enabled = true;
                Label11->Enabled = true;
                Edit5->Enabled = true;
        }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button5Click(TObject *Sender)
{
        if(ComboBox4->Text == "")
        {
                Application->MessageBoxA("“样本选择”不能为空！","系统提示",MB_ICONWARNING);
                return ;
        }
      if(SaveDialog1->Execute())
      {
      
            String file_str = SaveDialog1->FileName;
            if(FileExists(file_str.c_str()))
            {
                  Application->MessageBoxA("文件已存在！","系统提示",MB_ICONWARNING);
                  return ;
            }
            Edit5->SetTextBuf(file_str.c_str());
            int number = ComboBox4->Text.ToInt();
            ofstream fout(file_str.c_str());
            fout.close();
          //  FileCreate(file_str.c_str());

      }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
        if(ComboBox4->Text == "")
        {
                Application->MessageBoxA("“样本选择”不能为空！","系统提示",MB_ICONWARNING);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
        if(Edit5->Text=="")
        {
                Application->MessageBoxA("请选择保存路径！","系统提示",MB_ICONWARNING);
                return ;
        }
        String str[I_D] = {"一","二","三","四","五","六"};
        int number = ComboBox4->Text.ToInt();
        if(Form2->address[number-1]!="")
        {
                int xxx = Application->MessageBoxA("该类样本已存在，确认将其覆盖？","系统提示",MB_YESNO);
                if(xxx==7)return ;
        }
        Form2->address[number-1] = Edit5->Text;
        String ts = "第"+str[number-1]+"类地物样本已录入!";
        Label9->SetTextBuf(ts.c_str());
        Label9->Visible = true;
        //准备下一次样本选取
        Edit5->SetTextBuf("");
        Form3->back_to_photo();
        Form3->amount_of_yb = 0;
        Button5->Enabled = false;
        Label11->Enabled = false;
        Edit5->Enabled = false;
        Button6->Enabled = false;
        ComboBox4->SetTextBuf("");
        Memo1->SetTextBuf("");
        //将所选样本写入文件
        Form3->write_point_to_file(Form2->address[number-1]);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ComboBox3Change(TObject *Sender)
{
        Form3->D_YANGBEN = ComboBox3->Text.ToInt();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
                Form3->go_back();
                Form3->select_time = 0;
                Button4->SetTextBuf("选择地物");
                Form3->select_point.clear();
                Button5->Enabled = true;
                Button6->Enabled = true;
                Label11->Enabled = true;
                Edit5->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox4Change(TObject *Sender)
{
        Label9->Visible = false;        
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Button8Click(TObject *Sender)
{
        sea_v.clear();
       String ss="请确认信息：  您选择了  ";
       for(int i=0 ; i<CheckListBox1->Count ; i++)
       {
                if(CheckListBox1->Checked[i])
                {
                   sea_v.push_back(i+1);
                   ss+=1+i;
                   ss+="、";
                }
       }
       ss.Delete(ss.Length()-1,ss.Length()-1);
       ss+=" 地物为海洋地物";
       int Mxx = Application->MessageBox(ss.c_str(),"系统提示",MB_YESNO);
       if(Mxx==7)
       {
                sea_v.clear();
                return;
       }
       Button9->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{
        //设置Form4位置等
        int h =  Edit2->Text.ToInt();
        int w =  Edit3->Text.ToInt();
        Form4->HANG = h;
        Form4->LIE = w;
        Form4->Image1->Height = h;
        Form4->Image1->Width = w;
        Form4->Image1->Left = Form3->Image1->Left;
        Form4->Image1->Top = Form3->Image1->Top;
        Memo2->Lines->Append(h);
        Memo2->Lines->Append(w);
        //判断是否为数据库模式
        if(Form4->TXT2 != "")
        {
                char * st = Form4->TXT2.c_str();
                for(int i=0 ; i<h ; i++)
                {
                        for(int j=0 ; j<w ; j++)
                        {
                                if(st[i*w + j] == '1')
                                Form4->Image1->Canvas->Pixels[j][i]
                                =Graphics::TColor(RGB(0,0,0));
                                else
                                Form4->Image1->Canvas->Pixels[j][i]
                                =Graphics::TColor(RGB(255,255,255));

                        }
                }
                Form4->Show();
                return ;
        }
        //整体分成两类                   ······
        for(int i=1 ; i<h-1 ; i++)
       {
                for(int j=1 ; j<w-1 ; j++)
                {
                        Form3->picture[i][j].type = is_sea(i,j);
                }
       }
        //降噪
        int x_go[8] = {1,-1,0,0,1,1,-1,-1};
        int y_go[8] = {0,0,1,-1,1,-1,1,-1};
        int x1_go[24] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
        int y1_go[24] = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,1,2,-2,-1,0,1,2,-2,-1,0,1,2};
        int x2_go[48] = {-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3};
        int y2_go[48] = {-3,-2,-1,0,1,2,3,-3,-2,-1,0,1,2,3,-3,-2,-1,0,1,2,3,-3,-2,-1,1,2,3,-3,-2,-1,0,1,2,3,-3,-2,-1,0,1,2,3,-3,-2,-1,0,1,2,3};
        int x3_go[80] = {-4,-4,-4,-4,-4,-4,-4,-4,-4,-3,-3,-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4};
        int y3_go[80] = {-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,1,2,3,4,-4,-3,-2,-1,0,1,
2,3,4,-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,0,1,2,3,4,-4,-3,-2,-1,0,1,2,3,4};
        for(int time=1;time<=10;time++)
        {
                int flag=14;
                for(int i=2 ;i<Form3->HANG-2;i++)
                for(int j=2 ;j<Form3->LIE-2;j++)
                {
	                int x_,y_,f;
                        int diw[2] = {0,0};
	                for(int f=0 ; f<24 ; f++)
	                {
		                int x_ = i+x1_go[f];
		                int y_ = j+y1_go[f];
                                int number = Form3->picture[x_][y_].type;
		                diw[number]++;
		                if(diw[number]==flag)
		                {
			                Form3->picture[i][j].type = number;
		                }
	                }
                }
                for(int i=Form3->HANG-3 ;i>=2;i--)
                for(int j=Form3->LIE-3;j>=2 ;j--)
                {
	                int x_,y_,f;
                        int diw[2]={0,0};
                        memset(diw,0,sizeof(diw));
	                for(int f=0 ; f<24 ; f++)
	                {
		                int x_ = i+x1_go[f];
		                int y_ = j+y1_go[f];
                                int number = Form3->picture[x_][y_].type;
		                diw[number]++;
		                if(diw[number]==flag)
		                {
			                Form3->picture[i][j].type = number;
		                }
	                }
                }
        }

         //划线
       Form4->find_the_line();
       Form4->Show();
}
int __fastcall TForm1::check(int x,int y)
{
        int number_1 = 0;
        int number_2 = 0;
        int x_go[8] = {0,0,1,-1,1,1,-1,-1};
        int y_go[8] = {1,-1,0,0,1,-1,-1,1};
        number_1 = Form3->picture[x][y].type;
        if(number_1)
        {
                for(int i=0 ; i<8 ; i++)
                {
                        int xx = x+x_go[i];
                        int yy = y+y_go[i];
                        if(xx<0 || xx>=Form3->HANG) continue;
                        if(yy<0 || yy>=Form3->LIE)  continue;
                        number_2 = Form3->picture[xx][yy].type;
                        if(number_2 ==0) return 1;
                }
        }
        return 0;
}
int __fastcall TForm1::is_sea(int x,int y)
{
        int amount = sea_v.size();
        for(int i=0 ; i<amount ; i++)
        {
                if(Form3->picture[x][y].type == sea_v[i]) return 1;
        }
        return 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
        for(int i=0 ; i<Form3->HANG ; i++)
        {
                for(int j=0 ; j<Form3->LIE ; j++)
                {
                        int r = Form2->ys[Form3->picture[i][j].type+4].r;
                        int g = Form2->ys[Form3->picture[i][j].type+4].g;
                        int b = Form2->ys[Form3->picture[i][j].type+4].b;
                        Form2->Image1->Canvas->Pixels[j][i]
                        =Graphics::TColor(RGB(r,g,b));
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{
        Form5->Show();
        Form5->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{

//*******************************checklistbox元素添加*******************
        ComboBox4->Clear();
        CheckListBox1->Clear();
        int yybb = 1;
        for(int i=0 ; i<ComboBox1->Text.ToInt() ; i++)
        {
                ComboBox4->Items->Add(str_int(yybb));
                CheckListBox1->Items->Add(str_int(yybb));
                yybb++;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{            
        Form6->find();
        Form6->Show();
        Form6->Visible = true;
        Button9->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::In_SQL()
{
   ADOTable1->Open();
   ADOTable1->Append();
   ADOTable1->FieldValues["文件路径"] = Edit1->Text;
   ADOTable1->FieldValues["行数"] = Edit2->Text.ToInt();
   ADOTable1->FieldValues["列数"] = Edit3->Text.ToInt();
   ADOTable1->FieldValues["波段个数"] = ComboBox2->Text.ToInt();
   ADOTable1->FieldValues["图片格式"] = ComboBox5->Text;
   ADOTable1->FieldValues["样本个数"] = ComboBox3->Text.ToInt();
   ADOTable1->FieldValues["地物个数"] = ComboBox1->Text.ToInt();
   ADOTable1->FieldValues["区分地物"] = Form2->TXT1;
   ADOTable1->FieldValues["海岸线"] = Form4->TXT2;
   ADOTable1->Post();
   ADOTable1->Close();
}                                          
void __fastcall TForm1::select_from_SQL(String str)
{
        String select_str = "select * from dbo.history where 实验编号 = " + str;
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(select_str);
        ADOQuery1->Open();
        Edit1->Text = ADOQuery1->FieldByName("文件路径")->Value;
        Edit2->Text = ADOQuery1->FieldByName("行数")->Value;
        Edit3->Text = ADOQuery1->FieldByName("列数")->Value;
        ComboBox2->Text = ADOQuery1->FieldByName("波段个数")->Value;
        ComboBox5->Text = ADOQuery1->FieldByName("图片格式")->Value;
        ComboBox3->Text = ADOQuery1->FieldByName("样本个数")->Value;
        ComboBox1->Text = ADOQuery1->FieldByName("地物个数")->Value;
        Form2->TXT1 = ADOQuery1->FieldByName("区分地物")->Value;
        Form4->TXT2 = ADOQuery1->FieldByName("海岸线")->Value;
        //将Form3的对应数据传入
        Form3->ADDRESS = Edit1->Text;
        Form3->HANG = Edit2->Text.ToInt();
        Form3->LIE = Edit3->Text.ToInt();
        Form3->X_BODUAN = ComboBox2->Text.ToInt();
        Form3->MODEL = ComboBox5->Text;
        //将Form2的对应数据传入 
        Form2->ADDRESS = Edit1->Text;
        Form2->D = ComboBox1->Text.ToInt();
        Form2->X = ComboBox2->Text.ToInt();
        Form2->AMOUNT = ComboBox3->Text.ToInt();
        Form2->HANG = Edit2->Text.ToInt();
        Form2->LIE = Edit3->Text.ToInt();
        Form2->Image1->Height = Form2->HANG;
        Form2->Image1->Width = Form2->LIE; 
        Form2->Image1->Left = Form3->Image1->Left;
        Form2->Image1->Top = Form3->Image1->Top;
}






void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
        Panel1->Enabled = false;
        Panel4->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
        Form2->Close();
        Form3->Close();
        Form4->Close();
        Form5->Close();
        Form6->Close();
}
//---------------------------------------------------------------------------

