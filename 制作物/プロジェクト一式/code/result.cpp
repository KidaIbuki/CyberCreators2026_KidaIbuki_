//=================================
// 
// シーンクラス　result.cpp
// Auther kida ibuki 
// 
//==================================
#include "result.h"   // リザルト
#include "fade.h"     // フェード
#include "manager.h"  // マネージャー
#include "sound.h"   // サウンド
//====================================
// コンストラクタ
//====================================
CResult::CResult()
{
	m_nTimerCnt = 40;
}
//====================================
// デストラクタ
//====================================
CResult::~CResult()
{
}
//====================================
// 初期設定
//====================================
HRESULT CResult::Init()
{
	CScene::Init();
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	
	CManager* pManager = CManager::GetInstance();
	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM003);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CResult::Uninit()
{
	CScene::Uninit();
	CManager* pManager = CManager::GetInstance();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->DeathFlag();

			pObj = pNext;

		}
	}

	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CResult::Update()
{
	CScene::Update();
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->Update();

			pObj = pNext;

		}
	}

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得

	if (m_nTimerCnt > 0)
	{
		m_nTimerCnt--;
	}
	if (m_nTimerCnt <= 0)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
		{
			CFade::SetFade(CScene::MODE::MODE_TITLE);
			m_nTimerCnt = 40;
		}
	}
}
//====================================
// 描画処理
//====================================
void CResult::Draw()
{
	CScene::Draw();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];
		// 最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->Draw();

			pObj = pNext;

		}
	}

}
//======================================
// タイトルの生成
//======================================
CResult* CResult::Create()
{
	CResult* pResult = new CResult();
	pResult->Init();
	pResult->SetTexture("data/TEXTURE/resultclear.png");

	return pResult;
}

