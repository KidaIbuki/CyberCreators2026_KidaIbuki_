//=================================
// 
// シーンクラス　scene.cpp
//outher kida ibuki 
// 
//==================================
#include "title.h"     // タイトル
#include "fade.h"      // フェード
#include "manager.h"    // マネージャー
#include "sound.h"      // サウンド
#include "blockX.h"   // ブロック
#include "playerM.h"  // プレイヤー
#include "target.h"   // レティクル
#include "ui.h"       // UI
//====================================
// コンストラクタ
//====================================
CTitle::CTitle()
{
	m_nTimerCnt = 40;
}
//====================================
// デストラクタ
//====================================
CTitle::~CTitle()
{
}
//====================================
// 初期設定
//====================================
HRESULT CTitle::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();
	//SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	CUi::Create(D3DXVECTOR2(300.0f, 150.0f), 6);   // UI

	SetModel_File_Title();

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CTitle::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Uninit();

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
void CTitle::Update()
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
			CFade::SetFade(CScene::MODE::MODE_TITLE2);
			m_nTimerCnt = 40;
		}
	}
}

//====================================
// 描画処理
//====================================
void CTitle::Draw()
{
}
//======================================
// タイトルの生成
//======================================
CTitle* CTitle::Create()
{
	CTitle* pTitle = new CTitle();
	pTitle->Init();
	//pTitle->SetTexture("data/TEXTURE/titleTest.png");

	return pTitle;
}
//====================================
// コンストラクタ
//====================================
CTitleSecond::CTitleSecond()
{
	m_nTimerCnt = 40;
	m_Position = POSITION_NONE;
	m_nFrame = 0;

}
//====================================
// デストラクタ
//====================================
CTitleSecond::~CTitleSecond()
{
}
//====================================
// 初期設定
//====================================
HRESULT CTitleSecond::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();

	SetTitle_File();  // 外部ファイル出力

	// チュートリアル用のプレイヤーとレティクル
	CPlayerM* pPlayer = CPlayerM::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
	CTarget* pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 150.0f));
	pPlayer->MoveFlag(true);
	// オブジェクトの保存
	CreateSaveObject(pPlayer);
	CreateSaveObject(pTarget);

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CTitleSecond::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Uninit();

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
	CPlayerM::MoveFlag(false);
	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CTitleSecond::Update()
{
	
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
			CObject::TYPE type = pObj->GetType();

			//pObj->Update();  // オブジェクトのUpdate

			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //ダウンキャスト
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					// 各位置にチュートリアル用のテクスチャを張る
					if (playerPos.z >= POSITION_NUM_1 && playerPos.z <= POSITION_NUM_2)
					{
						m_Position = POSITION_1;
						m_nFrame = 1;   // フレームに代入
					}
					else if (playerPos.z >= POSITION_NUM_3 && playerPos.z <= POSITION_NUM_4)
					{
						m_Position = POSITION_2;
						m_nFrame = 1;   // フレームに代入
					}
					else if (playerPos.z >= POSITION_NUM_5 && playerPos.z <= POSITION_NUM_6)
					{
						m_Position = POSITION_3;
						m_nFrame = 1;   // フレームに代入
					}
					else if (playerPos.z >= POSITION_NUM_7 && playerPos.z <= POSITION_NUM_8)
					{
						m_Position = POSITION_4;
						m_nFrame = 1;   // フレームに代入
					}
					else
					{
						m_Position = POSITION_NONE;
					}

					// チュートリアルを終えたら
					if (playerPos.z >= POSITION_NUM_9 && playerPos.z <= POSITION_NUM_10)
					{
						CFade::SetFade(CScene::MODE::MODE_GAME);
					}
				}

			}

			pObj = pNext;

		}
	}
	// テクスチャを貼る
	switch (m_Position)
	{
	case POSITION_1:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 100.0f), 1);
		}
		break;
	case POSITION_2:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 100.0f), 2);
		}
		break;
	case POSITION_3:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 100.0f), 3);
		}
		break;
	case POSITION_4:
		m_nFrame--;
		if (m_nFrame <= 0)
		{
			CUi::Create(D3DXVECTOR2(640.0f, 100.0f), 4);
		}
		break;
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
			CFade::SetFade(CScene::MODE::MODE_GAME);
			m_nTimerCnt = 40;
		}
	}
}

