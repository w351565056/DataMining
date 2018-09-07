object Form5: TForm5
  Left = 971
  Top = 322
  BorderStyle = bsSingle
  Caption = #36164#28304#19977#21495#28023#23736#32447#25552#21462#31995#32479
  ClientHeight = 125
  ClientWidth = 357
  Color = clMoneyGreen
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 8
    Width = 160
    Height = 16
    Caption = #35831#36755#20837#26412#27425#23454#39564#21517#31216#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 56
    Width = 160
    Height = 16
    Caption = #35831#36873#25321#26412#27425#23454#39564#25928#26524#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 200
    Top = 8
    Width = 129
    Height = 21
    TabOrder = 0
    Text = #25105#30340#23454#39564
  end
  object ComboBox1: TComboBox
    Left = 200
    Top = 56
    Width = 129
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #20248
    Items.Strings = (
      #20248
      #33391
      #20013
      #24046
      #26080#25928)
  end
  object Button1: TButton
    Left = 136
    Top = 96
    Width = 73
    Height = 25
    Caption = #30830#23450
    TabOrder = 2
    OnClick = Button1Click
  end
  object ADOTable1: TADOTable
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Ground_System;Data Source=LAPTOP-U5ESPP' +
      'MJ'
    TableName = 'see'
    Left = 32
    Top = 80
  end
  object ADOTable2: TADOTable
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Ground_System;Data Source=LAPTOP-U5ESPP' +
      'MJ'
    TableName = 'G_sample'
    Left = 72
    Top = 80
  end
end
