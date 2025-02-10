//=================================
// 
// �Q�[�������N���X�@game.cpp
//outher kida ibuki 
// 
//==================================
#include "game.h"
#include "manager.h"  // �}�l�[�W���[
//======3D==============
#include "object3D.h"   // �I�u�W�F�N�g3D
#include "objectX.h"    // �I�u�W�F�N�gX
#include "blockX.h"    // �u���b�N
#include "bullet.h"    // �e
#include "playerM.h"   // �v���C���[
//======UI==============
#include "target.h"    // �^�[�Q�b�g
#include "background.h"  // �o�b�N�O���E���h
#include "ui.h"        // UI
#include "life.h"      // ���C�t
#include "explosion.h" // ����
//======�T�E���h========
#include "sound.h"       // �T�E���h

//====================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//====================================
CGame::~CGame()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CGame::Init()
{
	CManager* pManager = CManager::GetInstance();

	SetModel_File();
	SetEnemy_File();

	// �e�N�X�`���̃��[�h
	CBullet::Load();
	CBulletEnemy::Load();
	CBackGround::Load();
	CExplosion::Load();

	CLife::Create(D3DXVECTOR2(1200.0f, 520.0f));   // ���C�t

	CUi::Create(D3DXVECTOR2(1200.0f, 320.0f), 0);   // UI
	CUi::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), 5);

	CPlayerM* pPlayer = CPlayerM::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));  // �v���C���[
	CTarget* pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 150.0f));   // ���e�B�N��



	CreateSaveObject(pPlayer);
	CreateSaveObject(pTarget);


	
	// �Z���N�g�̃I�u�W�F�N�g�����
	for (int i = 0; i < MAX; i++)
	{
		m_pPause_Select[i] = CPause_Select::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 300.0f + (80.0f * i)), D3DXVECTOR2(200.0f, 50.0f), i);
	}
	m_pPause_Select[0]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM002);


	return S_OK;
}
//====================================
// �I������
//====================================
void CGame::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Uninit();

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];
		// �ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			pObj->DeathFlag();

			pObj = pNext;

		}
	}

	// �e�N�X�`���̃A�����[�h
	CBullet::Unload();
	CBulletEnemy::Unload();
	CBackGround::Unload();
	CExplosion::Unload();
	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CGame::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//�L�[�{�[�h�擾
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

	bool bPause = pManager->GetPause();
	
	if (pKeyboard->GetTrigger(DIK_P) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_START))
	{
		// �T�E���h�𗬂�
		pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_OPEN);

		bPause = bPause ? false : true;
		pManager->SetPause(bPause);
	}
	if (bPause)  // true�̎�
	{

		int nSelectOld = m_nSelect;
		if (pKeyboard->GetTrigger(DIK_S) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_DOWN))
		{
			m_nSelect++;
			if (m_nSelect >= SELECT::MAX)
			{
				m_nSelect = 0;
			}
			// �T�E���h�𗬂�
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);

		}
		if (pKeyboard->GetTrigger(DIK_W) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_UP))
		{
			m_nSelect--;
			if (m_nSelect < 0)
			{
				m_nSelect = SELECT::MAX - 1;
			}
			// �T�E���h�𗬂�
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SELECT);

		}
		if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A))
		{
			// �T�E���h�𗬂�
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
	else // false�̎�
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
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];

		//��ނ̎擾
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // ���̃|�C���^���擾
			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //�_�E���L���X�g

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
						CEnemyBoss::Create(D3DXVECTOR3(0.0f, 0.0f, playerPos.z + 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));   // �{�X�̐���
						CBackGround* pBg = CBackGround::Create(D3DXVECTOR3(350.0f, 0.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.35f));   // �{�X��̔w�i����
						pBg->Create(D3DXVECTOR3(350.0f, 175.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.65f)); // �{�X��̔w�i����

						pBg->Create(D3DXVECTOR3(350.0f, 0.0f, 13000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.35f));   // �{�X��̔w�i����
						pBg->Create(D3DXVECTOR3(350.0f, 175.0f, 13000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.65f)); // �{�X��̔w�i����

					}
					break;
				}

				// �{�X��̎��Ƀu���b�N����������
				if (playerPos.z >= POSITION6 + 810.0f * m_nCntCreateMap)
				{
					m_nCntCreateMap++;

					CBlockX* pBlock = nullptr;
					// ���ɕ��ׂ�
					for (int nCnt = 0; nCnt < 2; nCnt++)
					{
						// �V��
						pBlock->Create3(D3DXVECTOR3(-170.0f + (330.0f * nCnt), 280.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
						// ��
						pBlock->Create3(D3DXVECTOR3(-170.0f + (330.0f * nCnt), -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
					}
					// ����
					pBlock->Create3(D3DXVECTOR3(-340.0f, -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
					// �E��
					pBlock->Create3(D3DXVECTOR3(340.0f, -140.0f, POSITION6 + 810.0f * m_nCntCreateMap), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
				}

			}
			// �v���C���[���u���b�N����ɍs��������̂�����
			else if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = (CBlockX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 posBlock = pBlock->GetPos();
				for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
				{
					//�I�u�W�F�N�g�擾
					CObject* pObj1 = pTopObject[nPriority];

					//��ނ̎擾
					while (pObj1 != nullptr)
					{
						CObject::TYPE type1 = pObj1->GetType();
						CObject* pNext1 = pObj1->GetNext(); // ���̃|�C���^���擾

						// �Ăуv���C���[��T��
						if (type1 == CObject::TYPE::PLAYER_M)
						{
							CPlayerM* pPlayer = (CPlayerM*)pObj1; //�_�E���L���X�g
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
// �`�揈��
//====================================
void CGame::Draw()
{

}
//======================================
// �Q�[���̐���
//======================================
CGame* CGame::Create()
{
	CGame* pGame = new CGame();
	pGame->Init();
	return pGame;
}
//===========================================
//���f���t�@�C���̓ǂݍ���
//===========================================
void CGame::SetModel_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
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
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &m_gModelData[nCntModel].cFile[0]);
			m_gModelData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
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
					// �f�o�C�X�̎擾
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// �ꎞ�ϐ�(�O���t�@�C���œǂݎ���������i�[)
					LPD3DXMESH pMesh = nullptr;			//���b�V���ւ̃|�C���^
					LPD3DXBUFFER pBuffMat = nullptr;    //�}�e���A���ւ̃|�C���^
					DWORD dwNumMat = 0;           //�}�e���A���̐�

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == m_gModelData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&m_gModelData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1)->SizeVtx(); //�u���b�N�̃��b�V�������l��;

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// �I�u�W�F�N�g�̈ʒu���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// �I�u�W�F�N�g�̌������w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);

				}
				else if (!strcmp(cFileModel, "MOVERIGHT"))
				{// �G���ǂ��܂ňړ����邩(�E)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVELEFT"))
				{// �G���ǂ��܂ňړ����邩(��)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}
				else if (!strcmp(cFileModel, "SPEED_X"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}
			}
			nCnt++;
		}
	}

}
//===========================================
//�G�̃��f���t�@�C���̓ǂݍ���
//===========================================
void CGame::SetEnemy_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
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
			continue;		//�J��Ԃ��B�A���œǂݍ��݂����̂�
		}
		if (!strcmp(cFileModel, "NUM_ENEMY"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%d", &nSaveModel);
		}
		//���f���̖��O����������
		if (!strcmp(cFileModel, "ENEMY_FILENAME"))
		{
			fscanf(pFile, "%s", cFileModel);
			fscanf(pFile, "%s", &g_aEnemyData[nCntModel].cFile[0]);
			g_aEnemyData[nCntModel].nType = nCntModel;  // type�Ɍ��݂̃J�E���g�ɂ���(����ɂ��ォ��0�C1�C2...�Ɛݒ�ł���)
			nCntModel++;
		}


		//���f���ݒ�
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
					// �f�o�C�X�̎擾
					LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
					// �ꎞ�ϐ�(�O���t�@�C���œǂݎ���������i�[)
					LPD3DXMESH pMesh = nullptr;			//���b�V���ւ̃|�C���^
					LPD3DXBUFFER pBuffMat = nullptr;    //�}�e���A���ւ̃|�C���^
					DWORD dwNumMat = 0;           //�}�e���A���̐�

					for (int nCntE = 0; nCntE < nSaveModel; nCntE++)
					{
						if (nType == g_aEnemyData[nCntE].nType)
						{
							//�t�@�C����ݒ肵�����f�����ǂݍ���
							D3DXLoadMeshFromX(&g_aEnemyData[nCntE].cFile[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&pBuffMat, NULL, &dwNumMat, &pMesh);

							//���b�V���̏����擾(�����蔻��ɂȂ���)
							//���͂Ȃ�...
						}
					}
					// Create�֐��Ɋi�[�������������œn��
					CEnemyX*pEnemy = CEnemyX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1);
					CreateSaveObject(pEnemy);
					pEnemy->SizeVtx();

					break;
				}
				else if (!strcmp(cFileModel, "TYPE"))
				{// �I�u�W�F�N�g�̎�ނ��w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%d", &nType);
				}
				else if (!strcmp(cFileModel, "POS"))
				{// �I�u�W�F�N�g�̈ʒu���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

				}
				else if (!strcmp(cFileModel, "ROT"))
				{// �I�u�W�F�N�g�̌������w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);

				}
				else if (!strcmp(cFileModel, "MOVERIGHT"))
				{// �G���ǂ��܂ňړ����邩(��)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move1.x);
					fscanf(pFile, "%f", &move1.y);
					fscanf(pFile, "%f", &move1.z);

				}
				else if (!strcmp(cFileModel, "MOVELEFT"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &move2.x);
					fscanf(pFile, "%f", &move2.y);
					fscanf(pFile, "%f", &move2.z);

				}
				else if (!strcmp(cFileModel, "MOVEUP"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey1.x);
					fscanf(pFile, "%f", &movey1.y);
					fscanf(pFile, "%f", &movey1.z);

				}
				else if (!strcmp(cFileModel, "MOVEDOWN"))
				{// �G���ǂ��܂ňړ����邩(��O)���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &movey2.x);
					fscanf(pFile, "%f", &movey2.y);
					fscanf(pFile, "%f", &movey2.z);

				}

				else if (!strcmp(cFileModel, "SPEED_X"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed);

				}
				else if (!strcmp(cFileModel, "SPEED_Y"))
				{// �ǂ̂��炢�̑��x�ňړ����邩���w��
					fscanf(pFile, "%s", cFileModel);
					fscanf(pFile, "%f", &fSpeed1);

				}

			}
			nCnt++;
		}
	}

}

