//==============================================
// 
//オブジェクト(xファイルの読み込み)　objectX.cpp
//outher kida ibuki 
// 
//==============================================
#include "objectX.h"    // オブジェクトX
#include "manager.h"    // マネージャー


//==================================================
//コンストラクタ
//==================================================
CObjectX::CObjectX()
{
	// 変数の初期化
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pVtxBuff = nullptr;				// 頂点バッファ
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		m_pTexture[i] = nullptr;			// テクスチャ
	}
	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	//m_move = { 0.0f, 0.0f, 0.0f };		//移動量
	m_size = { 0.0f,0.0f,0.0f };
	m_nMaxVtx = { 0.0f,0.0f,0.0f };
	m_nMinVtx = { 0.0f,0.0f,0.0f };
}
CObjectX::CObjectX(int nPrioroty) :CObject(nPrioroty)
{
	// 変数の初期化
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pVtxBuff = nullptr;				// 頂点バッファ
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		m_pTexture[i] = nullptr;			// テクスチャ
	}
	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	//m_move = { 0.0f, 0.0f, 0.0f };		//移動量
	m_size = { 0.0f,0.0f,0.0f };
	m_nMaxVtx = { 0.0f,0.0f,0.0f };
	m_nMinVtx = { 0.0f,0.0f,0.0f };
}
//==================================================
//デストラクタ
//==================================================
CObjectX::~CObjectX()
{
}
//==================================================
//初期設定
//==================================================
HRESULT CObjectX::Init()
{
	CManager* pManager = CManager::GetInstance();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	

	return S_OK;


}

//===============================================
//モデルの頂点情報を元にサイズの最大値最小値を求める
//===============================================
void CObjectX::SizeVtx()
{
	//**========================メッシュの情報を取得================**

	if (m_pMesh != nullptr)
	{
		//頂点数の取得
		m_nNumVtx = m_pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		//頂点バッファのロック
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_bpVtxBuff);

		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			//頂点座標を代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_bpVtxBuff;

			//頂点座標を比較してモデルの最大値、最小値を取得
			//xの最大値
			if (vtx.x > m_nMaxVtx.x)
			{
				m_nMaxVtx.x = vtx.x;
			}
			//xの最小値
			else if (vtx.x < m_nMinVtx.x)
			{
				m_nMinVtx.x = vtx.x;
			}
			//yの最大値
			if (vtx.y > m_nMaxVtx.y)
			{
				m_nMaxVtx.y = vtx.y;
			}
			//yの最小値
			else if (vtx.y < m_nMinVtx.y)
			{
				m_nMinVtx.y = vtx.y;
			}
			//zの最大値
			if (vtx.z > m_nMaxVtx.z)
			{
				m_nMaxVtx.z = vtx.z;
			}
			//zの最小値
			else if (vtx.z < m_nMinVtx.z)
			{
				m_nMinVtx.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			m_bpVtxBuff += m_sizeFVF;
		}
		//頂点バッファのアンロック
		m_pMesh->UnlockVertexBuffer();

		//**=========================================================**
		m_size = m_nMaxVtx - m_nMinVtx;
	}
}

//==================================================
//終了処理
//==================================================
void CObjectX::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		// テクスチャの破棄
		if (m_pTexture[i] != nullptr)
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

}
//==================================================
//更新処理
//==================================================
void CObjectX::Update()
{

}
//==================================================
//描画処理
//==================================================
void CObjectX::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得
	D3DXMATRIX mtxRot, mtxTrans;											// 計算用マトリックス
	D3DMATERIAL9 matDef;				// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;					// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//※ブロック以外の向きや位置の反映↓
	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//==================================================================================
	// オブジェクトの描画[blockX]
	//==================================================================================
		// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//if (m_pMesh != nullptr) // メッシュの場合
	//{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			// モデルの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		// 保存していたマテリアルに戻す
		pDevice->SetMaterial(&matDef);
	//}
	//else  //メッシュ以外の場合
	//{
	//	// 頂点バッファをデータストリームに設定
	//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//	// 頂点フォーマットの設定
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	// テクスチャの設定
	//	pDevice->SetTexture(0, m_pTexture);

	//	// ポリゴンの描画
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //プリミティブの種類
	//		0, //描画する最初の頂点インデックス
	//		2);				//描画するプリミティブ数
	//}

}
//==================================================
//オブジェクトの生成(xファイルの)
//==================================================
CObjectX* CObjectX::Create()
{
	CObjectX* pObjectX = new CObjectX;
	pObjectX->Init();
	return pObjectX;

}
//==================================================
//モデルの設定(引数にパスを書く)
//==================================================
void CObjectX::SetModel(std::string sPath)
{
	CManager* pManager = CManager::GetInstance();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// モデルの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(sPath.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	SizeVtx();	// pMeshの情報を取得
}

//======================================
//サイズの設定
//======================================
void CObjectX::SetSize(float fWidth, float fHeight, float fDepth)
{
	m_size = D3DXVECTOR3(fWidth, fHeight, fDepth);
}

