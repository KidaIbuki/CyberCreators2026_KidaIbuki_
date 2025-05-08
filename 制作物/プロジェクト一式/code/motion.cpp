//===========================================
// 
// ���[�V����[motion.cpp]
// Auther:UedaKou  �V�F�[�_�[���� KidaIbuki
// 
//===========================================
#include "motion.h"
#include <fstream>
#include <iostream>
#include "pch.h"
#include "manager.h"

//============================================
// �R���X�g���N�^(�p�[�c�f�[�^)
//============================================
CPartsData::CPartsData()
{
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//============================================
// �f�X�g��(�p�[�c�f�[�^)
//============================================
CPartsData::~CPartsData()
{
}

//============================================
// �R���X�g���N�^(�L�[�t���[��)
//============================================
CKye::CKye()
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			m_pParts[nCntParts] = nullptr;
		}
	}
	m_nFrame = 0;
}
//============================================
// �f�X�g��(�L�[�t���[��)
//============================================
CKye::~CKye()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		delete m_pParts[nCnt];
	}
}
//============================================
// ����
//============================================
CPartsData* CKye::creatPartsData()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_pParts[nCnt] == nullptr)
		{
			m_pParts[nCnt] = new CPartsData;
			return m_pParts[nCnt];
		}
	}
	return 0;
}

//============================================
// �R���X�g���N�^
//============================================
CMotion::CMotion()
{
	for (int nCntkye = 0; nCntkye < MAX_KYE; nCntkye++)
	{
		m_pKye[nCntkye] = nullptr;
	}
	m_nNumKye = 0;
	m_bLoop = 0;
}
//============================================
// �f�X�g��
//============================================
CMotion::~CMotion()
{
	for (int nCnt = 0; nCnt < MAX_KYE; nCnt++)
	{
		if (m_pKye[nCnt] != nullptr)
		{
			delete m_pKye[nCnt];
		}
	}
}
//============================================
// �L�[�t���[������
//============================================
void CMotion::creatKye()
{
	for (int nCntKye = 0; nCntKye < m_nNumKye; nCntKye++)
	{
		if (m_pKye[nCntKye] == nullptr)
		{
			m_pKye[nCntKye] = new CKye;
			return;
		}
	}
}


//============================================
// �R���X�g(���݃��[�V����)
//============================================
CNowMotion::CNowMotion()
{
	m_nCntMotion = 0;
	m_nCntKye = 0;
	m_nCntFrame = 0;
}
//============================================
// �f�X�g��(���݃��[�V����)
//============================================
CNowMotion::~CNowMotion()
{
}

