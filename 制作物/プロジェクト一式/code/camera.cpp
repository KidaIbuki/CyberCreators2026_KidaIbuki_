//=================================
// 
//�J�����N���X�@camera.cpp
//outher kida ibuki 
// 
//==================================
#include "camera.h"   // �J����
#include "manager.h"    // �}�l�[�W���[
#include "title.h"     // �^�C�g��
//==============================
//�R���X�g���N�^
//==============================
CCamera::CCamera()
{
}
//==============================
//�f�X�g���N�^
//==============================
CCamera::~CCamera()
{
}
//==============================
//�����ݒ�
//==============================
HRESULT CCamera::Init()
{

	//�����o�ϐ�������
	m_posV = PERSPECTIVE;			        // ���_
	m_posR = POINT_OF_INTEREST;		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };				// �����
	m_rot = { 0.0f, 0.0f, 0.0f };
    m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//����
	m_fScaleDis = SCALEDIS;	//�{��

	m_nShakeFrame = 0;
	m_nShakeVolume = 0;

	m_move = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_nFrame = 10;
	m_nCntFrame = 0;
	m_Front = ANGLE_FRONT;

	m_bControll = false;

	return S_OK;

}
//==============================
//�I������
//==============================
void CCamera::Uninit()
{
}
//==============================
//�X�V����
//==============================
void CCamera::Update()
{
	//�v���C���[�̃^�C�v���擾���ăJ�����̒Ǐ]������
	//�I�u�W�F�N�g�擾
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	ANGLE angle = m_Front;

	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];
		//��ނ̎擾
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // ���̃|�C���^���擾
			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos(); // �v���C���[�̈ʒu���擾

					m_posR = playerPos;  // �����_�̒Ǐ]
					m_posV.y = playerPos.y + 50.0f;  //���_���Œ蒍���_�ɍ��킵�ĒǏ]  +�`�͎��_�̍���
					//�J�����̎��_�̒Ǐ]
					m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.x;
					m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + playerPos.z;

					// ���͈͓���������
					if (playerPos.z >= POSITION1 && playerPos.z <= POSITION2)
					{
						m_Front = ANGLE_RIGHT;  // ������ς���
					}
					else if (playerPos.z >= POSITION3 && playerPos.z <= POSITION4)
					{
						//m_Front = ANGLE_FRONT;  // ������߂�
					}
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


	if (angle != m_Front)
	{
		float fRotMove = 0.0f;
		switch (m_Front)
		{
		case ANGLE_RIGHT:   // �E���������Ƃ�
			fRotMove = D3DX_PI * 0.5f - m_rot.y;  // ������ς���
			break;
		case ANGLE_FRONT:   // �O���������Ƃ�
			fRotMove = 0 - m_rot.y;   // ������߂�
		}

		// ��]�ʂ�180���𒴂����Ƃ��������ق��ɂ���
		if (fRotMove > D3DX_PI)
		{
			fRotMove -= D3DX_PI * 2;
		}
		else if (fRotMove < -D3DX_PI)
		{
			fRotMove += D3DX_PI * 2;
		}

		m_rotMove.y = fRotMove / m_nFrame;   // ��]�ʂ��t���[���Ŋ���
		m_nCntFrame = m_nFrame;  // �t���[�����J�E���g�ɓ����
	}
	if (m_nCntFrame > 0)
	{
		m_nCntFrame--;  // �J�E���g�_�E��
		m_rot.y += m_rotMove.y;
	}

	CManager* pManager = CManager::GetInstance();

	CScene* pScene = pManager->GetScene();
	CScene::MODE mode = pScene->GetMode();
	// ���[�h�̎擾
	if (mode == CScene::MODE::MODE_TITLE)
	{// �^�C�g����ʂ�z�������ɃJ�������ړ�������
		m_posR += m_move;

		m_posR.z += 2.0f;
		//�J�����̎��_�̒Ǐ]
		m_posV.x = sinf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + m_posR.x;
		m_posV.z = cosf(D3DX_PI + m_rot.y) * m_fDistance * m_fScaleDis + m_posR.z;

		//�ړ��ʂ�����
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;
		m_move.y += (0.0f - m_move.y) * 0.1f;

		if (m_posR.z >= POSITION1 && m_posR.z <= POSITION2)
		{
			CFade::SetFade_Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
	if (pKey->GetTrigger(DIK_F))
	{
		m_bControll = m_bControll ? false : true;

	}
}
//==============================
//�J�����ݒ�
//==============================
void CCamera::SetCamera()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);


	// �v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//near
		5000.0f);   //far


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	//D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �J�����̗h��
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFrame > 0)
	{
		m_nShakeFrame--;
		adjust.x = (float)(rand() % m_nShakeVolume);
		adjust.y = (float)(rand() % m_nShakeVolume);
		//adjust.z = random;
	}
	D3DXVECTOR3 posR, posV;
	posR = m_posR + adjust;  // �����_
	posV = m_posV + adjust;  // ���_
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &m_vecU);
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}
//==============================
// �J�����̃��Z�b�g
//==============================
void CCamera::ResetCamera()
{
	m_posV = PERSPECTIVE;			        // ���_
	m_posR = POINT_OF_INTEREST;		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };			// �����
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//����
	m_fScaleDis = 1.0f;	//�{��

}
//==============================
// �^�C�g����ʂ̃J����
//==============================
void CCamera::TitleCamera()
{
	m_posV = PERSPECTIVE;			        // ���_
	m_posR = POINT_OF_INTEREST;		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };			// �����
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(DISTANCE_LEFT * DISTANCE_LEFT + -DISTANCE_RIGHT * -DISTANCE_RIGHT);		//����
	m_fScaleDis = 1.0f;	//�{��

}
//==============================
// �J�����̒��ߗp
//==============================
void CCamera::DebugCamera()
{
	m_posV = { 0.0f, 200.0f, -450.0f };			// ���_
	m_posR = { 0.0f, 0.0f, 40.0f };		        // �����_
	m_vecU = { 0.0f, 1.0f, 0.0f };				// �����
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);

	m_fDistance = sqrtf(100 * 100 + -250 * -250);		//����
	m_fScaleDis = 1.0f;	//�{��

}
//==============================
// �J�����̈ʒu�ݒ�
//==============================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_posR = pos;
}
//==============================
// �J�����̗h��̐ݒ�
//==============================
void CCamera::SetShake(int shakeFrame, float shakeVolume)
{
	m_nShakeFrame = shakeFrame;
	m_nShakeVolume = (int)shakeVolume;
}