//====================================
// 描画処理
//====================================
void CTitleSecond::Draw()
{

}
//======================================
// タイトルの生成
//======================================
CTitleSecond* CTitleSecond::Create()
{
	CTitleSecond* pTitle2 = new CTitleSecond();
	pTitle2->Init();

	return pTitle2;
}
//===========================================
//モデルファイルの読み込み(タイトル用)
//===========================================
void CTitleSecond::SetTitle_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
	FILE* pFile = fopen("data\\TXT\\SetTitle_File.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_OBJECTSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &m_gModelData[nCntModel].cFile[0]);
			m_gModelData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "MODELSET"))
		{
			int nType = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2 = { 0.0f,0.0f,0.f };
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;
			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_MODELSET"))
				{
					CManager* pManager = CManager::GetInstance();
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == m_gModelData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&m_gModelData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CBlockX* pBlock = CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1); //ブロックのメッシュ情報を獲得;
					CreateSaveObject(pBlock);
					pBlock->SizeVtx();
					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// オブジェクトの位置を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// オブジェクトの向きを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);

				}
				else if (!strcmp(cFileModel, "MOVERIGHT"))
				{// 敵がどこまで移動するか(右)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVELEFT"))
				{// 敵がどこまで移動するか(左)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}
				else if (!strcmp(cFileModel, "SPEED_X"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}
			}
			nCnt++;
		}
	}

}
//=============================================
// タイトルで見せるステージ
void CTitle::SetModel_File_Title()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
	FILE* pFile = fopen("data\\TXT\\SetModel_File.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_OBJECTSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &m_gModelData[nCntModel].cFile[0]);
			m_gModelData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "MODELSET"))
		{
			int nType = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2 = { 0.0f,0.0f,0.0f };
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;
			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_MODELSET"))
				{
					CManager* pManager = CManager::GetInstance();
					// デバイスの取得
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// 一時変数(外部ファイルで読み取った情報を格納)
					LPD3DXMESH pMesh = nullptr;			//メッシュへのポインタ
					LPD3DXBUFFER pBuffMat = nullptr;    //マテリアルへのポインタ
					DWORD dwNumMat = 0;           //マテリアルの数

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == m_gModelData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&m_gModelData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create関数に格納した情報を引数で渡す
					CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1)->SizeVtx(); //ブロックのメッシュ情報を獲得;

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// オブジェクトの種類を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// オブジェクトの位置を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// オブジェクトの向きを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);

				}
				else if (!strcmp(cFileModel, "MOVERIGHT"))
				{// 敵がどこまで移動するか(右)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVELEFT"))
				{// 敵がどこまで移動するか(左)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// 敵がどこまで移動するか(手前)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}
				else if (!strcmp(cFileModel, "SPEED_X"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// どのくらいの速度で移動するかを指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}
			}
			nCnt++;
		}
	}

}

//====================================
// 保存しておくコンストラクタ
//====================================
CTitle::CTitleSaveObject::CTitleSaveObject(CObject* pObject) :
	CSaveObject(pObject)
{
}
//====================================
// 保存しておくデストラクタ
//====================================
CTitle::CTitleSaveObject::~CTitleSaveObject()
{
}
//====================================
// 保存しておく初期設定
//====================================
HRESULT CTitle::CTitleSaveObject::Init()
{
	return S_OK;
}
//====================================
// 保存しておく終了処理
//====================================
void CTitle::CTitleSaveObject::Uninit()
{
}
//====================================
// 保存しておく更新処理
//====================================
void CTitle::CTitleSaveObject::Update()
{
}
//====================================
// 保存しておく描画処理
//====================================
void CTitle::CTitleSaveObject::Draw()
{
}
//====================================
// 保存しておくコンストラクタ
//====================================
CTitleSecond::CTitleSecondSaveObject::CTitleSecondSaveObject(CObject* pObject) :
	CSaveObject(pObject)
{
}
//====================================
// 保存しておくデストラクタ
//====================================
CTitleSecond::CTitleSecondSaveObject::~CTitleSecondSaveObject()
{
}
//====================================
// 保存しておく初期設定
//====================================
HRESULT CTitleSecond::CTitleSecondSaveObject::Init()
{
	return S_OK;
}
//====================================
// 保存しておく終了設定
//====================================
void CTitleSecond::CTitleSecondSaveObject::Uninit()
{

}
//====================================
// 保存しておく更新処理
//====================================
void CTitleSecond::CTitleSecondSaveObject::Update()
{
}
//====================================
// 保存しておく描画処理
//====================================
void CTitleSecond::CTitleSecondSaveObject::Draw()
{
}
