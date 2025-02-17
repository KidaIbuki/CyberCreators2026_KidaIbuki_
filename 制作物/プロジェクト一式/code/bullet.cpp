//=================================
// 
// 弾クラス　bullet.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"    // マネージャー
#include "bullet.h"   // 弾
#include "effect.h"   // エフェクト
#include "explosion.h"  // 爆発

// 静的メンバ変数を初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = {};

const int CBullet::LIFE = 1300;
const D3DXCOLOR CBullet::COL = D3DXCOLOR(0.7f, 0.3f, 0.0f, 1.0f);  // 色
const float CBullet::RADIUS = 3.0f;  // 半径
const float CBullet::SPLIT = 1.0f;  // 分割
const int CBullet::EFFECTLIFE = 10;  // エフェクトのライフ
const float CBullet::BILLSIZE = 3.0f;  // ビルボードサイズ
const float CBullet::BULLETSIZE = 4.0f;  // 弾のサイズ


const D3DXCOLOR CBulletEnemy::COL = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);  // 色
const float CBulletEnemy::RADIUS = 5.0f;  // 半径
const float CBulletEnemy::SPLIT = 1.0f;  // 分割
const int CBulletEnemy::EFFECTLIFE = 10;  // エフェクトのライフ
const float CBulletEnemy::BILLSIZE = 5.0f;  // ビルボードサイズ
const float CBulletEnemy::BULLETSIZE = 10.0f;  // 弾のサイズ

//==========================================
// コンストラクタ
//==========================================
CBullet::CBullet()
{
	m_dwLifeTime = timeGetTime();

	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_nHitCnt = 0;
}
//==========================================
// デストラクタ
//==========================================
CBullet::~CBullet()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CBullet::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::BULLET);
	SetBillboard(BILLSIZE, BILLSIZE, BILLSIZE);
	SetSize(D3DXVECTOR3(BULLETSIZE, BULLETSIZE, 0.0f));
	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// 終了処理
//==========================================
void CBullet::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CBullet::Update()
{
	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::DeathFlag();
	}

	CEffect::Create(m_pos, COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);



	//CollisionBullet();
	Collision();

	m_pos += m_move;
}
//==========================================
// 描画処理
//==========================================
void CBullet::Draw()
{
	CBillboard::Draw();

}
//==========================================
// 生成処理
//==========================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}

//=======================================
//ロード
//=======================================
HRESULT CBullet::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CBullet::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
//======================================
// 弾の設定
//======================================
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=======================================
//当たり判定(OBB)
//=======================================
void CBullet::Collision()
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
				CEnemyX* pEnemy = static_cast<CEnemyX*>(pObj); //ダウンキャスト
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z - 50.0f);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // 弾の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// 当たってないとき
				}

			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = static_cast<CEnemyBoss*>(pObj); //ダウンキャスト
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z + 150.0f), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // 弾の中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{// 当たってるとき
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// サウンドを流す
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// 当たってないとき
				}

			}
			pObj = pNext; // オブジェクトのポインタを次に進める
		}
	}


}

//==========================================
// コンストラクタ
//==========================================
CBulletEnemy::CBulletEnemy()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
}
//==========================================
// デストラクタ
//==========================================
CBulletEnemy::~CBulletEnemy()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CBulletEnemy::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::ENEMY_BULLET);
	SetBillboard(BILLSIZE, BILLSIZE, BILLSIZE);
	SetSize(D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE));

	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// 終了処理
//==========================================
void CBulletEnemy::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// 更新処理
//==========================================
void CBulletEnemy::Update()
{

	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);

	m_pos += m_move;
}
//==========================================
// 描画処理
//==========================================
void CBulletEnemy::Draw()
{
	CBillboard::Draw();

}
//==========================================
// 生成処理
//==========================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBulletEnemy* pBullet = new CBulletEnemy();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}
//=======================================
//ロード
//=======================================
HRESULT CBulletEnemy::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CBulletEnemy::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
//======================================
// 弾の設定
//======================================
void CBulletEnemy::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}
