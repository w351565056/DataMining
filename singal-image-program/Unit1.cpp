//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>

#define INIT_SIZE 10000 //�洢�ռ��ʼ������
#define INCREMENT 10  //�洢�ռ��������
static int LINE;
static int SAMPLE;
static int nodeID;
static int toClass;
static int nowClass;
static int spoint;
static int file_type;
static AnsiString name;
static AnsiString netname;
static AnsiString outname;
static int node[2600][2600];
static int af[2600][2600];

//���ɽڵ������ļ��������
static int flag_max=0;
static AnsiString netoutname;
static int adjacent[1000][1000]={0}; //����ķ�ΧӦ�ô��ڵ������ֵ+5 ����������Ϊ���Ϊ1-4����
static int adjacent_right[1000][1000]={0};
static int sideNum=0;
FILE *fp5;



#include "Unit1.h"

//��Ե���ж������β�
typedef struct{
         int r; //�Թ���r��c�е�λ��             //!!!!!!�úڰ壡����Ϊ��ȡ������ص���xy��ʽ�ģ�����maze.adr[��ֵ][��ֵ]
         int c;
}PostType;

typedef struct{
         PostType seat;//��ǰ����
         int  di;       //����һ����ķ���
}SElemType;       //ջ��Ԫ������

typedef struct{
         SElemType* base;
         SElemType* top;
         int stackSize;
}Stack;             //ջ����

void InitStack(Stack &S){  //�����ջS
         S.base=(SElemType*)malloc(INIT_SIZE *sizeof(SElemType));
         if(!S.base)
                   exit(OVERFLOW);//�洢����ʧ��
         S.top=S.base;
         S.stackSize=INIT_SIZE;

}

int StackEmpty(Stack S){  //�жϿ�ջ
         if(S.top==S.base)
           return 1;
           return 0;
}

void Push(Stack &S,SElemType e){//��ջ
         if(S.top-S.base >=S.stackSize){//ջ�����ӿռ�
                   S.base=(SElemType *)realloc(S.base,(S.stackSize+INCREMENT)*sizeof(SElemType));
                   if(!S.base)
                            exit(OVERFLOW);   //�洢����ʧ��
                            S.top=S.base+S.stackSize;
                            S.stackSize+=INCREMENT;
         }
         *S.top++=e;

}

int Pop(Stack &S,SElemType &e){//��ջ
         if(S.top==S.base)
           return 0;
           e=*--S.top;
		return 1;
}

typedef struct{
         int r;
         int c;
         int adr[2600][2600];
}MazeType;   //�Թ�����

MazeType maze;          //����ȫ���Զ�������Թ�maze
MazeType maze1;
PostType NextPos(PostType &curpos,int i){
//̽����һλ�ò�������һλ��(cpos)������
         PostType cpos;
         cpos=curpos;
         switch(i){        //1.2.3�ֱ��ʾ�ҡ��¡����Ϸ���
                   case 1 : cpos.r+=1; break;
                   case 2 : cpos.c+=1; break;
                   case 4 : cpos.c-=1; break;
                   case 3 : cpos.r-=1; break;
                   default: exit(0);
         }
         return cpos;
}



//�����߿鲢�޸�
void MazePath(MazeType &maze,PostType start,int flag,int toflag){
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //����"��ǰλ��"Ϊ"���λ��"
         //̽����һ��
         do{
             if(maze.adr[curpos.r][curpos.c]==flag){//��ǰλ�ÿ���ͨ��,
                 maze.adr[curpos.r][curpos.c]=-1;//�����㼣
                 af[curpos.r][curpos.c]=toflag;//���������Ҫ�޸ĵĽڵ��еĵ�
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //����·��
                 curpos=NextPos(curpos,1); //��һλ���ǵ�ǰλ�õĶ���
                   }
                   else{        //��ǰλ�ò�ͨ
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//����һ������̽��
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ���
                                     }
                            }
                   }

         }while(!StackEmpty(S));

}



