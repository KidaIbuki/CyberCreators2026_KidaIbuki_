//=================================
// 
// �K�w�\��player�@playerM.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"     // �}�l�[�W���[
#include "playerM.h"   // �v���C���[
#include "target.h"    // ���e�B�N��
#include "blockX.h"    // �u���b�N
#include "ui.h"        // UI
#include "obb.h"
#include "effect.h"
#include "bullet.h"    // �e
#include "explosion.h"

bool CPlayerM::m_bMove = false;
bool CPlayerM::m_bPlayerDeath = false;

const float CPlayerM::HALF2 = 0.75f;
const float CPlayerM::HALF1 = 0.5f;
const float CPlayerM::HALF = 0.25f;

const float CPlayerM::MOVE_SPEED = 0.25f;

const int CPlayerM::OVER = 190;   // ���E
const int CPlayerM::OVER_UP = 200;  // ��
const int CPlayerM::OVER_DOWN = 100;  // ��
const int CPlayerM::FRAMECNT = 40;   // �t���[���̃J�E���g(�e�̔��ˊԊu��ς����)

const D3DXCOLOR CPlayerM::COL = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);   // �G�t�F�N�g�J���[
const float CPlayerM::RADIUS = 3.0f;   // ���a
const float CPlayerM::SPLIT = 1.0f;    // ����
const int CPlayerM::EFFECTLIFE = 5;   // �G�t�F�N�g���C�t

const float CPlayerM::MOVE_PALYER = 4.0f;   // �v���C���[�̈ړ���
const float CPlayerM::MOVE_PALYER_Z = 2.0f;   // �v���C���[�̎��񂾂Ƃ��̈ړ���
const float CPlayerM::MOVE_PALYER_Y = 1.0f;   // �v���C���[�̎��񂾂Ƃ��̈ړ���

const int CPlayerM::SHAKE_FRAME = 30;   // ��ʂ̗h��̃t���[��
const int CPlayerM::SHAKE_VOLUME_DEATH = 3;   // ���񂾂ƂƂ��̗h��̋���
const int CPlayerM::SHAKE_VOLUME = 10;   // �_���[�W���󂯂��Ƃ��̗h��̋���
const int CPlayerM::LIFE_REDUCE = 10;   // ���C�t�����炷��

