//==============================================
// 
//�I�u�W�F�N�g(x�t�@�C���̓ǂݍ���)�@objectX.cpp
//outher kida ibuki 
// 
//==============================================
#include "objectX.h"    // �I�u�W�F�N�gX
#include "manager.h"    // �}�l�[�W���[


//==================================================
//�R���X�g���N�^
//==================================================
CObjectX::CObjectX()
{
	// �ϐ��̏�����
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pVtxBuff = nullptr;				// ���_�o�b�t�@
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		m_pTexture[i] = nullptr;			// �e�N�X�`��
	}
	m_pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };		// ����
	//m_move = { 0.0f, 0.0f, 0.0f };		//�ړ���
	m_size = { 0.0f,0.0f,0.0f };
	m_nMaxVtx = { 0.0f,0.0f,0.0f };
	m_nMinVtx = { 0.0f,0.0f,0.0f };
}
CObjectX::CObjectX(int nPrioroty) :CObject(nPrioroty)
{
	// �ϐ��̏�����
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pVtxBuff = nullptr;				// ���_�o�b�t�@
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		m_pTexture[i] = nullptr;			// �e�N�X�`��
	}
	m_pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };		// ����
	//m_move = { 0.0f, 0.0f, 0.0f };		//�ړ���
	m_size = { 0.0f,0.0f,0.0f };
	m_nMaxVtx = { 0.0f,0.0f,0.0f };
	m_nMinVtx = { 0.0f,0.0f,0.0f };
}
//==================================================
//�f�X�g���N�^
//==================================================
CObjectX::~CObjectX()
{
}
//==================================================
//�����ݒ�
//==================================================
HRESULT CObjectX::Init()
{
	CManager* pManager = CManager::GetInstance();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	

	return S_OK;


}

//===============================================
//���f���̒��_�������ɃT�C�Y�̍ő�l�ŏ��l�����߂�
//===============================================
void CObjectX::SizeVtx()
{
	//**========================���b�V���̏����擾================**

	if (m_pMesh != nullptr)
	{
		//���_���̎擾
		m_nNumVtx = m_pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_bpVtxBuff);

		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			//���_���W����
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_bpVtxBuff;

			//���_���W���r���ă��f���̍ő�l�A�ŏ��l���擾
			//x�̍ő�l
			if (vtx.x > m_nMaxVtx.x)
			{
				m_nMaxVtx.x = vtx.x;
			}
			//x�̍ŏ��l
			else if (vtx.x < m_nMinVtx.x)
			{
				m_nMinVtx.x = vtx.x;
			}
			//y�̍ő�l
			if (vtx.y > m_nMaxVtx.y)
			{
				m_nMaxVtx.y = vtx.y;
			}
			//y�̍ŏ��l
			else if (vtx.y < m_nMinVtx.y)
			{
				m_nMinVtx.y = vtx.y;
			}
			//z�̍ő�l
			if (vtx.z > m_nMaxVtx.z)
			{
				m_nMaxVtx.z = vtx.z;
			}
			//z�̍ŏ��l
			else if (vtx.z < m_nMinVtx.z)
			{
				m_nMinVtx.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			m_bpVtxBuff += m_sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		m_pMesh->UnlockVertexBuffer();

		//**=========================================================**
		m_size = m_nMaxVtx - m_nMinVtx;
	}
}

//==================================================
//�I������
//==================================================
void CObjectX::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	for (int i = 0; i < MAX_TEX_X; i++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[i] != nullptr)
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

}
//==================================================
//�X�V����
//==================================================
void CObjectX::Update()
{

}
//==================================================
//�`�揈��
//==================================================
void CObjectX::Draw()
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾
	D3DXMATRIX mtxRot, mtxTrans;											// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���u���b�N�ȊO�̌�����ʒu�̔��f��
	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//==================================================================================
	// �I�u�W�F�N�g�̕`��[blockX]
	//==================================================================================
		// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//if (m_pMesh != nullptr) // ���b�V���̏ꍇ
	//{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			// ���f���̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		// �ۑ����Ă����}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	//}
	//else  //���b�V���ȊO�̏ꍇ
	//{
	//	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//	// ���_�t�H�[�}�b�g�̐ݒ�
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	// �e�N�X�`���̐ݒ�
	//	pDevice->SetTexture(0, m_pTexture);

	//	// �|���S���̕`��
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
	//		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
	//		2);				//�`�悷��v���~�e�B�u��
	//}

}
//==================================================
//�I�u�W�F�N�g�̐���(x�t�@�C����)
//==================================================
CObjectX* CObjectX::Create()
{
	CObjectX* pObjectX = new CObjectX;
	pObjectX->Init();
	return pObjectX;

}
//==================================================
//���f���̐ݒ�(�����Ƀp�X������)
//==================================================
void CObjectX::SetModel(std::string sPath)
{
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// ���f���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(sPath.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	SizeVtx();	// pMesh�̏����擾
}

//======================================
//�T�C�Y�̐ݒ�
//======================================
void CObjectX::SetSize(float fWidth, float fHeight, float fDepth)
{
	m_size = D3DXVECTOR3(fWidth, fHeight, fDepth);
}

