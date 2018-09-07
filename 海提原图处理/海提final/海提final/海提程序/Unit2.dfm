object Form2: TForm2
  Left = 255
  Top = 111
  Width = 917
  Height = 555
  VertScrollBar.Position = 77
  Caption = #25552#21462#28023#27700#20859#27542#21306
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 360
    Top = -77
    Width = 2000
    Height = 2000
  end
  object GroupBox1: TGroupBox
    Left = 48
    Top = -69
    Width = 241
    Height = 161
    Caption = #24050#36755#20837#21442#25968
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 48
      Width = 20
      Height = 13
      Caption = 'R'#65306
    end
    object Label2: TLabel
      Left = 8
      Top = 72
      Width = 36
      Height = 13
      Caption = #34892#20540#65306
    end
    object Label3: TLabel
      Left = 8
      Top = 104
      Width = 36
      Height = 13
      Caption = #21015#20540#65306
    end
    object Label4: TLabel
      Left = 8
      Top = 136
      Width = 48
      Height = 13
      Caption = #27874#27573#25968#65306
    end
    object Label5: TLabel
      Left = 24
      Top = 48
      Width = 32
      Height = 13
      Caption = 'Label5'
    end
    object Label6: TLabel
      Left = 48
      Top = 72
      Width = 32
      Height = 13
      Caption = 'Label6'
    end
    object Label7: TLabel
      Left = 48
      Top = 104
      Width = 32
      Height = 13
      Caption = 'Label7'
    end
    object Label8: TLabel
      Left = 64
      Top = 136
      Width = 32
      Height = 13
      Caption = 'Label8'
    end
    object Label12: TLabel
      Left = 8
      Top = 24
      Width = 60
      Height = 13
      Caption = #25991#20214#36335#24452#65306
    end
    object Label13: TLabel
      Left = 72
      Top = 24
      Width = 38
      Height = 13
      Caption = 'Label13'
    end
    object Label14: TLabel
      Left = 56
      Top = 48
      Width = 20
      Height = 13
      Caption = 'G'#65306
    end
    object Label15: TLabel
      Left = 72
      Top = 48
      Width = 38
      Height = 13
      Caption = 'Label15'
    end
    object Label16: TLabel
      Left = 104
      Top = 48
      Width = 19
      Height = 13
      Caption = 'B'#65306
    end
    object Label17: TLabel
      Left = 120
      Top = 48
      Width = 38
      Height = 13
      Caption = 'Label17'
    end
  end
  object GroupBox2: TGroupBox
    Left = 40
    Top = 123
    Width = 257
    Height = 297
    Caption = #25552#21462#28023#27700#20859#27542#21306#21442#25968#36755#20837
    TabOrder = 1
    object Label9: TLabel
      Left = 8
      Top = 128
      Width = 81
      Height = 13
      AutoSize = False
      Caption = #38754#31215#19979#30028#65306
      WordWrap = True
    end
    object Label10: TLabel
      Left = 8
      Top = 168
      Width = 81
      Height = 13
      AutoSize = False
      Caption = #38754#31215#19978#30028#65306
      WordWrap = True
    end
    object Label11: TLabel
      Left = 8
      Top = 208
      Width = 89
      Height = 13
      AutoSize = False
      Caption = #32039#23494#24230#19979#30028#65306
      WordWrap = True
    end
    object Label18: TLabel
      Left = 24
      Top = 32
      Width = 217
      Height = 13
      AutoSize = False
      Caption = '*'#36755#20837#25552#21462#21333#20010#28023#27700#20859#27542#21306#26631#20934
      WordWrap = True
    end
    object Label19: TLabel
      Left = 8
      Top = 48
      Width = 241
      Height = 13
      AutoSize = False
      Caption = #38754#31215#19979#30028'<='#31526#21512#35201#27714#30340#26001#22359'<='#38754#31215#19978#30028
      WordWrap = True
    end
    object Label20: TLabel
      Left = 24
      Top = 64
      Width = 209
      Height = 13
      AutoSize = False
      Caption = #32039#23494#24230#26368#22823#20540#20026'1'#65292#32039#23494#24230#36234#39640#65292
      WordWrap = True
    end
    object Label21: TLabel
      Left = 24
      Top = 80
      Width = 129
      Height = 13
      AutoSize = False
      Caption = #24403#21069#26001#22359#36234#35268#21017#12290
      WordWrap = True
    end
    object Edit1: TEdit
      Left = 104
      Top = 120
      Width = 81
      Height = 21
      TabOrder = 0
      OnChange = Edit1Change
    end
    object Edit2: TEdit
      Left = 104
      Top = 160
      Width = 81
      Height = 21
      TabOrder = 1
      OnChange = Edit2Change
    end
    object Edit3: TEdit
      Left = 104
      Top = 200
      Width = 81
      Height = 21
      TabOrder = 2
      OnChange = Edit3Change
    end
    object Button1: TButton
      Left = 24
      Top = 240
      Width = 169
      Height = 41
      Caption = #25552#21462#28023#27700#20859#27542#21306#22270#20687
      TabOrder = 3
      OnClick = Button1Click
    end
  end
  object Edit4: TEdit
    Left = 64
    Top = 433
    Width = 153
    Height = 21
    TabOrder = 2
  end
  object Button2: TButton
    Left = 88
    Top = 465
    Width = 105
    Height = 25
    Caption = #30446#26631#25991#20214
    TabOrder = 3
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Left = 248
    Top = 416
  end
end