//============================================
// �R���X�g���N�^(�p�[�c)
//============================================
CParts::CParts()
{
	// ��{�ʒu
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.siz = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// �ǉ��ʒu
	m_xOffset.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ����
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;

	m_bDisplay = 0;		// �\�����邩�ǂ���

	m_pNowMotion = new CNowMotion;

}
CParts::CParts(int nPriority) : CObjectX(nPriority)
{
	// ��{�ʒu
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.siz = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// �ǉ��ʒu
	m_xOffset.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ����
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;	// �e

	//m_nIndex = 0;		// �p�[�c���// 
	m_bDisplay = 0;		// �\�����邩�ǂ���

	m_pNowMotion = new CNowMotion;

}
//============================================
// �f�X�g��(�p�[�c)
//============================================
CParts::~CParts()
{
	delete m_pNowMotion;
}
//============================================
// ������(�p�[�c)
//============================================
HRESULT CParts::Init()
{
	SetNormalUpdate(false);
	CObjectX::Init();

	return S_OK;
}
//============================================
// �I��(�p�[�c)
//============================================
void CParts::Uninit()
{
	UninitEffect();  // �G�t�F�N�g�̔j��
	CObjectX::Uninit();
}
//============================================
// �X�V(�p�[�c)
//============================================
void CParts::Update()
{
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();
	UpdateEffect(pDevice);  // �V�F�[�_�[�̍X�V

	// ���������Z
	m_xOffset.pos += m_xMove.pos;
	m_xOffset.rot += m_xMove.rot;
	m_xOffset.siz += m_xMove.siz;
	// ���Z�����v�Z
	D3DXVECTOR3 pos, rot, siz;
	pos = m_xOffset.pos + m_xBasic.pos;
	rot = m_xOffset.rot + m_xBasic.rot;
	siz = m_xOffset.siz + m_xBasic.siz;
	// �v�Z���𔽉f
	CObjectX::SetPos(pos);			//�e�I�u�W�F�N�g�̈ʒu�ݒ�
	CObjectX::SetRot(rot);
	CObjectX::SetSize(siz);
	//CObjectX::Update();

}
//============================================
// �`��(�p�[�c)
//============================================
void CParts::Draw()
{
#if 0
	CObjectX::Draw();
#else
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld, mtxParent;	// �v�Z�p�}�g���N�X	
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	//CModelX* pModel = CModelX::GetModel(GetID());

	D3DXVECTOR3 pos = CObjectX::GetPos();			//�ʒu�̎擾
	D3DXVECTOR3 rot = CObjectX::GetRot();
	D3DXVECTOR3 size = CObjectX::GetSize();	//�T�C�Y�̎擾


	mtxWorld = GetWorldMatrix();

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	mtxRot = m_mtxParent;

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	SetWorldMatrix(mtxWorld);

	DrawEffect(pDevice);   // �V�F�[�_�[�̕`��

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A���T�C�Y���J��Ԃ�
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �F
		//pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
		//pMat[nCntMat].MatD3D.Diffuse.a = 0.1f;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, pModel->GetTexture(nCntMat));
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

#endif // 0
}
//=======================================
// �V�F�[�_�[�̓ǂݍ���
//=======================================
bool CParts::LoadEffect(LPDIRECT3DDEVICE9 device, const char* fxFile)
{
	m_fxFilePath = fxFile; // �p�X�ۑ�

	LPD3DXBUFFER pErr = nullptr;
#ifdef _DEBUG
	// �f�o�b�N��
	HRESULT hr = D3DXCreateEffectFromFileA(
		device, fxFile, nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &m_pEffect, &pErr);
#else	
	// �����[�X��
	HRESULT hr = D3DXCreateEffectFromFileA(
		device, fxFile, nullptr, nullptr, D3DXSHADER_OPTIMIZATION_LEVEL3, nullptr, &m_pEffect, &pErr);
#endif	
	if (FAILED(hr))
	{
		if (pErr)
		{
			MessageBoxA(nullptr, (char*)pErr->GetBufferPointer(), "FX Compile Error", MB_OK);
			pErr->Release();
		}
		return false;
	}
	// �g�D�[���}�b�v�ǂݍ���
	if (FAILED(D3DXCreateTextureFromFileA(device, "data/TEXTURE/ToonMap.png", &m_pToonMap)))
	{
		MessageBoxA(nullptr, "ToonMap.png �̓ǂݍ��݂Ɏ��s���܂���", "Error", MB_OK);
		return false;
	}

	return true;
}
//=======================================
// �G�t�F�N�g�̔j��
//=======================================
void CParts::UninitEffect()
{
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
	if (m_pToonMap)
	{
		m_pToonMap->Release();
		m_pToonMap = nullptr;
	}


}
//=======================================
// �V�F�[�_�[�̍X�V
//=======================================
void CParts::UpdateEffect(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX world, view, proj, wvp;
	world = GetWorldMatrix();

	// ���[���h�s��F��]�Ȃǉ�����i����ɍ��j
	D3DXMatrixRotationY(&world, timeGetTime() / 1000.0f);

	// �r���[�s��
	D3DXVECTOR3 eye(0, 2, -5), at(0, 0, 0), up(0, 1, 0);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	// �ˉe�s��
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4, 800.0f / 600.0f, 0.1f, 100.0f);

	// ���[���h�r���[�ˉe����
	wvp = world * view * proj;

	// �V�F�[�_�֐ݒ�
	m_pEffect->SetMatrix("World", &world);
	m_pEffect->SetMatrix("View", &view);
	m_pEffect->SetMatrix("Projection", &proj);
	m_pEffect->SetMatrix("WorldViewProj", &wvp);

	// �@���ϊ��p�̋t�]�u�s����쐬
	D3DXMATRIX worldInvTrans;
	D3DXMatrixInverse(&worldInvTrans, NULL, &world);
	D3DXMatrixTranspose(&worldInvTrans, &worldInvTrans);
	m_pEffect->SetMatrix("gWorldInverseTranspose", &worldInvTrans);

}
//=======================================
// �V�F�[�_�[�̕`��
//=======================================
void CParts::DrawEffect(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX view, proj, wvp;
	D3DXMATRIX mtxWorld = GetWorldMatrix();
	D3DXMATRIX matWorldNoScale, matWorldInvTrans;

	device->GetTransform(D3DTS_VIEW, &view);
	device->GetTransform(D3DTS_PROJECTION, &proj);
	wvp = mtxWorld * view * proj;

	// �G�t�F�N�g�ɕϐ���n��(����4�̈ʒu��ς���Ƃ��������Ȃ��)
	m_pEffect->SetMatrix("World", &mtxWorld);
	m_pEffect->SetMatrix("View", &view);
	m_pEffect->SetMatrix("Projection", &proj);
	m_pEffect->SetMatrix("WorldViewProj", &wvp);

	// �G�t�F�N�g�ݒ�p�X�P�[���E��]�E���s�ړ�
	D3DXVECTOR3 scale, translation;
	D3DXQUATERNION rotation;

	// ���f���s��iWorld�j
	D3DXMatrixIdentity(&mtxWorld); // ��]�E�ړ�������

	D3DXVECTOR3 eye(0, 2, -5), at(0, 0, 0), up(0, 1, 0);

	// �r���[�E�v���W�F�N�V�����s��i�Œ� or �J�������琶���j
	D3DXMatrixLookAtLH(&view,
		&eye,  // Eye
		&at,   // LookAt
		&up);  // Up

	// �ˉe�s��
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4, 640.0f / 480.0f, 1.0f, 100.0f);

	D3DXVECTOR3 Scaling = D3DXVECTOR3(1, 1, 1);  // �X�P�[��

	// �@���ϊ��p�FWorld�̃X�P�[�����O�����O���ċt�]�u�s����쐬
	D3DXMatrixInverse(&matWorldInvTrans, NULL, &mtxWorld);
	D3DXMatrixTranspose(&matWorldInvTrans, &matWorldInvTrans);

	m_pEffect->SetMatrix("gWorldInverseTranspose", &matWorldInvTrans);  // ���O�����X�P�[�����O���G�t�F�N�g�ɓ����

	UINT numPasses = 0;

	// --- �A�E�g���C���`��i��Ɂj ---
	m_pEffect->SetTechnique("Outline");
	m_pEffect->Begin(&numPasses, 0);
	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		for (int n = 0; n < m_dwNumMat; ++n)
		{
			m_pEffect->CommitChanges();
			m_pMesh->DrawSubset(n);
		}
		m_pEffect->EndPass();
	}
	m_pEffect->End();

	// --- �g�D�[���{�̕`��i��Ɂj ---
	m_pEffect->SetTechnique("ToonTechnique");
	m_pEffect->Begin(&numPasses, 0);
	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		for (int n = 0; n < m_dwNumMat; ++n)
		{
			m_pEffect->SetTexture("DiffuseTexture", m_pToonMap);

			m_pEffect->CommitChanges();
			m_pMesh->DrawSubset(n);
		}
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}
//=======================================
// ���[�V�����̃Z�b�g
//=======================================
void CParts::SetMotion(int nMotion)
{
	m_pNowMotion->SetMotion(nMotion);
	m_pNowMotion->SetKye(0);
	m_pNowMotion->SetFrame(0);
}
//=======================================
// �����̃Z�b�g
//=======================================
void CParts::SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame)
{
	X x;
	x.pos = pos - m_xOffset.pos;
	x.rot = rot - m_xOffset.rot;
	x.siz = siz - m_xOffset.siz;


	if (x.rot.x > D3DX_PI)
	{
		x.rot.x -= TAU;
	}
	else if (x.rot.x < -D3DX_PI)
	{
		x.rot.x += TAU;
	}

	if (x.rot.y > D3DX_PI)
	{
		x.rot.y -= TAU;
	}
	else if (x.rot.y < -D3DX_PI)
	{
		x.rot.y += TAU;
	}

	if (x.rot.z > D3DX_PI)
	{
		x.rot.z -= TAU;
	}
	else if (x.rot.z < -D3DX_PI)
	{
		x.rot.z += TAU;
	}

	m_xMove.pos.x = x.pos.x / (float)nFrame;
	m_xMove.pos.y = x.pos.y / (float)nFrame;
	m_xMove.pos.z = x.pos.z / (float)nFrame;
	m_xMove.rot.x = x.rot.x / (float)nFrame;
	m_xMove.rot.y = x.rot.y / (float)nFrame;
	m_xMove.rot.z = x.rot.z / (float)nFrame;
	m_xMove.siz.x = x.siz.x / (float)nFrame;
	m_xMove.siz.y = x.siz.y / (float)nFrame;
	m_xMove.siz.z = x.siz.z / (float)nFrame;
	m_pNowMotion->SetFrame(nFrame);
}
//============================================
// �R���X�g���N�^
//============================================
CObjectMotion::CObjectMotion()
{
	// ���f��
	m_nModel = 0;

	// ���[�V�����f�[�^
	m_nNumMotion = 0;
	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_pMotion[i] = nullptr;
	}

	// �p�[�c
	m_nParts = 0;
	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_pParts[i] = nullptr;
	}

	//	���݃��[�V����
	m_nNextMotion = 0;


	m_xold = {};
}

