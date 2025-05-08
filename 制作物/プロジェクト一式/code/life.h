//==================================
// 
// プレイヤーライフ クラス　life.h
// Auther kida ibuki 
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
	static float m_fTexWidth;    // 横
	static int m_nFrame;   // フレームのカウント
	static int m_nLife;   // ライフ


	static constexpr float TEX_HEIGHT = 0.0f;   // テクスチャの縦の初期値
	static constexpr float TEX_WIDTH = 0.1f;    // テクスチャの横の初期値
	static constexpr float TEX_SIZE_X = 120.0f;   // テクスチャサイズx
	static constexpr float TEX_SIZE_Y = 350.0f;   // テクスチャサイズy
	static constexpr float TEX_MOVE_H = 0.1f;   // テクスチャ移動height
	static constexpr float TEX_MOVE_W = 0.1f;   // テクスチャ移動width

	static constexpr int FRAME = 3;     // カウントフレーム
	static constexpr int LIFE = 100;    // ライフ

};
#endif