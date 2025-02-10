//=================================
// 
// �V�[���N���X�@scene.cpp
//outher kida ibuki 
// 
//==================================
#include "title.h"     // �^�C�g��
#include "fade.h"      // �t�F�[�h
#include "manager.h"    // �}�l�[�W���[
#include "sound.h"      // �T�E���h
#include "blockX.h"   // �u���b�N
#include "playerM.h"  // �v���C���[
#include "target.h"   // ���e�B�N��
#include "ui.h"       // UI
//====================================
// �R���X�g���N�^
//====================================
CTitle::CTitle()
{
	m_nTimerCnt = 40;
}
//====================================
// �f�X�g���N�^
//====================================
CTitle::~CTitle()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CTitle::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();
	//SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	CUi::Create(D3DXVECTOR2(300.0f, 150.0f), 6);   // UI

	SetModel_File_Title();

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}
//====================================
// �I������
//====================================
void CTitle::Uninit()
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
	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CTitle::Update()
{
	CScene::Update();

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

			pObj->Update();

			pObj = pNext;

		}
	}

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* pKeyboard = pManager->GetKeyboard();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

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
// �`�揈��
//====================================
void CTitle::Draw()
{
}
//======================================
// �^�C�g���̐���
//======================================
CTitle* CTitle::Create()
{
	CTitle* pTitle = new CTitle();
	pTitle->Init();
	//pTitle->SetTexture("data/TEXTURE/titleTest.png");

	return pTitle;
}
//====================================
// �R���X�g���N�^
//====================================
CTitleSecond::CTitleSecond()
{
	m_nTimerCnt = 40;
	m_Position = POSITION_NONE;
	m_nFrame = 0;

}
//====================================
// �f�X�g���N�^
//====================================
CTitleSecond::~CTitleSecond()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CTitleSecond::Init()
{
	CManager* pManager = CManager::GetInstance();

	CScene::Init();

	SetTitle_File();  // �O���t�@�C���o��

	// �`���[�g���A���p�̃v���C���[�ƃ��e�B�N��
	CPlayerM* pPlayer = CPlayerM::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
	CTarget* pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 150.0f));
	pPlayer->MoveFlag(true);
	// �I�u�W�F�N�g�̕ۑ�
	CreateSaveObject(pPlayer);
	CreateSaveObject(pTarget);

	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);


	return S_OK;
}
//====================================
// �I������
//====================================
void CTitleSecond::Uninit()
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
	CPlayerM::MoveFlag(false);
	// �T�E���h���~�߂�
	pManager->GetSound()->StopSound();

}
//====================================
// �X�V����
//====================================
void CTitleSecond::Update()
{
	
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
			CObject::TYPE type = pObj->GetType();

			//pObj->Update();  // �I�u�W�F�N�g��Update

			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{

					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					// �e�ʒu�Ƀ`���[�g���A���p�̃e�N�X�`���𒣂�
					if (playerPos.z >= POSITION_NUM_1 && playerPos.z <= POSITION_NUM_2)
					{
						m_Position = POSITION_1;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else if (playerPos.z >= POSITION_NUM_3 && playerPos.z <= POSITION_NUM_4)
					{
						m_Position = POSITION_2;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else if (playerPos.z >= POSITION_NUM_5 && playerPos.z <= POSITION_NUM_6)
					{
						m_Position = POSITION_3;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else if (playerPos.z >= POSITION_NUM_7 && playerPos.z <= POSITION_NUM_8)
					{
						m_Position = POSITION_4;
						m_nFrame = 1;   // �t���[���ɑ��
					}
					else
					{
						m_Position = POSITION_NONE;
					}

					// �`���[�g���A�����I������
					if (playerPos.z >= POSITION_NUM_9 && playerPos.z <= POSITION_NUM_10)
					{
						CFade::SetFade(CScene::MODE::MODE_GAME);
					}
				}

			}

			pObj = pNext;

		}
	}
	// �e�N�X�`����\��
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
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

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
// �`�揈��
//====================================
void CTitleSecond::Draw()
{

}
//======================================
// �^�C�g���̐���
//======================================
CTitleSecond* CTitleSecond::Create()
{
	CTitleSecond* pTitle2 = new CTitleSecond();
	pTitle2->Init();

	return pTitle2;
}
//===========================================
//���f���t�@�C���̓ǂݍ���(�^�C�g���p)
//===========================================
void CTitleSecond::SetTitle_File()
{
	int nCnt = 0;
	char cFileModel[MAX_CHAR];//���f���̃p�X�̒���
	int nSaveModel = 0;
	int nCntModel = 0;  // �ǂݍ��񂾃��f���t�@�C���̃J�E���g�� MEMO �ϐ���1�Ŋ��������Ȃ��I
	//int nLoadData;

	//�t�@�C�����J��
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
			D3DXVECTOR3 pos, rot, move1, move2, movey1, movey2 = { 0.0f,0.0f,0.f };
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
					CBlockX* pBlock = CBlockX::Create(pos, rot, pMesh, pBuffMat, dwNumMat, move1, move2, movey1, movey2, fSpeed, fSpeed1); //�u���b�N�̃��b�V�������l��;
					CreateSaveObject(pBlock);
					pBlock->SizeVtx();
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
//=============================================
// �^�C�g���Ō�����X�e�[�W
void CTitle::SetModel_File_Title()
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

//====================================
// �ۑ����Ă����R���X�g���N�^
//====================================
CTitle::CTitleSaveObject::CTitleSaveObject(CObject* pObject) :
	CSaveObject(pObject)
{
}
//====================================
// �ۑ����Ă����f�X�g���N�^
//====================================
CTitle::CTitleSaveObject::~CTitleSaveObject()
{
}
//====================================
// �ۑ����Ă��������ݒ�
//====================================
HRESULT CTitle::CTitleSaveObject::Init()
{
	return S_OK;
}
//====================================
// �ۑ����Ă����I������
//====================================
void CTitle::CTitleSaveObject::Uninit()
{
}
//====================================
// �ۑ����Ă����X�V����
//====================================
void CTitle::CTitleSaveObject::Update()
{
}
//====================================
// �ۑ����Ă����`�揈��
//====================================
void CTitle::CTitleSaveObject::Draw()
{
}
//====================================
// �ۑ����Ă����R���X�g���N�^
//====================================
CTitleSecond::CTitleSecondSaveObject::CTitleSecondSaveObject(CObject* pObject) :
	CSaveObject(pObject)
{
}
//====================================
// �ۑ����Ă����f�X�g���N�^
//====================================
CTitleSecond::CTitleSecondSaveObject::~CTitleSecondSaveObject()
{
}
//====================================
// �ۑ����Ă��������ݒ�
//====================================
HRESULT CTitleSecond::CTitleSecondSaveObject::Init()
{
	return S_OK;
}
//====================================
// �ۑ����Ă����I���ݒ�
//====================================
void CTitleSecond::CTitleSecondSaveObject::Uninit()
{

}
//====================================
// �ۑ����Ă����X�V����
//====================================
void CTitleSecond::CTitleSecondSaveObject::Update()
{
}
//====================================
// �ۑ����Ă����`�揈��
//====================================
void CTitleSecond::CTitleSecondSaveObject::Draw()
{
}
