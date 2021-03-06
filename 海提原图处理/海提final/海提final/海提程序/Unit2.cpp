//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<stdio.h>
#include<math.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include <stdlib.h>
#define OVERFLOW -2
#define INIT_SIZE 10000 //存储空间初始分配量
#define INCREMENT 10  //存储空间分配增量
static int LINE;        //全局变量行值
static int SAMPLE;       //全局变量列值
static int bonum;          //全局变量波段数
int min;
int max;
float tcon;

//边缘点判断所需形参
typedef struct{
         int r; //迷宫中r行c列的位置             //!!!!!!敲黑板！！因为读取输出像素点是xy格式的，所以maze.adr[列值][行值]
         int c;
}PostType;

typedef struct{
         PostType seat;//当前坐标
         int  di;       //往下一坐标的方向
}SElemType;       //栈内元素类型

typedef struct{
         SElemType* base;
         SElemType* top;
         int stackSize;
}Stack;             //栈类型

void InitStack(Stack &S){  //构造空栈S
         S.base=(SElemType*)malloc(INIT_SIZE *sizeof(SElemType));
         if(!S.base)
                   exit(OVERFLOW);//存储分配失败
         S.top=S.base;
         S.stackSize=INIT_SIZE;

}

int StackEmpty(Stack S){  //判断空栈
         if(S.top==S.base)
           return 1;
           return 0;
}

void Push(Stack &S,SElemType e){//入栈
         if(S.top-S.base >=S.stackSize){//栈满，加空间
                   S.base=(SElemType *)realloc(S.base,(S.stackSize+INCREMENT)*sizeof(SElemType));
                   if(!S.base)
                            exit(OVERFLOW);   //存储分配失败
                            S.top=S.base+S.stackSize;
                            S.stackSize+=INCREMENT;
         }
         *S.top++=e;

}

int Pop(Stack &S,SElemType &e){//出栈
         if(S.top==S.base)
           return 0;
           e=*--S.top;
		return 1;
}

typedef struct{
         int r;
         int c;
         char adr[2000][2000];
}MazeType;   //迷宫类型

MazeType maze;          //定义全局自定义变量迷宫maze
MazeType addup;
void FootPrint(MazeType &maze,PostType curpos)//标记
{
         maze.adr[curpos.r][curpos.c]='%';
}

PostType NextPos(PostType &curpos,int i){
//探索下一位置并返回下一位置(cpos)的坐标
         PostType cpos;
         cpos=curpos;
         switch(i){        //1.2.3分别表示右、下、左、上方向
                   case 1 : cpos.r+=1; break;
                   case 2 : cpos.c+=1; break;
                   case 4 : cpos.c-=1; break;
                   case 3 : cpos.r-=1; break;
                   default: exit(0);
         }
         return cpos;
}

//根据大小判断的方法：MazePath
int MazePath(MazeType &maze,PostType start,MazeType &addup){
         Stack S;
         PostType curpos;
         int area=0;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
         do{
             if(maze.adr[curpos.r][curpos.c]=='1')
                {     //当前位置可以通过,
                 FootPrint(maze,curpos);
				 area++;//留下足迹
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));

         if(area>min&&area<max){
                 curpos=start;
         do{
             if(maze.adr[curpos.r][curpos.c]=='%')
             {     //当前位置可以通过,
                  maze.adr[curpos.r][curpos.c]='*';
                  addup.adr[curpos.r][curpos.c]='1';
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));
		 }
  else
  {
      curpos=start;
      do{
             if(maze.adr[curpos.r][curpos.c]=='%')
			 {     //当前位置可以通过,
                  maze.adr[curpos.r][curpos.c]='0';
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));
  }
	 return area;
}

// 根据形状进行二次判断

void sFootPrint(MazeType &maze,PostType curpos) //标记
{
         maze.adr[curpos.r][curpos.c]='#';
}

int scount(MazeType &maze,PostType curpos){
	int count = 0;
	if(maze.adr[curpos.r+1][curpos.c]=='*')
		count++;
	if(maze.adr[curpos.r-1][curpos.c]=='*')
		count++;
	if(maze.adr[curpos.r][curpos.c+1]=='*')
		count++;
	if(maze.adr[curpos.r][curpos.c-1]=='*')
		count++;
	return count;
}

