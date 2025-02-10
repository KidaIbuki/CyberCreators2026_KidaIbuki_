//=================================
// 
// マネージャ　manager.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"  // マネージャー
#include "object.h"   // オブジェクト
#include "objectX.h"  // オブジェクトX
#include "blockX.h"               // ブロック
#include "enemyX.h"               // エネミー
//=====シーン============
#include "title.h"     // タイトル
//======================================
//コンストラクタ
//======================================
CManager::CManager()
{
	srand((unsigned int)time(NULL));

	m_pRenderer = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pKeyboard = nullptr;
	m_pKeyJoypad = nullptr;
	m_pScene = nullptr;
	//m_pFade = nullptr;
	m_pKeyMouse = nullptr;
	m_pFog = nullptr;
}

//=======================================
//デストラクタ
//=======================================
CManager::~CManager()
{

}

//=====================================
//初期設定
//=====================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == nullptr)
	{
		// レンダラーの生成 レンダラーは一番上！
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd, bWindow);
	}

	if (m_pFog == nullptr)
	{
		m_pFog = new CFog();
		m_pFog->Init();
	}
	if (m_pSound == nullptr)
	{
		// サウンドの生成
		m_pSound = new CSound();
		m_pSound->InitSound(hWnd);
	}
	if (m_pCamera == nullptr)
	{
		//カメラの生成
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}
	if (m_pLight == nullptr)
	{
		//ライトの生成
		m_pLight = new CLight();
		m_pLight->Init();
	}
	if (m_pKeyboard == nullptr)
	{
		//キーボードの生成
		m_pKeyboard = new CInputKeyboard();
		m_pKeyboard->Init(hInstance, hWnd);
	}
	if (m_pKeyJoypad == nullptr)
	{
		//コントローラーの生成
		m_pKeyJoypad = new CInputJoypad();
		m_pKeyJoypad->Init(hInstance, hWnd);
	}
	if (m_pKeyMouse == nullptr)
	{
		//マウスの生成
		m_pKeyMouse = new CInputMouse();
		m_pKeyMouse->Init(hInstance, hWnd);
	}
	//if (m_pFade == nullptr)
	//{
	//	//フェードの生成
	//	m_pFade = new CFade();
	//	m_pFade->Init();
	//}
	if (m_pScene == nullptr)
	{
		// シーンの生成
		m_pScene = new CTitle();
	}

	//最初のシーン設定
	//SetMode(CScene::MODE::MODE_TITLE);
	m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//=====================================
// 終了
//=====================================
void CManager::Uninit()
{	
	// レンダラーを破棄する
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// フォグを破棄する
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		delete m_pFog;
		m_pFog = nullptr;
	}

	// サウンドを破棄する
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = nullptr;
	}
	//カメラの破棄
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//ライトの破棄
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	// キーボード入力破棄
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	// コントローラー入力破棄
	if (m_pKeyJoypad != nullptr)
	{
		m_pKeyJoypad->Uninit();
		delete m_pKeyJoypad;
		m_pKeyJoypad = nullptr;
	}
	// マウス入力破棄
	if (m_pKeyMouse != nullptr)
	{
		m_pKeyMouse->Uninit();
		delete m_pKeyMouse;
		m_pKeyMouse = nullptr;
	}

	//// シーンの破棄
	//if (m_pScene != nullptr)
	//{
	//	m_pScene->Uninit();
	//	delete m_pScene;
	//	m_pScene = nullptr;
	//}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	
}

//=====================================
// 更新
//=====================================
void CManager::Update()
{
	// シーンの更新
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	// レンダラーの更新
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}


	// フォグの更新
	if (m_pFog != nullptr)
	{
		m_pFog->Update();
	}
	// キーボードの更新
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}
	// コントローラーの更新
	if (m_pKeyJoypad != nullptr)
	{
		m_pKeyJoypad->Update();
	}
	// マウスの更新
	if (m_pKeyMouse != nullptr)
	{
		m_pKeyMouse->Update();
	}
	// カメラの更新
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	// ライトの更新
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	CObject::DeathAll();

}

//======================================
//描画
//======================================
void CManager::Draw()
{
	// レンダラーの描画
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}

	// フォグの更新
	if (m_pFog != nullptr)
	{
		m_pFog->Draw();
	}

	//シーンの描画
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Draw();
	}
}



//=======================================
// レンダラーの取得
//=======================================
CRenderer* CManager::GetRenderer()
{
	assert(m_pRenderer != nullptr);
	return m_pRenderer;
}
//======================================
//カメラの取得
//=====================================
CCamera* CManager::GetCamera()
{
	assert(m_pCamera != nullptr);
	return m_pCamera;
}
//======================================
//ライトの取得
//=====================================
CLight* CManager::GetLight()
{
	assert(m_pLight != nullptr);
	return m_pLight;
}
//======================================
//キーボードの取得
//=====================================
CInputKeyboard* CManager::GetKeyboard()
{
	assert(m_pKeyboard != nullptr);
	return m_pKeyboard;
}
//======================================
//コントローラーの取得
//=====================================
CInputJoypad* CManager::GetJoypad()
{
	assert(m_pKeyJoypad != nullptr);
	return m_pKeyJoypad;
}
//======================================
//マウスの取得
//=====================================
CInputMouse* CManager::GetMouse()
{
	assert(m_pKeyMouse != nullptr);
	return m_pKeyMouse;
}

//======================================
//シーンの設定
//======================================
void CManager::SetMode(CScene::MODE mode)
{
	// シーンの破棄
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	//生成
	m_pScene = CScene::Create(mode);

}

//======================================
//シーンの取得
//=====================================
CScene* CManager::GetScene()
{
	assert(m_pScene != nullptr);
	return m_pScene;
}

//======================================
//フェードの取得
//=====================================
CFade* CManager::GetFade()
{
	assert(m_pFade != nullptr);
	return m_pFade;
}
//======================================
//サウンドの取得
//=====================================
CSound* CManager::GetSound()
{
	assert(m_pSound != nullptr);
	return m_pSound;
}
//======================================
// フォグの取得
//=====================================
CFog* CManager::GetFog()
{
	return m_pFog;;
}
