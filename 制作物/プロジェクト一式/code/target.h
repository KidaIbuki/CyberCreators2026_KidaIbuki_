//=================================
// 
// 照準クラス　target.h
// Auther kida ibuki 
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

	static const D3DXCOLOR INIT_COLOR;   // カラーの初期化
	static const D3DXCOLOR CHANGE_COLOR;   // カラーの変更
	static const D3DXCOLOR CHANGE_COLOR_ELSE;   // カラーを戻す

	static constexpr float LEFT = 250.0f;  // 各方向の移動の最大値
	static constexpr float RIGHT = 250.0f;
	static constexpr float UP = 100.0f;
	static constexpr float DOWN = 170.0f;

	static constexpr float BILLSIZE_X = 20.0f;   // 各ビルボードサイズ
	static constexpr float BILLSIZE_Y = 40.0f;
	static constexpr float BILLSIZE_Z = 20.0f;

	// スティックの移動量
	static constexpr float STICK_MOVE_X = 0.0001f;
	static constexpr float STICK_MOVE_Y = 0.0001f;

	static constexpr float POS_DISTANS = 150.0f;  // posからどれくらい離すか


};

#endif