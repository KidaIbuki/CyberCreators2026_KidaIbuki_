//=================================
// 
// ポーズ クラス　pause.h
//outher kida ibuki 
// 
//==================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "object2D.h"   // オブジェクト2D

class CSelect :public CObject2D
{
public:
	CSelect();
	~CSelect()override;
	virtual HRESULT Init() = 0;		//初期設定
	virtual void Uninit() = 0;      //終了処理
	virtual void Update() = 0;      //更新処理
	virtual void Draw() = 0;		//描画処理
	virtual void SetType(int type) = 0;
	virtual int GetType() { return m_nType; }   // タイプの取得
	int m_nType;
private:
};

#endif