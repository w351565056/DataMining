object Form1: TForm1
  Left = 489
  Top = 128
  Width = 462
  Height = 478
  Caption = #26174#31034#21407#22270#20687
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 56
    Top = 8
    Width = 385
    Height = 13
    AutoSize = False
    Caption = '*'#25171#24320#25991#20214#35831#36873#25321#21518#32512#21517#20026'br'#30340#25991#20214#65292#19968#33324#20026#26368#22823#30340#25991#20214#12290
  end
  object Button1: TButton
    Left = 136
    Top = 40
    Width = 145
    Height = 65
    Caption = #25171#24320#25991#20214
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 64
    Top = 128
    Width = 297
    Height = 257
    Caption = #21442#25968#36755#20837
    TabOrder = 1
    object Label1: TLabel
      Left = 120
      Top = 72
      Width = 36
      Height = 13
      AutoSize = False
      Caption = #34892#20540#65306
    end
    object Label2: TLabel
      Left = 104
      Top = 152
      Width = 48
      Height = 13
      AutoSize = False
      Caption = #27874#27573#25968#65306
    end
    object Label3: TLabel
      Left = 120
      Top = 112
      Width = 36
      Height = 13
      AutoSize = False
      Caption = #21015#20540#65306
    end
    object Label5: TLabel
      Left = 8
      Top = 24
      Width = 281
      Height = 13
      AutoSize = False
      Caption = '*'#27492#22788#21442#25968#21487#29992#35760#20107#26412#25171#24320'HDR'#25991#20214#35835#21462#21518#36755#20837
    end
    object Label6: TLabel
      Left = 16
      Top = 40
      Width = 265
      Height = 13
      AutoSize = False
      Caption = #20219#20309#21442#25968#38169#35823#36755#20837#37117#20250#23548#33268#26080#27861#27491#30830#36816#34892
    end
    object ComboBox1: TComboBox
      Left = 16
      Top = 64
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = 'R'
      OnChange = ComboBox1Change
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9')
    end
    object ComboBox2: TComboBox
      Left = 16
      Top = 104
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'G'
      OnChange = ComboBox2Change
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9')
    end
    object ComboBox3: TComboBox
      Left = 16
      Top = 144
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = 'B'
      OnChange = ComboBox3Change
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9')
    end
    object Edit1: TEdit
      Left = 160
      Top = 64
      Width = 81
      Height = 21
      TabOrder = 3
      OnChange = Edit1Change
    end
    object Edit2: TEdit
      Left = 160
      Top = 104
      Width = 81
      Height = 21
      TabOrder = 4
      OnChange = Edit2Change
    end
    object Edit3: TEdit
      Left = 160
      Top = 144
      Width = 81
      Height = 21
      TabOrder = 5
      OnChange = Edit3Change
    end
    object Button2: TButton
      Left = 80
      Top = 200
      Width = 121
      Height = 41
      Caption = #26174#31034#22270#20687
      TabOrder = 6
      OnClick = Button2Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 288
    Top = 72
  end
end
