object Form6: TForm6
  Left = 844
  Top = 148
  Width = 671
  Height = 282
  Caption = #36164#28304#19977#21495#28023#23736#32447#25552#21462#31995#32479
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 489
    Height = 241
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object Button2: TButton
    Left = 504
    Top = 88
    Width = 129
    Height = 41
    Caption = #23548#20986#25152#36873#25968#25454
    TabOrder = 1
    OnClick = Button2Click
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 520
    Top = 208
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Ground_System;Data Source=LAPTOP-U5ESPP' +
      'MJ'
    Provider = 'SQLOLEDB.1'
    Left = 520
    Top = 168
  end
  object ADOQuery1: TADOQuery
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=Ground_System;Data Source=LAPTOP-U5ESPP' +
      'MJ'
    Parameters = <>
    Left = 576
    Top = 168
  end
end
