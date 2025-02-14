//=================================
// 
// uiクラス　ui.cpp
//outher kida ibuki 
// 
//==================================
#include "ui.h"    // UI
#include "manager.h" // マネージャー

float CUi::m_fTexHeight = 0;
float CUi::m_fTexWidht = 0;
int CUi::m_nFrame = 0;

const int CUi::FRAME = 3;
const float CUi::REDUCE_POS = 0.25f;
const float CUi::INITIAL_VALUE = 0.25f;
const float CUi::TEX_RANGE = 1.25f;

const float CUi::TEX_SIZE_X_1 = 120.0f;
const float CUi::TEX_SIZE_Y_1 = 50.0f;

const float CUi::TEX_SIZE_X_2 = 450.0f;
const float CUi::TEX_SIZE_Y_2 = 250.0f;

const float CUi::TEX_SIZE_X_3 = 100.0f;
const float CUi::TEX_SIZE_Y_3 = 100.0f;

const float CUi::TEX_SIZE_X_4 = 500.0f;
const float CUi::TEX_SIZE_Y_4 = 300.0f;

//====================================
// コンストラクタ
//====================================
CUi::CUi()
{
	m_nType = 0;
	m_nFrame = FRAME;
	m_fTexHeight = 0.0f;   //縦
	m_fTexWidht = INITIAL_VALUE;    //横

}
//====================================
// デストラクタ
//====================================
CUi::~CUi()
{
}
//====================================
// 初期設定
//====================================
HRESULT CUi::Init()
{
	CObject2D::Init();

	SetType(CObject::TYPE::UI);

	// 各テクスチャの設定
	if (m_nType == 0)
	{
		SetSize(TEX_SIZE_X_1, TEX_SIZE_Y_1);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nType == 1)
	{
		SetSize(TEX_SIZE_X_2, TEX_SIZE_Y_2);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nType == 2)
	{
		SetSize(TEX_SIZE_X_2, TEX_SIZE_Y_2);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nType == 3)
	{
		SetSize(TEX_SIZE_X_2, TEX_SIZE_Y_2);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nType == 4)
	{
		SetSize(TEX_SIZE_X_2, TEX_SIZE_Y_2);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nType == 5)
	{
		SetSize(TEX_SIZE_X_3, TEX_SIZE_Y_3);
	}
	else if (m_nType == 6)
	{
		SetSize(TEX_SIZE_X_4, TEX_SIZE_Y_4);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CUi::Uninit()
{
	CObject2D::Uninit();
}
//====================================
// 更新処理
//====================================
void CUi::Update()
{
	CObject2D::Update();
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	if (m_nType == 5)
	{
		//頂点バッファをロックして、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(m_fTexHeight, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_fTexWidht, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_fTexHeight, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_fTexWidht, 1.0f);

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();

		if (m_fTexHeight == 1.0f && m_fTexWidht == TEX_RANGE)
		{
			CUi::DeathFlag();
			CPlayerM::MoveFlag(true);
		}
	}
}
//====================================
// 描画処理
//====================================
void CUi::Draw()
{
	CObject2D::Draw();
}
//====================================
// ui生成処理
//====================================
CUi* CUi::Create(D3DXVECTOR2 pos, int nType)
{
	CUi* pUi = new CUi();
	pUi->m_nType = nType;
	pUi->Init();
	pUi->SetPos(pos.x, pos.y);
	if (nType == 0)
	{// ライフの文字
		pUi->SetTexture("data/TEXTURE/lifeUi.png");
	}
	else if (nType == 1)
	{// チュートリアルのテクスチャ1
		pUi->SetTexture("data/TEXTURE/tutorial001.png");
	}
	else if (nType == 2)
	{// チュートリアルのテクスチャ2
		pUi->SetTexture("data/TEXTURE/tutorial002.png");
	}
	else if (nType == 3)
	{// チュートリアルのテクスチャ3
		pUi->SetTexture("data/TEXTURE/tutorial003.png");
	}
	else if (nType == 4)
	{// チュートリアルのテクスチャ4
		pUi->SetTexture("data/TEXTURE/tutorial004.png");
	}
	else if (nType == 5)
	{
		pUi->SetTexture("data/TEXTURE/countdown.png");
	}
	else if (nType == 6)
	{
		pUi->SetTexture("data/TEXTURE/titleTex.png");
	}
	return pUi;
}

void CUi::SubTime()
{
	if (m_nFrame >= 0)
	{
		m_nFrame--;
	}
	if (m_nFrame <= 0)
	{
		m_fTexHeight += REDUCE_POS;   //縦
		m_fTexWidht += REDUCE_POS;    //横

		m_nFrame = FRAME;
	}
}
