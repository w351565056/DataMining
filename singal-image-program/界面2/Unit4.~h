//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox1;
        TImage *Image1;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall find_the_line();
        void __fastcall dfs(int x,int y);
        void __fastcall redfs(int x,int y);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
        int HANG;
        int LIE;
        POINT mouse_start,mouse_end;
        int mouse_is_down;
        int **change;
        int **change1;
        int max_length;
        int address_of_x;
        int address_of_y;
        String TXT2;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