//============================================
// �f�X�g��
//============================================
CObjectMotion::~CObjectMotion()
{
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (m_pMotion[nCnt])
		{
			delete m_pMotion[nCnt];
		}
	}
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{

		if (m_pParts[nCnt] != nullptr)
		{
			m_pParts[nCnt]->DeathFlag();
			m_pParts[nCnt] = nullptr;
		}
	}

}
//============================================
// ������
//============================================
HRESULT CObjectMotion::Init()
{
	for (int nCnt = 0; nCnt < m_nNumMotion; nCnt++)
	{
		CPartsData* TargetMotion = m_pMotion[GetNextMotion()]->GetKye(0)->GetPartsData(nCnt);	// �ڕW���[�V�����擾
		// ������ݒ�
		m_pParts[nCnt]->SetAddX(
			TargetMotion->GetPosTarget(),	// �ʒu
			TargetMotion->GetRotTarget(),	// ����
			TargetMotion->GetSizTarget());	// �傫��
		m_pParts[nCnt]->GetNowMotion()->SetFrame(1);
		m_pParts[nCnt]->SetMoveX(
			TargetMotion->GetPosTarget(),	// �ʒu
			TargetMotion->GetRotTarget(),	// ����
			TargetMotion->GetSizTarget(),
			m_pMotion[GetNextMotion()]->GetKye(0)->GetFrame());	// �傫��
	}

	return S_OK;
}
//============================================
// �I������
//============================================
void CObjectMotion::Uninit()
{
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		m_pParts[nCntParts]->Uninit();
	}
	CObject::DeathFlag();
}
//============================================
// �X�V����
//============================================
void CObjectMotion::Update()
{
	D3DXMATRIX mtxRot0, mtxRot1, mtxTrans;	// �v�Z�p�}�g���N�X

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot1, m_x.rot.y, m_x.rot.x, m_x.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot1);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_x.pos.x, m_x.pos.y, m_x.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[�V����
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		CNowMotion* pNowMotion = m_pParts[nCntParts]->GetNowMotion();
		CMotion* pTargetMotion0 = m_pMotion[pNowMotion->GetMotion()];

		pNowMotion->AddFrame(-1);	// �t���[�����P�i�߂�
		int nNowFrame = pNowMotion->GetFrame();
		if (nNowFrame <= 0)
		{// �L�[�̃t���[�����o�߂�����
			pNowMotion->AddKye(1);	// kye���P�i�߂�
			int nNowKye = pNowMotion->GetKye(),
				nTarget = pTargetMotion0->GetNumKye();
			if (nNowKye >= nTarget)
			{// ���[�V�����̃L�[���o�߂�����
				pNowMotion->SetKye(0);
				bool bLoop = pTargetMotion0->GetLoop();
				if (bLoop == false)
				{// ���[�v���Ȃ��Ȃ�
					pNowMotion->SetMotion(GetNextMotion());
				}
			}
			CPartsData* pTargetMotion1;	// ���[�V�����i�[�p
			pTargetMotion1 = m_pMotion[pNowMotion->GetMotion()]->GetKye(pNowMotion->GetKye())->GetPartsData(nCntParts);	// �ڕW���[�V�����擾
			// ������ݒ�
			m_pParts[nCntParts]->SetMoveX(
				pTargetMotion1->GetPosTarget(),	// �ʒu
				pTargetMotion1->GetRotTarget(),	// ����
				pTargetMotion1->GetSizTarget(),	// �傫��
				m_pMotion[pNowMotion->GetMotion()]->GetKye(0)->GetFrame());
		}
		m_pParts[nCntParts]->Update();
	}
}
//============================================
// �`�揈��
//============================================
void CObjectMotion::Draw()
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			int ParentID = m_pParts[nCntParts]->GetParentID();	// �eID�i�[�p
			// �e�����Ȃ�������
			if (ParentID == -1)
			{
				m_pParts[nCntParts]->SetParentMtx(m_mtxWorld);
			}
			// �e��������
			else
			{
				m_pParts[nCntParts]->SetParentMtx(m_pParts[ParentID]->GetWorldMatrix());
			}

			m_pParts[nCntParts]->Draw();
		}
	}
}

