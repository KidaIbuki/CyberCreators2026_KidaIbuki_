﻿//=================================
// 
// 弾クラス　bullet.h
//Auther kida ibuki 
// 
//==================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "pch.h"        // プリコンパイル済みヘッダー
#include "billboard.h"   // ビルボード
#include "target.h"   // レティクル
#include "enemyX.h"   // 敵
#include "playerM.h"  // プレイヤー
class CBullet :public CBillboard
{
public:
	CBullet();    // コンストラクタ
	~CBullet();   // デストラクタ
	HRESULT Init() override;   // 初期設定
	void Uninit() override;    // 終了処理
	void Update() override;    // 更新処理
	void Draw() override;      // 描画処理
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);    // 生成処理



	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);    // 弾の設定
	static HRESULT Load();													//テクスチャのロード
	static void Unload();													//テクスチャのアンロード
	void Collision();
	int GetCount() { return m_nHitCnt; }    // 当てた回数の取得
protected:
	DWORD m_dwLifeTime;    // ライフのタイマー

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート

	static constexpr int LIFE = 1300;

private:
	int m_nHitCnt;

	static const D3DXCOLOR COL;   // 色

	static constexpr float RADIUS = 3.0f;  // 半径
	static constexpr float SPLIT = 1.0f;  // 分割
	static constexpr int EFFECTLIFE = 10;  // エフェクトのライフ
	static constexpr float BILLSIZE = 3.0f;  // ビルボードサイズ
	static constexpr float BULLETSIZE = 4.0f;  // 弾のサイズ

};
class CBulletEnemy : public CBullet
{
public:
	CBulletEnemy();    // コンストラクタ
	~CBulletEnemy();   // デストラクタ
	HRESULT Init() override;   // 初期設定
	void Uninit() override;    // 終了処理
	void Update() override;    // 更新処理
	void Draw() override;      // 描画処理
	static CBulletEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);    // 生成処理
	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);    // 弾の設定
	static HRESULT Load();													//テクスチャのロード
	static void Unload();													//テクスチャのアンロード

private:
	static const D3DXCOLOR COL;   // 色

	static constexpr float RADIUS = 5.0f;  // 半径
	static constexpr float SPLIT = 1.0f;  // 分割
	static constexpr int EFFECTLIFE = 10;  // エフェクトのライフ
	static constexpr float BILLSIZE = 5.0f;  // ビルボードサイズ
	static constexpr float BULLETSIZE = 10.0f;  // 弾のサイズ

};

#endif