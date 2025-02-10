//=================================
// 
//カメラクラス　camera.cpp
//outher kida ibuki 
// 
//==================================
#include "camera.h"   // カメラ
#include "manager.h"    // マネージャー
#include "title.h"     // タイトル
//==============================
//コンストラクタ
//==============================
CCamera::CCamera()
{
}
//==============================
//デストラクタ
//==============================
CCamera::~CCamera()
{
}
//==============================
//初期設定
//==============================
HRESULT CCamera::Init()
{

	//メンバ変数初期化
	m_posV = PERSPECTIVE;			        // 視点
	m_posR = POINT_OF_INTEREST;		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };				// 上方向
	m_rot = { 0.0f, 0.0f, 0.0f };
    m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//距離
	m_fScaleDis = SCALEDIS;	//倍率

	m_nShakeFrame = 0;
	m_nShakeVolume = 0;

	m_move = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_nFrame = 10;
	m_nCntFrame = 0;
	m_Front = ANGLE_FRONT;

	m_bControll = false;

	return S_OK;

}
//==============================
//終了処理
//==============================
void CCamera::Uninit()
{
}
//==============================
//更新処理
//==============================
void CCamera::Update()
{
	//プレイヤーのタイプを取得してカメラの追従をする
	//オブジェクト取得
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	ANGLE angle = m_Front;

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
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // プレイヤーの位置を取得

					m_posR = playerPos;  // 注視点の追従
					m_posV.y = playerPos.y + 50.0f;  //視点を固定注視点に合わして追従  +～は視点の高さ
					//カメラの視点の追従
					m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.x;
					m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.z;

					// 一定範囲内だったら
					if (playerPos.z >= POSITION1 && playerPos.z <= POSITION2)
					{
						m_Front = ANGLE_RIGHT;  // 向きを変える
					}
					else if (playerPos.z >= POSITION3 && playerPos.z <= POSITION4)
					{
						//m_Front = ANGLE_FRONT;  // 向きを戻す
					}
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


	if (angle != m_Front)
	{
		float fRotMove = 0.0f;
		switch (m_Front)
		{
		case ANGLE_RIGHT:   // 右を向いたとき
			fRotMove = D3DX_PI * 0.5f - m_rot.y;  // 向きを変える
			break;
		case ANGLE_FRONT:   // 前を向いたとき
			fRotMove = 0 - m_rot.y;   // 向きを戻す
		}

		// 回転量が180°を超えたとき小さいほうにする
		if (fRotMove > D3DX_PI)
		{
			fRotMove -= D3DX_PI * 2;
		}
		else if (fRotMove < -D3DX_PI)
		{
			fRotMove += D3DX_PI * 2;
		}

		m_rotMove.y = fRotMove / m_nFrame;   // 回転量をフレームで割る
		m_nCntFrame = m_nFrame;  // フレームをカウントに入れる
	}
	if (m_nCntFrame > 0)
	{
		m_nCntFrame--;  // カウントダウン
		m_rot.y += m_rotMove.y;
	}

	CManager* pManager = CManager::GetInstance();

	CScene* pScene = pManager->GetScene();
	CScene::MODE mode = pScene->GetMode();
	// モードの取得
	if (mode == CScene::MODE::MODE_TITLE)
	{// タイトル画面でz軸方向にカメラを移動させる
		m_posR += m_move;

		m_posR.z += 2.0f;
		//カメラの視点の追従
		m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + m_posR.x;
		m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + m_posR.z;

		//移動量を減衰
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;
		m_move.y += (0.0f - m_move.y) * 0.1f;

		if (m_posR.z >= POSITION1 && m_posR.z <= POSITION2)
		{
			CFade::SetFade_Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
	if (pKey->GetTrigger(DIK_F))
	{
		m_bControll = m_bControll ? false : true;

	}
}
//==============================
//カメラ設定
//==============================
void CCamera::SetCamera()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);


	// プロジェクションマトリックスを作成(透視投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//near
		5000.0f);   //far


	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	//D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// カメラの揺れ
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFrame > 0)
	{
		m_nShakeFrame--;
		adjust.x = (float)(rand() % m_nShakeVolume);
		adjust.y = (float)(rand() % m_nShakeVolume);
		//adjust.z = random;
	}
	D3DXVECTOR3 posR, posV;
	posR = m_posR + adjust;  // 注視点
	posV = m_posV + adjust;  // 視点
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &m_vecU);
	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}
//==============================
// カメラのリセット
//==============================
void CCamera::ResetCamera()
{
	m_posV = PERSPECTIVE;			        // 視点
	m_posR = POINT_OF_INTEREST;		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };			// 上方向
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//距離
	m_fScaleDis = 1.0f;	//倍率

}
//==============================
// タイトル画面のカメラ
//==============================
void CCamera::TitleCamera()
{
	m_posV = PERSPECTIVE;			        // 視点
	m_posR = POINT_OF_INTEREST;		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };			// 上方向
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//距離
	m_fScaleDis = 1.0f;	//倍率

}
//==============================
// カメラの調節用
//==============================
void CCamera::DebugCamera()
{
	m_posV = { 0.0f, 200.0f, -450.0f };			// 視点
	m_posR = { 0.0f, 0.0f, 40.0f };		        // 注視点
	m_vecU = { 0.0f, 1.0f, 0.0f };				// 上方向
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//距離
	m_fScaleDis = 1.0f;	//倍率

}
//==============================
// カメラの位置設定
//==============================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_posR = pos;
}
//==============================
// カメラの揺れの設定
//==============================
void CCamera::SetShake(int shakeFrame, float shakeVolume)
{
	m_nShakeFrame = shakeFrame;
	m_nShakeVolume = (int)shakeVolume;
}
