//=================================
// 
// 階層構造player　playerM.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"     // マネージャー
#include "playerM.h"   // プレイヤー
#include "target.h"    // レティクル
#include "blockX.h"    // ブロック
#include "ui.h"        // UI
#include "obb.h"
#include "effect.h"
#include "bullet.h"    // 弾
#include "explosion.h"

bool CPlayerM::m_bMove = false;
bool CPlayerM::m_bPlayerDeath = false;

const float CPlayerM::HALF2 = 0.75f;
const float CPlayerM::HALF1 = 0.5f;
const float CPlayerM::HALF = 0.25f;

const float CPlayerM::MOVE_SPEED = 0.25f;

const int CPlayerM::OVER = 190;   // 左右
const int CPlayerM::OVER_UP = 200;  // 上
const int CPlayerM::OVER_DOWN = 100;  // 下
const int CPlayerM::FRAMECNT = 40;   // フレームのカウント(弾の発射間隔を変えれる)

const D3DXCOLOR CPlayerM::COL = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);   // エフェクトカラー
const float CPlayerM::RADIUS = 3.0f;   // 半径
const float CPlayerM::SPLIT = 1.0f;    // 分割
const int CPlayerM::EFFECTLIFE = 5;   // エフェクトライフ

const float CPlayerM::MOVE_PALYER = 4.0f;   // プレイヤーの移動量
const float CPlayerM::MOVE_PALYER_Z = 2.0f;   // プレイヤーの死んだときの移動量
const float CPlayerM::MOVE_PALYER_Y = 1.0f;   // プレイヤーの死んだときの移動量

const int CPlayerM::SHAKE_FRAME = 30;   // 画面の揺れのフレーム
const int CPlayerM::SHAKE_VOLUME_DEATH = 3;   // 死んだとときの揺れの強さ
const int CPlayerM::SHAKE_VOLUME = 10;   // ダメージを受けたときの揺れの強さ
const int CPlayerM::LIFE_REDUCE = 10;   // ライフを減らす数

//===============================
// コンストラクタ
//===============================
CPlayerM::CPlayerM()
{
	CObjectMotion::Load("data/TXT/motion.txt");   // txtファイルパスを入れる
	m_move = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_type = BULLET_NONE;
	m_state = STATE_NONE;
	m_nFrameCnt = FRAMECNT;
	m_nDeathCnt = 180;
	m_nSceneCnt = 60;
}
//===============================
// デストラクタ
//===============================
CPlayerM::~CPlayerM()
{

}
//===============================
// 初期設定
//===============================
HRESULT CPlayerM::Init()
{
	CObjectMotion::Init();


	SetType(CObject::TYPE::PLAYER_M);


	return S_OK;
}
//===============================
// 終了処理
//===============================
void CPlayerM::Uninit()
{
}
//===============================
// 更新処理
//===============================
void CPlayerM::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得
	CInputMouse* pMouse = pManager->GetMouse();    //コントローラー取得

	// モデル本体の位置、向きを取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//SetMotion(1);
	// モデルに操作を付ける
	if (m_bMove == true)
	{
		// 移動量の更新
		m_move += PlayerMove();
		// posを動かす
		pos += m_move;

		// rotを動かす
		rot += m_rotMove;

		//奥に動かす。
		pos.z += MOVE_PALYER;

		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z - 25.0f), COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);


	}
	if (m_bPlayerDeath == true)
	{
		pos.y -= MOVE_PALYER_Y;
		pos.z += MOVE_PALYER_Z;
		pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME_DEATH);   // 画面の揺れ

		m_nDeathCnt--;
		if (m_nDeathCnt <= 0)
		{
			CExplosion::Create(pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));

			DeathFlag();

			m_bPlayerDeath = false;
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_EXPLOSION);

			CFade::SetFade(CScene::MODE::MODE_GAME);
		}
	}
	else // 死んでないとき
	{
		Collision();  // プレイヤー関係の当たり判定
	}
	//移動量を減衰
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//回転を減衰
	m_rotMove.x += (0.0f - m_rotMove.x) * 0.1f;
	m_rotMove.z += (0.0f - m_rotMove.z) * 0.1f;
	m_rotMove.y += (0.0f - m_rotMove.y) * 0.1f;
	// 回転の制限
	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2;
	}


	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];

		//種類の取得
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // 次のポインタを取得
			if (type == CObject::TYPE::TARGET)
			{
				CTarget* pTarget = static_cast<CTarget*>(pObj); //ダウンキャスト

				if (pTarget != nullptr)
				{
					D3DXVECTOR3 targetPos = pTarget->GetPos();
					if (m_bMove == true)
					{
						if (m_type == BULLET_NONE)
						{

							if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_LEFT))
							{
								// サウンドを流す
								pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

								D3DXVECTOR3 bulletAngle;

								//======================ベクトルを使ってレティクルに弾を飛ばす===============================================
								bulletAngle = D3DXVECTOR3(targetPos.x * 0.5f, targetPos.y * 0.5f, targetPos.z) - D3DXVECTOR3(pos.x * 0.5f, pos.y * 0.5f, pos.z);  // 弾の位置からレティクルのベクトルを求める
								D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // 長さが1になる

								CBullet::Create(pos, bulletAngle * 10.0f);
								// MEMO targetのposがずれているか、bulletのmoveがおかしいか
								// xとyの値が倍になってる
								m_type = BULLET_SHOT;

							}
						}
						// 連射防止するためのやつ
						else if (m_type == BULLET_SHOT)
						{
							m_nFrameCnt--;
							if (m_nFrameCnt <= 0)
							{
								m_type = BULLET_NONE;
								m_nFrameCnt = FRAMECNT;
							}
						}
					}
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


	// ========================画面外に出ないようにする=================================
	// 左
	if (pos.x < -OVER)
	{
		pos.x = -OVER;
	}
	//右
	if (pos.x > OVER)
	{
		pos.x = OVER;
	}
	//下
	if (pos.y < -OVER_DOWN)
	{
		pos.y = -OVER_DOWN;
	}
	// 上
	if (pos.y > OVER_UP)
	{
		pos.y = OVER_UP;
	}


	// モデル本体の位置と向きを反映
	SetPos(pos);
	SetRot(rot);
	CObjectMotion::Update();

}
//===================================
// プレイヤーの移動処理
//===================================
D3DXVECTOR3 CPlayerM::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//キーボード取得
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得

	D3DXVECTOR3 move = { 0,0,0 };
	// モデル本体の位置、向きを取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//**========カメラの情報==========**
	CCamera* pCamera = pManager->GetCamera();  //カメラの取得
	D3DXVECTOR3 rotC = pCamera->GetRot();	//向き

	// ボス戦前の範囲内だったら
	if (pos.z >= 0.0f && pos.z <= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_D) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//Aキーが押された場合
			if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF2) * MOVE_SPEED;
				//rot.y = D3DX_PI * -HALF2 - rot.y;
			}
			else if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF1) * MOVE_SPEED;
			}

		}
		else if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{//Dキーが押された場合

			if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF2) * MOVE_SPEED;

			}
			else if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF1) * MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//Wキーが押された場合
			{
				move.y += MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//Sキーが押された場合
			{
				move.y -= MOVE_SPEED;

			}
		}
		if (pKeyboard->GetPress(DIK_E) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT_SHOULDER))
		{
			m_rotMove.z += 0.005f;
		}
		else if (pKeyboard->GetPress(DIK_Q) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT_SHOULDER))
		{
			m_rotMove.z -= 0.005f;
		}
		else
		{
			m_rotMove.z += (0.0f - rot.z) * 0.005f;
		}
	}
	// ボス戦の範囲内だったら
	else if (pos.z >= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//Wキーが押された場合
			move.y += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//Sキーが押された場合
			move.y -= MOVE_SPEED;
		}

	}
