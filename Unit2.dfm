object Form2: TForm2
  Left = 308
  Top = 400
  Width = 383
  Height = 126
  Caption = 'New Font'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 5
    Top = 5
    Width = 366
    Height = 61
    Caption = 'Characters Range'
    TabOrder = 0
    object Label4: TLabel
      Left = 5
      Top = 20
      Width = 23
      Height = 13
      Caption = 'From'
    end
    object Label5: TLabel
      Left = 135
      Top = 20
      Width = 13
      Height = 13
      Caption = 'To'
    end
    object CSpinEdit3: TCSpinEdit
      Left = 35
      Top = 20
      Width = 81
      Height = 22
      TabOrder = 0
      Value = 32
    end
    object CSpinEdit4: TCSpinEdit
      Left = 155
      Top = 20
      Width = 81
      Height = 22
      TabOrder = 1
      Value = 127
    end
  end
  object BitBtn1: TBitBtn
    Left = 210
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    TabOrder = 1
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 295
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = BitBtn2Click
  end
end
