//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	memoBST->Clear();
}
//---------------------------------------------------------------------------
int element = -1;
int target = -1;
int n = 5;
int rangeMax = 100;
bool autoDraw = false;
bool recursive = true;
BST bst;

void __fastcall TForm1::editElementChange(TObject *Sender)
{
	if (editElement->Text == "") {
		editElement->Text = "0";
	}
	element = StrToInt(editElement->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cbAutoDrawClick(TObject *Sender)
{
	autoDraw = cbAutoDraw->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::editTargetChange(TObject *Sender)
{
	if (editTarget->Text == "") {
		editTarget->Text = "0";
	}
	target = StrToInt(editTarget->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbCountChange(TObject *Sender)
{
	n = tbCount->Position;
	editCount->Text = IntToStr(n);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::editCountChange(TObject *Sender)
{
	n = StrToInt(editCount->Text);
	tbCount->Position = n;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbMaxChange(TObject *Sender)
{
	rangeMax = tbMax->Position;
	editMax->Text = IntToStr(rangeMax);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::editMaxChange(TObject *Sender)
{
	n = StrToInt(editMax->Text);
	tbMax->Position = n;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbNonRecursiveClick(TObject *Sender)
{
	recursive = !cbNonRecursive->Checked;
}
//---------------------------------------------------------------------------

// Function to print a vector as a formatted string
String printVector(const std::vector<int> &vec) {
	String msg = "";
	for (int num : vec) {
		msg += IntToStr(num) + "_";
	}
	return msg;
}

//---------------------------------------------------------------------------

// Event handler for inorder traversal button
void __fastcall TForm1::btnInorderClick(TObject *Sender)
{
	String msg;
	if (recursive) {
		msg = "Inorder (recursively):	" + printVector(bst.inorder());
	} else {
		msg = "Inorder (nonrecursively):	" + printVector(bst.inorderNonRecursive());
	}
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Event handler for preorder traversal button
void __fastcall TForm1::btnPreorderClick(TObject *Sender)
{
    String msg;
	if (recursive) {
		msg = "Preorder (recursively):	" + printVector(bst.preorder());
	} else {
		msg = "Preorder (nonrecursively):	" + printVector(bst.preorderNonRecursive());
	}
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Event handler for postorder traversal button
void __fastcall TForm1::btnPostorderClick(TObject *Sender)
{
	String msg;
	if (recursive) {
		msg = "Postorder (recursively):	" + printVector(bst.postorder());
	} else {
		msg = "Postsorder (nonrecursively):	" + printVector(bst.postorderNonRecursive());
	}
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Event handler for levelorder traversal button
void __fastcall TForm1::btnLevelorderClick(TObject *Sender)
{
	String msg = "Levelorder:	" + printVector(bst.levelorder());
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Function to insert random numbers into the BST
String insertRandomNumbers(int n, int min, int max) {
	String msg;
	int num;
	std::random_device rd;  // Obtain a random number from hardware
	std::mt19937 gen(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(min, max); // Define the range
	for (int i = 0; i < n; i++) {
		num = distr(gen);
		bst.insert(num); // Generate numbers and insert them into the BST
		msg += IntToStr(num) + "-";
	}
    return msg;
}

// Event handler for random insert button
void __fastcall TForm1::btnRandomInsertClick(TObject *Sender)
{
	String msg = insertRandomNumbers(n, 0, rangeMax);
	memoBST->Lines->Add(msg);
    msg = "Inorder (recursively):	" + printVector(bst.inorder());
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Event handler for search button
void __fastcall TForm1::btnSearchClick(TObject *Sender)
{
    if (target == -1) {
		ShowMessage("Please input a number");
		return;
	}
	bool result = bst.search(target);
	String msg = IntToStr(target);
	if (result) {
		msg += " has been found.";
	} else {
		msg += " has not been found.";
	}
	memoBST->Lines->Add(msg);
}
//---------------------------------------------------------------------------

// Calculate the height of the tree
int calculateTreeHeight(BSTNode* node) {
    if (!node) return 0;
    int leftHeight = calculateTreeHeight(node->left);
    int rightHeight = calculateTreeHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

// Calculate the maximum width of the tree
int calculateMaxWidth(BSTNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return calculateMaxWidth(node->left) + calculateMaxWidth(node->right);
}

// Helper function to calculate widths of each level
void calculateWidths(BSTNode* node, int depth, std::vector<int>& widths) {
    if (!node) return;
    if (depth >= widths.size()) {
        widths.push_back(0);
    }
    widths[depth]++;
    calculateWidths(node->left, depth + 1, widths);
    calculateWidths(node->right, depth + 1, widths);
}

// Draw lines connecting BST nodes
void DrawBSTNodeLines(TCanvas* Canvas, BSTNode* node, int x, int y, int hSpace, int vSpace, float zoomFactor) {
    if (!node) return;

    int nodeRadius = static_cast<int>(20 * zoomFactor); // Adjust node size based on zoom
    hSpace = static_cast<int>(hSpace * zoomFactor);
	vSpace = static_cast<int>(vSpace * zoomFactor);

    // Clamp hSpace and vSpace to reasonable limits to avoid floating point errors
    hSpace = std::max(1, std::min(hSpace, 1000)); // Example limits, adjust as needed
    vSpace = std::max(1, std::min(vSpace, 1000));

    // Draw the left child line
    if (node->left) {
        int newX = x - hSpace;
        int newY = y + vSpace;
        Canvas->MoveTo(x, y);
        Canvas->LineTo(newX, newY);
        DrawBSTNodeLines(Canvas, node->left, newX, newY, hSpace / 2, vSpace, zoomFactor);
    }

    // Draw the right child line
    if (node->right) {
        int newX = x + hSpace;
        int newY = y + vSpace;
        Canvas->MoveTo(x, y);
        Canvas->LineTo(newX, newY);
        DrawBSTNodeLines(Canvas, node->right, newX, newY, hSpace / 2, vSpace, zoomFactor);
    }
}

// Draw circles for BST nodes
void DrawBSTNodeCircles(TCanvas* Canvas, BSTNode* node, int x, int y, int hSpace, int vSpace, float zoomFactor) {
    if (!node) return;

    int nodeRadius = static_cast<int>(20 * zoomFactor); // Adjust node size based on zoom
    hSpace = static_cast<int>(hSpace * zoomFactor);
	vSpace = static_cast<int>(vSpace * zoomFactor);

    // Clamp hSpace and vSpace to reasonable limits to avoid floating point errors
    hSpace = std::max(1, std::min(hSpace, 1000)); // Example limits, adjust as needed
    vSpace = std::max(1, std::min(vSpace, 1000));

    // Draw the current node
    Canvas->Ellipse(x - nodeRadius, y - nodeRadius, x + nodeRadius, y + nodeRadius);
    Canvas->TextOut(x - 5, y - 5, IntToStr(node->data));

    // Draw the left child
    if (node->left) {
        int newX = x - hSpace;
        int newY = y + vSpace;
        DrawBSTNodeCircles(Canvas, node->left, newX, newY, hSpace / 2, vSpace, zoomFactor);
    }

    // Draw the right child
    if (node->right) {
        int newX = x + hSpace;
        int newY = y + vSpace;
        DrawBSTNodeCircles(Canvas, node->right, newX, newY, hSpace / 2, vSpace, zoomFactor);
    }
}

// Draw the entire BST
void DrawBST(TCanvas* Canvas, BSTNode* root, int x, int y, int offsetX, int offsetY, float zoomFactor) {
    if (!root) return;

    std::vector<int> widths;
    calculateWidths(root, 0, widths);
    int maxWidth = *std::max_element(widths.begin(), widths.end());
    int hSpace = std::max(50, 800 / (maxWidth + 1)); // Adjust horizontal space dynamically
    int vSpace = 60;  // Vertical space between levels

    // First pass: Draw lines
    DrawBSTNodeLines(Canvas, root, x + offsetX, y + offsetY, hSpace, vSpace, zoomFactor);



 // Second pass: Draw nodes
    DrawBSTNodeCircles(Canvas, root, x + offsetX, y + offsetY, hSpace, vSpace, zoomFactor);
}

// Variables for dragging and zooming
TPoint lastPos;  // Last mouse position for dragging
int offsetX = 0; // Horizontal offset for drawing
int offsetY = 0; // Vertical offset for drawing
bool dragging = false; // Flag to track dragging state
float zoomFactor = 1.0; // Zoom factor for scaling
const float zoomIncrement = 0.1; // Increment for zooming

// Function to draw the BST
void __fastcall TForm1::drawBST()
{
	zoomFactor = 1.0;
	offsetX = 0;
	offsetY = 0;
	TCanvas* Canvas = paintboxBST->Canvas;
	Canvas->Brush->Color = clWhite;
	Canvas->FillRect(paintboxBST->ClientRect); // Clear the canvas

	Canvas->Pen->Color = clBlack;
	Canvas->Brush->Color = clWhite;
	Canvas->Font->Color = clBlack;

	int x = paintboxBST->Width / 2; // Start from the center horizontally
	int y = 30; // Start drawing from this y-coordinate at the top of the canvas

	DrawBST(Canvas, bst.getRoot(), x, y, offsetX, offsetY, zoomFactor);
}

// Event handler for the draw button
void __fastcall TForm1::btnDrawClick(TObject *Sender)
{
	drawBST();
}
//---------------------------------------------------------------------------

// Event handler for mouse move event on the paintbox
void __fastcall TForm1::paintboxBSTMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
    if (dragging) {
        offsetX += (X - lastPos.x);
        offsetY += (Y - lastPos.y);
        lastPos = Point(X, Y);
		paintboxBST->Invalidate(); // Redraw the paint box
	}
}
//---------------------------------------------------------------------------

// Event handler for mouse down event on the paintbox
void __fastcall TForm1::paintboxBSTMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft) {
        dragging = true;
        lastPos = Point(X, Y);
    }
}
//---------------------------------------------------------------------------

// Event handler for paint event on the paintbox
void __fastcall TForm1::paintboxBSTPaint(TObject *Sender)
{
	TCanvas* Canvas = paintboxBST->Canvas;
	Canvas->Brush->Color = clWhite;
	Canvas->FillRect(paintboxBST->ClientRect); // Clear the canvas

	Canvas->Pen->Color = clBlack;
	Canvas->Brush->Color = clWhite;
	Canvas->Font->Color = clBlack;

	int x = paintboxBST->Width / 2; // Start from the center horizontally
	int y = 30; // Start drawing from this y-coordinate at the top of the canvas

	DrawBST(Canvas, bst.getRoot(), x, y, offsetX, offsetY, zoomFactor);
}
//---------------------------------------------------------------------------

// Event handler for mouse up event on the paintbox
void __fastcall TForm1::paintboxBSTMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if (Button == mbLeft) {
		dragging = false;
	}
}

// Event handler for mouse wheel event
void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled)
{
    if (Shift.Contains(ssCtrl)) {
        // Check if the mouse is over the paintboxBST
        if (paintboxBST->ClientRect.Contains(paintboxBST->ScreenToClient(MousePos))) {
            if (WheelDelta > 0) {
                if (zoomFactor < 10.0) { // Set an upper limit for zoom
                    zoomFactor += zoomIncrement;
                }
            } else {
                if (zoomFactor > zoomIncrement) { // Set a lower limit for zoom
                    zoomFactor -= zoomIncrement;
                }
            }
            paintboxBST->Invalidate(); // Redraw the paint box
            Handled = true;
        }
	}
}

//---------------------------------------------------------------------------

// Event handler for insert button
void __fastcall TForm1::btnInsertClick(TObject *Sender)
{
	if (element == -1) {
		ShowMessage("Please input a number");
		return;
	}
	bst.insert(element);
	String msg = IntToStr(element) + " has been inserted.";
	memoBST->Lines->Add(msg);
	msg = "Inorder (recursively):	" + printVector(bst.inorder());
	memoBST->Lines->Add(msg);
	if (autoDraw) {
		drawBST();
	}
}
//---------------------------------------------------------------------------

// Event handler for delete button
void __fastcall TForm1::btnDeleteClick(TObject *Sender)
{
	if (target == -1) {
		ShowMessage("Please input a number");
		return;
	}
	bool result = bst.deleteNode(target);
	String msg = IntToStr(target);
	if (result) {
		msg += " has been deleted.";
	} else {
		msg += " has not been found.";
	}
	memoBST->Lines->Add(msg);
	msg = "Inorder (recursively):	" + printVector(bst.inorder());
	memoBST->Lines->Add(msg);
    if (autoDraw) {
		drawBST();
	}
}

// Event handler for clear button
void __fastcall TForm1::btnClearClick(TObject *Sender)
{
	bst.clear();
	memoBST->Lines->Add("BST cleared");
	drawBST();
}

// Event handler for max edit exit
void __fastcall TForm1::editMaxExit(TObject *Sender)
{
    if (editMax->Text == "") {
		editMax->Text = "100";
	}
	if (StrToInt(editMax->Text) < 100) {
		editCount->Text = "5";
	}
	if (StrToInt(editMax->Text) > 10000) {
		editCount->Text = "100";
	}
	n = StrToInt(editMax->Text);
	tbMax->Position = n;
}
//---------------------------------------------------------------------------

// Event handler for count edit exit
void __fastcall TForm1::editCountExit(TObject *Sender)
{
    if (editCount->Text == "") {
		editCount->Text = "5";
	}
	if (StrToInt(editCount->Text) < 5) {
		editCount->Text = "5";
	}
    if (StrToInt(editCount->Text) > 100) {
		editCount->Text = "100";
	}
	n = StrToInt(editCount->Text);
	tbCount->Position = n;
}
//---------------------------------------------------------------------------
