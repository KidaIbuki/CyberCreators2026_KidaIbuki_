//=================================
// 
// ビルボードクラス　object3D.h
//Auther kida ibuki 
// 
//==================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"    // オブジェクト

class CBillboard :public CObject
{
public:
	CBillboard();		//コンストラクタ
	~CBillboard() override;		//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CBillboard* Create();		//オブジェクトの生成

	//**===========テクスチャの設定=============**
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);	//テクスチャの設定
	void SetTexture(std::string sPath);

	//================各オブジェクト設定==================
	D3DXVECTOR3 GetPos() { return m_pos; }			//位置の取得
	D3DXVECTOR3 GetSize() { return m_size; }		//サイズの取得

	void SetPos(D3DXVECTOR3 pos);			//各オブジェクトの位置設定
	void SetSize(D3DXVECTOR3 size);//各オブジェクトのサイズ設定
	void SetBillboard(float fWidth, float fHeight, float fDepth);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetColor(D3DXCOLOR col); // カラー設定  赤（Max1.0ｆ）,緑（Max1.0ｆ）, 青（Max1.0ｆ）, α（Max1.0ｆ）
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_move;                         // 移動量
	D3DXVECTOR3 m_size;                         // サイズ
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファ
private:

	LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャ
	D3DXMATRIX m_mtxWorld;						// ワールド変換行列
	D3DXCOLOR m_col;
};

#endif