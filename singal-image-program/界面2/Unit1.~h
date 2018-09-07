//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <CheckLst.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <vector>
#include <fstream>
using namespace std ;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit1;
        TButton *Button1;
        TComboBox *ComboBox2;
        TButton *Button2;
        TEdit *Edit2;
        TEdit *Edit3;
        TOpenDialog *OpenDialog1;
        TPanel *Panel3;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TPanel *Panel1;
        TLabel *Label7;
        TBitBtn *BitBtn3;
        TEdit *Edit4;
        TButton *Button3;
        TPanel *Panel4;
        TLabel *Label4;
        TComboBox *ComboBox3;
        TLabel *Label2;
        TComboBox *ComboBox1;
        TButton *Button4;
        TEdit *Edit5;
        TLabel *Label11;
        TButton *Button5;
        TSaveDialog *SaveDialog1;
        TLabel *Label8;
        TComboBox *ComboBox4;
        TButton *Button6;
        TBitBtn *BitBtn1;
        TLabel *Label9;
        TMemo *Memo1;
        TLabel *Label10;
        TButton *Button7;
        TLabel *Label12;
        TComboBox *ComboBox5;
        TCheckListBox *CheckListBox1;
        TLabel *Label13;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TADOTable *ADOTable1;
        TButton *Button11;
        TADOQuery *ADOQuery1;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TButton *Button12;
        TMemo *Memo2;
        TButton *Button13;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        int __fastcall check(int x,int y);
        int __fastcall is_sea(int x,int y);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall In_SQL();
        void __fastcall select_from_SQL(String str);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        String str_write;
        vector<int>sea_v;
String str_int(int n)
{
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
        
//******************************************************************************
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
