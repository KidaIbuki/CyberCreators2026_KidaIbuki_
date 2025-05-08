//=================================
// 
// エフェクトクラス　effect.cpp
//Auther kida ibuki 
// 
//==================================
#include "manager.h"    // マネージャー
#include "effect.h"   // エフェクト
//====================================
// コンストラクタ
//====================================
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_nType = 0;
	m_bUse = false; //使ってない状態へ
	m_bStartTexture = false; //テクスチャ初期位置を設定
	m_fRadius = 0.0f;
	m_Interval = 0.0f;
	m_EffectCnt = 0;
	m_fSplit = 0.0f;
	m_fAlpha = 0.0f;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// デストラクタ
//====================================
CEffect::~CEffect()
{
}
//====================================
// 初期設定
//====================================
HRESULT CEffect::Init()
{
	CManager* pManager = CManager::GetInstance();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CEffect::Uninit()
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
//====================================
// 更新処理
//====================================
void CEffect::Update()
{
	VERTEX_3D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bUse == true)
	{//エフェクト使われてる

		//テクスチャの初期位置を設定
		if (m_bStartTexture == false)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f / m_fSplit, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / m_fSplit, 1.0f);
			m_bStartTexture = true;
		}

		//テクスチャの横分割数から１コマ進む量を計算
		m_Interval = INTERVAL_EFFECT / m_fSplit;

		//エフェクトカウントを進める
		m_EffectCnt++;

		if (m_EffectCnt >= m_Interval)
		{
			pVtx[0].tex.x += 1.0f / m_fSplit;
			pVtx[1].tex.x += 1.0f / m_fSplit;
			pVtx[2].tex.x += 1.0f / m_fSplit;
			pVtx[3].tex.x += 1.0f / m_fSplit;

			m_EffectCnt = 0;
		}

		m_col.a -= m_fAlpha;

		//頂点の座標を半径に設定
		pVtx[0].pos = D3DXVECTOR3(-m_fRadius, m_fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fRadius, m_fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fRadius, -m_fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fRadius, -m_fRadius, 0.0f);

		//頂点カラー
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_nLife--;

		//軌跡が寿命を迎え入れた
		if (m_nLife <= 0)
		{
			m_bUse = false;
		}
	}
	if (m_bUse == false)
	{
		DeathFlag();
	}
	m_pVtxBuff->Unlock();

}
//====================================
// 描画処理
//====================================
void CEffect::Draw()
{
	CManager* pManager = CManager::GetInstance();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView; //ビューマトリックス取得用

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	if (m_bUse == true)
	{
		//ライトを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向けましょう
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める
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
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//ライトを有効に戻す
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αブレンディンを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//====================================
// 生成処理
//====================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nType, float fRadius, float fSplit, float fAlpha, int nLife)
{
	CEffect* pEffect = new CEffect();
	pEffect->Init();

	if (pEffect->m_bUse == false)
	{
		pEffect->m_pos = pos;    // 追跡させたいもの
		pEffect->m_col = col;    // 色
		pEffect->m_nType = nType;   // 種類
		pEffect->m_fRadius = fRadius;  // 大きさ
		pEffect->m_fSplit = fSplit;    // 分割数
		pEffect->m_fAlpha = fAlpha;    // 透明度(どれくらい透明にするか)
		pEffect->m_nLife = nLife;      // 寿命
		pEffect->m_bUse = true;
	}
	pEffect->SetTexture("data/TEXTURE/effect000.jpg");

	return pEffect;
}
//====================================
// テクスチャの設定
//====================================
void CEffect::SetTexture(std::string sPath)
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
