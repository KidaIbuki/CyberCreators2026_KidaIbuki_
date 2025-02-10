//=================================
// 
// �p�[�e�B�N�� �N���X�@particle.cpp
//outher kida ibuki 
// 
//==================================
#include "explosion.h"   // ����
#include "manager.h"       // �}�l�[�W���[

const int CExplosion::LIFE = 1000;
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureTemp = {};

#if 1
//===============================
// �R���X�g���N�^
//===============================
CExplosion::CExplosion()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_bUse = false;
	m_nLife = 0;
	m_dwLifeTime = timeGetTime();

}
//===============================
// �f�X�X�g���N�^
//===============================
CExplosion::~CExplosion()
{
}
//===============================
// �����ݒ�
//===============================
HRESULT CExplosion::Init()
{
	CObject3D::Init();
	SetType(CObject::TYPE::EXPLOSION);

	SetAnim(8, 30);
	SetField(10.0f, 10.0f);

	m_dwLifeTime = timeGetTime() + LIFE;

	return S_OK;
}
//===============================
// �I������
//===============================
void CExplosion::Uninit()
{
	CObject3D::Uninit();
}
//===============================
// �X�V����
//===============================
void CExplosion::Update()
{
	CObject3D::Update();
	
	if (timeGetTime() >= m_dwLifeTime)
	{
		CExplosion::m_bDeath = true;
	}

}
//===============================
// �`�揈��
//===============================
void CExplosion::Draw()
{
	CObject3D::Draw();

}
//===============================
// ��������
//===============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion* pExplosion = new CExplosion();
	pExplosion->Init();

	pExplosion->SetPos(pos);
	pExplosion->SetRot(rot);
	if (m_pTextureTemp != nullptr)
	{
		pExplosion->BindTexture(m_pTextureTemp);
	}

	return pExplosion;
}
//=======================================
//���[�h
//=======================================
HRESULT CExplosion::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data/TEXTURE/explosion000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CExplosion::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}

#endif
