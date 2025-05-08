//================================
//
//xファイルでブロック(blockX.h)
//Auther kida ibuki
//================================
#include "blockX.h"   // ブロック
#include "manager.h"    // マネージャー
//静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CBlockX::m_pTextureTemp = {};

//======================================
// コンストラクタ
//======================================
CBlockX::CBlockX()
{
	m_bMove = true;   // 動いているかどうかx軸
	m_bMove1 = true;   // 動いているかどうかy軸
	m_fMoveStorage1 = 0.0f;
	m_fMoveStorage2 = 0.0f;
	m_fMoveStorage3 = 0.0f;
	m_fMoveStorage4 = 0.0f;

	m_fSpeedStorage = 0.0f;
	m_fSpeedStorage1 = 0.0f;

	m_nType = 0;
}
//======================================
// デストラクタ
//======================================
CBlockX::~CBlockX()
{
}
//======================================
// 初期設定
//======================================
HRESULT CBlockX::Init()
{
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// 種類をブロックに設定
	SetType(CObject::TYPE::BLOCK);

	//m_pLine = CLine::Create();
	//m_pLine->SetLine(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXVECTOR3(m_pos.x, m_pos.y - 100.0f, m_pos.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}
//======================================
// 終了処理
//======================================
void CBlockX::Uninit()
{
	CObjectX::Uninit();
}
//======================================
// 更新処理
//======================================
void CBlockX::Update()
{
	//m_pLine->SetPos(m_pos);
	//m_pLine->SetRot(m_rot);

	m_pos += m_move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//CObjectX::Update();
	
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

}
//======================================
// 描画処理
//======================================
void CBlockX::Draw()
{
	CObjectX::Draw();
}
//======================================
// ブロックの生成
//======================================
CBlockX* CBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
	D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1)
{
	CBlockX* pBlockX = new CBlockX();

	pBlockX->SetPos(pos);
	pBlockX->SetRot(rot);
	pBlockX->m_pMesh = pMesh;
	pBlockX->m_pBuffMat = pBuffMat;
	pBlockX->m_dwNumMat = dwNumMat;
	pBlockX->m_fMoveStorage1 = movex1.x;
	pBlockX->m_fMoveStorage2 = movex2.x;
	pBlockX->m_fMoveStorage3 = movey1.y;
	pBlockX->m_fMoveStorage4 = movey2.y;
	pBlockX->m_fSpeedStorage = fSpeed;
	pBlockX->m_fSpeedStorage1 = fSpeed1;
	pBlockX->Init();

	return pBlockX;
}

//============================================
// ボスが生成させるブロック
//============================================
CBlockX* CBlockX::Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlockX* pBlock = new CBlockX();
	pBlock->Init();
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetModel("data/MODEL/ENEMY/bossblock.x");

	return pBlock;
}
//============================================
// ボス戦の時の自動生成ブロック
//============================================
CBlockX* CBlockX::Create3(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	CBlockX* pBlock = new CBlockX();
	pBlock->m_nType = type;
	pBlock->Init();
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);

	if (type == 0)
	{ // 上下
		pBlock->SetModel("data/MODEL/FIELD/title_floor.x");
	}
	else if (type == 1)
	{ // 左壁
		pBlock->SetModel("data/MODEL/FIELD/titlewall_left.x");
	}
	else if (type == 2)
	{ // 右壁
		pBlock->SetModel("data/MODEL/FIELD/titlewall_right.x");
	}

	return pBlock;
}