//����ͼ��ڵ������ļ����跽�����ظ�������ǰ����netǰ׺��

//��ȡ�߿���Ϣ�����л��߿�
void netMazePath(MazeType &maze,PostType start,int number,int flag){
         int count_all=0; //��¼��ǰ�߿�����е����
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //����"��ǰλ��"Ϊ"���λ��"
         //̽����һ��
         do{
             if(maze.adr[curpos.r][curpos.c]==flag){//��ǰλ�ÿ���ͨ��,
                 count_all++;
                 maze.adr[curpos.r][curpos.c]=number+flag_max;//�����㼣
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //����·��
                 curpos=NextPos(curpos,1); //��һλ���ǵ�ǰλ�õĶ���
                   }
                   else{        //��ǰλ�ò�ͨ
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//����һ������̽��
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ���
                                     }
                            }
                   }

         }while(!StackEmpty(S));
         fprintf(fp5, "%d\n",count_all);//������Ϣ��ĵ����

}

//�����ܰ߿�����
void MazePath1(MazeType &maze,PostType start,int number,int flag){
         int count_all=0; //��¼��ǰ�߿�����е����
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //����"��ǰλ��"Ϊ"���λ��"
         //̽����һ��
         do{
             if(maze.adr[curpos.r][curpos.c]==flag){//��ǰλ�ÿ���ͨ��,
                 count_all++;
                 maze.adr[curpos.r][curpos.c]=number+flag_max;//�����㼣
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //����·��
                 curpos=NextPos(curpos,1); //��һλ���ǵ�ǰλ�õĶ���
                   }
                   else{        //��ǰλ�ò�ͨ
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//����һ������̽��
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ���
                                     }
                            }
                   }

         }while(!StackEmpty(S));

}

int if_adjacent(MazeType &maze,int x,int y,int number,int flag){
        int ecount=0;
        if(x+1<LINE){
	if(maze.adr[x+1][y] != flag&&maze.adr[x+1][y] !=(number+flag)){
           if(maze.adr[x+1][y]>flag_max+number){ //���ʾ�������ڽӣ�x��ʾ����ֵ��adjacent_rightӦ����adjacent_below���������ﻥ����д���1��2����û������������
             adjacent[flag-flag_max][maze.adr[x+1][y]-number-flag_max]++;
             adjacent_right[flag-flag_max][maze.adr[x+1][y]-number-flag_max]++;
             }
           else{
             adjacent[flag-flag_max][maze.adr[x+1][y]-flag_max]++;
             adjacent_right[flag-flag_max][maze.adr[x+1][y]-flag_max]++;
             }
           ecount++;
        }
        }
        if(y+1<SAMPLE){
	if(maze.adr[x][y+1] != flag&&maze.adr[x][y+1] !=(number+flag)){
            if(maze.adr[x][y+1]>flag_max+number){
              adjacent[flag-flag_max][maze.adr[x][y+1]-number-flag_max]++;
              }
           else{
              adjacent[flag-flag_max][maze.adr[x][y+1]-flag_max]++;
              }
           ecount++;
        }
      }
      return ecount;
}

