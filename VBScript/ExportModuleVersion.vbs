Option Explicit

'-----------------------------------------------
' 定数定義
'-----------------------------------------------
Const LIST_FILE = ".\LMS_VersionList.txt"

'-----------------------------------------------
'メイン実行部
'-----------------------------------------------
Dim fsoObj
Dim objText

'オブジェクト生成
Set fsoObj = CreateObject("Scripting.FileSystemObject")

'ログファイルがあったら抹消
If fsoObj.FileExists(LIST_FILE) Then
  Call fsoObj.DeleteFile(LIST_FILE)
End If

'ログファイル準備
Set objText = fsoObj.OpenTextFile(LIST_FILE, 8, True, 0)

'処理対象パス設定
Dim sRootPath
Dim sAbsRootPath
sRootPath = ".\"
sAbsRootPath = fsoObj.GetAbsolutePathName(sRootPath)
objText.WriteLine("●対象フォルダ" & vbCrLf & sAbsRootPath & vbCrLf)

'バージョン情報出力
Call ExportModuleVersionList(sRootPath)

'ログファイルクローズ
objText.Close

'完了メッセージ表示
WScript.Echo("下記パス配下のモジュールファイルのバージョン情報を取得しました！" & vbCrLf & sAbsRootPath)

'オブジェクト開放
Set objText = Nothing
Set fsoObj = Nothing
 
Dim objWshShell
Dim objExec

Set objWshShell = CreateObject("WScript.Shell")
Set objExec = objWshShell.Exec("notepad.exe " & LIST_FILE)
'-----------------------------------------------

'*********************************************************
' ファイル一覧取得関数
'*********************************************************
Sub ExportModuleVersionList(inFolderPath)
    Dim bIsExistModule
    Dim fsoFolder
    Dim fsoSubFolder
    Dim fsoFile
    Dim sExtName
    Dim sFileName
    Dim sFileVersion
    Dim sAbsPath

    'フォルダオブジェクト取得
    Set fsoFolder = fsoObj.GetFolder(inFolderPath)

    'フォルダ内/ファイルループ
    Dim bIsPathExport
    bIsPathExport = False
    For Each fsoFile In fsoFolder.Files
        'ログに出力
        sExtName = fsoObj.GetExtensionName(fsoFile)
        '特定の拡張子のみを対象とする
        If sExtName = "exe" Or sExtName = "dll" Or sExtName = "ocx" Then
            '初回のみパス名を出力する
            If bIsPathExport = False Then
                '対象フォルダパスを出力
                sAbsPath = fsoObj.GetAbsolutePathName(inFolderPath)
                objText.WriteLine("[" & sAbsPath & "]")
                bIsPathExport = True
            End If
            'バージョン情報を出力する
            sFileName = fsoObj.GetFileName(fsoFile)
            sFileVersion = GetFileVersion(fsoFile)
            objText.WriteLine(sFileName & vbTab & sFileVersion)
        End If
    Next

    If bIsPathExport = True Then
        objText.WriteLine(vbCrLf)
    End If

    'フォルダ内/サブフォルダループ(サブフォルダが不要なら、このループは不要)
    For Each fsoSubFolder In fsoFolder.SubFolders
        'サブフォルダで再帰
        Call ExportModuleVersionList(fsoSubFolder)
    Next
End Sub

'*********************************************************
' ファイル一覧取得関数
'*********************************************************
Function GetFileVersion(pathspec)
   Dim fso, temp
   Set fso = CreateObject("Scripting.FileSystemObject")
   temp = fso.GetFileVersion(pathspec)
   If Len(temp) Then
      GetFileVersion = temp
   Else
      GetFileVersion = "バージョン情報はありません。"
   End If
End Function

