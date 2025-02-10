//==================================
// 
// �v���C���[���C�t �N���X�@life.h
//outher kida ibuki 
// 
//==================================
#include "life.h"  // ���C�t
#include "manager.h" // �}�l�[�W���[
#include "playerM.h"

float CLife::m_fTexHeight = 0;
float CLife::m_fTexWidht = 0;
int CLife::m_nFrame = 0;
int CLife::m_nLife = 0;
//=======================================
// �R���X�g���N�^
//=======================================
CLife::CLife()
{
	m_fTexHeight = 0.0f;   //�c
	m_fTexWidht = 0.1f;    //��
	m_nFrame = 3;
	m_nLife = 100;
}

//=======================================
// �f�X�g���N�^
//=======================================
CLife::~CLife()
{
}
//=======================================
// �����ݒ�
//=======================================
HRESULT CLife::Init()
{
	CObject2D::Init();
	SetType(CObject::TYPE::LIFE);
	SetSize(120.0f, 350.0f);
	//SetColor(D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f));


	return S_OK;
}
//=======================================
// �I������
//=======================================
void CLife::Uninit()
{
	CObject2D::Uninit();
}
//=======================================
// �X�V����
//=======================================
void CLife::Update()
{
	CObject2D::Update();

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexHeight, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexWidht, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fTexHeight, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexWidht, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	if (m_nLife <= 0)
	{
		CLife::DeathFlag();
	}

}
//=======================================
// �`�揈��
//=======================================
void CLife::Draw()
{
	CObject2D::Draw();
}
//=======================================
// ��������
//=======================================
CLife* CLife::Create(D3DXVECTOR2 pos)
{
	CLife* pLife = new CLife();
	pLife->Init();
	pLife->SetPos(pos.x, pos.y);
	pLife->SetTexture("data/TEXTURE/life001.png");

	return pLife;
}
//=======================================
// ���Z����
//=======================================
void CLife::SubLife(int nDamage)
{
	if (m_nFrame >= 0)  // 0��葽��������
	{
		m_nFrame--;   // �J�E���g�_�E��
	}
	if (m_nFrame <= 0)
	{ // ���W�𑝂₷

		m_fTexHeight += 0.1f;
		m_fTexWidht += 0.1f;
		m_nLife -= nDamage;  // ���C�t�����炷
		m_nFrame = 3;   // �t���[����߂�
	}
	if (m_nLife <= 0)
	{// ���C�t�������Ȃ�����
		//CFade::SetFade(CScene::MODE::MODE_GAME);
		CPlayerM::MoveFlag(false);
		CPlayerM::DeathMove(true);
	}
}