void AdjacentPath(MazeType &maze,PostType start,int number,int flag){
         int count_edge = 0;
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //����"��ǰλ��"Ϊ"���λ��"
         //̽����һ��
         do{
             if(maze.adr[curpos.r][curpos.c]==flag){//��ǰλ�ÿ���ͨ��,
                 count_edge+=if_adjacent(maze,curpos.r,curpos.c,number,flag);
                 maze.adr[curpos.r][curpos.c]=flag+number;//�����㼣
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //����·��
                 curpos=NextPos(curpos,1); //��һλ���ǵ�ǰλ�õĶ���
                   }
                   else{        //��ǰλ�ò�ͨ
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//����һ������̽��
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ���
                                     }
                            }
                   }

         }while(!StackEmpty(S));
      fprintf(fp5, "%d\n",count_edge);
     // sideNum+=count_edge;
      for(int i=1;i<=number;i++){
      if(adjacent[flag-flag_max][i]!=0){
      if(adjacent_right[flag-flag_max][i]!=0){
         fprintf(fp5, "%d,",flag-flag_max);
         fprintf(fp5, "%d,",i);
         fprintf(fp5, "%d,",2);
         fprintf(fp5, "%d\n",adjacent_right[flag-flag_max][i]/2);
        }
      if(adjacent[flag-flag_max][i]-adjacent_right[flag-flag_max][i]>0) {
         fprintf(fp5, "%d,",flag-flag_max);
         fprintf(fp5, "%d,",i);
         fprintf(fp5, "%d,",1);
         fprintf(fp5, "%d\n",adjacent[flag-flag_max][i]/2-adjacent_right[flag-flag_max][i]/2);
      } 

      }
   }

}

//�����ܵ�����
void AdjacentPath1(MazeType &maze,PostType start,int number,int flag){
         int count_edge = 0;
         Stack S;
         PostType curpos;
         SElemType e;
         InitStack(S);
         curpos=start; //����"��ǰλ��"Ϊ"���λ��"
         //̽����һ��
         do{
             if(maze.adr[curpos.r][curpos.c]==flag){//��ǰλ�ÿ���ͨ��,
                 count_edge+=if_adjacent(maze,curpos.r,curpos.c,number,flag);
                 maze.adr[curpos.r][curpos.c]=flag+number;//�����㼣
                 e.seat=curpos;
                 e.di=1;
                 Push(S,e);              //����·��
                 curpos=NextPos(curpos,1); //��һλ���ǵ�ǰλ�õĶ���
                   }
                   else{        //��ǰλ�ò�ͨ
                       if(!StackEmpty(S)){
                           Pop(S,e);
                            if(e.di <4){
                                e.di++;//����һ������̽��
                                Push(S,e);
                                curpos=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ���
                                     }
                            }
                   }

         }while(!StackEmpty(S));
      sideNum+=count_edge;

}

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

