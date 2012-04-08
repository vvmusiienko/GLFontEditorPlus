//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

#include "glfont2.cpp"
#include "stb_image.c"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Open1Click(TObject *Sender)
{
        if(OpenDialog1->Execute()) {
                font = new GLFont();
                if (! font->Create(OpenDialog1->FileName.c_str()) ) {
                        font = NULL;
                        ShowMessage("Can't open font!");
                        return;
                }

                currentCH = (font->texType == 120 ? 4 : 2);

                refreshStatusBar();
                // Filling with characters
                fillCharacters();

                refreshImage();
        }
}
//---------------------------------------------------------------------------

void TForm1::refreshStatusBar() {
        // Texture Width
        StatusBar1->Panels->Items[0]->Text = "Texture Width: " + IntToStr(font->header.tex_width);
        // Texture Height
        StatusBar1->Panels->Items[1]->Text = "Texture Height: " + IntToStr(font->header.tex_height);
        // Chars Range
        StatusBar1->Panels->Items[2]->Text = "Chars Range: " + IntToStr(font->header.start_char) + "-" + IntToStr(font->header.end_char);
        // Texture Type
        StatusBar1->Panels->Items[3]->Text = "Texture Type: " + (font->texType == 120 ? AnsiString("GL_RGBA") : AnsiString("GL_LUMINANCE_ALPHA"));
}


void TForm1::fillCharacters() {
        ListBox1->Items->Clear();

        for (int i = 0; i < font->header.end_char - font->header.start_char + 1; i++) {
                ListBox1->Items->Add(IntToStr(font->header.start_char + i) + " (" + (char)(font->header.start_char + i) + ")");

        }
}


void TForm1::refreshImage() {
        PaintBox1->Width = font->header.tex_width * zoom;
        PaintBox1->Height = font->header.tex_height * zoom;

        Image2->Width = font->header.tex_width * zoom;
        Image2->Height = font->header.tex_height * zoom;

        if (font->tex_bytes == NULL) {
                Image2->Picture = NULL;
                return;
        }

        if (currentCH == 2) {
                if (! stbi_write_bmp((path + "temp.bmp").c_str(), font->header.tex_width, font->header.tex_height, currentCH, font->tex_bytes ) ) {
                        ShowMessage("Can't save tmp data!");
                        return;
                }

                Image2->Picture->LoadFromFile(AnsiString((path + "temp.bmp").c_str()));
        } else {

                int zoom = 1;
                for (int x = 0; x < font->header.tex_width; x++) {
                        for (int y = 0; y < font->header.tex_height; y++) {
                                int index = (x / zoom) * font->header.tex_width * 4 + (y / zoom) * 4;
                                unsigned char r = (unsigned char)font->tex_bytes[index];
                                unsigned char g = (unsigned char)font->tex_bytes[index+1];
                                unsigned char b = (unsigned char)font->tex_bytes[index+2];

                                SetPixel(Image2->Canvas->Handle,y,x,(TColor)RGB(r, g, b));  //font->tex_bytes[(x / zoom) * 4 + (y / zoom) * 4];
                        }
                }
        }

}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        cursorStat = -1;
        font = NULL;
        gchar = NULL;
        zoom = 1;
        draging = false;
        memset(&tchar, 0, sizeof(tchar));

        path = string(Application->ExeName.c_str());
	for (int i = 1; i < path.size(); i++) {
		if (path[path.size()-i] == '\\') {
			path = path.substr(0, path.size()-i+1);
			break;
		}
	}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
        gchar = NULL;
        if (ListBox1->ItemIndex < 0)
                return;

	//Retrieve character size
        gchar = &font->header.chars[ListBox1->ItemIndex];

        refreshLabels();

        PaintBox1->Repaint();
        repaintShape();

}
//---------------------------------------------------------------------------


void TForm1::refreshLabels() {
        Edit1->Text = FloatToStr(gchar->tx1 * font->header.tex_width);
        Edit2->Text = FloatToStr(gchar->tx2 * font->header.tex_width);
        Edit3->Text = FloatToStr(gchar->ty1 * font->header.tex_height);
        Edit4->Text = FloatToStr(gchar->ty2 * font->header.tex_height);
        Edit5->Text = FloatToStr(gchar->dx * font->header.tex_width);
        Edit6->Text = FloatToStr(gchar->dy * font->header.tex_height);
}


