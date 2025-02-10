//=================================
// 
// �}�l�[�W���@manager.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"  // �}�l�[�W���[
#include "object.h"   // �I�u�W�F�N�g
#include "objectX.h"  // �I�u�W�F�N�gX
#include "blockX.h"               // �u���b�N
#include "enemyX.h"               // �G�l�~�[
//=====�V�[��============
#include "title.h"     // �^�C�g��
//======================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=======================================
CManager::~CManager()
{

}

//=====================================
//�����ݒ�
//=====================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == nullptr)
	{
		// �����_���[�̐��� �����_���[�͈�ԏ�I
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
		// �T�E���h�̐���
		m_pSound = new CSound();
		m_pSound->InitSound(hWnd);
	}
	if (m_pCamera == nullptr)
	{
		//�J�����̐���
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}
	if (m_pLight == nullptr)
	{
		//���C�g�̐���
		m_pLight = new CLight();
		m_pLight->Init();
	}
	if (m_pKeyboard == nullptr)
	{
		//�L�[�{�[�h�̐���
		m_pKeyboard = new CInputKeyboard();
		m_pKeyboard->Init(hInstance, hWnd);
	}
	if (m_pKeyJoypad == nullptr)
	{
		//�R���g���[���[�̐���
		m_pKeyJoypad = new CInputJoypad();
		m_pKeyJoypad->Init(hInstance, hWnd);
	}
	if (m_pKeyMouse == nullptr)
	{
		//�}�E�X�̐���
		m_pKeyMouse = new CInputMouse();
		m_pKeyMouse->Init(hInstance, hWnd);
	}
	//if (m_pFade == nullptr)
	//{
	//	//�t�F�[�h�̐���
	//	m_pFade = new CFade();
	//	m_pFade->Init();
	//}
	if (m_pScene == nullptr)
	{
		// �V�[���̐���
		m_pScene = new CTitle();
	}

	//�ŏ��̃V�[���ݒ�
	//SetMode(CScene::MODE::MODE_TITLE);
	m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//=====================================
// �I��
//=====================================
void CManager::Uninit()
{	
	// �����_���[��j������
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �t�H�O��j������
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		delete m_pFog;
		m_pFog = nullptr;
	}

	// �T�E���h��j������
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = nullptr;
	}
	//�J�����̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//���C�g�̔j��
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	// �L�[�{�[�h���͔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	// �R���g���[���[���͔j��
	if (m_pKeyJoypad != nullptr)
	{
		m_pKeyJoypad->Uninit();
		delete m_pKeyJoypad;
		m_pKeyJoypad = nullptr;
	}
	// �}�E�X���͔j��
	if (m_pKeyMouse != nullptr)
	{
		m_pKeyMouse->Uninit();
		delete m_pKeyMouse;
		m_pKeyMouse = nullptr;
	}

	//// �V�[���̔j��
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
// �X�V
//=====================================
void CManager::Update()
{
	// �V�[���̍X�V
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	// �����_���[�̍X�V
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}


	// �t�H�O�̍X�V
	if (m_pFog != nullptr)
	{
		m_pFog->Update();
	}
	// �L�[�{�[�h�̍X�V
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}
	// �R���g���[���[�̍X�V
	if (m_pKeyJoypad != nullptr)
	{
		m_pKeyJoypad->Update();
	}
	// �}�E�X�̍X�V
	if (m_pKeyMouse != nullptr)
	{
		m_pKeyMouse->Update();
	}
	// �J�����̍X�V
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	// ���C�g�̍X�V
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
//�`��
//======================================
void CManager::Draw()
{
	// �����_���[�̕`��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}

	// �t�H�O�̍X�V
	if (m_pFog != nullptr)
	{
		m_pFog->Draw();
	}

	//�V�[���̕`��
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
// �����_���[�̎擾
//=======================================
CRenderer* CManager::GetRenderer()
{
	assert(m_pRenderer != nullptr);
	return m_pRenderer;
}
//======================================
//�J�����̎擾
//=====================================
CCamera* CManager::GetCamera()
{
	assert(m_pCamera != nullptr);
	return m_pCamera;
}
//======================================
//���C�g�̎擾
//=====================================
CLight* CManager::GetLight()
{
	assert(m_pLight != nullptr);
	return m_pLight;
}
//======================================
//�L�[�{�[�h�̎擾
//=====================================
CInputKeyboard* CManager::GetKeyboard()
{
	assert(m_pKeyboard != nullptr);
	return m_pKeyboard;
}
//======================================
//�R���g���[���[�̎擾
//=====================================
CInputJoypad* CManager::GetJoypad()
{
	assert(m_pKeyJoypad != nullptr);
	return m_pKeyJoypad;
}
//======================================
//�}�E�X�̎擾
//=====================================
CInputMouse* CManager::GetMouse()
{
	assert(m_pKeyMouse != nullptr);
	return m_pKeyMouse;
}

//======================================
//�V�[���̐ݒ�
//======================================
void CManager::SetMode(CScene::MODE mode)
{
	// �V�[���̔j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	//����
	m_pScene = CScene::Create(mode);

}

//======================================
//�V�[���̎擾
//=====================================
CScene* CManager::GetScene()
{
	assert(m_pScene != nullptr);
	return m_pScene;
}

//======================================
//�t�F�[�h�̎擾
//=====================================
CFade* CManager::GetFade()
{
	assert(m_pFade != nullptr);
	return m_pFade;
}
//======================================
//�T�E���h�̎擾
//=====================================
CSound* CManager::GetSound()
{
	assert(m_pSound != nullptr);
	return m_pSound;
}
//======================================
// �t�H�O�̎擾
//=====================================
CFog* CManager::GetFog()
{
	return m_pFog;;
}
