//==================================
// 
// プレイヤーライフ クラス　life.h
//outher kida ibuki 
// 
//==================================
#include "life.h"  // ライフ
#include "manager.h" // マネージャー
#include "playerM.h"

float CLife::m_fTexHeight = 0;
float CLife::m_fTexWidht = 0;
int CLife::m_nFrame = 0;
int CLife::m_nLife = 0;
//=======================================
// コンストラクタ
//=======================================
CLife::CLife()
{
	m_fTexHeight = 0.0f;   //縦
	m_fTexWidht = 0.1f;    //横
	m_nFrame = 3;
	m_nLife = 100;
}

//=======================================
// デストラクタ
//=======================================
CLife::~CLife()
{
}
//=======================================
// 初期設定
//=======================================
HRESULT CLife::Init()
{
	CObject2D::Init();
	SetType(CObject::TYPE::LIFE);
	SetSize(120.0f, 350.0f);
	//SetColor(D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f));


	return S_OK;
}
//=======================================
// 終了処理
//=======================================
void CLife::Uninit()
{
	CObject2D::Uninit();
}
//=======================================
// 更新処理
//=======================================
void CLife::Update()
{
	CObject2D::Update();

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTexHeight, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexWidht, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fTexHeight, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexWidht, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	if (m_nLife <= 0)
	{
		CLife::DeathFlag();
	}

}
//=======================================
// 描画処理
//=======================================
void CLife::Draw()
{
	CObject2D::Draw();
}
//=======================================
// 生成処理
//=======================================
CLife* CLife::Create(D3DXVECTOR2 pos)
{
	CLife* pLife = new CLife();
	pLife->Init();
	pLife->SetPos(pos.x, pos.y);
	pLife->SetTexture("data/TEXTURE/life001.png");

	return pLife;
}
//=======================================
// 減算処理
//=======================================
void CLife::SubLife(int nDamage)
{
	if (m_nFrame >= 0)  // 0より多かったら
	{
		m_nFrame--;   // カウントダウン
	}
	if (m_nFrame <= 0)
	{ // 座標を増やす

		m_fTexHeight += 0.1f;
		m_fTexWidht += 0.1f;
		m_nLife -= nDamage;  // ライフを減らす
		m_nFrame = 3;   // フレームを戻す
	}
	if (m_nLife <= 0)
	{// ライフが無くなったら
		//CFade::SetFade(CScene::MODE::MODE_GAME);
		CPlayerM::MoveFlag(false);
		CPlayerM::DeathMove(true);
	}
}
