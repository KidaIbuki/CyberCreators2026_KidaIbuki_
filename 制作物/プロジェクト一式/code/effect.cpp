//=================================
// 
// �G�t�F�N�g�N���X�@effect.cpp
//Auther kida ibuki 
// 
//==================================
#include "manager.h"    // �}�l�[�W���[
#include "effect.h"   // �G�t�F�N�g
//====================================
// �R���X�g���N�^
//====================================
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_nType = 0;
	m_bUse = false; //�g���ĂȂ���Ԃ�
	m_bStartTexture = false; //�e�N�X�`�������ʒu��ݒ�
	m_fRadius = 0.0f;
	m_Interval = 0.0f;
	m_EffectCnt = 0;
	m_fSplit = 0.0f;
	m_fAlpha = 0.0f;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}
//====================================
// �f�X�g���N�^
//====================================
CEffect::~CEffect()
{
}
//====================================
// �����ݒ�
//====================================
HRESULT CEffect::Init()
{
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//====================================
// �I������
//====================================
void CEffect::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}
//====================================
// �X�V����
//====================================
void CEffect::Update()
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bUse == true)
	{//�G�t�F�N�g�g���Ă�

		//�e�N�X�`���̏����ʒu��ݒ�
		if (m_bStartTexture == false)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f / m_fSplit, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / m_fSplit, 1.0f);
			m_bStartTexture = true;
		}

		//�e�N�X�`���̉�����������P�R�}�i�ޗʂ��v�Z
		m_Interval = INTERVAL_EFFECT / m_fSplit;

		//�G�t�F�N�g�J�E���g��i�߂�
		m_EffectCnt++;

		if (m_EffectCnt >= m_Interval)
		{
			pVtx[0].tex.x += 1.0f / m_fSplit;
			pVtx[1].tex.x += 1.0f / m_fSplit;
			pVtx[2].tex.x += 1.0f / m_fSplit;
			pVtx[3].tex.x += 1.0f / m_fSplit;

			m_EffectCnt = 0;
		}

		m_col.a -= m_fAlpha;

		//���_�̍��W�𔼌a�ɐݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fRadius, m_fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fRadius, m_fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fRadius, -m_fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fRadius, -m_fRadius, 0.0f);

		//���_�J���[
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_nLife--;

		//�O�Ղ��������}�����ꂽ
		if (m_nLife <= 0)
		{
			m_bUse = false;
		}
	}
	if (m_bUse == false)
	{
		DeathFlag();
	}
	m_pVtxBuff->Unlock();

}
//====================================
// �`�揈��
//====================================
void CEffect::Draw()
{
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X�擾�p

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	if (m_bUse == true)
	{
		//���C�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ����܂��傤
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//���C�g��L���ɖ߂�
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B�������ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//====================================
// ��������
//====================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nType, float fRadius, float fSplit, float fAlpha, int nLife)
{
	CEffect* pEffect = new CEffect();
	pEffect->Init();

	if (pEffect->m_bUse == false)
	{
		pEffect->m_pos = pos;    // �ǐՂ�����������
		pEffect->m_col = col;    // �F
		pEffect->m_nType = nType;   // ���
		pEffect->m_fRadius = fRadius;  // �傫��
		pEffect->m_fSplit = fSplit;    // ������
		pEffect->m_fAlpha = fAlpha;    // �����x(�ǂꂭ�炢�����ɂ��邩)
		pEffect->m_nLife = nLife;      // ����
		pEffect->m_bUse = true;
	}
	pEffect->SetTexture("data/TEXTURE/effect000.jpg");

	return pEffect;
}
//====================================
// �e�N�X�`���̐ݒ�
//====================================
void CEffect::SetTexture(std::string sPath)
{
	CManager* pManager = CManager::GetInstance();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);

}