//===============================
// �R���X�g���N�^
//===============================
CPlayerM::CPlayerM()
{
	CObjectMotion::Load("data/TXT/motion.txt");   // txt�t�@�C���p�X������
	m_move = { 0.0f,0.0f,0.0f };
	m_rotMove = { 0.0f,0.0f,0.0f };
	m_type = BULLET_NONE;
	m_state = STATE_NONE;
	m_nFrameCnt = FRAMECNT;
	m_nDeathCnt = 180;
	m_nSceneCnt = 60;
}
//===============================
// �f�X�g���N�^
//===============================
CPlayerM::~CPlayerM()
{

}
//===============================
// �����ݒ�
//===============================
HRESULT CPlayerM::Init()
{
	CObjectMotion::Init();


	SetType(CObject::TYPE::PLAYER_M);


	return S_OK;
}
//===============================
// �I������
//===============================
void CPlayerM::Uninit()
{
}
//===============================
// �X�V����
//===============================
void CPlayerM::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾
	CInputMouse* pMouse = pManager->GetMouse();    //�R���g���[���[�擾

	// ���f���{�̂̈ʒu�A�������擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//SetMotion(1);
	// ���f���ɑ����t����
	if (m_bMove == true)
	{
		// �ړ��ʂ̍X�V
		m_move += PlayerMove();
		// pos�𓮂���
		pos += m_move;

		// rot�𓮂���
		rot += m_rotMove;

		//���ɓ������B
		pos.z += MOVE_PALYER;

		CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z - 25.0f), COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);


	}
	if (m_bPlayerDeath == true)
	{
		pos.y -= MOVE_PALYER_Y;
		pos.z += MOVE_PALYER_Z;
		pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME_DEATH);   // ��ʂ̗h��

		m_nDeathCnt--;
		if (m_nDeathCnt <= 0)
		{
			CExplosion::Create(pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));

			DeathFlag();

			m_bPlayerDeath = false;
			pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_EXPLOSION);

			CFade::SetFade(CScene::MODE::MODE_GAME);
		}
	}
	else // ����łȂ��Ƃ�
	{
		Collision();  // �v���C���[�֌W�̓����蔻��
	}
	//�ړ��ʂ�����
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//��]������
	m_rotMove.x += (0.0f - m_rotMove.x) * 0.1f;
	m_rotMove.z += (0.0f - m_rotMove.z) * 0.1f;
	m_rotMove.y += (0.0f - m_rotMove.y) * 0.1f;
	// ��]�̐���
	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2;
	}


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
			if (type == CObject::TYPE::TARGET)
			{
				CTarget* pTarget = static_cast<CTarget*>(pObj); //�_�E���L���X�g

				if (pTarget != nullptr)
				{
					D3DXVECTOR3 targetPos = pTarget->GetPos();
					if (m_bMove == true)
					{
						if (m_type == BULLET_NONE)
						{

							if (pJoypad->GetJoypadTrigger(pJoypad->JOYKEY_A) || pMouse->GetTrigger(pMouse->MOUSEBUTTON_LEFT))
							{
								// �T�E���h�𗬂�
								pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

								D3DXVECTOR3 bulletAngle;

								//======================�x�N�g�����g���ă��e�B�N���ɒe���΂�===============================================
								bulletAngle = D3DXVECTOR3(targetPos.x * 0.5f, targetPos.y * 0.5f, targetPos.z) - D3DXVECTOR3(pos.x * 0.5f, pos.y * 0.5f, pos.z);  // �e�̈ʒu���烌�e�B�N���̃x�N�g�������߂�
								D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // ������1�ɂȂ�

								CBullet::Create(pos, bulletAngle * 10.0f);
								// MEMO target��pos������Ă��邩�Abullet��move������������
								// x��y�̒l���{�ɂȂ��Ă�
								m_type = BULLET_SHOT;

							}
						}
						// �A�˖h�~���邽�߂̂��
						else if (m_type == BULLET_SHOT)
						{
							m_nFrameCnt--;
							if (m_nFrameCnt <= 0)
							{
								m_type = BULLET_NONE;
								m_nFrameCnt = FRAMECNT;
							}
						}
					}
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


	// ========================��ʊO�ɏo�Ȃ��悤�ɂ���=================================
	// ��
	if (pos.x < -OVER)
	{
		pos.x = -OVER;
	}
	//�E
	if (pos.x > OVER)
	{
		pos.x = OVER;
	}
	//��
	if (pos.y < -OVER_DOWN)
	{
		pos.y = -OVER_DOWN;
	}
	// ��
	if (pos.y > OVER_UP)
	{
		pos.y = OVER_UP;
	}


	// ���f���{�̂̈ʒu�ƌ����𔽉f
	SetPos(pos);
	SetRot(rot);
	CObjectMotion::Update();

}
//===================================
// �v���C���[�̈ړ�����
//===================================
D3DXVECTOR3 CPlayerM::PlayerMove()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();	//�L�[�{�[�h�擾
	CInputJoypad* pJoypad = pManager->GetJoypad();    //�R���g���[���[�擾

	D3DXVECTOR3 move = { 0,0,0 };
	// ���f���{�̂̈ʒu�A�������擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//**========�J�����̏��==========**
	CCamera* pCamera = pManager->GetCamera();  //�J�����̎擾
	D3DXVECTOR3 rotC = pCamera->GetRot();	//����

	// �{�X��O�͈͓̔���������
	if (pos.z >= 0.0f && pos.z <= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_D) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT))
		{//A�L�[�������ꂽ�ꍇ
			if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF2) * MOVE_SPEED;
				//rot.y = D3DX_PI * -HALF2 - rot.y;
			}
			else if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rotC.y - D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rotC.y - D3DX_PI * HALF1) * MOVE_SPEED;
			}

		}
		else if (pKeyboard->GetPress(DIK_A) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT))
		{//D�L�[�������ꂽ�ꍇ

			if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_W) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF2) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF2) * MOVE_SPEED;

			}
			else if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetPress(DIK_S) ||
				pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT) && pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF) * MOVE_SPEED;
			}
			else
			{
				move.x -= sinf(rotC.y + D3DX_PI * HALF1) * MOVE_SPEED;
				move.y -= cosf(rotC.y + D3DX_PI * HALF1) * MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//W�L�[�������ꂽ�ꍇ
			{
				move.y += MOVE_SPEED;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//S�L�[�������ꂽ�ꍇ
			{
				move.y -= MOVE_SPEED;

			}
		}
		if (pKeyboard->GetPress(DIK_E) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_RIGHT_SHOULDER))
		{
			m_rotMove.z += 0.005f;
		}
		else if (pKeyboard->GetPress(DIK_Q) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_LEFT_SHOULDER))
		{
			m_rotMove.z -= 0.005f;
		}
		else
		{
			m_rotMove.z += (0.0f - rot.z) * 0.005f;
		}
	}
	// �{�X��͈͓̔���������
	else if (pos.z >= POSITION1)
	{
		if (pKeyboard->GetPress(DIK_W) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_UP))
		{//W�L�[�������ꂽ�ꍇ
			move.y += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_S) || pJoypad->GetJoypadPress(pJoypad->JOYKEY_DOWN))
		{//S�L�[�������ꂽ�ꍇ
			move.y -= MOVE_SPEED;
		}

	}
