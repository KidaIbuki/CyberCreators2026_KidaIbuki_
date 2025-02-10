//=================================
// 
//ライトクラス　　light.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"   // メイン

#define MAX_LIGHT (3) //ライトの数
#define VEC_DIR (D3DXVECTOR3(0.22f, -0.87f, 0.44f))    // 1つ目のライトの方向ベクトルの設定
#define VEC_DIR1 (D3DXVECTOR3(-0.18f, 0.88f, -0.44f))  // 2つ目のライトの方向ベクトルの設定
#define VEC_DIR2 (D3DXVECTOR3(0.89f, 0.11f, 0.44f))    // 3つ目のライトの方向ベクトルの設定

//ライトのクラス定義
class CLight
{
public:
	CLight();		    //コンストラクタ
	~CLight();		    //デストラクタ
	HRESULT Init();     //初期設定
	void Uninit();		//終了処理
	void Update();      //更新処理
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //ライト構造体

};

#endif