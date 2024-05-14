object Form1: TForm1
  Left = 0
  Top = 0
  Width = 866
  Height = 767
  AutoScroll = True
  AutoSize = True
  BorderWidth = 10
  Caption = 'HW6 Binary Search Tree'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnMouseWheel = FormMouseWheel
  TextHeight = 15
  object Label1: TLabel
    Left = 0
    Top = 355
    Width = 106
    Height = 15
    Caption = '# of Integers (5-100)'
  end
  object Label2: TLabel
    Left = 0
    Top = 456
    Width = 97
    Height = 15
    Caption = 'Range (100-10000)'
  end
  object PageControl1: TPageControl
    Left = 128
    Top = 0
    Width = 700
    Height = 700
    ActivePage = tsBST
    TabOrder = 0
    object tsBST: TTabSheet
      Caption = 'Inorder sequence of BST'
      object memoBST: TMemo
        Left = 3
        Top = 3
        Width = 686
        Height = 662
        Lines.Strings = (
          'memoBST')
        ReadOnly = True
        TabOrder = 0
      end
    end
    object tsDrawing: TTabSheet
      Caption = 'BST Drawing'
      ImageIndex = 1
      object paintboxBST: TPaintBox
        Left = 3
        Top = 3
        Width = 686
        Height = 664
        OnMouseDown = paintboxBSTMouseDown
        OnMouseMove = paintboxBSTMouseMove
        OnMouseUp = paintboxBSTMouseUp
        OnPaint = paintboxBSTPaint
      end
    end
  end
  object btnInsert: TButton
    Left = 0
    Top = 29
    Width = 100
    Height = 25
    Caption = 'Insert'
    TabOrder = 1
    OnClick = btnInsertClick
  end
  object editElement: TEdit
    Left = 0
    Top = 0
    Width = 100
    Height = 23
    MaxLength = 5
    NumbersOnly = True
    TabOrder = 2
    TextHint = 'Element'
    OnChange = editElementChange
  end
  object cbAutoDraw: TCheckBox
    Left = 0
    Top = 60
    Width = 100
    Height = 17
    Caption = 'Auto Drawing'
    TabOrder = 3
    OnClick = cbAutoDrawClick
  end
  object editTarget: TEdit
    Left = 0
    Top = 96
    Width = 100
    Height = 23
    MaxLength = 5
    NumbersOnly = True
    TabOrder = 4
    TextHint = 'Target'
    OnChange = editTargetChange
  end
  object btnDelete: TButton
    Left = 0
    Top = 156
    Width = 100
    Height = 25
    Caption = 'Delete'
    TabOrder = 5
    OnClick = btnDeleteClick
  end
  object tbCount: TTrackBar
    Left = 0
    Top = 376
    Width = 100
    Height = 45
    Max = 100
    Min = 5
    Frequency = 5
    Position = 5
    TabOrder = 6
    OnChange = tbCountChange
  end
  object editCount: TEdit
    Left = 0
    Top = 419
    Width = 100
    Height = 23
    MaxLength = 3
    NumbersOnly = True
    TabOrder = 7
    Text = '5'
    TextHint = '# of Integers'
    OnChange = editCountChange
    OnExit = editCountExit
  end
  object tbMax: TTrackBar
    Left = 0
    Top = 477
    Width = 100
    Height = 45
    Max = 10000
    Min = 100
    Frequency = 500
    Position = 100
    TabOrder = 8
    OnChange = tbMaxChange
  end
  object editMax: TEdit
    Left = 0
    Top = 515
    Width = 100
    Height = 23
    MaxLength = 5
    NumbersOnly = True
    TabOrder = 9
    Text = '100'
    TextHint = 'Range'
    OnChange = editMaxChange
    OnExit = editMaxExit
  end
  object btnRandomInsert: TButton
    Left = 0
    Top = 544
    Width = 100
    Height = 25
    Caption = 'Random Insert'
    TabOrder = 10
    OnClick = btnRandomInsertClick
  end
  object btnDraw: TButton
    Left = 0
    Top = 588
    Width = 100
    Height = 25
    Caption = 'Draw BST'
    TabOrder = 11
    OnClick = btnDrawClick
  end
  object btnClear: TButton
    Left = 0
    Top = 619
    Width = 100
    Height = 25
    Caption = 'Clear BST'
    TabOrder = 12
    OnClick = btnClearClick
  end
  object btnInorder: TButton
    Left = 0
    Top = 195
    Width = 100
    Height = 25
    Caption = 'Inorder'
    TabOrder = 13
    OnClick = btnInorderClick
  end
  object btnPreorder: TButton
    Left = 0
    Top = 226
    Width = 100
    Height = 25
    Caption = 'Preorder'
    TabOrder = 14
    OnClick = btnPreorderClick
  end
  object btnPostorder: TButton
    Left = 0
    Top = 257
    Width = 100
    Height = 25
    Caption = 'Postorder'
    TabOrder = 15
    OnClick = btnPostorderClick
  end
  object btnLevelorder: TButton
    Left = 0
    Top = 288
    Width = 100
    Height = 25
    Caption = 'Levelorder'
    TabOrder = 16
    OnClick = btnLevelorderClick
  end
  object cbNonRecursive: TCheckBox
    Left = 0
    Top = 319
    Width = 100
    Height = 17
    Caption = 'Non-recursive'
    TabOrder = 17
    OnClick = cbNonRecursiveClick
  end
  object btnSearch: TButton
    Left = 0
    Top = 125
    Width = 100
    Height = 25
    Caption = 'Search'
    TabOrder = 18
    OnClick = btnSearchClick
  end
end