CObjectMotion* CObjectMotion::creat(const char* FileName)
{
	CObjectMotion* p = new CObjectMotion();

	p->Init();
	p->Load(FileName);

	return p;
}

CObjectMotion* CObjectMotion::creat(string FileName)
{
	CObjectMotion* p = creat(FileName.c_str());
	return p;
}

//============================================
// �ǂݍ��ݏ���
//============================================
bool CObjectMotion::Load(const char* aFileName)
{

	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	ifstream file(aFileName);  // �ǂݍ��ރt�@�C���̃p�X���w��
	if (file.fail()) {
		cerr << "�t�@�C�����J���܂���ł���\n";
		return false;
	}
	string str0, str1, str2 , str3;	// ������i�[�p
	string skip;			// �X�L�b�v�p�i�[
	string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

	int nCntModel = 0;		// �ǂݍ��񂾃��f����
	int nCntPartsset0 = 0;	// �ǂݍ��񂾃p�[�c��(�x�[�X)
	int nCntPartsset1 = 0;	// �ǂݍ��񂾃p�[�c��
	int nCntMotion = 0;		// �ǂݍ��񂾃��[�V������
	int nCntKye = 0;		// �ǂݍ��񂾃L�[��


	// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
	while (file >> str0)
	{
		// �R�����g�A�E�g
		if (str0[0] == '#')
		{
			getline(file, skip);	// ��s�X�L�b�v
		}
		// ���f����
		else if (str0.compare("NUM_MODEL") == 0)
		{
			file >> skip;	// �ꕶ�X�L�b�v
			file >> str1;	// ���f�������擾
			m_nModel = atoi(str1.c_str());
			getline(file, skip);	// ��s�X�L�b�v
		}
		// ���f���t�@�C�����O
		else if (str0.compare("MODEL_FILENAME") == 0 &&
			nCntModel < m_nModel &&
			m_nModel > 0)
		{
			file >> skip;	// �ꕶ�X�L�b�v
			file >> str1;	// ���f�������擾
			aModelFile[nCntModel] = str1;

			nCntModel++;
			getline(file, skip);	// ��s�X�L�b�v
		}
		// �L�����N�^�[���
		else if (str0.compare("CHARACTERSET") == 0)
		{
			while (file >> str1 &&
				str1.compare("END_CHARACTERSET") != 0)
			{
				// �p�[�c��
						// �R�����g�A�E�g
				if (str1[0] == '#')
				{
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("NUM_PARTS") == 0)
				{
					file >> skip;	// �ꕶ�X�L�b�v
					file >> str2;	// ���f�������擾
					m_nParts = atoi(str2.c_str());
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("MOVE") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("JUMP") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("RADIUS") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("HEIGHT") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				// �p�[�c�f�[�^
				else if (str1.compare("PARTSSET") == 0)
				{
					if (nCntPartsset0 < MAX_PARTS)
					{
						m_pParts[nCntPartsset0] = new CParts(4);
						m_pParts[nCntPartsset0]->Init();
						//m_pParts[nCntPartsset0]->SetID(nCntPartsset0);
						while (file >> str2 &&
							str2.compare("END_PARTSSET") != 0)
						{
							// �R�����g�A�E�g
							if (str2[0] == '#')
							{
								getline(file, skip);	// ��s�X�L�b�v
							}
							// ���f�������擾
							else if (str2.compare("INDEX") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾

								//m_pParts[nCntPartsset0]->CObjectX::SetModel(aModelFile[atoi(str3.c_str())].c_str());
								m_pParts[nCntPartsset0]->CObjectX::LoadXModel(pDevice, aModelFile[atoi(str3.c_str())].c_str());
								m_pParts[nCntPartsset0]->LoadEffect(pDevice, "shader/ToonShader.fx");


								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("PARENT") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								int nParentID = atoi(str3.c_str());
								m_pParts[nCntPartsset0]->SetParentID(nParentID);

								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("POS") == 0)
							{
								D3DXVECTOR3 pos;// pos �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								pos.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								pos.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								pos.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicPos(pos);
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("ROT") == 0)
							{
								D3DXVECTOR3 rot;// rot �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								rot.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								rot.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								rot.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicRot(rot);
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("SIZ") == 0)
							{
								D3DXVECTOR3 siz;// siz �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								siz.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								siz.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								siz.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicSiz(siz);
								getline(file, skip);	// ��s�X�L�b�v
							}
						}
						nCntPartsset0++;
					}
				}
			}
		}
		else if (str0.compare("MOTIONSET") == 0)
		{
			if (nCntMotion < MAX_MOTION)
			{
				creatMotion();
				while (file >> str1 &&
					str1.compare("END_MOTIONSET") != 0)
				{
					// �R�����g�A�E�g
					if (str1[0] == '#')
					{
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("LOOP") == 0)
					{
						file >> skip;	// �ꕶ�X�L�b�v
						file >> str2;	// ���f�������擾
						if (str2.compare("0") == 0)
						{ m_pMotion[nCntMotion]->SetLoop(false); }
						else
						{ m_pMotion[nCntMotion]->SetLoop(true); }
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("NUM_KEY") == 0)
					{
						file >> skip;	// �ꕶ�X�L�b�v
						file >> str2;	// ���f�������擾
						m_pMotion[nCntMotion]->SetNumKye(atoi(str2.c_str()));
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("KEYSET") == 0)
					{
						m_pMotion[nCntMotion]->creatKye();
						while (file >> str2 &&
							str2.compare("END_KEYSET") != 0)
						{
							// �R�����g�A�E�g
							if (str2[0] == '#')
							{
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("FRAME") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// �t���[�������擾
								m_pMotion[nCntMotion]->GetKye(nCntKye)->SetFrame(atoi(str3.c_str()));
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("KEY") == 0)
							{
								m_pMotion[nCntMotion]->GetKye(nCntKye)->creatPartsData();
								while (file >> str3 &&
									str3.compare("END_KEY") != 0)
								{
									if (str3[0] == '#')
									{
										getline(file, skip);	// ��s�X�L�b�v
									}
									else if (str3.compare("POS") == 0)
									{
										D3DXVECTOR3 pos;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										pos.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										pos.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										pos.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetPosTarget(pos);
									}
									else if (str3.compare("ROT") == 0)
									{
										D3DXVECTOR3 rot;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										rot.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										rot.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										rot.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetRotTarget(rot);
									}
									else if (str3.compare("SIZ") == 0)
									{
										D3DXVECTOR3 siz;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										siz.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										siz.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										siz.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetSizTarget(siz);
									}
								}
								nCntPartsset1++;
							}
						}
						nCntKye++;
						nCntPartsset1 = 0;
					}
				}
				nCntMotion++;
				nCntKye = 0;
			}
		}
	}
	// �t�@�C�������
	file.close();
	return true;
}
void CObjectMotion::SetMotion(int nMotion)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);

		if (pParts->GetNowMotion()->GetMotion() != nMotion)
		{
			pParts->SetMotion(nMotion);

			CPartsData* pTarget = GetMotion(nMotion)->GetKye(0)->GetPartsData(nCnt);
			pParts->SetMoveX(
				pTarget->GetPosTarget(),	// �ʒu
				pTarget->GetRotTarget(),	// ����
				pTarget->GetSizTarget(),
				10);	// �傫��
		}
	}
}
//============================================
// ���[�V��������
//============================================
void CObjectMotion::creatMotion()
{
	for (int nCntMotion = 0; nCntMotion < MAX_KYE; nCntMotion++)
	{
		if (m_pMotion[nCntMotion] == nullptr)
		{
			m_pMotion[nCntMotion] = new CMotion;
			return;
		}
	}
}