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
	static const float LEFT;   // 各方向の移動する最大値
	static const float RIGHT;
	static const float UP;
	static const float DOWN;

	static const float BILLSIZE_X;   // ビルボードサイズ
	static const float BILLSIZE_Y;   // ビルボードサイズ
	static const float BILLSIZE_Z;   // ビルボードサイズ

	static const D3DXCOLOR INIT_COLOR;   // カラーの初期化
	static const D3DXCOLOR CHANGE_COLOR;   // カラーの変更
	static const D3DXCOLOR CHANGE_COLOR_ELSE;   // カラーを戻す

	static const float STICK_MOVE_X;   // スティックの移動量
	static const float STICK_MOVE_Y;   // スティックの移動量

	static const float POS_DISTANS;    // posからどれくらい離すか
};

#endif