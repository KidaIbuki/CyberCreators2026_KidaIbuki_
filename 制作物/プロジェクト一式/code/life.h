//==================================
// 
// プレイヤーライフ クラス　life.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "object2D.h"   // オブジェクト2D
#include "pch.h"    // プリコンパイル済みヘッダー

class CLife :public CObject2D
{
public:
	CLife();
	~CLife();
	HRESULT Init()override;		//初期設定
	void Uninit()override;      //終了処理
	void Update()override;      //更新処理
	void Draw()override;		//描画処理
	static CLife* Create(D3DXVECTOR2 pos);

	static void SubLife(int nDamage);
private:
	static float m_fTexHeight;   // 縦
	static float m_fTexWidht;    // 横
	static int m_nFrame;   // フレームのカウント
	static int m_nLife;   // ライフ
};
#endif