//=================================
// 
// 敵クラス　enemyX.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"   // マネージャー
#include "enemyX.h"  // 敵
#include "bullet.h"  // 弾
#include "blockX.h"  // ブロック

//int CEnemyBoss::m_nFrameEnemy = 0;
//int CEnemyBoss::m_nLife = 0;
//==================================
// コンストラクタ
//==================================
CEnemyX::CEnemyX()
{
	// 敵の基本パラメーター
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_bMove = true;   // 動いているかどうかx軸
	m_bMove1 = true;   // y軸
	m_bTouch = false;
	m_fMoveStorage1 = 0.0f;
	m_fMoveStorage2 = 0.0f;
	m_fMoveStorage3 = 0.0f;
	m_fMoveStorage4 = 0.0f;

	m_fSpeedStorage = 0.0f;
	m_fSpeedStorage1 = 0.0f;
	m_state = ENEMYSTATE_NONE;
	m_nFrameCnt = 0;
	m_nFrame = 100;
	m_pLine = nullptr;

}
//==================================
// デストラクタ
//==================================
CEnemyX::~CEnemyX()
{
}
//==================================
// 初期設定
//==================================
HRESULT CEnemyX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_X);

	return S_OK;
}
//==================================
// 終了処理
//==================================
void CEnemyX::Uninit()
{
	CObjectX::Uninit();

	if (m_pLine != nullptr)
	{
		m_pLine->Release();
		m_pLine = nullptr;
	}

}
//==================================
// 更新処理
//==================================
void CEnemyX::Update()
{
	// 敵の行動処理
    m_pos += m_move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	// 指定した座標の間を行き来する処理
	//x軸
	if (m_pos.x > m_fMoveStorage1)//奥
	{
		m_bMove = true;
	}
	else if (m_pos.x < m_fMoveStorage2)//手前
	{
		m_bMove = false;
	}
	if (m_bMove == true)
	{
		m_pos.x -= m_fSpeedStorage;
	}
	else if (m_bMove == false)
	{
		m_pos.x += m_fSpeedStorage;
	}

	//y軸
	if (m_pos.y > m_fMoveStorage3)//上
	{
		m_bMove1 = true;
	}
	else if (m_pos.y < m_fMoveStorage4)//下
	{
		m_bMove1 = false;
	}
	if (m_bMove1 == true)
	{
		m_pos.y -= m_fSpeedStorage1;
	}
	else if (m_bMove1 == false)
	{
		m_pos.y += m_fSpeedStorage1;
	}
	//移動量を減衰
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.y += (0.0f - m_move.y) * 0.3f;

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
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					if (m_nFrameCnt <= 0)
					{
						// プレイヤーに向かって敵が弾を飛ばす
						D3DXVECTOR3 bulletAngle, position;
						bulletAngle = D3DXVECTOR3(playerPos.x * 0.5f, playerPos.y * 0.5f, playerPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // 敵の位置からプレイヤーのベクトルを求める
						position = playerPos - m_pos;   // 敵とプレイヤーのベクトルを求める
						D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // 長さが1になる

						// 敵より後ろに行ったら弾は撃たない
						if(playerPos.z > m_pos.z ||
							D3DXVec3Length(&position) >= 300)   // 敵から一定距離離れていたら以下の処理をしない(弾を飛ばさない)
						{
							pObj = pNext; // オブジェクトのポインタを次に進める
							continue;
						}
						CBulletEnemy::Create(m_pos, bulletAngle * 10.0f);

						m_nFrameCnt = m_nFrame;
					}
					if (m_nFrameCnt > 0)
					{
						m_nFrameCnt--;
					}
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}
}
//==================================
// 描画処理
//==================================
void CEnemyX::Draw()
{

	CObjectX::Draw();
#if 0
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

	D3DXCreateLine(pDevice, &m_pLine);

	// OBB初期化
	D3DXVECTOR3 center(m_pos.x, m_pos.y, m_pos.z), halfWidths(m_size.x, m_size.y, m_size.z);
	D3DXMATRIX rotation;
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(45), 0, 0); // Y軸を中心に45度回転	OBB obb(center, halfWidths, rotation);
	OBB obb(center, halfWidths, rotation);


	 //OBBを描画
	DrawOBB(m_pLine, obb, pDevice, D3DCOLOR_XRGB(255, 0, 0));


	m_pLine->Release();
    // TODO : ラインはまだバグがあるから要修正
