Option Explicit

'-----------------------------------------------
' �萔��`
'-----------------------------------------------
Const LIST_FILE = ".\LMS_VersionList.txt"

'-----------------------------------------------
'���C�����s��
'-----------------------------------------------
Dim fsoObj
Dim objText

'�I�u�W�F�N�g����
Set fsoObj = CreateObject("Scripting.FileSystemObject")

'���O�t�@�C�����������疕��
If fsoObj.FileExists(LIST_FILE) Then
  Call fsoObj.DeleteFile(LIST_FILE)
End If

'���O�t�@�C������
Set objText = fsoObj.OpenTextFile(LIST_FILE, 8, True, 0)

'�����Ώۃp�X�ݒ�
Dim sRootPath
Dim sAbsRootPath
sRootPath = ".\"
sAbsRootPath = fsoObj.GetAbsolutePathName(sRootPath)
objText.WriteLine("���Ώۃt�H���_" & vbCrLf & sAbsRootPath & vbCrLf)

'�o�[�W�������o��
Call ExportModuleVersionList(sRootPath)

'���O�t�@�C���N���[�Y
objText.Close

'�������b�Z�[�W�\��
WScript.Echo("���L�p�X�z���̃��W���[���t�@�C���̃o�[�W���������擾���܂����I" & vbCrLf & sAbsRootPath)

'�I�u�W�F�N�g�J��
Set objText = Nothing
Set fsoObj = Nothing
 
Dim objWshShell
Dim objExec

Set objWshShell = CreateObject("WScript.Shell")
Set objExec = objWshShell.Exec("notepad.exe " & LIST_FILE)
'-----------------------------------------------

'*********************************************************
' �t�@�C���ꗗ�擾�֐�
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

    '�t�H���_�I�u�W�F�N�g�擾
    Set fsoFolder = fsoObj.GetFolder(inFolderPath)

    '�t�H���_��/�t�@�C�����[�v
    Dim bIsPathExport
    bIsPathExport = False
    For Each fsoFile In fsoFolder.Files
        '���O�ɏo��
        sExtName = fsoObj.GetExtensionName(fsoFile)
        '����̊g���q�݂̂�ΏۂƂ���
        If sExtName = "exe" Or sExtName = "dll" Or sExtName = "ocx" Then
            '����̂݃p�X�����o�͂���
            If bIsPathExport = False Then
                '�Ώۃt�H���_�p�X���o��
                sAbsPath = fsoObj.GetAbsolutePathName(inFolderPath)
                objText.WriteLine("[" & sAbsPath & "]")
                bIsPathExport = True
            End If
            '�o�[�W���������o�͂���
            sFileName = fsoObj.GetFileName(fsoFile)
            sFileVersion = GetFileVersion(fsoFile)
            objText.WriteLine(sFileName & vbTab & sFileVersion)
        End If
    Next

    If bIsPathExport = True Then
        objText.WriteLine(vbCrLf)
    End If

    '�t�H���_��/�T�u�t�H���_���[�v(�T�u�t�H���_���s�v�Ȃ�A���̃��[�v�͕s�v)
    For Each fsoSubFolder In fsoFolder.SubFolders
        '�T�u�t�H���_�ōċA
        Call ExportModuleVersionList(fsoSubFolder)
    Next
End Sub

'*********************************************************
' �t�@�C���ꗗ�擾�֐�
'*********************************************************
Function GetFileVersion(pathspec)
   Dim fso, temp
   Set fso = CreateObject("Scripting.FileSystemObject")
   temp = fso.GetFileVersion(pathspec)
   If Len(temp) Then
      GetFileVersion = temp
   Else
      GetFileVersion = "�o�[�W�������͂���܂���B"
   End If
End Function

