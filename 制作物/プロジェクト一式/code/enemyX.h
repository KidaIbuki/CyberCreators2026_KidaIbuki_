//=================================
// 
// 敵クラス　enemyX.h
//outher kida ibuki 
// 
//==================================
#ifndef _ENEMYX_H_
#define _ENEMYX_H_


#include "pch.h"   // プリコンパイル済みヘッダー
#include "objectX.h"  // オブジェクトX
#include "playerM.h"
#include "obb.h"
// 通常の敵クラス
class CEnemyX :public CObjectX
{
public:
	enum ENEMYSTATE
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_MAX,
	};

	CEnemyX();							// コンストラクタ
	~CEnemyX() override;				// デストラクタ
	HRESULT Init() override;			// 初期設定
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	static CEnemyX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1);

	ENEMYSTATE GetState() { return m_state; }

	void DrawOBB(ID3DXLine* pLine, const OBB& obb, IDirect3DDevice9* pDevice, D3DCOLOR color);  // ID3DXLineを使ってOBBを描画する関数
	void ProjectVertices(const std::vector<D3DXVECTOR3>& vertices, std::vector<D3DXVECTOR2>& projectedVertices, IDirect3DDevice9* pDevice);  // 3D座標を2Dスクリーン座標に変換する関数


private:

	bool m_bMove;     // 動いているか否かx軸
	bool m_bMove1;     // 動いているか否かy軸
	bool m_bTouch;  // 触れているかどうか

	//移動量などを格納する変数
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;	// 速さの格納変数1
    float m_fSpeedStorage1; // 速さの格納変数2

	ENEMYSTATE m_state;
	int m_nFrameCnt;       // 弾を飛ばすフレームのカウント
	int m_nFrame;          // フレーム保持用変数

	ID3DXLine* m_pLine;

};

// ボス敵クラス
class CEnemyBoss :public CEnemyX
{
public:
	CEnemyBoss();
	~CEnemyBoss();
	HRESULT Init() override;			// 初期設定
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	static CEnemyBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void DamageEnemy(int nDamage);
private:
	int m_nFrameCntBoss;       // 弾を飛ばすフレームのカウント
	int m_nFrame;          // フレーム保持用変数
	bool m_bMoveBoss;     // 動いているか否か
	int m_nLife;
	int m_nFrameEnemy;
};

#endif