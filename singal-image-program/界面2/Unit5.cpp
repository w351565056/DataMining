//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm5::Button1Click(TObject *Sender)
{
        ADOTable1->Open();
        ADOTable1->Append();
        SYSTEMTIME t;
        GetLocalTime(&t);
        String mth = t.wMonth;
        String d = t.wDay;
        String h = t.wHour;
        String m = t.wMinute;
        String s = t.wSecond;
        String time_str =
        (String)t.wYear +"/"+
        ((mth.Length()==1)?("0"+mth):mth) + "/" +
        ((d.Length()==1)?("0"+d):d) + "  " + 
        ((h.Length()==1)?("0"+h):h) + " : "+
        ((m.Length()==1)?("0"+m):m) + " : "+
        ((s.Length()==1)?("0"+s):s);
        ADOTable1->FieldValues["实验时间"] = time_str;
        ADOTable1->FieldValues["实验名称"] = Edit1->Text;
        ADOTable1->FieldValues["实验评价"] = ComboBox1->Text;
        ADOTable1->Post();
        ADOTable1->Close();
        Form1->In_SQL();
        Form5->Visible = false;

        ADOTable2->Open();
        ADOTable2->Append();
        int x = Form1->ComboBox1->Text.ToInt();
        ADOTable2->FieldValues["地物个数"] = x;        
        String ssr[7] = {"1","2","3","4","5","6","7"};
        for(int i=0 ; i<x ; i++)
        {
                ADOTable2->FieldValues["Ground_" + ssr[i]] = Form2->address[i];
                ADOTable2->FieldValues["rule_" + ssr[i]] = Form2->stringg[i];
        }
        ADOTable2->Post();
        ADOTable2->Close();
        Form5->Visible = false;
}
//---------------------------------------------------------------------------
