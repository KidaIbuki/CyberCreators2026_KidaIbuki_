//=================================
// 
// パーティクル クラス　particle.h
//outher kida ibuki 
// 
//==================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "object3D.h"    // オブジェクト3D
#include "pch.h"     // プリコンパイル済みヘッダー

class CExplosion :public CObject3D
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init()override;		//初期設定
	void Uninit()override;      //終了処理
	void Update()override;      //更新処理
	void Draw()override;		//描画処理
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static HRESULT Load();													//テクスチャのロード
	static void Unload();													//テクスチャのアンロード

private:
	bool m_bUse;         // 使用されているかどうか
	float m_fRadius;     // 半径
	D3DXCOLOR m_col;     // カラー
	int m_nLife;         // ライフ
	DWORD m_dwLifeTime;    // ライフのタイマー
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート
	static const int LIFE;				//ライフ
	static const int DIVIDE;   // アニメーションの分割数
	static const int TIME;     // アニメーションのタイプ
	static const float SIZE_X;   // テクスチャサイズ
	static const float SIZE_Z;   // テクスチャサイズ
};



#endif