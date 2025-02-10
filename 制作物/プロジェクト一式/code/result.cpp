//=================================
// 
// �V�[���N���X�@result.cpp
//outher kida ibuki 
// 
//==================================
#include "result.h"   // ���U���g
#include "fade.h"     // �t�F�[�h
#include "manager.h"  // �}�l�[�W���[
#include "sound.h"   // �T�E���h
//====================================
// �R���X�g���N�^
//====================================
CResult::CResult()
{
	m_nTimerCnt = 40;
}
//====================================
// �f�X�g���N�^
//====================================
CResult::~CResult()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CResult::Init()
{
	CScene::Init();
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	
	CManager* pManager = CManager::GetInstance();
	// �T�E���h�𗬂�
	pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_BGM003);


	return S_OK;
}
//====================================
// �I������
//====================================
void CResult::Uninit()
{
	CScene::Uninit();
	CManager* pManager = CManager::GetInstance();

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
void CResult::Update()
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
			CFade::SetFade(CScene::MODE::MODE_TITLE);
			m_nTimerCnt = 40;
		}
	}
}
//====================================
// �`�揈��
//====================================
void CResult::Draw()
{
	CScene::Draw();

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

			pObj->Draw();

			pObj = pNext;

		}
	}

}
//======================================
// �^�C�g���̐���
//======================================
CResult* CResult::Create()
{
	CResult* pResult = new CResult();
	pResult->Init();
	pResult->SetTexture("data/TEXTURE/resultclear.png");

	return pResult;
}