#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_U))
	{
		move.z += 0.5;
	}
	if (pKeyboard->GetPress(DIK_J))
	{
		move.z -= 0.5;
	}

#endif


	// モデル本体の位置と向きを反映
	SetPos(pos);
	SetRot(rot);

	return move;
}
//==============================================
// プレイヤーのx軸を元に戻す
//==============================================
void CPlayerM::ResetPlayer()
{
	// モデル本体の位置、向きを取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	pos.x = 0.0f;
	rot.z = 0.0f;
	m_rotMove.z = 0.0f;

	// モデル本体の位置と向きを反映
	SetPos(pos);
	SetRot(rot);

}
//===============================================
// プレイヤーの当たり判定(有向境界ボックス)
//===============================================
void CPlayerM::Collision()
{
	// モデルパーツの位置、向きを取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSiz();
	CManager* pManager = CManager::GetInstance();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];

		//種類の取得
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // 次のポインタを取得
			if (type == CObject::TYPE::ENEMY_X)
			{
				CEnemyX* pEnemy = static_cast<CEnemyX*>(pObj); //ダウンキャスト

				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // 画面の揺れ
					CLife::SubLife(LIFE_REDUCE);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = static_cast<CBlockX*>(pObj); //ダウンキャスト
				D3DXVECTOR3 blockPos = pBlock->GetPos();
				D3DXVECTOR3 blockSize = pBlock->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(blockPos.x, blockPos.y, blockPos.z), halfWidths1(blockSize.x, blockSize.y, blockSize.z);  // ブロックの中心点とサイズ
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // 画面の揺れ
					CLife::SubLife(LIFE_REDUCE);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = static_cast<CBulletEnemy*>(pObj); //ダウンキャスト

				D3DXVECTOR3 BulletPos = pBullet->GetPos();
				D3DXVECTOR3 BulletSize = pBullet->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(BulletPos.x, BulletPos.y, BulletPos.z), halfWidths1(BulletSize.x, BulletSize.y, BulletSize.z);  // 敵の弾の中心点とサイズ
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // 画面の揺れ
					CLife::SubLife(LIFE_REDUCE);
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// 当たってないとき
				}

			}

			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}

	// モデル本体の位置と向きとサイズを反映
	SetPos(pos);
	SetRot(rot);
	SetSiz(size);
}
//===============================
// 描画処理
//===============================
void CPlayerM::Draw()
{
	CObjectMotion::Draw();
}

//===============================
// 生成
//===============================
CPlayerM* CPlayerM::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerM* pPlayer = new CPlayerM();
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	return pPlayer;
}
