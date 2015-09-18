
// ClassInheritABTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CClassInheritABTestApp:
// このクラスの実装については、ClassInheritABTest.cpp を参照してください。
//

class CClassInheritABTestApp : public CWinApp
{
public:
	CClassInheritABTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CClassInheritABTestApp theApp;