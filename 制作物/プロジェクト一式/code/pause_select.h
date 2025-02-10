//=================================
// 
// ポーズ用 クラス　pause_select.h
//outher kida ibuki 
// 
//==================================
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "select.h"  // セレクト

class CGame;
class CPause_Select :public CSelect
{
public:
	CPause_Select();
	~CPause_Select()override;
	HRESULT Init()override;		//初期設定
	void Uninit()override;      //終了処理
	void Update()override;      //更新処理
	void Draw()override;		//描画処理
	void SetType(int type)override;
	static CPause_Select* Create(D3DXVECTOR2 pos, D3DXVECTOR2 siz, int type);
private:
};

#endif