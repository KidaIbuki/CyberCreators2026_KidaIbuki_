//=================================
// 
// ボス戦背景クラス　background.h
//Auther kida ibuki 
// 
//==================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "object3D.h"   // オブジェクト3D



// ボス戦背景クラス
class CBackGround :public CObject3D
{
public:
	CBackGround();					//コンストラクタ
	~CBackGround() override;			//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CBackGround* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);    //生成処理
	static HRESULT Load();				//テクスチャのロード
	static void Unload();				//テクスチャのアンロード
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート

	// 背景のサイズ
	static constexpr float FIELD_X = 100.0f;
	static constexpr float FIELD_Z = 6000.0f;
	// 背景の動く速度
	static constexpr float MOVE_Y = 0.003f;


};


#endif
