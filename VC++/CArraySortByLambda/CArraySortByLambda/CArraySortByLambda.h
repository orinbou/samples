
// CArraySortByLambda.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CCArraySortByLambdaApp:
// このクラスの実装については、CArraySortByLambda.cpp を参照してください。
//

class CCArraySortByLambdaApp : public CWinApp
{
public:
	CCArraySortByLambdaApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCArraySortByLambdaApp theApp;