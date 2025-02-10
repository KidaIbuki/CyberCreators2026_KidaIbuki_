//=================================
// 
// ボス戦背景クラス　background.h
//outher kida ibuki 
// 
//==================================
#include "background.h"   // バックグラウンド
#include "manager.h"        // マネージャー

// 静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CBackGround::m_pTextureTemp = {};

//===============================
// コンストラクタ
//===============================
CBackGround::CBackGround()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };

}
//===============================
// デストラクタ
//===============================
CBackGround::~CBackGround()
{
}
//===============================
// 初期設定
//===============================
HRESULT CBackGround::Init()
{
	SetType(CObject::TYPE::BG);
	CObject3D::Init();
	SetTexUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	SetField(100.0f, 6000.0f);
	SetUVmove(D3DXVECTOR2(0.0f, 0.003f));

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CBackGround::Uninit()
{
	CObject3D::Uninit();
}
//===============================
// 更新処理
//===============================
void CBackGround::Update()
{
	CObject3D::Update();
}
//===============================
// 描画処理
//===============================
void CBackGround::Draw()
{
	CObject3D::Draw();
}
//===============================
// 生成処理
//===============================
CBackGround* CBackGround::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBackGround* pBack = new CBackGround();
	pBack->Init();
	pBack->SetPos(pos);
	pBack->SetRot(rot);
	if (m_pTextureTemp != nullptr)
	{
		pBack->BindTexture(m_pTextureTemp);
	}
	return pBack;
}
//===============================
// テクスチャのロード
//===============================
HRESULT CBackGround::Load()
{
	CManager* pManager = CManager::GetInstance();

	//ポインタがnullなら
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込む
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data/TEXTURE/anim001.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//===============================
// テクスチャのアンロード
//===============================
void CBackGround::Unload()
{
	//テクスチャを使用していたら破棄
	if (m_pTextureTemp != nullptr)
	{
		//nullにする
		m_pTextureTemp = nullptr;
	}
}
