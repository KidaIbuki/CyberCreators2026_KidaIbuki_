//=================================
// 
// uiクラス　ui.h
//outher kida ibuki 
// 
//==================================
#ifndef _UI_H_
#define _UI_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "object2D.h"  // オブジェクト2D

class CUi :public CObject2D
{
public:
	CUi();
	~CUi()override;
	HRESULT Init()override;		//初期設定
	void Uninit()override;      //終了処理
	void Update()override;      //更新処理
	void Draw()override;		//描画処理
	static CUi* Create(D3DXVECTOR2 pos, int nType);
	static void SubTime();
	int GetType() { return m_nType; }  // タイプの取得
private:
	int m_nType;   // 種類
	static int m_nFrame;
	static float m_fTexHeight;   // 縦
	static float m_fTexWidht;    // 横

	static const int FRAME;  // フレームのカウント
	static const float REDUCE_POS;  // テクスチャ座標を減らす

	static const float INITIAL_VALUE;   // 位置の初期値
	static const float TEX_RANGE;      // テクスチャの範囲

	// テクスチャのサイズ
	static const float TEX_SIZE_X_1;   
	static const float TEX_SIZE_Y_1;

	static const float TEX_SIZE_X_2;
	static const float TEX_SIZE_Y_2;

	static const float TEX_SIZE_X_3;
	static const float TEX_SIZE_Y_3;

	static const float TEX_SIZE_X_4;
	static const float TEX_SIZE_Y_4;

};
#endif