#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_U))
	{
		move.z += 0.5;
	}
	if (pKeyboard->GetPress(DIK_J))
	{
		move.z -= 0.5;
	}

#endif


	// ���f���{�̂̈ʒu�ƌ����𔽉f
	SetPos(pos);
	SetRot(rot);

	return move;
}
//==============================================
// �v���C���[��x�������ɖ߂�
//==============================================
void CPlayerM::ResetPlayer()
{
	// ���f���{�̂̈ʒu�A�������擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	pos.x = 0.0f;
	rot.z = 0.0f;
	m_rotMove.z = 0.0f;

	// ���f���{�̂̈ʒu�ƌ����𔽉f
	SetPos(pos);
	SetRot(rot);

}
//===============================================
// �v���C���[�̓����蔻��(�L�����E�{�b�N�X)
//===============================================
void CPlayerM::Collision()
{
	// ���f���p�[�c�̈ʒu�A�������擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSiz();
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
				CEnemyX* pEnemy = static_cast<CEnemyX*>(pObj); //�_�E���L���X�g

				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // ��ʂ̗h��
					CLife::SubLife(LIFE_REDUCE);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::BLOCK)
			{
				CBlockX* pBlock = static_cast<CBlockX*>(pObj); //�_�E���L���X�g
				D3DXVECTOR3 blockPos = pBlock->GetPos();
				D3DXVECTOR3 blockSize = pBlock->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(blockPos.x, blockPos.y, blockPos.z), halfWidths1(blockSize.x, blockSize.y, blockSize.z);  // �u���b�N�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // ��ʂ̗h��
					CLife::SubLife(LIFE_REDUCE);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::ENEMY_BULLET)
			{
				CBulletEnemy* pBullet = static_cast<CBulletEnemy*>(pObj); //�_�E���L���X�g

				D3DXVECTOR3 BulletPos = pBullet->GetPos();
				D3DXVECTOR3 BulletSize = pBullet->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(BulletPos.x, BulletPos.y, BulletPos.z), halfWidths1(BulletSize.x, BulletSize.y, BulletSize.z);  // �G�̒e�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(pos.x, pos.y, pos.z), halfWidths2(size.x, size.y, size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pManager->GetInstance()->GetCamera()->SetShake(SHAKE_FRAME, SHAKE_VOLUME);   // ��ʂ̗h��
					CLife::SubLife(LIFE_REDUCE);
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_DAMAGE);
				}
				else 
				{// �������ĂȂ��Ƃ�
				}

			}

			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}

	// ���f���{�̂̈ʒu�ƌ����ƃT�C�Y�𔽉f
	SetPos(pos);
	SetRot(rot);
	SetSiz(size);
}
//===============================
// �`�揈��
//===============================
void CPlayerM::Draw()
{
	CObjectMotion::Draw();
}

//===============================
// ����
//===============================
CPlayerM* CPlayerM::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerM* pPlayer = new CPlayerM();
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);

	return pPlayer;
}
