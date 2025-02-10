//=================================
// 
// �t�H�O�N���X�@�@fog.cpp
//outher kida ibuki 
// 
//==================================
#include "fog.h"
#include "manager.h"

#define NUM (1)   // 0->�͈͎w��t�H�O:  1->���x�w��t�H�O
//==============================================
// �R���X�g���N�^
//==============================================
CFog::CFog()
{
	m_fFogDensity = 0.0f;
	m_fFogStartPos = 0.0f;
	m_fFogEndPos = 0.0f;
}
//==============================================
// �f�X�g���N�^
//==============================================
CFog::~CFog()
{
}
//==============================================
// �����ݒ�
//==============================================
HRESULT CFog::Init()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

#if NUM
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);  // �t�H�O���[�h�̎w��(���ꂼ��ɍ��������[�h���w��)
#else
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);  // �t�H�O���[�h�̎w��(���ꂼ��ɍ��������[�h���w��)
#endif
	// �t�H�O�̗L��
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	// �t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�t�H�O�p�����[�^�[��ݒ�

#if NUM  // 0��1�Ńt�H�O�ݒ��ς����(�ς�����t�H�O���[�h���ς���)

	m_fFogDensity = 0.0005f;   // ���x�ݒ�

	// D3DFOG_EXP(���x�w��̏ꍇ)
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));
#else
	// D3DFOG_LINEAR(�͈͎w��̏ꍇ)
	m_fFogStartPos = 100.0f;
	m_fFogEndPos = 1000.0f;

	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));
#endif

	return S_OK;
}
//==============================================
// �I������
//==============================================
void CFog::Uninit()
{
}
//==============================================
// �X�V����
//==============================================
void CFog::Update()
{
}
//==============================================
// �`�揈��
//==============================================
void CFog::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

		// �A���t�@�u�����f�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �e�N�X�`���A���t�@�ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

}
