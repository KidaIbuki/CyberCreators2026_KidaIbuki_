//=================================
// 
// 照準クラス　target.cpp
//outher kida ibuki 
// 
//==================================

#include "target.h"   // レティクル
#include "bullet.h"   // 弾
#include "playerM.h"  // プレイヤー
#include "manager.h"    // マネージャー
#include "ui.h"
const float CTarget::LEFT = 250.0f;  // 各方向の移動の最大値
const float CTarget::RIGHT = 250.0f;
const float CTarget::UP = 100.0f;
const float CTarget::DOWN = 170.0f;

const float CTarget::BILLSIZE_X = 20.0f;   // 各ビルボードサイズ
const float CTarget::BILLSIZE_Y = 40.0f;
const float CTarget::BILLSIZE_Z = 20.0f;

// カラーのマクロ
const D3DXCOLOR CTarget::INIT_COLOR = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
const D3DXCOLOR CTarget::CHANGE_COLOR = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR CTarget::CHANGE_COLOR_ELSE = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);

// スティックの移動量
const float CTarget::STICK_MOVE_X = 0.0001f;
const float CTarget::STICK_MOVE_Y = 0.0001f;

const float CTarget::POS_DISTANS = 150.0f;  // posからどれくらい離すか

//==========================================
// コンストラクタ
//==========================================
CTarget::CTarget()
{
	m_bColor = false;
	m_nTargetFrame = 1;
}
//==========================================
// デストラクタ
//==========================================
CTarget::~CTarget()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CTarget::Init()
{
	CBillboard::Init();
	SetType(CObject::TYPE::TARGET);
	SetBillboard(BILLSIZE_X, BILLSIZE_Y, BILLSIZE_Z);
	SetColor(INIT_COLOR);

	return S_OK;
}
//==========================================
// 終了処理
//==========================================
void CTarget::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CTarget::Update()
{

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

			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //ダウンキャスト

				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				// 一定の範囲内だったら
				if (playerPos.z >= 0.0f && playerPos.z <= POSITION1)
				{
					if (pPlayer != nullptr)
					{
						MoveTatget();
						this->m_pos.z = playerPos.z + POS_DISTANS;  // レティクルをプレイヤーの移動に合わして移動させる
					}
				}
				// ボス戦の範囲内だったら
				else if (playerPos.z >= POSITION1)
				{
					this->m_pos = playerPos;
					this->m_pos.z = playerPos.z + POS_DISTANS;
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


	CollisionTarget();
	// ========================画面外に出ないようにする=================================
	CManager* pManager = CManager::GetInstance();
	CCamera* pCamera = pManager->GetCamera();  //カメラの取得
	D3DXVECTOR3 posR = pCamera->GetPosR();	//向き

    // 左
	if (m_pos.x < posR.x - LEFT)
	{
		m_pos.x = posR.x - LEFT;
	}
	//右
	if (m_pos.x > posR.x + RIGHT)
	{
		m_pos.x = posR.x + RIGHT;
	}
	//下
	if (m_pos.y < posR.y - DOWN)
	{
		m_pos.y = posR.y - DOWN;
	}
	// 上
	if (m_pos.y > posR.y + UP)
	{
		m_pos.y = posR.y + UP;
	}

	// 当たり判定の範囲内にいたら色を変える
	if (m_bColor == true)
	{
		SetColor(CHANGE_COLOR);
	}
	else
	{
		SetColor(CHANGE_COLOR_ELSE);
	}
}
//==========================================
// 描画処理
//==========================================
void CTarget::Draw()
{
	CBillboard::Draw();
}
//==========================================
// 生成処理
//==========================================
CTarget* CTarget::Create(D3DXVECTOR3 pos)
{
	CTarget* pTarget = new CTarget();
	pTarget->Init();
	pTarget->SetPos(pos);
	pTarget->SetTexture("data/TEXTURE/target001.png");
	
	return pTarget;
}
//==========================================
// レティクルの操作
//==========================================
void CTarget::MoveTatget()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //キーボード取得
	CInputMouse* pMouse = pManager->GetMouse();
	D3DXVECTOR2 move = pMouse->GetMove();

	// マウスで移動
	this->m_pos.x += move.x;   // x軸移動
	this->m_pos.y += 0 - move.y;   // x軸移動

	// 右スティックでレティクル移動(斜めも対応)
	if (pJoypad->GetJoyR() == true)
	{
		XINPUT_STATE stick = pJoypad->GetStickR();   // 右スティックの情報を取得
		this->m_pos.x += stick.Gamepad.sThumbRX * STICK_MOVE_X;   // x軸移動
		this->m_pos.y += stick.Gamepad.sThumbRY * STICK_MOVE_Y;   // y軸移動
	}


}
//============================================
// エイムアシストをするための判定
//============================================
void CTarget::CollisionTarget()
{
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
				bool bSwitch = pManager->GetSwitching();
				CEnemyX* pEnemy = static_cast<CEnemyX*>(pObj); //ダウンキャスト

				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x + 10.0f, m_size.y + 10.0f, m_size.z + 200.0f);  // 照準の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たったとき
					bSwitch = true;
					pManager->SetSwitch(bSwitch);
					m_bColor = true;
					break;
				}
				else
				{// 当たってないとき
					bSwitch = false;
					pManager->SetSwitch(bSwitch);
					m_bColor = false;
				}

			}

			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}
}
