//=================================
// 
// 階層構造player　playerM.h
//outher kida ibuki 
// 
//==================================
#ifndef _PLAYERM_H_
#define _PLAYERM_H_

#include "object.h"    // オブジェクト
#include "life.h"      // ライフ
#include "motion.h"

#define MAX_CHAR (256)   // 読み込む文の最大数

class CPlayerM :public CObjectMotion
{
public:
	// 攻撃状態
	typedef enum
	{
		BULLET_NONE = 0,
		BULLET_SHOT,
		BULLET_MAX
	}BULLET_TYPE;
    // プレイヤーの状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;
	CPlayerM();    // コンストラクタ
	~CPlayerM();   // デストラクタ
	HRESULT Init() override;    // 初期設定
	void Uninit() override;     // 終了処理
	void Update() override;     // 更新処理
	void Draw() override;       // 描画処理
	static CPlayerM* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);   // 生成処理
	//void SetPos(D3DXVECTOR3 pos);   // 位置設定
	//void SetRot(D3DXVECTOR3 rot);   // 向き設定
	D3DXVECTOR3 PlayerMove();   // プレイヤーの移動処理
	//D3DXVECTOR3 GetPos() { return m_pos; }  // 階層構造のposの取得
	//D3DXVECTOR3 GetSize() { return m_pModel->m_size; }		//サイズの取得
	void ResetPlayer();   // プレイヤーのx軸の位置を元の位置に戻す
	void Collision();         // プレイヤーの当たり判定
	static void MoveFlag(bool bMove) { m_bMove = bMove; }
	static void DeathMove(bool bDeath) { m_bPlayerDeath = bDeath; }
	//**=================c++版マクロ====================**
	static const float HALF2;				//3.14の半分の２等分
	static const float HALF1;				//3.14の半分の３等分
	static const float HALF;				//上の半分
	static const float MOVE_SPEED;			//移動の速度
	static const int OVER;         // 左右の上限
	static const int OVER_UP;      // 上の上限
	static const int OVER_DOWN;    // 下の上限
	static const int FRAMECNT;     // フレームのカウント

	//D3DXVECTOR3 m_pos;          // 位置
	//D3DXVECTOR3 m_rot;          // 向き
	//D3DXVECTOR3 m_size;			//サイズ
private:
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	D3DXVECTOR3 m_move;         // 移動量
	D3DXVECTOR3 m_rotMove;      // rot用のmove(滑らか回転用)
	D3DXVECTOR3 m_collitionSize;   // 当たり判定用のサイズ
	BULLET_TYPE m_type;         // 弾の状態
	STATE m_state;              // プレイヤーの状態
	float m_fAngle;				// 向き
	int m_nFrameCnt;            // 弾のフレームカウント 
	int m_nLife;                // プレイヤーのライフ

	int m_nDamegeCnt;                 // ダメージのカウント
	int m_nDeathCnt;           // どれくらいで死ぬかカウント
	int m_nSceneCnt;           // 画面遷移する時間
	static bool m_bMove;          // 動いたかどうか
	static bool m_bPlayerDeath;         // 死んだかどうか
};

#endif

