//=================================
// 
//レンダラークラス(DirectX描画)renderer.cpp
//Auther kida ibuki 
// 
//==================================
#include "renderer.h"   // レンダラー
#include "manager.h"   // マネージャー
#include "sound.h"     // サウンド
#include "main.h"      // メイン

bool g_isSwitch = false;

//==========================
//コンストラクタ
//==========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pFont = nullptr;
}

//===========================
//デストラクタ
//===========================
CRenderer::~CRenderer()
{

}

//============================
//初期化設定
//============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;		//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ
	HRESULT hr;

	//DirectXオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードの取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面のサイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面のサイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;				//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;//デブスバッファとステンシルバッファを生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デブスバッファとして16bitを使用
	d3dpp.Windowed = bWindow;				//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;    // アンチエイリアス有効化

	////D3DPRESENT_PARAMETERS構造体に設定した内容でアンチエイリアシングが使用可能かチェックする。
	//hr = CheckAntialias(D3DMULTISAMPLE_16_SAMPLES);

	//DIrectXデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DIrectXデバイスの生成（描画処理はハードウェア頂点処理はCPUで行う）
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//DIrectXデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	////アンチエイリアシングが使用可能なときはレンダーステートのアンチエイリアシングを有効にする。
	//if (SUCCEEDED(hr))
	//{
	//	m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	//}
	//else
	//{
	//	m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	//}

	//デバック表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	return S_OK;

}
//============================
//終了処理
//============================
void CRenderer::Uninit()
{

	//DirectXデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//DirectXオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}


}
//============================
//更新処理
//============================
void CRenderer::Update()
{
	CObject::UpdateAll();
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();



#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F10))g_isSwitch = !g_isSwitch;
#endif
}
//============================
//描画処理
//============================
void CRenderer::Draw()
{
	//画面クリア（バックバッファ＆Zバッファのクリア）
	m_pD3DDevice->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(50, 50, 50, 0), 1.0f, 0);  //色変えれる


	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		CManager* pManager = CManager::GetInstance();
		LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// デバイスを取得

		//ワイヤーフレーム
		g_isSwitch ? pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

#ifdef _DEBUG
		DrawFPS();
#endif
		//カメラの設定
		pManager->GetCamera()->SetCamera();

		pManager->GetInstance()->GetScene()->Draw();


		//各種オブジェクトの描画処理
		CObject::DrawAll();
		//描画終了
		m_pD3DDevice->EndScene();

	}
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
void CRenderer::DrawFPS()
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int nCntFps = GetFPS();
	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", nCntFps);

	//テキスト描画
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//===========================
//デバイスの取得
//===========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;

}

#if 0
HRESULT CRenderer::CheckAntialias(D3DMULTISAMPLE_TYPE AntialiasMode)
{
	HRESULT hr = E_FAIL;
	DWORD QualityBackBuffer = 0;
	DWORD QualityZBuffer = 0;
	DWORD m = (DWORD)AntialiasMode;
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ


	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	while (m)
	{
		//レンダリングターゲットでアンチエイリアシングがサポートされているかをチェック
		hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dpp.BackBufferFormat,
			d3dpp.Windowed,
			(D3DMULTISAMPLE_TYPE)m,
			&QualityBackBuffer);
		if (SUCCEEDED(hr))
		{
			//深度ステンシル サーフェイスでアンチエイリアシングがサポートされているかをチェック
			hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				d3dpp.AutoDepthStencilFormat,
				d3dpp.Windowed,
				(D3DMULTISAMPLE_TYPE)m,
				&QualityZBuffer);
			if (SUCCEEDED(hr))
			{
				//アンチエイリアシングが使用できるのでD3DPRESENT_PARAMETERSにタイプをセットする。
				d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)m;

				//QualityBackBufferとQualityZBufferで小さい方の値を有効にする。どんなパターンで値が返るのかわからんので、こうしたほうが安全かと。
				if (QualityBackBuffer < QualityZBuffer)
					d3dpp.MultiSampleQuality = QualityBackBuffer - 1;
				else
					d3dpp.MultiSampleQuality = QualityZBuffer - 1;

				break;
			}
		}

		//現在のタイプでアンチエイリアシングが使用できないので、１段階低いタイプで再チェックする。
		m--;
	}

	return hr;
}
#endif