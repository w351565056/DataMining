object Form2: TForm2
  Left = 723
  Top = 157
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #22320#29289#21306#20998
  ClientHeight = 663
  ClientWidth = 697
  Color = clGray
  TransparentColorValue = clMoneyGreen
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PrintScale = poNone
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 616
    Width = 696
    Height = 110
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    TabOrder = 0
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 697
    Height = 600
    AutoScroll = False
    TabOrder = 1
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 377
      Height = 321
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      OnMouseUp = Image1MouseUp
    end
  end
  object BitBtn1: TBitBtn
    Left = 0
    Top = 600
    Width = 697
    Height = 26
    Caption = #26174#31034#35268#21017#9660
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object ADOQuery1: TADOQuery
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Ground_System;Data Source=LAPTOP-U5ESPP' +
      'MJ'
    Parameters = <>
    Left = 704
    Top = 152
  end
end
