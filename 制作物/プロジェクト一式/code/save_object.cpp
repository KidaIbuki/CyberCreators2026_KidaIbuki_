//=================================
// 
// �I�u�W�F�N�g�ۑ� �N���X�@save_object.cpp
//outher kida ibuki 
// 
//==================================
#include "save_object.h"  // �Z�[�u�I�u�W�F�N�g

//===============================
// �R���X�g���N�^
//===============================
CSaveObject::CSaveObject(CObject* pObject)
{
	m_pObject = pObject;
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
//===============================
// �f�X�g���N�^
//===============================
CSaveObject::~CSaveObject()
{
	if (m_pObject != nullptr)
	{
		m_pObject->DeathFlag();
		m_pObject = nullptr;
	}
}
//===============================
// �����ݒ�
//===============================
HRESULT CSaveObject::Init()
{
	if (FAILED(Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//===============================
// �I������
//===============================
void CSaveObject::Uninit()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
	}
}
//===============================
// �X�V����
//===============================
void CSaveObject::Update()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Update();
	}
}
//===============================
// �`�揈��
//===============================
void CSaveObject::Draw()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Draw();
	}
}
//===============================
// ��������
//===============================
CSaveObject* CSaveObject::Create(CSaveObject* pTop, CSaveObject* pCur)
{
	if (pTop == nullptr)
	{
		pTop = this;
	}
	if (pCur == nullptr)
	{
		pCur = this;
	}
	else
	{
		this->m_pPrev = pCur;
		pCur->m_pNext = this;
		pCur = this;
	}
	return this;
}
