//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

#include "glfont2.h"
#include <Buttons.hpp>
#include <string>

using namespace glfont;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TMenuItem *Image1;
        TImage *Image2;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TMenuItem *New1;
        TStatusBar *StatusBar1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TPaintBox *PaintBox1;
        TGroupBox *GroupBox1;
        TComboBox *ComboBox1;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TLabel *Label8;
        TEdit *Edit5;
        TEdit *Edit6;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TMenuItem *Load1;
        TMenuItem *Save2;
        TSaveDialog *SaveDialog2;
        TOpenDialog *OpenDialog2;
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Edit5KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit5KeyPress(TObject *Sender, char &Key);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall Save2Click(TObject *Sender);
        void __fastcall Load1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        std::string path;

        GLFont* font;
        GLFontChar *gchar; // Curent Char
        GLFontChar tchar; // Temp Char
        int currentCH; // current count of chanels

        int zoom; // curent zoom

        int cursorStat; // 0 - top line
                        // 1 - bottom line
                        // 2 - left line
                        // 3 - right line

        bool draging; // true if line draging

        void refreshStatusBar();
        void fillCharacters();
        void refreshImage();
        void repaintShape();
        void refreshLabels();
        void refreshCursorStatus(int x, int y);
        void applyMetrics();
        void applySizing();
        void refreshSize();


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
