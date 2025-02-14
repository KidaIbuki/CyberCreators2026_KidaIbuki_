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
float CLife::m_fTexWidth = 0;
int CLife::m_nFrame = 0;
int CLife::m_nLife = 0;

const float CLife::TEX_HEIGHT = 0.0f;   // テクスチャの縦の初期値
const float CLife::TEX_WIDTH = 0.1f;    // テクスチャの横の初期値
const float CLife::TEX_SIZE_X = 120.0f;   // テクスチャサイズx
const float CLife::TEX_SIZE_Y = 350.0f;   // テクスチャサイズy
const float CLife::TEX_MOVE_H = 0.1f;   // テクスチャ移動height
const float CLife::TEX_MOVE_W = 0.1f;   // テクスチャ移動width

const int CLife::FRAME = 3;     // カウントフレーム
const int CLife::LIFE = 100;    // ライフ

//=======================================
// コンストラクタ
//=======================================
CLife::CLife()
{
	m_fTexHeight = TEX_HEIGHT;   //縦
	m_fTexWidth = TEX_WIDTH;    //横
	m_nFrame = FRAME;
	m_nLife = LIFE;
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
	SetSize(TEX_SIZE_X, TEX_SIZE_Y);

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
	pVtx[1].tex = D3DXVECTOR2(m_fTexWidth, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fTexHeight, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexWidth, 1.0f);

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

		m_fTexHeight += TEX_MOVE_H;
		m_fTexWidth += TEX_MOVE_W;
		m_nLife -= nDamage;  // ライフを減らす
		m_nFrame = FRAME;   // フレームを戻す
	}
	if (m_nLife <= 0)
	{// ライフが無くなったら
		//CFade::SetFade(CScene::MODE::MODE_GAME);
		CPlayerM::MoveFlag(false);
		CPlayerM::DeathMove(true);
	}
}