int side,point,sleft,plane;
int tplane;
float con;
//side为斑块的边数，point为斑块中点的数量，
//sbase为点数为point时内部面最多的形状的最大正方形一边的点数
//sleft为减去最大正方形剩下的点
//plane是该斑块点数能构成构成最大内部面数，tplane是该斑块的内部面数
//con是斑块所含有的内部面数除以最大内部面数的紧密度

int planes(int a){      //求最大内部面数量的方法，输入的数据为斑块的点数
	int splane=0;
	int sbase;
	int scan;
	sbase = (int)sqrt(a)+1;
	scan = (int)point/sbase;
	if(point%sbase != 0)
        {
		splane = (sbase-1)*(scan-1)+point%sbase-1;
	}
	if(point%sbase == 0)
        {
		splane = (sbase-1)*(scan-1);
	}
	return splane;
}

float shape(MazeType &maze,PostType start,MazeType &addup){
         Stack S;
         PostType curpos;
         int curstep = 1;
         side = 0;
         point = 0;
         con = 0.000;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
         do{
             if(maze.adr[curpos.r][curpos.c]=='*')
                {     //当前位置可以通过
                 sFootPrint(maze,curpos);
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 point++;
                 side+=scount(maze,curpos);
                 curpos=NextPos(curpos,1);  //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }
         }while(!StackEmpty(S));
		 tplane = side-point+1;
		 plane = planes(point);
		 con = (float)tplane/plane;
         if(con>tcon){
                 curpos=start;

         do{
             if(maze.adr[curpos.r][curpos.c]=='#')
             {     //当前位置可以通过
                  maze.adr[curpos.r][curpos.c]='y';
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));
		 }
  else
  {
      curpos=start;
      double summ=0;
                         for(int a=curpos.r;a<curpos.r+80;a++){  //行/2的十四分之一左右
                          for(int b=curpos.c;b<curpos.c+100;b++){ //列/2的二十分之一左右
                           if(addup.adr[a][b]=='1'){
                            summ++;
                           }
                          }
                         }
                         if((summ/(8000))>0.5){ //占比达到50% 以上，说明该处为斑块群。
                               do{
             if(maze.adr[curpos.r][curpos.c]=='#')
			 {     //当前位置可以通过,
                  maze.adr[curpos.r][curpos.c]='y';
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));
                         } //if(summ)
      do{
             if(maze.adr[curpos.r][curpos.c]=='#')
			 {     //当前位置可以通过,
                  maze.adr[curpos.r][curpos.c]='0';
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径
                 curpos=NextPos(curpos,1); //下一位置是当前位置的东邻
                   }
                   else{        //当前位置不通
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di < 4){
                                e.di++;//换下一个方向探索
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }

         }while(!StackEmpty(S));
  }
  return con;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1Change(TObject *Sender)
{
     //int a = StrToInt(Edit1->Text);
     
     if(Edit1->Text=="")
     min=0;
     else{
     min=StrToInt(Edit1->Text);
     }

}

//---------------------------------------------------------------------------
void __fastcall TForm2::Edit2Change(TObject *Sender)
{
    // int a = StrToInt(Edit2->Text);

     if(Edit2->Text=="")
     max=0;
     else
     max=StrToInt(Edit2->Text);


}

//---------------------------------------------------------------------------
void __fastcall TForm2::Edit3Change(TObject *Sender)
{
     //float a = StrToFloat(Edit3->Text);


     if(Edit3->Text=="")
     tcon=0;
     else
     tcon=StrToFloat(Edit3->Text);

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
   if(min < 0)
     {
        MessageBox(NULL,"面积下界必须是正整数！请重新输入。", "Error",MB_ICONERROR);
     }
     if(max < 0)
     {
        MessageBox(NULL,"面积上界必须是正整数！请重新输入。", "Error",MB_ICONERROR);
     }
     if(tcon < 0||tcon > 1){
        MessageBox(NULL,"0<=紧密度<=1！请重新输入。", "Error",MB_ICONERROR);
     }
   LINE=Form1->LINE;
   SAMPLE=Form1->SAMPLE;
   int r1,b1,g1;
   r1=Form1->r1;
   g1=Form1->g1;
   b1=Form1->b1;
   bonum=Form1->bonum;
   Form3->Image1->Canvas->FloodFill(0,0,clYellow,fsBorder);
   int count=0,count1=0;
   int offset=SAMPLE*bonum*2-bonum*2;//1996列*8字节-读取的16字节
   int r,g,b,a;
   FILE *fp;
   unsigned short int idata[20];//用来读取本行数据
   unsigned short int idatanext[20];//用来读取下行数据
   AnsiString name;
   name=Form1->name;
   maze.r=SAMPLE;maze.c=LINE;
   fp=fopen(name.c_str(),"rb");//打开文件
   if(fp!=NULL)
 {
  while(!feof(fp))
   {
    fread(idata,2,bonum,fp);//读取数据储存在idata[]中
    //fseek(fp,offset,1);  //调整指针到下一行
    //fread(idatanext,2,bonum*2,fp);// 读取调整指针后的这一行数据
    //if(count%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
    //fseek(fp,-(offset+bonum*4),1);//将指针调回上一行并退回到上一次读取的位置

    count++;
    r=idata[r1]/3.2;
    g=idata[g1]/3.2;
    b=idata[b1]/3.2;
    if(r<27&&r>10&&b>40&&b<82&&g>30&&g<85)
          maze.adr[(count-1)%SAMPLE][count/SAMPLE]='1';
          else
          maze.adr[(count-1)%SAMPLE][count/SAMPLE]='0';
      }
       fclose(fp);
    }


    PostType start;
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[j][i]=='1'){
	          start.r=j;start.c=i;
                  MazePath(maze,start,addup);
			}
		    }
		 }
    //输出矢量二进制文件
     /*if(Edit4->Text == "")
        {
                MessageBox(NULL,"请选择矢量文件路径！", "Error",MB_ICONERROR);
        }
        FILE *fptwo;
        char ac=1,bc=0;
        fptwo=fopen(Edit4->Text.c_str(),"wb");//打开文件
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]=='*')
                        fwrite(&ac,1,1,fptwo);
                        else
                        fwrite(&bc,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"成功生成二进制矢量文件！请在对应文件查看。", "Message",MB_ICONASTERISK);
          */

    for(int k=0;k<LINE;k++){
        for(int l=0;l<SAMPLE;l++){
                if(maze.adr[l][k]=='*'){
                        start.r=l;
                        start.c=k;
                        shape(maze,start,addup);
                }
        }
    }

    //输出矢量二进制文件
     /*if(Edit4->Text == "")
        {
                MessageBox(NULL,"请选择矢量文件路径！", "Error",MB_ICONERROR);
        }
        FILE *fptwo;
        char ac=1,bc=0;
        fptwo=fopen(Edit4->Text.c_str(),"wb");//打开文件
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]=='y')
                        fwrite(&ac,1,1,fptwo);
                        else
                        fwrite(&bc,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"成功生成二进制矢量文件！请在对应文件查看。", "Message",MB_ICONASTERISK);
         */