void TForm1::repaintShape() {
        if (! gchar || !font)
                return;
        TRect r = TRect(gchar->tx1 * font->header.tex_width * zoom, gchar->ty1 * font->header.tex_width * zoom, gchar->tx2 * font->header.tex_width * zoom, gchar->ty2 * font->header.tex_width * zoom);

        PaintBox1->Canvas->Brush->Style = bsSolid;
        PaintBox1->Canvas->Brush->Color = 0x00ff00;
        PaintBox1->Canvas->FrameRect(r);
}

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
        repaintShape();
}
//---------------------------------------------------------------------------


void TForm1:: refreshCursorStatus(int x, int y) {
        cursorStat = -1;
        if (! gchar || !font)
                return;

        float x1 = gchar->tx1 * font->header.tex_width * zoom;
        float x2 = gchar->tx2 * font->header.tex_width * zoom;
        float y1 = gchar->ty1 * font->header.tex_height * zoom;
        float y2 = gchar->ty2 * font->header.tex_height * zoom;

        const float bold = 1 * zoom; 

        // top linr
        if (x >= x1 && x <= x2 && y >= y1 - bold && y <= y1 + bold)
                cursorStat = 0;
        // bottom line
        if (x >= x1 && x <= x2 && y >= y2 - bold && y <= y2 + bold)
                cursorStat = 1;
        // left line
        if (x >= x1 - bold && x <= x1 + bold && y >= y1 && y <= y2)
                cursorStat = 2;
        // left line
        if (x >= x2 - bold && x <= x2 + bold && y >= y1 && y <= y2)
                cursorStat = 3;
}

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

        static int lastX = X;
        static int lastY = Y;
        int dX = X - lastX;
        int dY = Y - lastY;
        lastX = X;
        lastY = Y;

        if (! draging) {
                refreshCursorStatus(X, Y);
        } else {

                // Logic for changing char rect
                if (gchar && font) {

                        // Sizing
                        if (ComboBox2->ItemIndex == 0) {
                                // top
                                if (cursorStat == 0) {
                                        gchar->ty1 += dY * (1.0f / (font->header.tex_height * zoom));
                                } else
                                // bottom
                                if (cursorStat == 1) {
                                        gchar->ty2 += dY * (1.0f / (font->header.tex_height * zoom));
                                } else
                                // left
                                if (cursorStat == 2) {
                                        gchar->tx1 += dX * (1.0f / (font->header.tex_width * zoom));
                                } else
                                // right
                                if (cursorStat == 3) {
                                        gchar->tx2 += dX * (1.0f / (font->header.tex_width * zoom));
                                }
                        } else {
                        // Moving
                                // vertical
                                if (cursorStat == 0 || cursorStat == 1) {
                                        gchar->ty1 += dY * (1.0f / (font->header.tex_height * zoom));
                                        gchar->ty2 += dY * (1.0f / (font->header.tex_height * zoom));
                                } else
                                // bottom
                                if (cursorStat == 2 || cursorStat == 3) {
                                        gchar->tx1 += dX * (1.0f / (font->header.tex_width * zoom));
                                        gchar->tx2 += dX * (1.0f / (font->header.tex_width * zoom));
                                }
                        }


                       refreshSize();
                       refreshLabels();
                       PaintBox1->Repaint();
                       repaintShape();
                }

        }

        if (cursorStat == 0 || cursorStat == 1) {
                PaintBox1->Cursor = crSizeNS;
        } else
        if (cursorStat == 2 || cursorStat == 3) {
                PaintBox1->Cursor = crSizeWE;
        } else {
                PaintBox1->Cursor = crDefault;
        }
}
//---------------------------------------------------------------------------


void TForm1::refreshSize() {
        gchar->dx = gchar->tx2 - gchar->tx1; //StrToFloat(Edit5->Text) / font->header.tex_width;
        gchar->dy = gchar->ty2 - gchar->ty1; //StrToFloat(Edit6->Text) / font->header.tex_height;
}


