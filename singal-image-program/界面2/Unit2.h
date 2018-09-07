//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include<stdio.h>
#include<stdlib.h>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include<time.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include<algorithm>
#include<queue>
#include<string>
#include<strstream>
#include<iostream>
#define I_X 5    //ÿ�������������θ���
#define I_D 6     //��������
#define I_AMOUNT 10000
using namespace std;
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TBitBtn *BitBtn1;
        TADOQuery *ADOQuery1;
        void __fastcall Image1MouseDown(TObject *Sender,
                  TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall BitBtn1Click(TObject *Sender);
        void  __fastcall change_color();
        void  __fastcall select_from_SQL(String str);

private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
        String stringg[I_D];            //������¼����
        String address[I_D];            //������¼������ַ��
        String ADDRESS;
        int HANG;
        int LIE;
        int X;
        int D;
        int AMOUNT;
        POINT mouse_start,mouse_end;
        int mouse_is_down;
        String TXT1;
int summmm;
int ed_feature_1[I_X+1][I_X+1];	//��¼һ����չ�Ĺ�����v_0�����е�address�����ڼ�ʱ�����λ�ã���ʼ��Ϊ-1��
int ed_feature_2[I_X+1][I_X+1][I_X+1][I_X+1];	//��¼һ����չ�Ĺ�����v_1�����е�address�����ڼ�ʱ�����λ�ã���ʼ��Ϊ-1��
int ed_feature_3[I_X+1][I_X+1][I_X+1][I_X+1][3];	//��¼һ����չ�Ĺ�����v_2�����е�address�����ڼ�ʱ�����λ�ã���ʼ��Ϊ-1��
int max_suggest;        //��¼���в���ֵ���е����ֵ
//int all_number=0;				//��¼�������������� 
int amount_of_feature;      //��¼��������������
int amount_of_feature_2;
int amount_of_feature_3;
typedef struct //����
{
	int ID;          //���α�� 
	int number;	 	 //����ֵ 
}boduan, *pboduan;
typedef struct //���� 
{
	int yangben_id;	     //������� 
	boduan bo_duan[I_X];	 //�������ڵĲ��ξ������
}yangben, *pyangben;
typedef struct //������
{
	int number;				//������ı��
	pyangben yang_ben;		//�������ڵ���������
	char str[I_X+1];			//��Щ���м��������е���������
}group, *pgroup;
typedef struct //����
{
	int ID;					//�����ż��ڼ������
	pgroup pgp;				//������������������ɸ�������
	int group_amount;		//����������
	int yangben_amount;		//������������������
}diwu, *pdiwu;
typedef struct Node
{
	//*********************ͳ������*********************************
	int diw_fat,diw_thin;		//���Ƶ������Ƶ���
	long long pass;				//ͨ������
	int flag; 					//��չ����
	double percent;				//���ֶ�
	int yu; 					//��ֵ
	double IGR;					//��Ϣ�����
	//**********************0����չ*********************************
	int fat,thin;				//ǿ�Ʋ������Ʋ���
	//**********************1����չ*********************************
	int fat_plus,thin_plus;		//ǿ�Ʋ�������ɫ���μ����ǵ����� (������չҲʹ�ô����ԣ������ظ�)
	//**********************2����չ*********************************
	int number_of_bk;			//��¼������չ����bkֵ
	int type_2;
}feature;
struct cmp
{
	bool operator()(Node a,Node b){return a.percent<b.percent;}
};
typedef struct
{
	int * tree;
}forest;
typedef struct
{
	vector<feature>f;
	vector<int>ff;
}v_v_v;
v_v_v vvv[I_D];
typedef struct
{
        int r,g,b;
}yanse;
yanse ys[13];
vector<feature>v_0;
vector<feature>v_1;
vector<feature>v_2;
priority_queue<Node,vector<Node>,cmp>q;		//������¼���й���Ķ�
vector<feature>feature_v;					//������¼ǰʮ�����������
diwu grand[I_D+1];
FILE *fp[I_D+1]; 
//*************************************************������*****************************
int hanshu()
{
//	��¼�����׼������
   /* 	fp[0] = fopen("G:\\������Ŀ\\2017_03_14\\ԭʼ\\����\\��Դ��������\\��ˮ.txt", "r");
	fp[1] = fopen("G:\\������Ŀ\\2017_03_14\\ԭʼ\\����\\��Դ��������\\����.txt", "r");
	fp[2] = fopen("G:\\������Ŀ\\2017_03_14\\ԭʼ\\����\\��Դ��������\\����.txt", "r");
	fp[3] = fopen("G:\\������Ŀ\\2017_03_14\\ԭʼ\\����\\��Դ��������\\ֲ��.txt", "r");*/
        for(int i=0 ; i<D ; i++)
        {
                fp[i] = fopen(address[i].c_str(),"r");
        }
        	for(int i=0 ; i<D ; i++)
	{
		stringg[i] = "";
	}
	for(int i=0 ; i<D ; i++)
	{
		if(fp[i]==NULL)
		{
			printf("error����%d!\n",i);
			exit(-1);
		}
	} 
//	�����ʼ��	
	diwuchushihua();
//	�������
//	diwubianli();
//	printf("max_suggest:%lld\n",max_suggest);
//  �Ƚ�
  /*      for(int i=0 ; i<D ; i++)
	{
		for(int j=i+1 ; j<D ; j++)
		{
			compare(grand[i],grand[j]);
		}
	}
//	�������
	for(int i=0 ; i<amount_of_feature ; i++)
	{
		v_0[i].percent = 1.0*v_0[i].pass/(grand[v_0[i].diw_fat].yangben_amount*grand[v_0[i].diw_thin].yangben_amount);
		q.push(v_0[i]);
		printf("diw_fat:%d\tdiw_thin:%d\tpass:%7lld\tflag:%d\tfat:%2d\tthin:%2d\tpercnet:%f\t%d\n",v_0[i].diw_fat,v_0[i].diw_thin,v_0[i].pass,v_0[i].flag,v_0[i].fat,v_0[i].thin,v_0[i].percent,(grand[v_0[i].diw_fat].yangben_amount*grand[v_0[i].diw_thin].yangben_amount));
	}
	for(int i=0 ; i<amount_of_feature_2 ; i++)
	{
		v_1[i].percent = 1.0*v_1[i].pass/(grand[v_1[i].diw_fat].yangben_amount*grand[v_1[i].diw_thin].yangben_amount);
		q.push(v_1[i]);
		printf("diw_fat:%d\tdiw_thin:%d\tpass:%7lld\tflag:%2lld\tfat:%2d\tfat_plus:%2d\tthin:%2d\tthin_plus:%2d\tpercnet:%f\t%d\n",v_1[i].diw_fat,v_1[i].diw_thin,v_1[i].pass,v_1[i].flag,v_1[i].fat,v_1[i].fat_plus,v_1[i].thin,v_1[i].thin_plus,v_1[i].percent,(grand[v_1[i].diw_fat].yangben_amount*grand[v_1[i].diw_thin].yangben_amount));
	}
	for(int i=0 ; i<amount_of_feature_3 ; i++)
	{
		v_2[i].percent = 1.0*v_2[i].pass/(grand[v_2[i].diw_fat].yangben_amount*grand[v_2[i].diw_thin].yangben_amount);
		q.push(v_2[i]);
		printf("diw_fat:%d\tdiw_thin:%d\tpass:%7lld\tflag:%2lld\tfat:%2d\tfat_plus:%2d\tthin:%2d\tthin_plus:%2d\tpercnet:%f\t%d\n",v_2[i].diw_fat,v_2[i].diw_thin,v_2[i].pass,v_2[i].flag,v_2[i].fat,v_2[i].fat_plus,v_2[i].thin,v_2[i].thin_plus,v_2[i].percent,(grand[v_2[i].diw_fat].yangben_amount*grand[v_2[i].diw_thin].yangben_amount));
	}
	int power = 10;
	while(power--)
	{
		feature f = q.top();
		q.pop();
		printf("�����ֹ�����ѭ%d����չ�����ֶ�Ϊ��%.3f %%\t��������%d,%d����\n",f.flag,f.percent*100,f.diw_fat,f.diw_thin);
		printf("ǿ�ƣ�%2d\tǿ��_plus��%2d\t���ƣ�%2d\t����_plus��%2d \n",f.fat,f.fat_plus,f.thin,f.thin_plus);
		int flag = 0;
		for(int i=0 ; i<feature_v.size() ; i++)
		{
			if(f.fat==feature_v[i].fat && f.thin==feature_v[i].thin && f.fat_plus==feature_v[i].fat_plus && f.thin_plus==feature_v[i].thin_plus)
			flag = 1;
			else if(f.fat==feature_v[i].thin && f.thin==feature_v[i].fat && f.fat_plus==feature_v[i].thin_plus && f.thin_plus==feature_v[i].fat_plus)
			flag = 1;
		}
		if(flag) continue;
		feature_v.push_back(f);
		printf("������������������������������������������������������������\n");
	}   */
//������������
	feature f;
	for(int i=0 ; i<X ; i++)
	{
		f.fat = i;
		f.thin = 4;
		f.fat_plus = 4;
		f.thin_plus = 4;
		f.flag = -1;
		feature_v.push_back(f);
	} 
//������������
//	int all_yangben = 0;
//	for(int i=0 ; i<D ; i++)
//	all_yangben += grand[i].yangben_amount;
//	printf("%d\n",all_yangben);
//	pyangben word = (pyangben)malloc(sizeof(yangben)*all_yangben);
	vector<yangben>word;
	for(int i=0 ; i<D ; i++)
	{
		for(int j=0 ; j<grand[i].group_amount ; j++)
		{
			for(int k=0 ; k<grand[i].pgp[j].number ; k++)
			{
				word.push_back(grand[i].pgp[j].yang_ben[k]);
			}
		}
	}
	int shuzu[I_D];
	for(int i=0 ; i<D ; i++)
	{
		shuzu[i] = grand[i].yangben_amount;
	}
	double et = entropy(shuzu);
	printf("-----------------------------C4.5�㷨��ʼ��----------------------------\n");
	C4_5(word,et);
    /*	for(int i=0 ; i<D ; i++)
	{
		stringg[i] = "��"+str_int(i+1)+"����"+stringg[i]+"��";
		cout<<stringg[i]<<endl;
	}   */
	for(int i=0 ; i<D ; i++)
	{
		printf("*********************************************\n");
		for(int j=0 ; j<vvv[i].f.size() ; j++)
		{			
			printf("***********%d\n",vvv[i].ff[j]);
			printf("fat:%d\tthin:%d\tfat_plus:%d\tthin_plus:%d\tyu:%d\n",vvv[i].f[j].fat,vvv[i].f[j].thin,vvv[i].f[j].fat_plus,vvv[i].f[j].thin_plus,vvv[i].f[j].yu);
		}
	}
        Memo1->Lines->SetText("");
        String ott1[11] = {"��","һ","��","��","��","��","��","��","��","��","ʮ"} ;
        String ott2[11] = {"��","��","��","��","��","��","��","��","��","��","��"} ;
        String ssttrr;
        for(int i=0 ; i<D ; i++)
        {
                ssttrr =  "��"+ott1[i+1]+"����";
           //     Memo1->Lines->Append(ssttrr.c_str());
            //    ssttrr = "";
                for(int j=0 ; j<vvv[i].f.size() ; j++)
                {
                        if(j)  ssttrr+=" �� ";
                        if(vvv[i].f[j].flag == -1)
                        {
                                ssttrr += "����" + str_int(vvv[i].f[j].fat+1) + ((vvv[i].ff[j]<0)?"��":"��") + str_int(vvv[i].f[j].yu);
                        }
                        else if(vvv[i].f[j].flag == 0)
                        {
                                ssttrr += "����" + str_int(vvv[i].f[j].fat+1) + " - ����" + str_int(vvv[i].f[j].thin+1) +
                                ((vvv[i].ff[j]<0)?"��":"��") + str_int(vvv[i].f[j].yu);
                        }
                }
                ssttrr+="��";
                stringg[i] = ssttrr;
                Memo1->Lines->Append(ssttrr.c_str());
                ssttrr = "";
        }
        change_color();
        clean_all();
	return 0;
}
void diwuchushihua()
{
	yangben yb;
	int i, j, k;
	char ch[I_X];
	for (j = 0; j<D; j++)
	{
		grand[j].ID=j;
		grand[j].pgp = (pgroup)malloc(sizeof(group) * AMOUNT);
		grand[j].group_amount = 0;
		i = 0;
		k = 0;
		int w = 0;
		int m=0;
		if (fp[j] == 0)
		{ 
			printf("fp[%d]δ�ҵ��ļ���\n", j);
			exit(-1); 
		}
		else
		{
			while (!feof(fp[j]))
			{
				yb.bo_duan[i].ID = i;
				fscanf(fp[j], "%d", &(yb.bo_duan[i].number));
				if(yb.bo_duan[i].number > max_suggest)
				max_suggest = yb.bo_duan[i].number ;
				if (i == X-1)
				{
					paixu_1(yb, ch);
					yb.yangben_id = j;
					k++;
					for (m = 0; m < grand[j].group_amount; m++)
					{
						if (strcmp(ch, grand[j].pgp[m].str) == 0)
						{
							grand[j].pgp[m].yang_ben[grand[j].pgp[m].number] = yb;
							grand[j].pgp[m].number++;
							break;
						}
					}
					if (m == grand[j].group_amount)
					{
						grand[j].pgp[m].yang_ben = (pyangben)malloc(sizeof(yangben) * AMOUNT);
						grand[j].pgp[m].number=0;
						strcpy(grand[j].pgp[m].str, ch);
						grand[j].pgp[m].yang_ben[0] = yb;
						grand[j].pgp[m].number++;
						grand[j].group_amount++;
					}
				}
				i++;
				i %= X;
			}
		}
		grand[j].yangben_amount = k;
		fclose(fp[j]);
	}
	return;
}
void paixu_1(yangben yang_ben, char ch[])
{
	int j, k;
	boduan t;
	char c;
	for (j = 0; j<X; j++)
	{
		for (k = j; k<X; k++)
		{
			if (yang_ben.bo_duan[j].number>yang_ben.bo_duan[k].number)
			{
				t = yang_ben.bo_duan[j];
				yang_ben.bo_duan[j] = yang_ben.bo_duan[k];
				yang_ben.bo_duan[k] = t;
			}
		}
	}
	for (j = 0; j<X; j++)
	{
		c = (char)(yang_ben.bo_duan[j].ID + 48);
		ch[j] = c;
	}
	ch[j] = '\0';
	return;
}
void diwubianli()
{
	int i, k,p,j;
	for (k = 0; k<D; k++)
	{
		printf("****\t*****\t****\t*****\n����%d\n������%d\n��������:%d\n******\t******\t****\t*****\n", k + 1,grand[k].group_amount,grand[k].yangben_amount);
		for (i = 0; i<grand[k].group_amount; i++)
		{
			printf("��%d��\n��Ա������%d\n��������:%s\n",i+1,grand[k].pgp[i].number,grand[k].pgp[i].str);
			for (j = 0; j < grand[k].pgp[i].number;j++)
			{
				printf("����:%d{",grand[k].pgp[i].yang_ben[j].yangben_id);
				for (p = 0; p < X; p++)
				{
					printf("%d",grand[k].pgp[i].yang_ben[j].bo_duan[p].number);
					if (p < X - 1)
					{
						printf("\t");
					}
				}
				printf("}\n");
			}
		}
	}
	return;
}
void compare(diwu d1,diwu d2)
{
	printf("���ڷֱ����%d�͵���%d,���Ժ�........\n",d1.ID,d2.ID); 
	memset(ed_feature_1,-1,sizeof(ed_feature_1));
	memset(ed_feature_2,-1,sizeof(ed_feature_2));
	memset(ed_feature_3,-1,sizeof(ed_feature_3));
	for(int i=0 ; i<d1.group_amount ; i++)
	{
		for(int j=0 ; j<d2.group_amount ; j++)
		{
			if(strcmp(d1.pgp[i].str,d2.pgp[j].str)==0)
			compare__1(d1.pgp[i],d2.pgp[j],d1.ID,d2.ID);
//			continue;
			else
			compare_0(d1.pgp[i].str,d2.pgp[j].str,d1.ID,d2.ID,d1.pgp[i].number,d2.pgp[j].number);
//			continue; 
		}
	}
}
void compare__1(group a,group b,int a_d,int b_d)
{
//	printf("hrere:����%d(group%d)%s\t�͵���%d(group%d)%s\n",a_d,a.number,a.str,b_d,b.number,b.str);
	int k1,k2;
	for(k1=0;k1<a.number;k1++)
	{
		for(k2=0;k2<b.number;k2++)
		{
			compare_1(a.yang_ben[k1],b.yang_ben[k2],a.str,a_d,b_d);
		}
	}
	return ;
}
void compare_1(yangben a,yangben b,char ch[],int a_d,int b_d)
{
	int p,q,r,n=1,m1,m2,bingo=0;
	for(q=1;q<X-1;q++)
	{
		p=q-1;
		r=q+1;
			while(p>=0&&r<X)
			{
				m1=a.bo_duan[ch[p]-48].number + a.bo_duan[ch[r]-48].number-2*(a.bo_duan[ch[q]-48].number); //ǿ�� 
				m2=b.bo_duan[ch[p]-48].number + b.bo_duan[ch[r]-48].number-2*(b.bo_duan[ch[q]-48].number); //���� 
				if(m1<=0&&m2<=0) r++;
				else if(m1>0&&m2>0)	p--; 
				else
				{
					int big,big_plus,small,small_plus;
					int diw_fat = a_d;
					int diw_thin = b_d;
					if(m1>0)
					{
						big = ch[p]-'0';
						big_plus = ch[r]-'0';
						small = ch[q]-'0';
						small_plus = X+1;   		
					}
					else
					{
						small = ch[p]-'0';
						small_plus = ch[r]-'0';
						big = ch[q]-'0';
						big_plus = X+1;
					}
					//X+1������һ�����õĲ��Σ��ò����ܴ��ڵĵ�X+1�����α�ʾ���м� 
					if(ed_feature_2[big][big_plus][small][small_plus]!=-1)
					v_1[ed_feature_2[big][big_plus][small][small_plus]].pass++;
					else
					{
						feature f;
						f.diw_fat = diw_fat;
						f.diw_thin =diw_thin;
						f.flag = 1;
						f.fat = big;
						f.fat_plus = big_plus;
						f.thin = small;
						f.thin_plus = small_plus;
						f.pass = 1;
						ed_feature_2[big][big_plus][small][small_plus]= amount_of_feature_2++;
						v_1.push_back(f);
					} 
					if(p>0)	p--;
					else r++;
					bingo = 1; 
				}
			}	
	}
//	if(bingo)
//	compare_2(a,b,ch,a_d,b_d);
	return ;
}
void compare_0(char str_1[],char str_2[],int fat,int thin,int amount_1,int amount_2)
{
	int number_1[I_X+1],number_2[I_X+1];
	for(int i=0 ; i<X ; i++)
	{
		number_1[str_1[i]-'0'] = i;
		number_2[str_2[i]-'0'] = i;
	}
	for(int i=0 ; i<X ; i++)
	{
		for(int j=i+1 ; j<X ; j++)
		{
			if((number_1[i]<number_1[j]) == (number_2[i]>number_2[j]))
			{
				int k;
				int temporary_fat = (number_1[i]>number_1[j])?i:j;
				int temporary_thin = (number_1[i]>number_1[j])?j:i;
//				int address = temporary_fat*100+temporary_thin;
				if(ed_feature_1[temporary_fat][temporary_thin]!=-1)
				v_0[ed_feature_1[temporary_fat][temporary_thin]].pass+=amount_1*amount_2;
				else
				{
					feature f;
					f.flag = 0;
					f.diw_fat =fat;
					f.diw_thin =thin;
					f.pass =amount_1*amount_2;
					f.fat = temporary_fat;
					f.thin = temporary_thin;
					f.fat_plus = X+1;
					f.thin_plus = X+1;
					ed_feature_1[temporary_fat][temporary_thin] = amount_of_feature++;
					v_0.push_back(f);
				}
			}
		}
	}
}
void compare_2(yangben a,yangben b,char ch[10],int a_d,int b_d)
{
	for(int i=0; i<X-1 ; i++)
	{
		for(int j=i+1 ; j<X ; j++)
		{
			int a_i = a.bo_duan[ch[i]-48].number;
			int a_j = a.bo_duan[ch[j]-48].number;
			int b_i = b.bo_duan[ch[i]-48].number;
			int b_j = b.bo_duan[ch[j]-48].number;	
			/***************************************С��չ*************************************/
			int buttom_a = max(2*a_i-a_j,1);
			int buttom_b = max(2*b_i-b_j,1);
			erci(buttom_a,buttom_b,a_d,b_d,i,j,0); 
			/***************************************����չ*************************************/
			buttom_a = (a_i+a_j)/2;
			buttom_b = (b_i+b_j)/2;
			erci(buttom_a,buttom_b,a_d,b_d,i,j,1);
			/***************************************����չ*************************************/
			buttom_a = 2*a_j-a_i;
			buttom_b = 2*a_j-a_i;
			erci(buttom_a,buttom_b,a_d,b_d,i,j,2);
		}
	}
}
int equl_f(feature a,feature b)
{
	if(a.flag != b.flag) return 0;
	if(a.diw_fat != b.diw_fat) return 0;
	if(a.diw_thin != b.diw_thin) return 0;
	if(a.fat==b.fat&&a.fat_plus==b.fat_plus&&a.thin==b.thin&&a.thin_plus==b.thin_plus)
	{
		if(a.flag==2 && a.number_of_bk!=b.number_of_bk) return 0;  
	} 
	return 1;
}
int lowbit(int x)
{
	return x&(-x);
}
void update(int tree[],int x,int pos)
{
	while(x<max_suggest*2+3)
	{
		tree[x] += pos;
		x += lowbit(x);
	}
	return ;
} 
int ffind(int tree[],int x)
{
	int sum = 0;
	while(x>0)
	{
//		printf("%d,tree[x]:%d\n",x,tree[x]);
		sum += tree[x];
		x -= lowbit(x);
	}
	return sum;
}
void erci(int buttom_a,int buttom_b,int a_d,int b_d,int i,int j,int type)
{
//	printf("a:%d\tb:%d\n",buttom_a,buttom_b);
	if(buttom_a == buttom_b)
	return; 
	feature f;
	f.flag = 2;
	f.type_2 = type;
	f.diw_fat = a_d;
	f.diw_thin = b_d;
	f.pass = 1;
	if(buttom_a>buttom_b)
	{
		switch(type)
		{
			case 0:{
				f.fat = j;
				f.fat_plus = 32;
				f.thin = i;
				f.thin_plus = X+1;
				break;
			}
			case 1:{				
				f.fat = j;
				f.fat_plus = i;
				f.thin = 32;
				f.thin_plus = X+1;
				break;
			}
			case 3:{
				f.fat = 32;
				f.fat_plus = i;
				f.thin = j;
				f.thin_plus = X+1;
				break;
			}
		 } 
		 f.number_of_bk = (buttom_a+buttom_b)/2;
	}
	else
	{
		switch(type)
		{
			case 0:{
				f.thin = j;
				f.thin_plus = 32;
				f.fat = i;
				f.fat_plus = X+1;
				break;
			}
			case 1:{				
				f.thin = j;
				f.thin_plus = i;
				f.fat = 32;
				f.fat_plus = X+1;
				break;
			}
			case 3:{
				f.thin = 32;
				f.thin_plus = i;
				f.fat = j;
				f.fat_plus = X+1;
				break;
			}
		 } 
		 f.number_of_bk = buttom_a-buttom_b;
	}
	if(ed_feature_3[f.fat][f.fat_plus][f.thin][f.thin_plus][f.type_2]!=-1)
	v_2[ed_feature_3[f.fat][f.fat_plus][f.thin][f.thin_plus][f.type_2]].pass++;
	else
	{
		v_2.push_back(f);
		ed_feature_3[f.fat][f.fat_plus][f.thin][f.thin_plus][f.type_2]=amount_of_feature_3++; 
	}
} 
double entropy(int shuzu[])
{
	double sum = 0;
	for(int i=0 ; i<D ; i++)
	{
		 sum+=shuzu[i];
	}
	double T=0;
	for(int i=0;i<D;i++)
	{
		if(shuzu[i]==0)
		{
//			printf("%d\n",shuzu[i]);			//��ֹ����Ƿ�ֵ������ʱ���� 
			continue;
		}
		T+=shuzu[i]*1.0/sum*log(shuzu[i]*1.0/sum)/log(2);
//		printf("T:%f\n",T);
	}
	return -T;
}
void C4_5(vector<yangben>word,double et)
{
//	if(feature_v.size()==0)
//	return ;
	printf("%f\n",et);
	forest trees[I_D];
	for(int i=0 ; i<D ; i++)
	{
		trees[i].tree = (int *)malloc(sizeof(int)*(max_suggest*2+3));
	}
//	printf("4��������ֲ���\n");
	int sum_of_word = word.size(); //��¼��������˿�
	vector<int>yu;					//������¼������ֵ 
	double max_GRT = 0;		//��¼������Ϣ����� 
	int max_yu = 0;			//��¼�����Ϣ���������Ӧ����ֵ 
	int address=0;
	for(int i=0 ; i<feature_v.size() ; i++)
	{
		if(feature_v[i].flag==-32) continue;
		printf("���ڷ�����%d������\n",i);
		int fat = feature_v[i].fat;
		int thin = feature_v[i].thin;
		int fat_plus = feature_v[i].fat_plus;
		int thin_plus = feature_v[i].thin_plus;
//		printf("fat:%d\tthin:%d\tfat_plus:%d\tthin_plus:%d\n",fat,thin,fat_plus,thin_plus);
		int temporary_yu;		//������ʱ��¼��ֵ
		for(int j=0 ; j<D ; j++)
		{
			memset(trees[j].tree,0,sizeof(int)*(max_suggest*2+3));
		} 
//		printf("����ʼ�����\n");
//		printf("%d\n",sum_of_word);
		for(int j=0 ; j<sum_of_word ; j++)
		{
//			printf("��ǰ����:%d\n",feature_v[i].flag);
			switch(feature_v[i].flag)
			{
				case 0:{
					temporary_yu = word[j].bo_duan[fat].number - word[j].bo_duan[thin].number;
					break;
				}
				case 1:{
					if(fat_plus==D) temporary_yu = word[j].bo_duan[fat].number - (word[j].bo_duan[thin].number+word[j].bo_duan[thin_plus].number)/2;
					else			temporary_yu = (word[j].bo_duan[fat].number+word[j].bo_duan[fat_plus].number)/2 - word[j].bo_duan[thin].number;
					break;
				}
				case -1:{
					temporary_yu = word[j].bo_duan[fat].number;
					break;
				}
			}
//			printf("temporary:%d\n",temporary_yu);
			yu.push_back(temporary_yu);
			update(trees[word[j].yangben_id].tree,temporary_yu+max_suggest+1,1);
//			if(j%10)printf("%d\n",j);
		}
//		printf("���Ľ������\n");
		int sum_of_yu = yu.size();	//��¼������ֵ�ĸ���;
		int left[I_D],right[I_D];
		for(int j=0 ; j<sum_of_yu ; j++)
		{
			for(int k=0 ; k<D ; k++)
			{
				left[k] = ffind(trees[k].tree,yu[j]+max_suggest);
				right[k] = ffind(trees[k].tree,max_suggest*2+2)-left[k];
			}
			double GRT = GainRatio(left,right,et);
//			printf("%f\n",GRT); 
			if(GRT>max_GRT)
			{
			 	max_GRT = GRT; 
				max_yu = yu[j];
				address = i;
			} 
		}
	}
	printf("�����Ϣ����ȣ�%f\t��ֵ��%d\t��ַ��%d\n",max_GRT,max_yu,address);
	vector<yangben>left_word;
	vector<yangben>right_word;
	int amount_of_left[I_D];
	int amount_of_right[I_D];
	memset(amount_of_left,0,sizeof(amount_of_left));
	memset(amount_of_right,0,sizeof(amount_of_right));
	int fat = feature_v[address].fat;
	int thin = feature_v[address].thin;
	int fat_plus = feature_v[address].fat_plus;
	int thin_plus = feature_v[address].thin_plus;
	for(int j=0 ; j<sum_of_word ; j++)
	{
		int temporary_yu;
		switch(feature_v[address].flag)
		{
			case 0:{
				temporary_yu = word[j].bo_duan[fat].number - word[j].bo_duan[thin].number;
				break;
			}
			case 1:{
				if(fat_plus==D) temporary_yu = word[j].bo_duan[fat].number - (word[j].bo_duan[thin].number+word[j].bo_duan[thin_plus].number)/2;
				else			temporary_yu = (word[j].bo_duan[fat].number+word[j].bo_duan[fat_plus].number)/2 - word[j].bo_duan[thin].number;
				break;
			}
			case -1:{
				temporary_yu = word[j].bo_duan[fat].number;
				break;
			}
		} 
		if(temporary_yu <= max_yu)
		{
			 left_word.push_back(word[j]);
			 amount_of_left[word[j].yangben_id] ++;
		}
		else 
		{
			right_word.push_back(word[j]);
			amount_of_right[word[j].yangben_id] ++;
		}
	}
	if(left_word.size()>100 && right_word.size()>100||1) 
	{ 
		printf("fat:%d\tthin:%d\tfat_plus:%d\tthin_plus:%d\n",feature_v[address].fat,feature_v[address].thin,feature_v[address].fat_plus,feature_v[address].thin_plus);
		printf("������������%d\t������������%d\n",left_word.size(),right_word.size());
	//	if(max_GRT<0.5) getchar();
                if(left_word.size()==0 || right_word.size()==0)return;
		feature_v[address].yu = max_yu;
		for(int i=0 ; i<D ; i++)
		{
			if(amount_of_left[i]<AMOUNT && amount_of_left[i]>AMOUNT/2)
			{
				vvv[i].f.push_back(feature_v[address]);
				vvv[i].ff.push_back(-1);
		    /*		if(stringg[i]=="") stringg[i] += str_1;
				else stringg[i] += " �� " +str_1;   */
			}
			printf("%5d",amount_of_left[i]);
		}
		printf("\n");
		for(int i=0 ; i<D ; i++)
		{
			if(amount_of_right[i]<AMOUNT && amount_of_right[i]>AMOUNT/2)
			{
				vvv[i].f.push_back(feature_v[address]);
				vvv[i].ff.push_back(1);
			   /*	if(stringg[i]=="") stringg[i] += str_2;
				else stringg[i] += " �� " +str_2;      */
			}
			printf("%5d",amount_of_right[i]);
		} 
		printf("\n");
		printf("-----------------------------------------------------------------------------\n");
	} 
	feature_v[address].flag = -32;							//������ù�������Ϊ-32 
//	printf("��ѡ����Ҫ�ݹ�ķ���\n��1����ݹ�\n��2���ҵݹ�\n��0�����ݹ�\n");
//	int select;
//	scanf("%d",&select);
//	getchar();
	double et_1 = entropy(amount_of_left);
	double et_2 = entropy(amount_of_right);
	if(left_word.size()>AMOUNT*3/2) C4_5(left_word,et_1);
	if(right_word.size()>AMOUNT*3/2) C4_5(right_word,et_2);
//	switch(select)
//	{
//		case 1:{
//			C4_5(left_word,et_1);
//			break;
//		}
//		case 2:{
//			C4_5(right_word,et_2);
//			break;
//		}
//		case 0:{
//			return ;
//			break;
//		}
//	}
}
double GainRatio(int left[],int right[],double et)
{
	double left_amount = 0;
	double right_amount = 0;
	for(int i=0 ; i<D ; i++)
	{
		left_amount += left[i];
		right_amount += right[i];
	} 
	if(!(left_amount+right_amount))	return 0;
	double lb = left_amount/(left_amount+right_amount);
	double rb = right_amount/(left_amount+right_amount);
	double Gain = et - (lb*entropy(left) + rb*entropy(right));
	if(!lb || !rb)
	return 0; 
	double SplitInfo = -(lb*log(lb)/log(2)+rb*log(rb)/log(2));
	return Gain/SplitInfo;
}
String str_int(int n)
{
        if(n==0)return 0;
    String s="";
    String number[10]={"0","1","2","3","4","5","6","7","8","9"};
    int flag_n=0;
    if(n<0)
    {
    	flag_n = 1;
    	n=-n;
    }
    while(n)
    {
        int i = n%10;
        s=number[i]+s;
        n/=10;
    }
    if(flag_n)
    s="-"+s;
    return s;
}
void clean_all()
{
	for(int i=0 ; i<D ; i++)
	{
		free((void *)(grand[i].pgp));
		printf("??\n");
		vvv[i].f.clear();
		vvv[i].ff.clear();
		fclose(fp[i]);
	}
	v_0.clear();
	v_1.clear();
	v_2.clear();
	amount_of_feature = 0;       
	amount_of_feature_2 = 0;
	amount_of_feature_3 = 0;	
	while(!q.empty())
	{
		q.pop();
	}	
	feature_v.clear();			 
} 




};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