fp=fopen(name.c_str(),"rb");//打开文件
if(fp!=NULL)
 {
  while(!feof(fp))
   {
    fread(idata,2,bonum,fp);//读取本行数据储存在idata[]中
    /*fseek(fp,offset,1);  //调整指针到下一行
    fread(idatanext,2,bonum,fp);// 读取调整指针后的这一行数据
    if(count1%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
    fseek(fp,-(offset+bonum*4),1);//将指针调回上一行并退回到上一次读取的位置
    */
    count1++;
    r=idata[r1]/3.2;
    g=idata[g1]/3.2;
    b=idata[b1]/3.2;
  if(maze.adr[(count1-1)%SAMPLE][count1/SAMPLE]=='y')
    Form3->Image1->Canvas->Pixels[(count1-1)%SAMPLE][count1/SAMPLE]
        =Graphics::TColor(RGB(r,g,b));
    }

    fclose(fp);
 }
 
 Form3->Label13->Caption=name;
 Form3->Label14->Caption=r1;
 Form3->Label15->Caption=g1;
 Form3->Label16->Caption=b1;
 Form3->Label17->Caption=Form1->LINE;
 Form3->Label19->Caption=Form1->SAMPLE;
 Form3->Label21->Caption=bonum;
 Form3->Label4->Caption=Edit1->Text;
 Form3->Label5->Caption=Edit2->Text;
 Form3->Label6->Caption=Edit3->Text;
 Form3->Show();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
        /*if(OpenDialog1->Execute()){
                Edit4->Text = OpenDialog1->FileName;
        }  */
}
//---------------------------------------------------------------------------
