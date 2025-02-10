//=================================
// 
// �Ə��N���X�@target.cpp
//outher kida ibuki 
// 
//==================================

#include "target.h"   // ���e�B�N��
#include "bullet.h"   // �e
#include "playerM.h"  // �v���C���[
#include "manager.h"    // �}�l�[�W���[
#include "ui.h"
const int CTarget::OVER = 280;
const int CTarget::OVER_UP = 110;
const int CTarget::OVER_DOWN = 100;

//==========================================
// �R���X�g���N�^
//==========================================
CTarget::CTarget()
{
	m_bColor = false;
	m_nTargetFrame = 1;
}
//==========================================
// �f�X�g���N�^
//==========================================
CTarget::~CTarget()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CTarget::Init()
{
	CBillboard::Init();
	SetType(CObject::TYPE::TARGET);
	SetBillboard(20.0f, 40.0f, 20.0f);
	SetColor(D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f));

	return S_OK;
}
//==========================================
// �I������
//==========================================
void CTarget::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CTarget::Update()
{

	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
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

				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				// ���͈͓̔���������
				if (playerPos.z >= 0.0f && playerPos.z <= POSITION1)
				{
					if (pPlayer != nullptr)
					{
						MoveTatget();
						this->m_pos.z = playerPos.z + 150.0f;  // ���e�B�N�����v���C���[�̈ړ��ɍ��킵�Ĉړ�������
					}
				}
				// �{�X��͈͓̔���������
				else if (playerPos.z >= POSITION1)
				{
					this->m_pos = playerPos;
					this->m_pos.z = playerPos.z + 150.0f;  
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


	CollisionTarget();
	// ========================��ʊO�ɏo�Ȃ��悤�ɂ���=================================
	CManager* pManager = CManager::GetInstance();
	CCamera* pCamera = pManager->GetCamera();  //�J�����̎擾
	D3DXVECTOR3 posR = pCamera->GetPosR();	//����

    // ��
	if (m_pos.x < posR.x - 250.0f)
	{
		m_pos.x = posR.x - 250.0f;
	}
	//�E
	if (m_pos.x > posR.x + 250.0f)
	{
		m_pos.x = posR.x + 250.0f;
	}
	//��
	if (m_pos.y < posR.y - 170.0f)
	{
		m_pos.y = posR.y - 170.0f;
	}
	// ��
	if (m_pos.y > posR.y + 100.0f)
	{
		m_pos.y = posR.y + 100.0f;
	}

	// �����蔻��͈͓̔��ɂ�����F��ς���
	if (m_bColor == true)
	{
		SetColor(D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f));
	}
}
//==========================================
// �`�揈��
//==========================================
void CTarget::Draw()
{
	CBillboard::Draw();
}
//==========================================
// ��������
//==========================================
CTarget* CTarget::Create(D3DXVECTOR3 pos)
{
	CTarget* pTarget = new CTarget();
	pTarget->Init();
	pTarget->SetPos(pos);
	pTarget->SetTexture("data/TEXTURE/target001.png");
	
	return pTarget;
}
//==========================================
// ���e�B�N���̑���
//==========================================
void CTarget::MoveTatget()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�L�[�{�[�h�擾
	CInputMouse* pMouse = pManager->GetMouse();
	D3DXVECTOR2 move = pMouse->GetMove();

	// �}�E�X�ňړ�
	this->m_pos.x += move.x;   // x���ړ�
	this->m_pos.y += 0 - move.y;   // x���ړ�

	// �E�X�e�B�b�N�Ń��e�B�N���ړ�(�΂߂��Ή�)
	if (pJoypad->GetJoyR() == true)
	{
		XINPUT_STATE stick = pJoypad->GetStickR();   // �E�X�e�B�b�N�̏����擾
		this->m_pos.x += stick.Gamepad.sThumbRX * 0.0001f;   // x���ړ�
		this->m_pos.y += stick.Gamepad.sThumbRY * 0.0001f;   // y���ړ�
	}


}
//============================================
// �G�C���A�V�X�g�����邽�߂̔���
//============================================
void CTarget::CollisionTarget()
{
	CManager* pManager = CManager::GetInstance();
	CObject* pTopObject[NUM_MAX_PRIORITY];
	CObject::GetObj(pTopObject);
	for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = pTopObject[nPriority];

		//��ނ̎擾
		while (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			CObject* pNext = pObj->GetNext(); // ���̃|�C���^���擾
			if (type == CObject::TYPE::ENEMY_X)
			{
				bool bSwitch = pManager->GetSwitching();

				CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x + 10.0f, m_size.y + 10.0f, m_size.z + 200.0f);  // �Ə��̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// ���������Ƃ�
					bSwitch = true;
					pManager->SetSwitch(bSwitch);
					m_bColor = true;
					break;
				}
				else
				{// �������ĂȂ��Ƃ�
					bSwitch = false;
					pManager->SetSwitch(bSwitch);
					m_bColor = false;
				}

			}

			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}
}
