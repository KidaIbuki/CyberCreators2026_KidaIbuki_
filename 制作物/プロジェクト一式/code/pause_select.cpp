//=================================
// 
// ポーズ用 クラス　pause_select.h
// Auther kida ibuki 
// 
//==================================

#include "pause_select.h"  // ポーズ
#include "game.h"    // ゲーム
#include "manager.h"  // マネージャー

//====================================
// コンストラクタ
//====================================
CPause_Select::CPause_Select()
{
	SetNormalDraw(false);
	SetNormalUpdate(false);
	SetPauseUpdate(true);
}
//====================================
// デストラクタ
//====================================
CPause_Select::~CPause_Select()
{
}
//====================================
// 初期設定
//====================================
HRESULT CPause_Select::Init()
{
	CObject2D::Init();
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CPause_Select::Uninit()
{
	CObject2D::Uninit();
}
//====================================
// 更新処理
//====================================
void CPause_Select::Update()
{
	CObject2D::Update();
}
//====================================
// 描画処理
//====================================
void CPause_Select::Draw()
{
	CManager* pManager = CManager::GetInstance();
	bool bPause = pManager->GetPause();
	CScene* pScene = pManager->GetScene();
	CScene::MODE mode = pScene->GetMode();
	if (mode == CScene::MODE::MODE_GAME)
	{
		if (bPause == true)
		{
			CObject2D::Draw();
		}
	}

}

//====================================
// タイプの設定
//====================================
void CPause_Select::SetType(int type)
{
	m_nType = type;
}
//====================================
// 生成処理
//====================================
CPause_Select* CPause_Select::Create(D3DXVECTOR2 pos, D3DXVECTOR2 siz, int type)
{
	CPause_Select* pPause = new CPause_Select();
	pPause->SetType(type);
	pPause->SetSize(siz.x, siz.y);
	pPause->Init();
	pPause->SetPos(pos.x, pos.y);
	if (type == 0)
	{
		pPause->SetTexture("data/TEXTURE/pause_continue.png");
	}
	if (type == 1)
	{
		pPause->SetTexture("data/TEXTURE/pause_retry.png");
	}
	if (type == 2)
	{
		pPause->SetTexture("data/TEXTURE/pause_quit.png");
	}

	return pPause;
}
