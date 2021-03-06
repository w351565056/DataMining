
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<stdio.h>
#include<math.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include <stdlib.h>
#define OVERFLOW -2
#define INIT_SIZE 10000 //存储空间初始分配量
#define INCREMENT 10  //存储空间分配增量

static int SAMPLE,LINE;
static int bonum;          //全局变量波段数
static int min;
static int max;
static float tcon;
int r1,g1,b1;//用来改变显示遥感图像的波段

//存入shp格式文件所需变量
AnsiString named;
AnsiString name3;
AnsiString nameshp;
AnsiString nameshx;
AnsiString namedbf;
AnsiString namep;
AnsiString namex;
AnsiString namef;

static int blankr;            //用户输入的空缺度上限
int mazeunion[2000][2000]; //用于标记邻接斑块的maze
int cgap[2000][2000];	//用于标记斑块间空白点的maze
int gap[2000][2000];            //用于标记所有符合要求的空白像素点
int anarea[10];		//用于存入邻接斑块的面积
int blank[10];		//用于存入与第n个邻接斑块间的空白像素点数量的数组

static double Xmin,Xmax,Ymin,Ymax;//shp文件所需的边界值
static double Xminn,Yminn,Xmaxx,Ymaxx;
static double beginX=117.22305734,beginY=38.87130808,offsetX=6.5049860000e-005,offsetY=-5.0974060000e-005;
static int sumturnpoint=0;//总点数（shp用）
static int turnpoint=0;//当前转折点数目（shp用）

