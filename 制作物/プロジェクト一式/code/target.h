//=================================
// 
// 照準クラス　target.h
//outher kida ibuki 
// 
//==================================
#ifndef _TARGET_H_
#define _TARGET_H_

#include "billboard.h"  // ビルボード
#include "pch.h"  // プリコンパイル済みヘッダー
#include "enemyX.h"   // 敵

class CTarget :public CBillboard
{
public:
	CTarget();		//コンストラクタ
	~CTarget() override;		//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CTarget* Create(D3DXVECTOR3 pos);		//オブジェクトの生成
	void MoveTatget();
private:
	void CollisionTarget();
	int m_nTargetFrame;         // ターゲットを出現させるカウント
	bool m_bColor;
	static const int OVER;
	static const int OVER_UP;
	static const int OVER_DOWN;
};

#endif