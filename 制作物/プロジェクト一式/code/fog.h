//=================================
// 
// フォグクラス　　fog.h
// Auther kida ibuki 
// 
//==================================
#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"


class CFog
{
public:
	CFog();		    // コンストラクタ
	~CFog();		    // デストラクタ
	HRESULT Init();     // 初期設定
	void Uninit();		// 終了処理
	void Update();      // 更新処理
	void Draw();        // 描画処理 
private:
	float m_fFogDensity;  // 密度指定

	float m_fFogStartPos;  // フォグの開始位置
	float m_fFogEndPos;    // フォグの終了位置

	static const D3DXCOLOR COL;  // フォグカラー
	static constexpr float DENSITY = 0.0005f;  // 密度
};

#endif