void __fastcall TForm1::Button1Click(TObject *Sender)
{
          if(OpenDialog1->Execute())
                name=OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
          if(OpenDialog2->Execute()){
                netname=OpenDialog2->FileName;
                }
}
//---------------------------------------------------------------------------
//---------------------Button3ʵ������޸ĺ��ͼ���ļ�
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        if(file_type==1){
         //��ʼ����ά���麯��
        memset(node,-1,sizeof(node));
        memset(af,-1,sizeof(af));

        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        FILE *fp;
        unsigned char idata;//������ȡ��������
        maze.r=SAMPLE;maze.c=LINE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)%SAMPLE][(count-1)/SAMPLE]=idata;

        }
        fclose(fp);
        }

        //����ԭͼ�����Ƿ���ȷ��ȡ
        /*FILE *ff;
        ff = fopen("d://ff.txt","w+");
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        fprintf(ff,"%d ",maze.adr[j][i]);
                }
                fprintf(ff,"\n");
        } */

        //��ȡ�ڵ������ļ��е�����

        FILE *fpc;
        //FILE *fpt;
        //fpt = fopen("d://tt.txt","w+");
        fpc = fopen(netname.c_str(),"r+");
        int IDnums,relnums,bnums;//�ڵ�����,��ϵ�����ܱ���
        int pro,ID,tolnums;//���Ը�����2�������ڵ�ID����ǰ�ڵ��ܵ�����������nowclass����ʼ��λ��spoint�ڴ���ͷ�Ѷ��壩
        fscanf(fpc,"%d%d%d",&IDnums,&relnums,&bnums);
        //fprintf(fpt,"%d %d %d\n",IDnums,relnums,bnums);
        for(int i=0;i<IDnums;i++){
                fscanf(fpc,"%d%d%d%d%d",&pro,&toClass,&spoint,&ID,&tolnums);
                node[(spoint-1)%SAMPLE][(spoint-1)/SAMPLE]=toClass;
                //fprintf(fpt,"%d %d %d %d %d\n",pro,toClass,spoint,ID,tolnums);
        }
        //fprintf(fpt,"%d %d\n",maze.adr[65][0],node[65][0]);
        fclose(fpc);


        //�ҳ��ڵ����͸ı�İ߿�

        PostType start;
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                /*if(i*SAMPLE+j==66)
                {
                fprintf(fpt," %d",af[65][0]);
                   int a;
                   a=65;
                } */
                        if(node[j][i] != -1){     //ֻѰ�Ҳ��Ƚ�һ���ڵ�ĵ�һ����
                        if(maze.adr[j][i]!=node[j][i]){
                                start.r=j;
                                start.c=i;
                                toClass=node[j][i];
                                nowClass=maze.adr[j][i];
                                MazePath(maze,start,nowClass,toClass);//�޸ĵ�ǰ�ڵ�
                                //Memo1->Lines->Append(i*SAMPLE+j);
                                }
                        }
                }
        }


        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(af[j][i]!=-1 && maze.adr[j][i]==-1)
                        maze.adr[j][i]=af[j][i];
                }
        }     

        //fprintf(fpt,"%d %d %d%d%d\n",maze.adr[43][0],node[43][0],maze.adr[44][0],maze.adr[45][0],maze.adr[46][0]);
        //fclose(fpt);
        //���ʸ���������ļ�
        if(Edit3->Text == "")
        {
                MessageBox(NULL,"��ѡ������ļ�·����", "Error",MB_ICONERROR);
        }
        FILE *fptwo;
        char a=1,b=2,c=3,d=4,e=0;
        fptwo=fopen(Edit3->Text.c_str(),"wb");//���ļ�
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]==1)
                        fwrite(&a,1,1,fptwo);
                        if(maze.adr[j][i]==2)
                        fwrite(&b,1,1,fptwo);
                        if(maze.adr[j][i]==3)
                        fwrite(&c,1,1,fptwo);
                        if(maze.adr[j][i]==4)
                        fwrite(&d,1,1,fptwo);
                        if(maze.adr[j][i]==0)
                        fwrite(&e,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"�ɹ�����ͼ���ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
    }


    if(file_type==2){
         //��ʼ����ά���麯��
        memset(node,-1,sizeof(node));
        memset(af,-1,sizeof(af));

        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        FILE *fp;
        unsigned short idata;//������ȡ��������
        maze.r=SAMPLE;maze.c=LINE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)%SAMPLE][(count-1)/SAMPLE]=idata;

        }
        fclose(fp);
        }

        //����ԭͼ�����Ƿ���ȷ��ȡ
        /*FILE *ff;
        ff = fopen("d://ff.txt","w+");
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        fprintf(ff,"%d ",maze.adr[j][i]);
                }
                fprintf(ff,"\n");
        } */

        //��ȡ�ڵ������ļ��е�����

        FILE *fpc;
        //FILE *fpt;
        //fpt = fopen("d://tt.txt","w+");
        fpc = fopen(netname.c_str(),"r+");
        int IDnums,relnums,bnums;//�ڵ�����,��ϵ�����ܱ���
        int pro,ID,tolnums;//���Ը�����2�������ڵ�ID����ǰ�ڵ��ܵ�����������nowclass����ʼ��λ��spoint�ڴ���ͷ�Ѷ��壩
        fscanf(fpc,"%d%d%d",&IDnums,&relnums,&bnums);
        //fprintf(fpt,"%d %d %d\n",IDnums,relnums,bnums);
        for(int i=0;i<IDnums;i++){
                fscanf(fpc,"%d%d%d%d%d",&pro,&toClass,&spoint,&ID,&tolnums);
                node[(spoint-1)%SAMPLE][(spoint-1)/SAMPLE]=toClass;
                //fprintf(fpt,"%d %d %d %d %d\n",pro,toClass,spoint,ID,tolnums);
        }
        //fprintf(fpt,"%d %d\n",maze.adr[65][0],node[65][0]);
        fclose(fpc);


        //�ҳ��ڵ����͸ı�İ߿�

        PostType start;
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                /*if(i*SAMPLE+j==66)
                {
                fprintf(fpt," %d",af[65][0]);
                   int a;
                   a=65;
                } */
                        if(node[j][i] != -1){     //ֻѰ�Ҳ��Ƚ�һ���ڵ�ĵ�һ����
                        if(maze.adr[j][i]!=node[j][i]){
                                start.r=j;
                                start.c=i;
                                toClass=node[j][i];
                                nowClass=maze.adr[j][i];
                                MazePath(maze,start,nowClass,toClass);//�޸ĵ�ǰ�ڵ�
                                //Memo1->Lines->Append(i*SAMPLE+j);
                                }
                        }
                }
        }


        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(af[j][i]!=-1 && maze.adr[j][i]==-1)
                        maze.adr[j][i]=af[j][i];
                }
        }     

        //fprintf(fpt,"%d %d %d%d%d\n",maze.adr[43][0],node[43][0],maze.adr[44][0],maze.adr[45][0],maze.adr[46][0]);
        //fclose(fpt);
        //���ʸ���������ļ�
        if(Edit3->Text == "")
        {
                MessageBox(NULL,"��ѡ������ļ�·����", "Error",MB_ICONERROR);
        }
        FILE *fptwo;
        char a=1,b=2,c=3,d=4,e=0;
        fptwo=fopen(Edit3->Text.c_str(),"wb");//���ļ�
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]==1)
                        fwrite(&a,1,1,fptwo);
                        if(maze.adr[j][i]==2)
                        fwrite(&b,1,1,fptwo);
                        if(maze.adr[j][i]==3)
                        fwrite(&c,1,1,fptwo);
                        if(maze.adr[j][i]==4)
                        fwrite(&d,1,1,fptwo);
                        if(maze.adr[j][i]==0)
                        fwrite(&e,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"�ɹ�����ͼ���ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
    }

    if(file_type==4){
         //��ʼ����ά���麯��
        memset(node,-1,sizeof(node));
        memset(af,-1,sizeof(af));

        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        FILE *fp;
        unsigned int idata;//������ȡ��������
        maze.r=SAMPLE;maze.c=LINE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)%SAMPLE][(count-1)/SAMPLE]=idata;

        }
        fclose(fp);
        }

        //����ԭͼ�����Ƿ���ȷ��ȡ
        /*FILE *ff;
        ff = fopen("d://ff.txt","w+");
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        fprintf(ff,"%d ",maze.adr[j][i]);
                }
                fprintf(ff,"\n");
        } */

        //��ȡ�ڵ������ļ��е�����

        FILE *fpc;
        //FILE *fpt;
        //fpt = fopen("d://tt.txt","w+");
        fpc = fopen(netname.c_str(),"r+");
        int IDnums,relnums,bnums;//�ڵ�����,��ϵ�����ܱ���
        int pro,ID,tolnums;//���Ը�����2�������ڵ�ID����ǰ�ڵ��ܵ�����������nowclass����ʼ��λ��spoint�ڴ���ͷ�Ѷ��壩
        fscanf(fpc,"%d%d%d",&IDnums,&relnums,&bnums);
        //fprintf(fpt,"%d %d %d\n",IDnums,relnums,bnums);
        for(int i=0;i<IDnums;i++){
                fscanf(fpc,"%d%d%d%d%d",&pro,&toClass,&spoint,&ID,&tolnums);
                node[(spoint-1)%SAMPLE][(spoint-1)/SAMPLE]=toClass;
                //fprintf(fpt,"%d %d %d %d %d\n",pro,toClass,spoint,ID,tolnums);
        }
        //fprintf(fpt,"%d %d\n",maze.adr[65][0],node[65][0]);
        fclose(fpc);


        //�ҳ��ڵ����͸ı�İ߿�

        PostType start;
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                /*if(i*SAMPLE+j==66)
                {
                fprintf(fpt," %d",af[65][0]);
                   int a;
                   a=65;
                } */
                        if(node[j][i] != -1){     //ֻѰ�Ҳ��Ƚ�һ���ڵ�ĵ�һ����
                        if(maze.adr[j][i]!=node[j][i]){
                                start.r=j;
                                start.c=i;
                                toClass=node[j][i];
                                nowClass=maze.adr[j][i];
                                MazePath(maze,start,nowClass,toClass);//�޸ĵ�ǰ�ڵ�
                                //Memo1->Lines->Append(i*SAMPLE+j);
                                }
                        }
                }
        }


        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(af[j][i]!=-1 && maze.adr[j][i]==-1)
                        maze.adr[j][i]=af[j][i];
                }
        }     

        //fprintf(fpt,"%d %d %d%d%d\n",maze.adr[43][0],node[43][0],maze.adr[44][0],maze.adr[45][0],maze.adr[46][0]);
        //fclose(fpt);
        //���ʸ���������ļ�
        if(Edit3->Text == "")
        {
                MessageBox(NULL,"��ѡ������ļ�·����", "Error",MB_ICONERROR);
        }
        FILE *fptwo;
        char a=1,b=2,c=3,d=4,e=0;
        fptwo=fopen(Edit3->Text.c_str(),"wb");//���ļ�
        for(int i=0;i<LINE;i++){
                for(int j=0;j<SAMPLE;j++){
                        if(maze.adr[j][i]==1)
                        fwrite(&a,1,1,fptwo);
                        if(maze.adr[j][i]==2)
                        fwrite(&b,1,1,fptwo);
                        if(maze.adr[j][i]==3)
                        fwrite(&c,1,1,fptwo);
                        if(maze.adr[j][i]==4)
                        fwrite(&d,1,1,fptwo);
                        if(maze.adr[j][i]==0)
                        fwrite(&e,1,1,fptwo);
                }
        }
        fclose(fptwo);
        MessageBox(NULL,"�ɹ�����ͼ���ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        if(Edit1->Text == ""){
                LINE = 0;
        }
        else{
        LINE = StrToInt(Edit1->Text);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        if(Edit2->Text == ""){
                SAMPLE = 0;
        }
        else{
        SAMPLE = StrToInt(Edit2->Text);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        if(OpenDialog3->Execute()){
                outname=OpenDialog3->FileName;
                Edit3->Text = outname;
                }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
        if(OpenDialog4->Execute()){
                netoutname=OpenDialog4->FileName;
                Edit4->Text = netoutname;
                }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
     //һ�ֽڶ�ȡ unsigned char idata;
     if(file_type==1){
        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        PostType start;
        int flag;    //��¼��ǰ�߿������
        FILE *fp;
        unsigned char idata;//������ȡ��������
        maze.r=LINE;maze.c=SAMPLE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;
                maze1.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;//�����ܰ߿������ܵ�����
                if(flag_max<idata)
                        flag_max=idata;


        }
       fclose(fp);
    }
    //�����ܰ߿���
    int number1=0;//��¼��ǰ�߿�����
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]<=flag_max && maze1.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  MazePath1(maze1,start,number1,flag);//�˷�����maze1�����л� (5-107)
			}
		    }
		 }
    //�����ܵ���
    int seq1=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]==seq1+flag_max&& maze1.adr[i][j]!=flag_max){
             if(seq1<=number1){
                  seq1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath1(maze1,start,number1,flag);
                           }
			}
		    }
		 }


    //�����߿飬����߿���Ϣ�����л��߿�
     fp5=fopen(Edit4->Text.c_str(),"w");
     fprintf(fp5, "%d\t",number1); //�ڵ���
     fprintf(fp5, "%d\t",2);  //��ϵ��
     fprintf(fp5, "%d\n",sideNum);//����
     int number = 0;
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]<=flag_max && maze.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number++;
                  fprintf(fp5, "%d ",2);
                  fprintf(fp5, "%d ",maze.adr[i][j]);//classֵ
                  fprintf(fp5, "%d ",i* SAMPLE+j+1);//��ʼ���
                  fprintf(fp5, "%d ",number);//�߿�id ���������Ϣ�ļ�¼��MazePath������
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  netMazePath(maze,start,number,flag);//�˷�����maze�����л� (5-107)
			}
		    }
		 }
    // ��ϵ��Ϣ
     fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\t",1);fprintf(fp5, "%d\t",0); fprintf(fp5, "%d\n",0);
     fprintf(fp5, "%d\t",2); fprintf(fp5, "%d\t",0);fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\n",0);
     //��ȡ�߿����ڽ�·��
    int seq=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]==seq+flag_max&& maze.adr[i][j]!=flag_max){
             if(seq<=number){
                  fprintf(fp5, "%d,",-1);
                  fprintf(fp5, "%d,",seq);
                  seq++;
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath(maze,start,number,flag);
                           }
			}
		    }
		 }

            fclose(fp5);
            MessageBox(NULL,"�ɹ����ɽڵ������ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
          }
          
     //���ֽڶ�ȡ unsigned short idata;
     if(file_type==2){
        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        PostType start;
        int flag;    //��¼��ǰ�߿������
        FILE *fp;
        unsigned short idata;//������ȡ��������
        maze.r=LINE;maze.c=SAMPLE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;
                maze1.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;//�����ܰ߿������ܵ�����
                if(flag_max<idata)
                        flag_max=idata;


        }
       fclose(fp);
    }
    //�����ܰ߿���
    int number1=0;//��¼��ǰ�߿�����
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]<=flag_max && maze1.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  MazePath1(maze1,start,number1,flag);//�˷�����maze1�����л� (5-107)
			}
		    }
		 }
    //�����ܵ���
    int seq1=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]==seq1+flag_max&& maze1.adr[i][j]!=flag_max){
             if(seq1<=number1){
                  seq1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath1(maze1,start,number1,flag);
                           }
			}
		    }
		 }


    //�����߿飬����߿���Ϣ�����л��߿�
     fp5=fopen(Edit4->Text.c_str(),"w");
     fprintf(fp5, "%d\t",number1); //�ڵ���
     fprintf(fp5, "%d\t",2);  //��ϵ��
     fprintf(fp5, "%d\n",sideNum);//����
     int number = 0;
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]<=flag_max && maze.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number++;
                  fprintf(fp5, "%d ",2);
                  fprintf(fp5, "%d ",maze.adr[i][j]);//classֵ
                  fprintf(fp5, "%d ",i* SAMPLE+j+1);//��ʼ���
                  fprintf(fp5, "%d ",number);//�߿�id ���������Ϣ�ļ�¼��MazePath������
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  netMazePath(maze,start,number,flag);//�˷�����maze�����л� (5-107)
			}
		    }
		 }
    // ��ϵ��Ϣ
     fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\t",1);fprintf(fp5, "%d\t",0); fprintf(fp5, "%d\n",0);
     fprintf(fp5, "%d\t",2); fprintf(fp5, "%d\t",0);fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\n",0);
     //��ȡ�߿����ڽ�·��
    int seq=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]==seq+flag_max&& maze.adr[i][j]!=flag_max){
             if(seq<=number){
                  fprintf(fp5, "%d,",-1);
                  fprintf(fp5, "%d,",seq);
                  seq++;
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath(maze,start,number,flag);
                           }
			}
		    }
		 }

            fclose(fp5);
            MessageBox(NULL,"�ɹ����ɽڵ������ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
          }

     //���ֽڶ�ȡ unsigned int idata;
     if(file_type==4){
        //��ȡ���е���maze����
        if(LINE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        if(SAMPLE <= 0){
                MessageBox(NULL,"��ֵ��������������������������ֵ��", "Error",MB_ICONERROR);
        }
        PostType start;
        int flag;    //��¼��ǰ�߿������
        FILE *fp;
        unsigned int idata;//������ȡ��������
        maze.r=LINE;maze.c=SAMPLE;
        int count=0;
        fp=fopen(name.c_str(),"rb");//���ļ�
        if(fp!=NULL)
        {
        while(!feof(fp))
        {
                fread(&idata,file_type,1,fp);//��ȡ���ݴ�����idata[]��
                count++;
                maze.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;
                maze1.adr[(count-1)/SAMPLE][(count-1)%SAMPLE]=idata;//�����ܰ߿������ܵ�����
                if(flag_max<idata)
                        flag_max=idata;


        }
       fclose(fp);
    }
    //�����ܰ߿���
    int number1=0;//��¼��ǰ�߿�����
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]<=flag_max && maze1.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  MazePath1(maze1,start,number1,flag);//�˷�����maze1�����л� (5-107)
			}
		    }
		 }
    //�����ܵ���
    int seq1=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze1.adr[i][j]==seq1+flag_max&& maze1.adr[i][j]!=flag_max){
             if(seq1<=number1){
                  seq1++;
                  flag=maze1.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath1(maze1,start,number1,flag);
                           }
			}
		    }
		 }


    //�����߿飬����߿���Ϣ�����л��߿�
     fp5=fopen(Edit4->Text.c_str(),"w");
     fprintf(fp5, "%d\t",number1); //�ڵ���
     fprintf(fp5, "%d\t",2);  //��ϵ��
     fprintf(fp5, "%d\n",sideNum);//����
     int number = 0;
    for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]<=flag_max && maze.adr[i][j]!=0){ //�õ������������� 1.��������0 ��2. �ܹ�103���߿飿
                  number++;
                  fprintf(fp5, "%d ",2);
                  fprintf(fp5, "%d ",maze.adr[i][j]);//classֵ
                  fprintf(fp5, "%d ",i* SAMPLE+j+1);//��ʼ���
                  fprintf(fp5, "%d ",number);//�߿�id ���������Ϣ�ļ�¼��MazePath������
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  netMazePath(maze,start,number,flag);//�˷�����maze�����л� (5-107)
			}
		    }
		 }
    // ��ϵ��Ϣ
     fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\t",1);fprintf(fp5, "%d\t",0); fprintf(fp5, "%d\n",0);
     fprintf(fp5, "%d\t",2); fprintf(fp5, "%d\t",0);fprintf(fp5, "%d\t",1); fprintf(fp5, "%d\n",0);
     //��ȡ�߿����ڽ�·��
    int seq=1;
     for(int i=0;i<LINE;i++){
          for(int j=0;j<SAMPLE;j++){
            if(maze.adr[i][j]==seq+flag_max&& maze.adr[i][j]!=flag_max){
             if(seq<=number){
                  fprintf(fp5, "%d,",-1);
                  fprintf(fp5, "%d,",seq);
                  seq++;
                  flag=maze.adr[i][j];
	          start.r=i;start.c=j;
                  AdjacentPath(maze,start,number,flag);
                           }
			}
		    }
		 }

            fclose(fp5);
            MessageBox(NULL,"�ɹ����ɽڵ������ļ������ڶ�Ӧ�ļ��鿴��", "Message",MB_ICONASTERISK);
          }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Change(TObject *Sender)
{
        if(Edit5->Text == ""){
                file_type = 1;
        }
        else{
        file_type = StrToInt(Edit5->Text);
        }
}
//---------------------------------------------------------------------------