void TForm1::applyMetrics() {
        gchar->tx1 = StrToFloat(Edit1->Text) / font->header.tex_width;
        gchar->tx2 = StrToFloat(Edit2->Text) / font->header.tex_width;
        gchar->ty1 = StrToFloat(Edit3->Text) / font->header.tex_height;
        gchar->ty2 = StrToFloat(Edit4->Text) / font->header.tex_height;
        gchar->dx = gchar->tx2 - gchar->tx1; //StrToFloat(Edit5->Text) / font->header.tex_width;
        gchar->dy = gchar->ty2 - gchar->ty1; //StrToFloat(Edit6->Text) / font->header.tex_height;
        PaintBox1->Repaint();
        repaintShape();
        refreshLabels();
}


void TForm1::applySizing() {
        gchar->tx1 = StrToFloat(Edit1->Text) / font->header.tex_width;
        gchar->ty1 = StrToFloat(Edit3->Text) / font->header.tex_height;
        gchar->dx = StrToFloat(Edit5->Text) / font->header.tex_width;
        gchar->dy = StrToFloat(Edit6->Text) / font->header.tex_height;
        gchar->tx2 = gchar->tx1 + gchar->dx; //StrToFloat(Edit2->Text) / font->header.tex_width;
        gchar->ty2 = gchar->ty1 + gchar->dy; //StrToFloat(Edit4->Text) / font->header.tex_height;
        PaintBox1->Repaint();
        repaintShape();
        refreshLabels();
}


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        zoom = ComboBox1->ItemIndex + 1;
        refreshImage();
        repaintShape();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        draging = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        draging = false;         
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Exit1Click(TObject *Sender)
{
        exit(0);        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit5KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 13) {
                applySizing();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 13) {
                applyMetrics();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5KeyPress(TObject *Sender, char &Key)
{
        if (Key == 13) {
                applySizing();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
        tchar = *gchar;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
        *gchar = tchar;
        refreshLabels();
        PaintBox1->Repaint();
        repaintShape();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save2Click(TObject *Sender)
{
        if (! font) {
                ShowMessage("No font opened!");
                return;
        }

        if (SaveDialog2->Execute()) {
                if (! stbi_write_tga(SaveDialog2->FileName.c_str(), font->header.tex_width, font->header.tex_height, (font->texType == 120 ? 4 : 2), font->tex_bytes ) ) {
                        ShowMessage("Can't save image!");
                        return;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Load1Click(TObject *Sender)
{
        if (! font) {
                ShowMessage("Create new font first!");
                return;
        }

        if (OpenDialog2->Execute()) {

                int ch;
                int w, h;

	        unsigned char * buff = stbi_load(OpenDialog2->FileName.c_str(), &w, &h, &ch, 0);
	        if (!buff) {
                        ShowMessage("Can't open image!");
                        return;
                }

                currentCH = ch;

                if (ch == 2) {
                        font->texType = 0;
                } else {
                        font->texType = 120;
                        /*ShowMessage("Wrong chanel count! (" + IntToStr(ch) + ")");
                        return;*/
                }

                font->tex_bytes = buff;
                font->header.tex_width = w;
                font->header.tex_height = w;

                refreshStatusBar();
                refreshImage();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
        if (! font) {
                ShowMessage("No font opened!");
                return;
        }

        if (! font->tex_bytes) {
                ShowMessage("No texture assigned!");
                return;
        }

        if (OpenDialog1->Execute()) {

                // saving
                FILE* f = fopen(OpenDialog1->FileName.c_str(), "wb");
                if (! f) {
                        ShowMessage("Can't save!");
                        return;
                }

                font->header.tex = font->texType;
                fwrite(&font->header, sizeof(font->header), 1, f);

                //Allocate space for character array
	        int num_chars = font->header.end_char - font->header.start_char + 1;

	        //Write character array
	        fwrite((char *)font->header.chars, sizeof(GLFontChar) *  num_chars, 1, f);

	        //Write character array
	        fwrite((char *)font->tex_bytes, font->header.tex_width * font->header.tex_height * currentCH, 1, f);
                fclose(f);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{
        Form2->ShowModal();
}
//---------------------------------------------------------------------------

