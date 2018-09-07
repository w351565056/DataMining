object Form3: TForm3
  Left = 728
  Top = 184
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #36164#28304#19977#21495#21355#26143#22270#20687
  ClientHeight = 601
  ClientWidth = 684
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
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 681
    Height = 600
    AutoScroll = False
    TabOrder = 0
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 393
      Height = 353
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      OnMouseUp = Image1MouseUp
    end
  end
  object Memo1: TMemo
    Left = 712
    Top = 176
    Width = 17
    Height = 25
    Lines.Strings = (
      'M'
      'e'
      'm'
      'o1')
    TabOrder = 1
  end
end
