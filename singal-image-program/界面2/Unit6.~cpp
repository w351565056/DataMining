//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{ 

}
//---------------------------------------------------------------------------


void __fastcall TForm6::Button2Click(TObject *Sender)
{
       String str = DBGrid1->SelectedField->AsString;
   //    Memo1->SetTextBuf(str.c_str());
       Form1->select_from_SQL(str);
       Form2->select_from_SQL(str);
       Form6->Visible = false;
}
void __fastcall TForm6::find()
{
        AnsiString sql="select * from dbo.see";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(sql);
        ADOQuery1->Open();
        DBGrid1->DataSource=DataSource1;
        for(int i=0 ; i<4 ; i++)
        DBGrid1->Columns->Items[i]->Width = i==3?150:100;
        DBGrid1->ReadOnly = true;
}
//---------------------------------------------------------------------------
