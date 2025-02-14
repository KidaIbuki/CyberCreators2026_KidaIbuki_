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
	static float m_fTexWidth;    // 横
	static int m_nFrame;   // フレームのカウント
	static int m_nLife;   // ライフ

	static const float TEX_HEIGHT;  // テクスチャの縦の初期値
	static const float TEX_WIDTH;   // テクスチャの横の初期値
	static const float TEX_SIZE_X;   // テクスチャのサイズ
	static const float TEX_SIZE_Y;   // テクスチャのサイズ
	static const float TEX_MOVE_H;   // テクスチャの移動
	static const float TEX_MOVE_W;   // テクスチャの移動

	static const int FRAME;         // フレーム
	static const int LIFE;          // ライフ
};
#endif