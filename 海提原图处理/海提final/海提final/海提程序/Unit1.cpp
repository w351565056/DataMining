//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#pragma hdrstop
 #include<math.h>
#include "Unit1.h"
#include "Unit2.h"
#include <stdlib.h>
#define OVERFLOW -2
#define INIT_SIZE 10000 //存储空间初始分配量
#define INCREMENT 10  //存储空间分配增量
//static int LINE;         //全局变量行值
//static int SAMPLE;        //全局变量列值
//static int bonum;          //全局变量波段数

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
AnsiString storefile;//用来存放文件路径

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(OpenDialog1->Execute())
                storefile=OpenDialog1->FileName;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
  switch(ComboBox1->ItemIndex)
  {
   case 0: r1=0 ;break;
   case 1: r1=1 ;break;
   case 2: r1=2 ;break;
   case 3: r1=3 ;break;
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
 switch(ComboBox2->ItemIndex)
  {
   case 0: g1=0 ;break;
   case 1: g1=1 ;break;
   case 2: g1=2 ;break;
   case 3: g1=3 ;break;
   }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox3Change(TObject *Sender)
{
  switch(ComboBox3->ItemIndex)
  {
   case 0: b1=0 ;break;
   case 1: b1=1 ;break;
   case 2: b1=2 ;break;
   case 3: b1=3 ;break;
  }
}

//---------------------------------------------------------------------------
//行值输入
void __fastcall TForm1::Edit1Change(TObject *Sender)
{

        //int a =  StrToInt(Edit1->Text);
        if(Edit1->Text == ""){
                LINE = 0;
        }
        else{
        LINE = StrToInt(Edit1->Text);
        //LINE /= 2;
        }

}

//---------------------------------------------------------------------------
//列值
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        //int a =  StrToInt(Edit2->Text);
        if(Edit2->Text == ""){
                SAMPLE = 0;
        }

        else{
        SAMPLE = StrToInt(Edit2->Text);
        //SAMPLE /= 2;
        }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edit3Change(TObject *Sender)
{
               //获取数据文件中每个点的波段个数
        //int a =  StrToInt(Edit3->Text);
        if(Edit3->Text == ""){
                bonum = 0;
        }
        else
        bonum = StrToInt(Edit3->Text);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        if(LINE <= 0){
                MessageBox(NULL,"行值必须是正整数！请重新输入行值。", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"列值必须是正整数！请重新输入列值。", "Error",MB_ICONERROR);
        }
        if(bonum <= 3){
                MessageBox(NULL,"波段数必须大于3！请重新输入波段数。", "Error",MB_ICONERROR);
        }
int count1=0;//用来计算绘图位置
int offset=SAMPLE*bonum*2-bonum*2;//1996列*8字节-读取的16字节 //缩小后为998*2*8-16
int r,g,b;//用来储存RGB

FILE *fp;//定义文件指针
unsigned short int idata[20];//用来读取本行数据
unsigned short int idatanext[20];//用来读取下行数据
name=storefile;


fp=fopen(name.c_str(),"rb");//打开文件
if(fp!=NULL)
 {
  while(!feof(fp))//循环一直到文件读取完毕
   {
    fread(idata,2,bonum,fp);//读取本行数据储存在idata[]中
    //fseek(fp,offset,1);  //调整指针到下一行
    //fread(idatanext,2,bonum,fp);// 读取调整指针后的这一行数据
    //if(count1%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
    //fseek(fp,-(offset+bonum*2),1);//将指针调回上一行并退回到上一次读取的位置

    count1++;
    r=idata[r1]/3.2;
    g=idata[g1]/3.2;
    b=idata[b1]/3.2;
    //将读取出本行和下一行的共16个数据每相邻的四个一组求平均值作为RGB输出到image，以实现图像缩小或者说压缩    //if(r>10&&r<27&&g>30&&g<85&&b<82&&b>40)
    Form2->Image1->Canvas->Pixels[(count1-1)%SAMPLE][count1/SAMPLE]
        =Graphics::TColor(RGB(r,g,b));//将图像输出到image

    }
    fclose(fp);//关闭文件
 }

 Form2->Label5->Caption=ComboBox1->Text;//R
 Form2->Label15->Caption=ComboBox2->Text;//G
 Form2->Label17->Caption=ComboBox3->Text;//B
 Form2->Label6->Caption=LINE;//行值
 Form2->Label7->Caption=SAMPLE; //列值
 Form2->Label8->Caption=Edit3->Text; //波段
 Form2->Label13->Caption=storefile;
 Form2->Show();

}
//---------------------------------------------------------------------------
