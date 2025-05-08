//=================================
// 
// パーティクル クラス　particle.cpp
//Auther kida ibuki 
// 
//==================================
#include "explosion.h"   // 爆発
#include "manager.h"       // マネージャー

LPDIRECT3DTEXTURE9 CExplosion::m_pTextureTemp = {};

//===============================
// コンストラクタ
//===============================
CExplosion::CExplosion()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_bUse = false;
	m_nLife = 0;
	m_dwLifeTime = timeGetTime();

}
//===============================
// デスストラクタ
//===============================
CExplosion::~CExplosion()
{
}
//===============================
// 初期設定
//===============================
HRESULT CExplosion::Init()
{
	CObject3D::Init();
	SetType(CObject::TYPE::EXPLOSION);

	SetAnim(DIVIDE, TIME);   // アニメーション設定
	SetField(SIZE_X, SIZE_Z);// テクスチャのサイズ

	m_dwLifeTime = timeGetTime() + LIFE;  // ライフ設定

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CExplosion::Uninit()
{
	CObject3D::Uninit();
}
//===============================
// 更新処理
//===============================
void CExplosion::Update()
{
	CObject3D::Update();
	
	// 一定時間で消す
	if (timeGetTime() >= m_dwLifeTime)
	{
		CExplosion::m_bDeath = true;
	}

}
//===============================
// 描画処理
//===============================
void CExplosion::Draw()
{
	CObject3D::Draw();

}
//===============================
// 生成処理
//===============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion* pExplosion = new CExplosion();
	pExplosion->Init();

	pExplosion->SetPos(pos);
	pExplosion->SetRot(rot);
	if (m_pTextureTemp != nullptr)
	{
		pExplosion->BindTexture(m_pTextureTemp);
	}

	return pExplosion;
}
//=======================================
//ロード
//=======================================
HRESULT CExplosion::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data/TEXTURE/explosion000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//アンロード
//======================================
void CExplosion::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}

