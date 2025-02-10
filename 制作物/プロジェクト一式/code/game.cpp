//=================================
// 
// ゲーム処理クラス　game.cpp
//outher kida ibuki 
// 
//==================================
#include "game.h"
#include "manager.h"  // マネージャー
//======3D==============
#include "object3D.h"   // オブジェクト3D
#include "objectX.h"    // オブジェクトX
#include "blockX.h"    // ブロック
#include "bullet.h"    // 弾
#include "playerM.h"   // プレイヤー
//======UI==============
#include "target.h"    // ターゲット
#include "background.h"  // バックグラウンド
#include "ui.h"        // UI
#include "life.h"      // ライフ
#include "explosion.h" // 爆発
//======サウンド========
#include "sound.h"       // サウンド

//====================================
// コンストラクタ
//====================================
CGame::CGame()
{
	m_bUseBoss = false;
	m_nFrame = 1;
	m_nSelect = 0;
	m_nFrameTime = 20;
	m_nCnt = 0;
	m_nCntCreateMap = 0;
}
//====================================
// デストラクタ
//====================================
CGame::~CGame()
{
}
//====================================
// 初期設定
//====================================
HRESULT CGame::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File();
	SetEnemy_File();

	// テクスチャのロード
	CBullet::Load();
	CBulletEnemy::Load();
	CBackGround::Load();
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(1200.0f, 520.0f));   // ライフ

	CUi::Create(D3DXVECTOR2(1200.0f, 320.0f), 0);   // UI
	CUi::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), 5);

	CPlayerM* pPlayer = CPlayerM::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));  // プレイヤー
	CTarget* pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 150.0f));   // レティクル



	CreateSaveObject(pPlayer);
	CreateSaveObject(pTarget);


	
	// セレクトのオブジェクトを作る
	for (int i = 0; i < MAX; i++)
	{
		m_pPause_Select[i] = CPause_Select::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 300.0f + (80.0f * i)), D3DXVECTOR2(200.0f, 50.0f), i);
	}
	m_pPause_Select[0]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// サウンドを流す
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM002);


	return S_OK;
}
//====================================
// 終了処理
//====================================
void CGame::Uninit()
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

	// テクスチャのアンロード
	CBullet::Unload();
	CBulletEnemy::Unload();
	CBackGround::Unload();
	CExplosion::Unload();
	// サウンドを止める
	pManager->GetSound()->StopSound();

}
//====================================
// 更新処理
//====================================
void CGame::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//キーボード取得
	CInputJoypad* pJoypad = pManager->GetJoypad();    //コントローラー取得

	bool bPause = pManager->GetPause();
	
	if (pKeyboard->GetTrigger(DIK_P) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
	{
		// サウンドを流す
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_OPEN);

		bPause = bPause ? false : true;
		pManager->SetPause(bPause);
	}
	if (bPause)  // trueの時
	{

		int nSelectOld = m_nSelect;
		if (pKeyboard->GetTrigger(DIK_S) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_DOWN))
		{
			m_nSelect++;
			if (m_nSelect >= SELECT::MAX)
			{
				m_nSelect = 0;
			}
			// サウンドを流す
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);

		}
		if (pKeyboard->GetTrigger(DIK_W) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_UP))
		{
			m_nSelect--;
			if (m_nSelect < 0)
			{
				m_nSelect = SELECT::MAX - 1;
			}
			// サウンドを流す
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);

		}
		if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A))
		{
			// サウンドを流す
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_OK);

			switch (m_nSelect)
			{
			case SELECT::CONTINUE:
				pManager->SetPause(false);
				break;
			case SELECT::RETRY:
				pManager->SetPause(false);
				CFade::SetFade(CScene::MODE::MODE_GAME);
				CPlayerM::MoveFlag(false);
				break;
			case SELECT::QUIT:
				pManager->SetPause(false);
				CFade::SetFade(CScene::MODE::MODE_TITLE);
				CPlayerM::MoveFlag(false);
				break;
			}
		}
		if (m_nSelect != nSelectOld)
		{
			m_pPause_Select[nSelectOld]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pPause_Select[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else // falseの時
	{

		if (m_nFrameTime >= 0)
		{
			m_nFrameTime--;
		}
		if (m_nFrameTime <= 0)
		{
			CUi::SubTime();
			m_nCnt++;
			m_nFrameTime = 20;
		}
		if (m_nCnt == 3)
		{
			m_nFrameTime = 0;
		}

	}
	
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//オブジェクト取得
		CObject* pObj = pTopObject[nPriority];

		//種類の取得
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // 次のポインタを取得
			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //ダウンキャスト

				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				if (playerPos.z >= POSITION1 && playerPos.z <= POSITION5)
				{
					m_bUseBoss = true;
				}
				else
				{
					m_bUseBoss = false;
				}
				switch (m_bUseBoss)
				{
				case true:
					m_nFrame--;
					if (m_nFrame <= 0)
					{
						pPlayer->ResetPlayer();
						CEnemyBoss::Create(D3DXVECTOR3(0.0f, 0.0f, playerPos.z + 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));   // ボスの生成
						CBackGround* pBg = CBackGround::Create(D3DXVECTOR3(350.0f, 0.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.35f));   // ボス戦の背景生成
						pBg->Create(D3DXVECTOR3(350.0f, 175.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.65f)); // ボス戦の背景生成

						pBg->Create(D3DXVECTOR3(350.0f, 0.0f, 13000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.35f));   // ボス戦の背景生成
						pBg->Create(D3DXVECTOR3(350.0f, 175.0f, 13000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.65f)); // ボス戦の背景生成

					}
					break;
				}

				// ボス戦の時にブロックを自動生成
				if (playerPos.z >= POSITION6 + 810.0f * m_nCntCreateMap)
				{
					m_nCntCreateMap++;

					CBlockX* pBlock = nullptr;
					// 横に並べる
					for (int nCnt = 0; nCnt < 2; nCnt++)
					{
						// 天井
						pBlock->Create3(D3DXVECTOR3(-170.0f + (330.0f * nCnt), 280.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
						// 床
						pBlock->Create3(D3DXVECTOR3(-170.0f + (330.0f * nCnt), -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
					}
					// 左壁
					pBlock->Create3(D3DXVECTOR3(-340.0f, -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
					// 右壁
					pBlock->Create3(D3DXVECTOR3(340.0f, -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
				}

			}
			// プレイヤーがブロックより先に行ったら後ろのを消す
			else if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //ダウンキャスト
				D3DXVECTOR3 posBlock = pBlock->GetPos();
				for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
				{
					//オブジェクト取得
					CObject* pObj1 = pTopObject[nPriority];

					//種類の取得
					while (pObj1 != nullptr)
					{
						CObject::TYPE type1 = pObj1->GetType();
						CObject* pNext1 = pObj1->GetNext(); // 次のポインタを取得

						// 再びプレイヤーを探す
						if (type1 == CObject::TYPE::PLAYER_M)
						{
							CPlayerM* pPlayer = (CPlayerM*)pObj1; //ダウンキャスト
							D3DXVECTOR3 posPlayer = pPlayer->GetPos();
							if (posBlock.z < posPlayer.z - 2000.0f)
							{
								pBlock->DeathFlag();
							}
						}
						pObj1 = pNext1;
					}
				}
			}
			pObj = pNext;
		}
	}
	

}
//====================================
// 描画処理
//====================================
void CGame::Draw()
{

}
//======================================
// ゲームの生成
//======================================
CGame* CGame::Create()
{
	CGame* pGame = new CGame();
	pGame->Init();
	return pGame;
}
//===========================================
//モデルファイルの読み込み
//===========================================
void CGame::SetModel_File()
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
//===========================================
//敵のモデルファイルの読み込み
//===========================================
void CGame::SetEnemy_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//モデルのパスの長さ
	int nSaveModel = 0;
	int nCntModel = 0;  // 読み込んだモデルファイルのカウント※ MEMO 変数を1つで完結させない！
	//int nLoadData;

	//ファイルを開く
	FILE* pFile = fopen("data\\TXT\\SetEnemy_File.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", cFileModel);

		if (!strcmp(cFileModel, "END_MODEL_ENEMYSET"))
		{
			fclose(pFile);
			break;
		}
		if (cFileModel[0] == '#')
		{
			continue;		//繰り返す。連続で読み込みたいので
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//モデルの名前を検索する
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // typeに現在のカウントにする(これにより上から0，1，2...と設定できる)
			nCntModel++;
		}


		//モデル設定
		if (!strcmp(cFileModel, "ENEMY_MODELSET"))
		{
			int nType = 0;
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2 = { 0.0f,0.0f,0.0f };
			float fSpeed = 0.0f;
			float fSpeed1 = 0.0f;

			while (1)
			{
				fscanf(pFile, "%s", cFileModel);

				if (!strcmp(cFileModel, "END_ENEMYSET"))
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
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//ファイルを設定したモデル分読み込む
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

							//メッシュの情報を取得(当たり判定につながる)
							//今はなし...
						}
					}
					// Create関数に格納した情報を引数で渡す
					CEnemyX*pEnemy = CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1);
					CreateSaveObject(pEnemy);
					pEnemy->SizeVtx();

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
				{// 敵がどこまで移動するか(奥)を指定
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVELEFT"))
				{// 敵がどこまで移動するか(手前)を指定
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