#endif
}
//==================================
// 生成処理
//==================================
CEnemyX* CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
	D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1)
{
	CEnemyX* pEnemyX = new CEnemyX;
	pEnemyX->SetPos(pos);
	pEnemyX->SetRot(rot);
	pEnemyX->SizeVtx();
	pEnemyX->m_pMesh = pMesh;
	pEnemyX->m_pBuffMat = pBuffMat;
	pEnemyX->m_dwNumMat = dwNumMat;
	pEnemyX->m_fMoveStorage1 = movex1.x;
	pEnemyX->m_fMoveStorage2 = movex2.x;
	pEnemyX->m_fMoveStorage3 = movey1.y;
	pEnemyX->m_fMoveStorage4 = movey2.y;

	//y軸も追加するかも...
	pEnemyX->m_fSpeedStorage = fSpeed;
	pEnemyX->m_fSpeedStorage1 = fSpeed1;


	pEnemyX->Init();
	return pEnemyX;
}
//==========================================
// コンストラクタ
//==========================================
CEnemyBoss::CEnemyBoss()
{
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };

	m_nFrameCntBoss = 0;
	m_nFrame = 80;
	m_nLife = 100;
	m_nFrameEnemy = 3;
}
//==========================================
// デストラクタ
//==========================================
CEnemyBoss::~CEnemyBoss()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CEnemyBoss::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_BOSS);  // タイプ設定

	return S_OK;
}
//==========================================
// 終了処理
//==========================================
void CEnemyBoss::Uninit()
{
	CObjectX::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CEnemyBoss::Update()
{
	// 敵の行動処理
	m_pos += m_move;

	m_pos.z += m_move.z;

	m_pos.z += 4.0f;  // 敵の速さ

	//y軸
	if (m_pos.y > 160)//上
	{
		m_bMoveBoss = true;
	}
	else if (m_pos.y < -100)//下
	{
		m_bMoveBoss = false;
	}
	if (m_bMoveBoss == true)
	{
		m_pos.y -= 0.5f;
	}
	else if (m_bMoveBoss == false)
	{
		m_pos.y += 0.5f;
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
			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //ダウンキャスト
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					if (m_nFrameCntBoss <= 0)
					{

						// プレイヤーに向かって敵が弾を飛ばす
						D3DXVECTOR3 bulletAngle, position;
						bulletAngle = D3DXVECTOR3(playerPos.x * 0.5f, playerPos.y * 0.5f, playerPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // 敵の位置からプレイヤーのベクトルを求める
						position = playerPos - m_pos;   // 敵とプレイヤーのベクトルを求める
						D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // 長さが1になる

						if (D3DXVec3Length(&position) >= 300)   // 敵から一定距離離れていたら以下の処理をしない(弾を飛ばさない)
						{
							pObj = pNext; // オブジェクトのポインタを次に進める
							continue;
						}
						// ランダムでボスの行動を決める
						int Random = 0;
						Random = rand() % 3;
						if (Random == 0)
						{
							CBulletEnemy::Create(m_pos, bulletAngle * 10.0f);  // 弾を撃つ
						}
						else if (Random == 1)
						{
							CBlockX::Create2(m_pos, m_rot);   // 障害物を飛ばす
						}
						else if (Random == 2)
						{

						}
						m_nFrameCntBoss = m_nFrame;   // カウントにフレームを入れる
					}
					if (m_nFrameCntBoss > 0)  // カウントが残っていたら
					{
						m_nFrameCntBoss--;   // カウントダウン
					}
				}
			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


	m_move.z += (0.0f - m_move.z) * 0.3f;

}
//==========================================
// 描画処理
//==========================================
void CEnemyBoss::Draw()
{
	CObjectX::Draw();
}
//==========================================
// 生成処理
//==========================================
CEnemyBoss* CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemyBoss* pBoss = new CEnemyBoss();
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
	pBoss->Init();
	pBoss->SetModel("data/MODEL/ENEMY/EnemyBoss.x");

	return pBoss;
}
void CEnemyBoss::DamageEnemy(int nDamage)
{
	m_nLife -= nDamage;  // ライフを減らす

	if (m_nLife <= 0)
	{// ライフが無くなったら
		CEnemyBoss::DeathFlag();
		CFade::SetFade(CScene::MODE::MODE_RESULT);
	}
}
//========================================
// ID3DXLineを使ってOBBを描画する関数
//========================================
void CEnemyX::DrawOBB(ID3DXLine* pLine, const OBB& obb, IDirect3DDevice9* pDevice, D3DCOLOR color)
{
	// OBBの頂点を取得
	std::vector<D3DXVECTOR3> vertices3D(8);
	for (int i = 0; i < 8; ++i) {
		vertices3D[i] = obb.GetVertex(i);
	}
	// OBBのエッジを定義（ライン接続順）
	std::vector<D3DXVECTOR3> edges3D = {
		vertices3D[0], vertices3D[1], vertices3D[1], vertices3D[3],
		vertices3D[3], vertices3D[2], vertices3D[2], vertices3D[0], // 底面
		vertices3D[4], vertices3D[5], vertices3D[5], vertices3D[7],
		vertices3D[7], vertices3D[6], vertices3D[6], vertices3D[4], // 上面
		vertices3D[0], vertices3D[4], vertices3D[1], vertices3D[5],
		vertices3D[2], vertices3D[6], vertices3D[3], vertices3D[7]  // 垂直辺
	};
	// 2Dスクリーン座標に変換
	std::vector<D3DXVECTOR2> edges2D;
	ProjectVertices(edges3D, edges2D, pDevice);
	// ラインを描画
	pLine->Begin();
	pLine->Draw(edges2D.data(), edges2D.size(), color);
	pLine->End();
}
//========================================
// 3D座標を2Dスクリーン座標に変換する関数
//========================================
void CEnemyX::ProjectVertices(const std::vector<D3DXVECTOR3>& vertices, std::vector<D3DXVECTOR2>& projectedVertices, IDirect3DDevice9* pDevice)
{
	D3DVIEWPORT9 viewport;
	D3DXMATRIX viewMatrix, projMatrix;
	// ビューポート、ビュー行列、射影行列を取得
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
	pDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);
	projectedVertices.clear();
	// 各頂点をプロジェクト
	for (const auto& vertex : vertices) {
		D3DXVECTOR3 projected;
		D3DXVec3Project(&projected, &vertex, &viewport, &projMatrix, &viewMatrix, nullptr);
		projectedVertices.push_back(D3DXVECTOR2(projected.x, projected.y));
	}
}