typedef struct{
         int r; //迷宫中r行c列的位置
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
void FootPrint(MazeType &maze,PostType curpos){//标记
         maze.adr[curpos.r][curpos.c]='%';
}

PostType NextPos(PostType &curpos,int i){
//探索下一位置并返回下一位置(cpos)的坐标
         PostType cpos;
         cpos=curpos;
         switch(i){        //1.2.3分别表示右、下、左、上方向
                   case 1: cpos.r+=1; break;
                   case 2: cpos.c+=1; break;
                   case 4: cpos.c-=1; break;
                   case 3: cpos.r-=1; break;
                   default: exit(0);
         }
         return cpos;
}

//寻找连续边缘点方法RoundPos（在一个点以向上为起始方向顺时针寻找）
PostType RoundPos(PostType &curpos,int i){
//探索下一位置并返回下一位置(cpos)的坐标
         PostType cpos;
         cpos=curpos;
         switch(i){
                   case 7: if(cpos.c>0)
                                cpos.c-=1;
                            break;//上
                   case 8: if(cpos.c>0&&cpos.r<SAMPLE-1)                                {cpos.c-=1;cpos.r+=1;}
                           break;//右上
                   case 1: if(cpos.r<SAMPLE-1)
                                cpos.r+=1;
                           break;//右
                   case 2: if(cpos.r<SAMPLE-1&&cpos.c<LINE-1){                                cpos.r+=1;cpos.c+=1;}
                            break; //右下
                   case 3: if(cpos.c<LINE-1){
                                cpos.c+=1;}
                            break;//下
                   case 4: if(cpos.c<LINE-1&&cpos.r>0){                                cpos.c+=1;cpos.r-=1;}
                           break;//左下
                   case 5: if(cpos.r>0){
                                cpos.r-=1;}
                           break;//左
                   case 6: if(cpos.r>0&&cpos.c>0){
                                cpos.r-=1;cpos.c-=1; }
                           break; //左上
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

void sFootPrint(MazeType &maze,PostType curpos)//标记
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
	if(point%sbase != 0){
		splane = (sbase-1)*(scan-1)+point%sbase-1;
	}
	if(point%sbase == 0){
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

typedef struct edge {   //shp
    double num,num1;
    struct edge *Prior,*Next;
}LNode,*LinkList;

//边缘点判定
int edge(MazeType &maze,int x,int y){
	if(x==0||y==0||x==SAMPLE-1||y==LINE-1) return 1;//图片的边缘点判定
	if(maze.adr[x-1][y] == '0') return 1;
	if(maze.adr[x+1][y] == '0') return 1;
	if(maze.adr[x][y+1] == '0') return 1;
	if(maze.adr[x][y-1] == '0') return 1;
	return 0;
}

int ePass(MazeType &maze,PostType curpos){
//判断当前位置是否可通
         if(maze.adr[curpos.r][curpos.c]=='y')//可通
                  return 1;
          return 0;
}

void eFootPrint(MazeType &maze,PostType curpos){//标记
         maze.adr[curpos.r][curpos.c]='6';
}

//提取出斑块边缘点方法 
LinkList MazeEdge(MazeType &maze,PostType start){

        int i;
        int counts=0;
        LNode *p1,*p2,*head,*p3;//shp
        head = (LinkList)malloc(sizeof(LNode));
        head->Prior = head;
        head->Next = head;
        p2 = head;
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
         Xmin=start.r;Ymin=start.c;  //shp
         Xmax=start.r;Ymax=start.c;   //shp
		 //探索第一步
         do{
             if(ePass(maze,curpos)&&edge(maze,curpos.r,curpos.c)){     //当前位置可以通过,
                // if(edge(maze,curpos.r,curpos.c)){
                 	if(curpos.r<Xmin)//shp
                        Xmin=curpos.r;

                        if(curpos.c<Ymin)
                        Ymin=curpos.c;

                        if(curpos.r>Xmax)
                 	Xmax=curpos.r;

                 	if(curpos.c>Ymax)
                 	Ymax=curpos.c;

                        counts++;

                        if(counts==1){
                    	head->num1=curpos.r;
                    	head->num=curpos.c;
                        }

                        if(counts!=1){
                 	 p1 = (LinkList)malloc(sizeof(LNode));
                 	 p1->num=curpos.c;
                         p1->num1=curpos.r;
                         p1->Prior=p2;
                         p1->Next=head;
                 	 p2->Next = p1;
                         head->Prior=p1;
                         p2 = p1;
                         }     //shp
                // }

                 eFootPrint(maze,curpos);//将遍历过的点标记为‘6’
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //加入路径           
                 curpos=RoundPos(curpos,1); //下一位置是当前位置的东邻
                   }

                   else{ //当前位置不通
                       if(!StackEmpty(S)){        
                           Pop(S,e);
                            if(e.di < 8){
                                e.di++;//换下一个方向探索
                                Push(S,e);            
                                curpos=RoundPos(e.seat,e.di);//设定当前位置是该新方向上的相
                                     }
                            }
                   }
		 
         }while(!StackEmpty(S));

         turnpoint=0;   //shp
         int acc=1;
          p3 = head;
                     do{

                      if((p3->num-1==head->num&&p3->num1==head->num1)||(p3->num1+1==head->num1&&p3->num-1==head->num)||(p3->num1-1==head->num1&&p3->num-1==head->num)){                        if(acc>3){
                         turnpoint=turnpoint+1;
                          break;
                          } else{
                              turnpoint=turnpoint+1;
                          }
                        }else{
			if(p3->num-p3->Prior->num!=p3->Next->num-p3->num||p3->num1-p3->Prior->num1!=p3->Next->num1-p3->num1){        	          turnpoint=turnpoint+1;

			        }
                        }

                           p3 = p3->Next;
                           acc=acc+1;


                         } while(p3!=head);//shp
    return head;

}

//位序转换函数 shp用
int ExChangeOrder(int input)
{
	int ret=0;
	int mask=0xff;
	int i;
	for(i=0;i<4;i++)
	{
		ret |=((input&(mask<<(i*8)))>>(i*8)&mask)<<((3-i)*8);
	}

	return ret;
}



//优化连接两斑块方法：以边缘点为圆心向四周寻找其他点
void markunion(MazeType &maze,int x,int y){
        int dx,dy;
        int yy,xx,x1,y1;
        for(dx=-blankr;dx<=blankr;dx++){
                for(dy=-blankr;dy<=blankr;dy++){
                        if(dx*dx+dy*dy<=blankr*blankr){
                                if(maze.adr[x+dx][y+dy]=='y'||maze.adr[x+dx][y+dy]=='b'){
                                        float xy=0.00;
                                        float yx=0.00;
                                        if(dy!=0){
                                                xy = (float)dx/dy;
                                        }
                                        if(dx!=0){
                                                yx = (float)dy/dx;
                                        }
                                        if(dx==0){
                                                if(dy<0){
                                                        for(int i=-1;i>dy;i--){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                                if(dy>0){
                                                        for(int i=1;i<dy;i++){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        if(dy==0){
                                                if(dx<0){
                                                        for(int i=-1;i>dx;i--){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                                if(dx>0){
                                                        for(int i=1;i<dx;i++){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        //dy/dx>1.00说明dy的增长比dx快，y增长1时x增长n可能经过多个斑块
                                        if(yx>1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy>1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==-dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy<-1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++) {
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(yx<-1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                }
                        }
                }
        }
}



//连接海水养殖区斑块方法!!!
void linkarea(MazeType &maze,PostType start){
		 Stack S;
         PostType curpos;
         int curstep=1;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
        do{
             if(maze.adr[curpos.r][curpos.c]=='y'){     //当前位置可以通过,
                 if(edge(maze,curpos.r,curpos.c)){
                 	markunion(maze,curpos.r,curpos.c);
                        }
                 maze.adr[curpos.r][curpos.c] = 'b';//将遍历过的点标记为'b'
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
//执行两遍合并方法尝试消除空白死角
void tmarkunion(MazeType &maze,int x,int y){
        int dx,dy;
        int yy,xx,x1,y1;
        int tblankr=blankr-1;
        for(dx=-tblankr;dx<=tblankr;dx++){
                for(dy=-tblankr;dy<=tblankr;dy++){
                        if(dx*dx+dy*dy<=tblankr*tblankr){
                                if(maze.adr[x+dx][y+dy]=='b'||maze.adr[x+dx][y+dy]=='c'){
                                        float xy=0.00;
                                        float yx=0.00;
                                        if(dy!=0){
                                                xy = (float)dx/dy;
                                        }
                                        if(dx!=0){
                                                yx = (float)dy/dx;
                                        }
                                        if(dx==0){
                                                if(dy<0){
                                                        for(int i=-1;i>dy;i--){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                                if(dy>0){
                                                        for(int i=1;i<dy;i++){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        if(dy==0){
                                                if(dx<0){
                                                        for(int i=-1;i>dx;i--){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                                if(dx>0){
                                                        for(int i=1;i<dx;i++){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        //dy/dx>1.00说明dy的增长比dx快，y增长1时x增长n可能经过多个斑块
                                        if(yx>1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy>1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==-dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy<-1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++) {
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(yx<-1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                }
                        }
                }
        }
}



//连接海水养殖区斑块方法!!!
void tlinkarea(MazeType &maze,PostType start){
		 Stack S;
         PostType curpos;
         int curstep=1;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
        do{
             if(maze.adr[curpos.r][curpos.c]=='b'){     //当前位置可以通过,
                 if(edge(maze,curpos.r,curpos.c)){
                 	tmarkunion(maze,curpos.r,curpos.c);
                        }
                 maze.adr[curpos.r][curpos.c] = 'c';//将遍历过的点标记为'b'
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
//第3遍合并方法尝试消除空白死角
void smarkunion(MazeType &maze,int x,int y){
        int dx,dy;
        int yy,xx,x1,y1;
        int sblankr=blankr-2;
        for(dx=-sblankr;dx<=sblankr;dx++){
                for(dy=-sblankr;dy<=sblankr;dy++){
                        if(dx*dx+dy*dy<=sblankr*sblankr){
                                if(maze.adr[x+dx][y+dy]=='c'||maze.adr[x+dx][y+dy]=='d'){
                                        float xy=0.00;
                                        float yx=0.00;
                                        if(dy!=0){
                                                xy = (float)dx/dy;
                                        }
                                        if(dx!=0){
                                                yx = (float)dy/dx;
                                        }
                                        if(dx==0){
                                                if(dy<0){
                                                        for(int i=-1;i>dy;i--){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                                if(dy>0){
                                                        for(int i=1;i<dy;i++){
                                                                if(maze.adr[x][y+i]=='0'){
                                                                        //maze.adr[x][y+i]='b';
                                                                        gap[x][y+i]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        if(dy==0){
                                                if(dx<0){
                                                        for(int i=-1;i>dx;i--){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                                if(dx>0){
                                                        for(int i=1;i<dx;i++){
                                                                if(maze.adr[x+i][y]=='0'){
                                                                        //maze.adr[x+i][y]='b';
                                                                        gap[x+i][y]=1;
                                                                }
                                                        }
                                                }
                                        }
                                        //dy/dx>1.00说明dy的增长比dx快，y增长1时x增长n可能经过多个斑块
                                        if(yx>1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy>1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){
                                                        if(maze.adr[x+i][y+i]=='0'){
                                                                //maze.adr[x+i][y+i]='b';
                                                                gap[x+i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(dx==-dy){
                                        if(dy<0){
                                                for(int i=-1;i>dy;i--){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                for(int i=1;i<dy;i++){

                                                        if(maze.adr[x-i][y+i]=='0'){
                                                                //maze.adr[x-i][y+i]='b';
                                                                gap[x-i][y+i]=1;
                                                        }
                                                }
                                        }
                                        }
                                        if(xy<-1.00){
                                        if(dx<0){
                                                y1=0;
                                                for(int i=-1;i>dx;i--){
                                                        yy = (int)((float)dy*i/dx+0.99);
                                                        for(int j=y1;j<=yy;j++) {
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        if(dx>0){
                                                y1=0;
                                                for(int i=1;i<dx;i++){
                                                        yy = (int)((float)dy*i/dx-0.99);
                                                        for(int j=y1;j>=yy;j--){
                                                        if(maze.adr[x+i][y+j]=='0'){
                                                                //maze.adr[x+i][yy]='b';
                                                                gap[x+i][y+j]=1;
                                                        }
                                                        y1=yy;
                                                        }
                                                }
                                        }
                                        }
                                        if(yx<-1.00){
                                        if(dy<0){
                                                x1=0;
                                                for(int i=-1;i>dy;i--){
                                                        xx = (int)((float)dx*i/dy+0.99);
                                                        for(int j=x1;j<=xx;j++){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        if(dy>0){
                                                x1=0;
                                                for(int i=1;i<dy;i++){
                                                        xx = (int)((float)dx*i/dy-0.99);
                                                        for(int j=x1;j>=xx;j--){
                                                        if(maze.adr[x+j][y+i]=='0'){
                                                                //maze.adr[xx][y+i]='b';
                                                                gap[x+j][y+i]=1;
                                                        }
                                                        x1=xx;
                                                        }
                                                }
                                        }
                                        }
                                }
                        }
                }
        }
}



//连接海水养殖区斑块方法!!!
void slinkarea(MazeType &maze,PostType start){
		 Stack S;
         PostType curpos;
         int curstep=1;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
        do{
             if(maze.adr[curpos.r][curpos.c]=='c'){     //当前位置可以通过,
                 if(edge(maze,curpos.r,curpos.c)){
                 	smarkunion(maze,curpos.r,curpos.c);
                        }
                 maze.adr[curpos.r][curpos.c] = 'd';//将遍历过的点标记为'b'
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
//二次处理时找到一个斑块中内的空白像素点并标记
void searchblank(MazeType &maze,int x,int y){		//返回
	PostType start;
	int current;
        if(x-1>0){
	if(maze.adr[x-1][y] == '0'){
		for(int i=2;i<2+blankr/2;i++){
			if(x-i<0) break;
			if(maze.adr[x-i][y] == 'b'||maze.adr[x-i][y] == 't'){
                        start.r = x-i;
                        start.c = y;
                       // bancount++;
                        for(int j=1;j<i;j++){
                                gap[x-j][y] = 1;
                                maze.adr[x-j][y] = 't';
                        }
                        break;
			}
		}
	}
        }
        if(x+1<SAMPLE-1){
                if(maze.adr[x+1][y] == '0'){
                        for(int i=2;i<2+blankr/2;i++){
                                if(x+i>SAMPLE-1) break;
                                if(maze.adr[x+i][y] == 'b'||maze.adr[x+i][y] == 't'){
                                        //start.r = x+i;
                                        //start.c = y;
                                        //bancount++;
                                        for(int j=1;j<i;j++){
                                                gap[x+j][y] = 1;
                                                maze.adr[x+j][y] = 't';
                                        }
                                }
                        }
                }
        }
        if(y-1>0){
	if(maze.adr[x][y-1] == '0'){
		for(int i=2;i<2+blankr/2;i++){
			if(y-i<0) break;
			if(maze.adr[x][y-i] == 'b'||maze.adr[x][y-i] == 't'){
                                //start.r = x;
                                //start.c = y-i;
                                //bancount++;
                                for(int j=1;j<i;j++){
                                        gap[x][y-j] = 1;
                                        maze.adr[x][y-j] = 't';
                                }
                                break;
			}
		}
	}
        }

        if(y+1<LINE-1){
                if(maze.adr[x][y+1] == '0'){
                        for(int i=2;i<2+blankr/2;i++){
                                if(y+i>LINE-1) break;
                                if(maze.adr[x][y+i] == 'b'||maze.adr[x][y+i] == 't'){
                                        //start.r = x;
                                        //start.c = y+i;
                                        //bancount++;
                                        for(int j=1;j<i;j++){
                                                gap[x][y+j] = 1;
                                                maze.adr[x][y+j] = 't';
                                        }
                                }
                        }
                }
        }

}

//二次处理合并斑块方法
void secondunion(MazeType &maze,PostType start){
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
         do{
             if(maze.adr[curpos.r][curpos.c]=='b')
                {     //当前位置可以通过,
                 maze.adr[curpos.r][curpos.c]='t';
                 searchblank(maze,curpos.r,curpos.c);
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
}

//三次处理时找到一个斑块中内的空白像素点并标记
void thirdblank(MazeType &maze,int x,int y){		//返回
	PostType start;
	int current;
        if(x-1>0){
	if(maze.adr[x-1][y] == '0'){
		for(int i=2;i<2+blankr/2;i++){
			if(x-i<0) break;
			if(maze.adr[x-i][y] == 't'||maze.adr[x-i][y] == 'c'){
                        start.r = x-i;
                        start.c = y;
                        //bancount++;
                        for(int j=1;j<i;j++){
                                gap[x-j][y] = 1;
                                maze.adr[x-j][y] = 'c';
                        }
                        break;
			}
		}
	}
        }
        if(x+1<SAMPLE-1){
                if(maze.adr[x+1][y] == '0'){
                        for(int i=2;i<2+blankr/2;i++){
                                if(x+i>SAMPLE-1) break;
                                if(maze.adr[x+i][y] == 't'||maze.adr[x+i][y] == 'c'){
                                        //start.r = x+i;
                                        //start.c = y;
                                        //bancount++;
                                        for(int j=1;j<i;j++){
                                                gap[x+j][y] = 1;
                                                maze.adr[x+j][y] = 'c';
                                        }
                                }
                        }
                }
        }

        if(y-1>0){
	if(maze.adr[x][y-1] == '0'){
		for(int i=2;i<2+blankr/2;i++){
			if(y-i<0) break;
			if(maze.adr[x][y-i] == 't'||maze.adr[x][y-i] == 'c'){
                                //start.r = x;
                                //start.c = y-i;
                                //bancount++;
                                for(int j=1;j<i;j++){
                                        gap[x][y-j] = 1;
                                        maze.adr[x][y-j] = 'c';
                                }
                                break;
			}
		}
	}
        }

        if(y+1<LINE-1){
                if(maze.adr[x][y+1] == '0'){
                        for(int i=2;i<2+blankr/2;i++){
                                if(y+i>LINE-1) break;
                                if(maze.adr[x][y+i] == 't'||maze.adr[x][y+i] == 'c'){
                                        //start.r = x;
                                        //start.c = y+i;
                                        //bancount++;
                                        for(int j=1;j<i;j++){
                                                gap[x][y+j] = 1;
                                                maze.adr[x][y+j] = 'c';
                                        }
                                }
                        }
                }
        }

}


//三次处理合并斑块方法
void thirdunion(MazeType &maze,PostType start){
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //设置"当前位置"为"入口位置"
		 //探索第一步
         do{
             if(maze.adr[curpos.r][curpos.c]=='t')
                {     //当前位置可以通过,
                 maze.adr[curpos.r][curpos.c]='c';
                 thirdblank(maze,curpos.r,curpos.c);
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
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender) //生成shp文件按钮
{
   r1=Form1->r1;
   g1=Form1->g1;
   b1=Form1->b1;
   LINE=Form1->LINE;
   SAMPLE=Form1->SAMPLE;
   bonum=Form1->bonum;
   Xminn=0;Yminn=0;Xmaxx=SAMPLE;Ymaxx=LINE;
   min=StrToInt(Label4->Caption);
   max=StrToInt(Label5->Caption);
   tcon=StrToFloat(Label6->Caption);
   int count=0;
   int offset1=SAMPLE*bonum*2-bonum*2;//1996列*8字节-读取的16字节
   int r,g,b,a;
   FILE *fp;
   unsigned short int idata[20];//用来读取本行数据
   unsigned short int idatanext[20];//用来读取下行数据
   AnsiString name1;
   name1=Label13->Caption;
   maze.r=SAMPLE;maze.c=LINE;
   fp=fopen(name1.c_str(),"rb");//打开文件
   if(fp!=NULL)
 {
  while(!feof(fp))
   {
    fread(idata,2,bonum,fp);//读取数据储存在idata[]中
    /*fseek(fp,offset1,1);  //调整指针到下一行
    fread(idatanext,2,bonum,fp);// 读取调整指针后的这一行数据
    if(count%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
    fseek(fp,-(offset1+bonum*2),1);//将指针调回上一行并退回到上一次读取的位置
      */
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

    for(int k=0;k<LINE;k++){
        for(int l=0;l<SAMPLE;l++){
                if(maze.adr[l][k]=='*'){
                        start.r=l;
                        start.c=k;
                        shape(maze,start,addup);
                }
        }
    }
     //提取图像数据至shapfile文件
    //写入头文件
    //FILE *fp1;
    //fp1=fopen("d:\\xiang.txt","w+");
    named = "d:\\";
    namep = ".shp";
    namex = ".shx";
    namef = ".dbf";

    nameshp = named + name3 + namep;
    nameshx = named + name3 + namex;
    namedbf = named + name3 + namef;

   FILE *fp2;
   //fp2=fopen("d:\\xiang.shp","wb+");
   fp2=fopen(nameshp.c_str(),"wb+");
   //写入FileCode
   int fileCode=ExChangeOrder(9994);
   fwrite(&fileCode,sizeof(int),1,fp2);
   fseek(fp2,24,SEEK_CUR);//跳过24个字节先写版本号，文件长度最后再写

   //写入版本号
   int version=1000;
   fwrite(&version,sizeof(int),1,fp2);
   //写入几何类型
   int shapeType=5;
   fwrite(&shapeType,sizeof(int),1,fp2);
   //写入坐标范围（待确定）

   Xminn=beginX+Xminn*offsetX;
   fwrite(&Xminn,sizeof(double),1,fp2);

   Yminn=beginY+Yminn*offsetY;
   fwrite(&Yminn,sizeof(double),1,fp2);

   Xmaxx=beginX+Xmaxx*offsetX;
   fwrite(&Xmaxx,sizeof(double),1,fp2);

   Ymaxx=beginY+Ymaxx*offsetY;
   fwrite(&Ymaxx,sizeof(double),1,fp2);
   //头文件结束

   //写入索引文件的头文件
   FILE *fp3;
   //fp3=fopen("d:\\xiang.shx","wb+");
   fp3=fopen(nameshx.c_str(),"wb+");
   //写入FileCode
   fwrite(&fileCode,sizeof(int),1,fp3);
   //跳过文件长度 先写版本号
   fseek(fp3,24,SEEK_CUR);


   //写入版本号
   fwrite(&version,sizeof(int),1,fp3);
   //写入几何类型
   fwrite(&shapeType,sizeof(int),1,fp3);
   //写入坐标范围（待确定）
   fwrite(&Xminn,sizeof(double),1,fp3);

   fwrite(&Yminn,sizeof(double),1,fp3);

   fwrite(&Xmaxx,sizeof(double),1,fp3);

   fwrite(&Ymaxx,sizeof(double),1,fp3);
   //头文件结束

   //从101位开始写入实体信息
   fseek(fp2,100,SEEK_SET);

   fseek(fp3,100,SEEK_SET);

   int offset,bigoffset;
   int lastlength=0;
         //提取出边缘点中的转折点并写入shp文件和shx文件
        LNode *p,*head;
        int num=0;//当前记录号和总记录号
        //PostType start;
   for(int k=0;k<LINE;k++){
        for(int l=0;l<SAMPLE;l++){
                if(maze.adr[l][k]=='y'&&edge(maze,l,k)){
                        start.r=l;
                        start.c=k;
                        num++;
                        head=MazeEdge(maze,start);
                        sumturnpoint=sumturnpoint+turnpoint;

                        //记录号
                        int recordNum=ExChangeOrder(num);
                        fwrite(&recordNum,sizeof(int),1,fp2);

                     //坐标记录长度（待确定）一个记录的内容长度是按16位字衡量的记录内容长度。每个记录因此为文件的总长度贡献（4＋内容长度）个16位字，正如文件头是24字节一样。
                     int contentLen,bigcontentLen;
                     contentLen=(48+turnpoint*2*8)/2;
                     bigcontentLen=ExChangeOrder(contentLen);
                     fwrite(&bigcontentLen,sizeof(int),1,fp2);

                     if(num==1)
                     {
                     offset=50;
                     bigoffset=ExChangeOrder(offset);
                     fwrite(&bigoffset,sizeof(int),1,fp3);  //索引文件里第一个记录的偏移量
                     fwrite(&bigcontentLen,sizeof(int),1,fp3); //索引文件里第一个记录的长度
                     }

                     else{
                     offset=offset+lastlength;
                     bigoffset= ExChangeOrder(offset);
                     fwrite(&bigoffset,sizeof(int),1,fp3);
                     fwrite(&bigcontentLen,sizeof(int),1,fp3);
                     }
                     lastlength=contentLen+4;

                    //几何类型
                    fwrite(&shapeType,sizeof(int),1,fp2);
   					
                    //坐标范围
                    Xmin=beginX+Xmin*offsetX;
                    fwrite(&Xmin,sizeof(double),1,fp2);

                    Ymin=beginY+Ymin*offsetY;
                    fwrite(&Ymin,sizeof(double),1,fp2);

                    Xmax=beginX+Xmax*offsetX;
                    fwrite(&Xmax,sizeof(double),1,fp2);

                    Ymax=beginY+Ymax*offsetY;
                    fwrite(&Ymax,sizeof(double),1,fp2);


                    //子线段个数
                    int numParts=1;
                    fwrite(&numParts,sizeof(int),1,fp2);
   					
                    //坐标点数
                    fwrite(&turnpoint,sizeof(int),1,fp2);

                    //Parts数组（每个子面的坐标在Points数组中的起始位置）
                    int Parts=0;
                    fwrite(&Parts,sizeof(int),1,fp2);
                    
                    //fprintf(fp1,"%d\n",num);
                    /*p=head;
                    do{
                      fprintf(fp1,"%lf,%lf\n",p->num1,p->num);
                      p=p->Next;
                    }while(p!=head);*/
                    //fprintf(fp1,"%d\n",turnpoint);

                    double changeNum1,changeNum;
                    int ac=1;
                         p = head;
                          do{
                         //判断下一个边缘点是不是起点
                         if((p->num-1==head->num&&p->num1==head->num1)||(p->num1+1==head->num1&&p->num-1==head->num)||(p->num1-1==head->num1&&p->num-1==head->num)){
                                  //是，封闭该图像
                                  if(ac>3){
                                  changeNum1=beginX+head->num1*offsetX;
                                  changeNum=beginY+head->num*offsetY;
				  fwrite(&changeNum1,sizeof(double),1,fp2);
				  fwrite(&changeNum,sizeof(double),1,fp2);
                                  break;
                                  }else{
                                  changeNum1=beginX+p->num1*offsetX;
                                  changeNum=beginY+p->num*offsetY;
				  fwrite(&changeNum1,sizeof(double),1,fp2);
				  fwrite(&changeNum,sizeof(double),1,fp2);
                                  }

                         }else{
                         //否，继续判断该点是不是转折点
                         if(p->num-p->Prior->num!=p->Next->num-p->num||p->num1-p->Prior->num1!=p->Next->num1-p->num1){
                                 //是，写入shp
                                  changeNum1=beginX+p->num1*offsetX;
                                  changeNum=beginY+p->num*offsetY;
				  fwrite(&changeNum1,sizeof(double),1,fp2);
				  fwrite(&changeNum,sizeof(double),1,fp2);


			        }


                         }

                           p = p->Next;
                           ac=ac+1;
    				}while(p!=head);

				 }
			 }
		 }

        //写入shp里的文件长度（待确定）文件长度的值是在16位字下文件的总长度（包括组成文件头的50个16位字）。
        fseek(fp2,24,SEEK_SET);
        int fileLength,bigfileLength;
        fileLength=(100+num*56+sumturnpoint*2*8)/2; //一个点记录两次所以sumpointturn要乘2
        bigfileLength=ExChangeOrder(fileLength);
        fwrite(&bigfileLength,sizeof(int),1,fp2);

        //写入shx里的文件长度（待确定）文件长度的值是在16位字下文件的总长度（包括组成文件头的50个16位字）。
        fseek(fp3,24,SEEK_SET);
        int shxfilelen,bigshxfilelen;
        shxfilelen=(100+num*8)/2;
        bigshxfilelen=ExChangeOrder(shxfilelen);
        fwrite(&bigshxfilelen,sizeof(int),1,fp3);

        //写dbf文件头
	FILE *fp4;
	//fp4=fopen("d:\\xiang.dbf","wb+");

        fp4=fopen(namedbf.c_str(),"wb+");
        //第0个字节为数据库类型
	int tempByte = 0x03;
	fwrite(&tempByte,1,1,fp4);
        //1至3字节为yymmdd
	int year=2017-1900;
	int mouth=5;
	int day=5;
	fwrite(&year,1,1,fp4);

	fwrite(&mouth,1,1,fp4);

	fwrite(&day,1,1,fp4);

	//第4到7个字节为行数
	fwrite(&num,4,1,fp4);

	//第8-9字节为文件头的长度
	int dbffilelen=32+32+1;//文件头32+1个字段定义信息32+16进制OD结尾1个字节
	fwrite(&dbffilelen,2,1,fp4);

	 //第10-11为每行数据所占长度 
	 int dbfdatalen=4+1;//字段长度加上每行开头默认20（表示空格）的1个字节
	 fwrite(&dbfdatalen,2,1,fp4);

	 //第12-31为保留字段，默认为0
         fseek(fp4,20,SEEK_CUR);

	 //开始写字段 
	 //0-10为记录项名称 
        int name='I';
        fwrite(&name,1,1,fp4);
        name='D';
        fwrite(&name,1,1,fp4);
        fseek(fp4,9,SEEK_CUR);

        //第11个字节为数据类型
        int dbftype='N';
        fwrite(&dbftype,1,1,fp4);

        //第12-15为保留字节
        fseek(fp4,4,SEEK_CUR);

        //第16个字节为字段长度
        int ziduanlen=4;
        fwrite(&ziduanlen,1,1,fp4);

        //接着第17-31都为保留字节
        fseek(fp4,15,SEEK_CUR);

        //最后以0D结尾
        tempByte = 0x0D;
        fwrite(&tempByte,1,1,fp4);
        
        //写入单元格数据
	 for(int i=49;i<num+49;i++){
	 	//每一行第一个字节默认为20
	 	tempByte = 0x20;
	 	fwrite(&tempByte,1,1,fp4);
	 	fwrite(&i,4,1,fp4);
	 }

	 tempByte = 0x1A;//该字节表示数据终止，不计入文件头与字段的大小中
         fwrite(&tempByte,1,1,fp4);

        //fclose(fp1);
    	fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        MessageBox(NULL,"成功生成shp格式文件！请在D盘查看。", "Message",MB_ICONASTERISK);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
   if(blankr <= 0)
        MessageBox(NULL,"空缺半径必须是正整数！请重新输入。", "Error",MB_ICONERROR);
   r1=Form1->r1;
   g1=Form1->g1;
   b1=Form1->b1;
   LINE=Form1->LINE;
   SAMPLE=Form1->SAMPLE;
   bonum=Form1->bonum;

   min=StrToInt(Label4->Caption);
   max=StrToInt(Label5->Caption);
   tcon=StrToFloat(Label6->Caption);
   
   int count=0,count1=0;
   int offset=SAMPLE*bonum*2-bonum*2;//1996列*8字节-读取的16字节
   int r,g,b,a;

   unsigned short int idata[20];//用来读取本行数据
   unsigned short int idatanext[20];//用来读取下行数据
   AnsiString name;
   name=Label13->Caption;
   maze.r=SAMPLE;maze.c=LINE;


   FILE *fp;
   fp=fopen(name.c_str(),"rb");//打开文件
   if(fp!=NULL)
 {
  while(!feof(fp))
   {
    fread(idata,2,bonum,fp);//读取数据储存在idata[]中
    /*fseek(fp,offset,1);  //调整指针到下一行
    fread(idatanext,2,bonum*2,fp);// 读取调整指针后的这一行数据
    if(count%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
    fseek(fp,-(offset+bonum*4),1);//将指针调回上一行并退回到上一次读取的位置
    */
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

    for(int k=0;k<LINE;k++){
        for(int l=0;l<SAMPLE;l++){
                if(maze.adr[l][k]=='*'){
                        start.r=l;
                        start.c=k;
                        shape(maze,start,addup);
                }
        }
    }
        //第三步：合并小斑块
    for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                gap[j][i]=0;
        }
    }

    for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(maze.adr[j][i]=='y'){
                        start.r = j;
                        start.c = i;
                        linkarea(maze,start);
                        }
                }
        }
    for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(gap[j][i]==1){
                        maze.adr[j][i]='b';
                }
        }
    }
    for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(maze.adr[j][i]=='b'){
                        start.r = j;
                        start.c = i;
                        tlinkarea(maze,start);
                        }
                }
        }
        for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(gap[j][i]==1){
                        maze.adr[j][i]='c';
                }
        }
    }
    for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(maze.adr[j][i]=='c'){
                        start.r = j;
                        start.c = i;
                        slinkarea(maze,start);
                        }
                }
        }

    FILE *fptwo;
        char ac=1,bc=0;
        fptwo=fopen("h://10","wb");//打开文件
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]=='d'||gap[j][i]==1)
                        fwrite(&ac,1,1,fptwo);
                        else
                        fwrite(&bc,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"成功生成二进制矢量文件！请在对应文件查看。", "Message",MB_ICONASTERISK);

     /*for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(maze.adr[j][i]=='b'){
                        start.r = j;
                        start.c = i;
                        secondunion(maze,start);
                }
        }
     }

     for(int i=0;i<LINE;i++){
        for(int j=0;j<SAMPLE;j++){
                if(maze.adr[j][i]=='t'){
                        start.r = j;
                        start.c = i;
                        thirdunion(maze,start);
                }
        }
     }
          */
     Form4->Label2->Caption=name;
     Form4->Label4->Caption=r1;
     Form4->Label6->Caption=g1;
     Form4->Label8->Caption=b1;
     Form4->Label10->Caption=Form1->LINE;
     Form4->Label12->Caption=Form1->SAMPLE;
     Form4->Label14->Caption=bonum;
     Form4->Label16->Caption=min;
     Form4->Label18->Caption=max;
     Form4->Label20->Caption=tcon;
     Form4->Label22->Caption=blankr;
     Form4->Show();

     fp=fopen(name.c_str(),"rb");//打开文件
        if(fp!=NULL)
        {
          while(!feof(fp))
           {
            fread(idata,2,bonum,fp);//读取本行数据储存在idata[]中
           /* fseek(fp,offset,1);  //调整指针到下一行
            fread(idatanext,2,bonum,fp);// 读取调整指针后的这一行数据
            
            if(count1%SAMPLE!=0)  //如果这一行数据读到头，要调到隔一行的那一行
            fseek(fp,-(offset+4*bonum),1);//将指针调回上一行并退回到上一次读取的位置
             */
            count1++;

            //if(maze.adr[(count1-1)%SAMPLE][count1/SAMPLE]=='b'){
                if(gap[(count1-1)%SAMPLE][count1/SAMPLE]==1){
                        Form4->Image1->Canvas->Pixels[(count1-1)%SAMPLE][count1/SAMPLE]
                        =Graphics::TColor(RGB(20,60,55));               //给符合要求标记过的空白像素点赋值折中的蓝色
                }

            if(maze.adr[(count1-1)%SAMPLE][count1/SAMPLE]=='d'){
                if(gap[(count1-1)%SAMPLE][count1/SAMPLE]!=1){
                        r=idata[r1]/3.2;
                        g=idata[g1]/3.2;
                        b=idata[b1]/3.2;
                        Form4->Image1->Canvas->Pixels[(count1-1)%SAMPLE][count1/SAMPLE]
                        =Graphics::TColor(RGB(r,g,b));
                }
            }
            }
            fclose(fp);
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm3::Edit1Change(TObject *Sender)
{
        
        if(Edit1->Text=="")
        blankr=0;
        else
        blankr=StrToInt(Edit1->Text);
}

//---------------------------------------------------------------------------


void __fastcall TForm3::Edit2Change(TObject *Sender)
{
        if(Edit2->Text == "")
        {
                MessageBox(NULL,"请输入文件名！", "Error",MB_ICONERROR);
        }else
        name3 = Edit2->Text;
}

//---------------------------------------------------------------------------

