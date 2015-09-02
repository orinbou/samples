
// MyPropertyTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMyPropertyTestApp:
// このクラスの実装については、MyPropertyTest.cpp を参照してください。
//

class CMyPropertyTestApp : public CWinApp
{
public:
	CMyPropertyTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMyPropertyTestApp theApp;