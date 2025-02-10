//=================================
// 
// エフェクトクラス　effect.h
//outher kida ibuki 
// 
//==================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object.h"   // オブジェクト
#include "pch.h"    // プリコンパイル済みヘッダー

//マクロ定義
#define MAX_EFFECT (256) //エフェクト最大数
#define NUM_EFFECT (1) //エフェクトテクスチャの種類
#define INTERVAL_EFFECT (60.f) //インターバル時間
#define COUNT_EFFECT (60) //インターバルの(int)時間

class CEffect :public CObject
{
public:
    CEffect();			//コンストラクタ
    ~CEffect()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理
    void Draw()override;		//描画処理
    static CEffect* Create(D3DXVECTOR3 pos, D3DCOLOR col, int nType, float fRadius, float fSplit, float fAlpha, int nLife);
	void SetTexture(std::string sPath);

private:
	D3DXVECTOR3 m_pos;   //位置
	D3DXCOLOR m_col;     //色
	int  m_nType;        //種類識別
	float m_fRadius;     //半径（大きさ）
	int m_nLife;         //寿命（表示時間）
	bool m_bUse;         //使用しているかどうかの確認
	bool m_bStartTexture; //初期テクスチャの座標設定
	float m_Interval;  //インターバルチェック
	int m_EffectCnt;   //UV座標の更新に使うカウンター;
	float m_fSplit;       //横分割数
	float m_fAlpha;       //引きたいα値の設定

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列

};


#endif