//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "lib/bst.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *tsBST;
	TTabSheet *tsDrawing;
	TButton *btnInsert;
	TEdit *editElement;
	TCheckBox *cbAutoDraw;
	TEdit *editTarget;
	TButton *btnDelete;
	TTrackBar *tbCount;
	TEdit *editCount;
	TTrackBar *tbMax;
	TEdit *editMax;
	TButton *btnRandomInsert;
	TButton *btnDraw;
	TButton *btnClear;
	TLabel *Label1;
	TLabel *Label2;
	TButton *btnInorder;
	TButton *btnPreorder;
	TButton *btnPostorder;
	TButton *btnLevelorder;
	TCheckBox *cbNonRecursive;
	TMemo *memoBST;
	TButton *btnSearch;
	TPaintBox *paintboxBST;
	void __fastcall editElementChange(TObject *Sender);
	void __fastcall cbAutoDrawClick(TObject *Sender);
	void __fastcall editTargetChange(TObject *Sender);
	void __fastcall tbCountChange(TObject *Sender);
	void __fastcall editCountChange(TObject *Sender);
	void __fastcall tbMaxChange(TObject *Sender);
	void __fastcall editMaxChange(TObject *Sender);
	void __fastcall cbNonRecursiveClick(TObject *Sender);
	void __fastcall btnInsertClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
	void __fastcall btnInorderClick(TObject *Sender);
	void __fastcall btnPreorderClick(TObject *Sender);
	void __fastcall btnPostorderClick(TObject *Sender);
	void __fastcall btnLevelorderClick(TObject *Sender);
	void __fastcall btnClearClick(TObject *Sender);
	void __fastcall btnRandomInsertClick(TObject *Sender);
	void __fastcall btnSearchClick(TObject *Sender);
	void __fastcall btnDrawClick(TObject *Sender);
	void __fastcall paintboxBSTMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall paintboxBSTMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall paintboxBSTPaint(TObject *Sender);
	void __fastcall paintboxBSTMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
	void __fastcall editMaxExit(TObject *Sender);
	void __fastcall editCountExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void __fastcall drawBST();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
