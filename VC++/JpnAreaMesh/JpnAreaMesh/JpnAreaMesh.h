
// JpnAreaMesh.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CJpnAreaMeshApp:
// このクラスの実装については、JpnAreaMesh.cpp を参照してください。
//

class CJpnAreaMeshApp : public CWinApp
{
public:
	CJpnAreaMeshApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CJpnAreaMeshApp theApp;