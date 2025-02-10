//=================================
// 
//���C�g�N���X�@�@light.cpp
//outher kida ibuki 
// 
//==================================
#include "light.h"   // ���C�g
#include "manager.h"  // �}�l�[�W���[

//==============================
//�R���X�g���N�^
//==============================
CLight::CLight()
{
	//���C�g�����N���A����
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

}
//==============================
//�f�X�g���N�^
//==============================
CLight::~CLight()
{
}
//==============================
//�����ݒ�
//==============================
HRESULT CLight::Init()
{
#if 1
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pManager->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;		//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCntLight)
		{
		case 0:
			vecDir = VEC_DIR;
			break;
		case 1:
			vecDir = VEC_DIR1;
			break;
		case 2:
			vecDir = VEC_DIR2;
			break;
		}
		//���C�g�̕�����ݒ�
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCntLight].Direction = vecDir;

		//���C�g�̐ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

#endif
}
//==============================
//�I������
//==============================
void CLight::Uninit()
{
}
//==============================
//�X�V����
//==============================
void CLight::Update()
{
}
