//=================================
// 
// �{�X��w�i�N���X�@background.h
//outher kida ibuki 
// 
//==================================
#include "background.h"   // �o�b�N�O���E���h
#include "manager.h"        // �}�l�[�W���[

// �ÓI�����o�ϐ�������
LPDIRECT3DTEXTURE9 CBackGround::m_pTextureTemp = {};

//===============================
// �R���X�g���N�^
//===============================
CBackGround::CBackGround()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };

}
//===============================
// �f�X�g���N�^
//===============================
CBackGround::~CBackGround()
{
}
//===============================
// �����ݒ�
//===============================
HRESULT CBackGround::Init()
{
	SetType(CObject::TYPE::BG);
	CObject3D::Init();
	SetTexUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	SetField(100.0f, 6000.0f);
	SetUVmove(D3DXVECTOR2(0.0f, 0.003f));

	return S_OK;
}
//===============================
// �I������
//===============================
void CBackGround::Uninit()
{
	CObject3D::Uninit();
}
//===============================
// �X�V����
//===============================
void CBackGround::Update()
{
	CObject3D::Update();
}
//===============================
// �`�揈��
//===============================
void CBackGround::Draw()
{
	CObject3D::Draw();
}
//===============================
// ��������
//===============================
CBackGround* CBackGround::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBackGround* pBack = new CBackGround();
	pBack->Init();
	pBack->SetPos(pos);
	pBack->SetRot(rot);
	if (m_pTextureTemp != nullptr)
	{
		pBack->BindTexture(m_pTextureTemp);
	}
	return pBack;
}
//===============================
// �e�N�X�`���̃��[�h
//===============================
HRESULT CBackGround::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data/TEXTURE/anim001.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//===============================
// �e�N�X�`���̃A�����[�h
//===============================
void CBackGround::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
