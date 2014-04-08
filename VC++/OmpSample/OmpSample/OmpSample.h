
// OmpSample.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// COmpSampleApp:
// このクラスの実装については、OmpSample.cpp を参照してください。
//

class COmpSampleApp : public CWinApp
{
public:
	COmpSampleApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern COmpSampleApp theApp;