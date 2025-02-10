//=================================
// 
// ビルボードクラス　billboard.cpp
//outher kida ibuki 
// 
//==================================
#include "billboard.h"  // ビルボード
#include "manager.h"   // マネージャー
//==========================================
// コンストラクタ
//==========================================
CBillboard::CBillboard()
{
	m_pVtxBuff = nullptr;				// 頂点バッファ
	m_pTexture = nullptr;			// テクスチャ
	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	m_move = { 0.0f,0.0f,0.0f };       // 移動量
	m_size = { 0.0f,0.0f,0.0f };    // サイズ
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}
//==========================================
// デストラクタ
//==========================================
CBillboard::~CBillboard()
{
}
//==========================================
// 初期設定
//==========================================
HRESULT CBillboard::Init()
{
	CManager* pManager = CManager::GetInstance();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//==========================================
// 終了処理
//==========================================
void CBillboard::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}
//==========================================
// 更新処理
//==========================================
void CBillboard::Update()
{

}
//==========================================
// 描画処理
//==========================================
void CBillboard::Draw()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス取得用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの初期化
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);	//逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	//Zの比較方法を変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない(奥に表示するか、手前に表示するか)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//==========================================
// 生成処理
//==========================================
CBillboard* CBillboard::Create()
{
	CBillboard* pBillboard = new CBillboard();
	pBillboard->Init();
	return pBillboard;
}
//==========================================
// テクスチャの設定
//==========================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
void CBillboard::SetTexture(std::string sPath)
{
	CManager* pManager = CManager::GetInstance();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);

}
//==========================================
// 位置の設定
//==========================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//==========================================
// サイズの設定
//==========================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//==========================================
// ビルボードの設定(サイズ)
//==========================================
void CBillboard::SetBillboard(float fWidth, float fHeight, float fDepth)
{
	CManager* pManager = CManager::GetInstance();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, fDepth);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, fDepth);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);
	pVtx[3].pos = D3DXVECTOR3(fWidth, 0.0f, -fDepth);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//==========================================
// ビルボードのカラー設定
//==========================================
void CBillboard::SetColor(D3DXCOLOR col)
{ // 赤（Max1.0ｆ）,緑（Max1.0ｆ）, 青（Max1.0ｆ）, α（Max1.0ｆ）

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
