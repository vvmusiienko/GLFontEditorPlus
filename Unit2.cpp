//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "glfont2.h"
#include <string>

using namespace glfont;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
        Form1->font = new GLFont();
        Form1->font->tex_bytes = NULL;
        Form1->font->header.start_char = CSpinEdit3->Value;
        Form1->font->header.end_char = CSpinEdit4->Value;

        // init chars
        int chars_num = Form1->font->header.end_char - Form1->font->header.start_char + 1;
        Form1->font->header.chars = new GLFontChar[chars_num];
        for (int i = 0; i < chars_num; i++) {
                Form1->font->header.chars[i].tx1 = 0.0f;
                Form1->font->header.chars[i].tx2 = 0.1f;
                Form1->font->header.chars[i].ty1 = 0.0f;
                Form1->font->header.chars[i].ty2 = 0.1f;
                Form1->font->header.chars[i].dx = 0.1f;
                Form1->font->header.chars[i].dy = 0.1f;
       }

       Form1->refreshStatusBar();
       Form1->refreshImage();
       Form1->repaintShape();
       Form1->fillCharacters();
       /*Form1->
       Form1->

        void
        void
        void refreshLabels();
        void refreshCursorStatus(int x, int y);
        void applyMetrics();
        void applySizing();
        void refreshSize(); */

       Close();
}
//---------------------------------------------------------------------------

