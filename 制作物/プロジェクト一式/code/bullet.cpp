//=================================
// 
// �e�N���X�@bullet.cpp
//outher kida ibuki 
// 
//==================================
#include "manager.h"    // �}�l�[�W���[
#include "bullet.h"   // �e
#include "effect.h"   // �G�t�F�N�g
#include "explosion.h"  // ����

// �ÓI�����o�ϐ���������
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = {};

const int CBullet::LIFE = 1300;
const D3DXCOLOR CBullet::COL = D3DXCOLOR(0.7f, 0.3f, 0.0f, 1.0f);  // �F
const float CBullet::RADIUS = 3.0f;  // ���a
const float CBullet::SPLIT = 1.0f;  // ����
const int CBullet::EFFECTLIFE = 10;  // �G�t�F�N�g�̃��C�t
const float CBullet::BILLSIZE = 3.0f;  // �r���{�[�h�T�C�Y
const float CBullet::BULLETSIZE = 4.0f;  // �e�̃T�C�Y


const D3DXCOLOR CBulletEnemy::COL = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);  // �F
const float CBulletEnemy::RADIUS = 5.0f;  // ���a
const float CBulletEnemy::SPLIT = 1.0f;  // ����
const int CBulletEnemy::EFFECTLIFE = 10;  // �G�t�F�N�g�̃��C�t
const float CBulletEnemy::BILLSIZE = 5.0f;  // �r���{�[�h�T�C�Y
const float CBulletEnemy::BULLETSIZE = 10.0f;  // �e�̃T�C�Y

//==========================================
// �R���X�g���N�^
//==========================================
CBullet::CBullet()
{
	m_dwLifeTime = timeGetTime();

	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_nHitCnt = 0;
}
//==========================================
// �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CBullet::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::BULLET);
	SetBillboard(BILLSIZE, BILLSIZE, BILLSIZE);
	SetSize(D3DXVECTOR3(BULLETSIZE, BULLETSIZE, 0.0f));
	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// �I������
//==========================================
void CBullet::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CBullet::Update()
{
	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::DeathFlag();
	}

	CEffect::Create(m_pos, COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);



	//CollisionBullet();
	Collision();

	m_pos += m_move;
}
//==========================================
// �`�揈��
//==========================================
void CBullet::Draw()
{
	CBillboard::Draw();

}
//==========================================
// ��������
//==========================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}

//=======================================
//���[�h
//=======================================
HRESULT CBullet::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CBullet::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
//======================================
// �e�̐ݒ�
//======================================
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//=======================================
//�����蔻��(OBB)
//=======================================
void CBullet::Collision()
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
				CEnemyX* pEnemy = static_cast<CEnemyX*>(pObj); //�_�E���L���X�g
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z - 50.0f);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �e�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pEnemy->m_bDeath = true;
					CExplosion::Create(pEnemy->m_pos, D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}
			if (type == CObject::TYPE::ENEMY_BOSS)
			{
				CEnemyBoss* pEnemy = static_cast<CEnemyBoss*>(pObj); //�_�E���L���X�g
				D3DXVECTOR3 enemyPos = pEnemy->GetPos();
				D3DXVECTOR3 enemySize = pEnemy->GetSize();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z + 150.0f), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �e�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�

				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);

				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{// �������Ă�Ƃ�
					pEnemy->DamageEnemy(10);
					CBullet::DeathFlag();
					// �T�E���h�𗬂�
					pManager->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_E_DAMAGE);
				}
				else
				{// �������ĂȂ��Ƃ�
				}

			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


}

//==========================================
// �R���X�g���N�^
//==========================================
CBulletEnemy::CBulletEnemy()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
}
//==========================================
// �f�X�g���N�^
//==========================================
CBulletEnemy::~CBulletEnemy()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CBulletEnemy::Init()
{
	CBillboard::Init();

	SetType(CObject::TYPE::ENEMY_BULLET);
	SetBillboard(BILLSIZE, BILLSIZE, BILLSIZE);
	SetSize(D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE));

	m_dwLifeTime = timeGetTime() + LIFE;


	return S_OK;

}
//==========================================
// �I������
//==========================================
void CBulletEnemy::Uninit()
{
	CBillboard::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CBulletEnemy::Update()
{

	if (timeGetTime() >= m_dwLifeTime)
	{
		CBullet::m_bDeath = true;
	}

	CEffect::Create(m_pos, COL, 0, RADIUS, SPLIT, 0.0f, EFFECTLIFE);

	m_pos += m_move;
}
//==========================================
// �`�揈��
//==========================================
void CBulletEnemy::Draw()
{
	CBillboard::Draw();

}
//==========================================
// ��������
//==========================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBulletEnemy* pBullet = new CBulletEnemy();
	pBullet->Init();
	pBullet->SetBullet(pos, move);
	pBullet->SetPos(pos);

	if (m_pTextureTemp != nullptr)
	{
		pBullet->BindTexture(m_pTextureTemp);
	}

	return pBullet;
}
//=======================================
//���[�h
//=======================================
HRESULT CBulletEnemy::Load()
{
	CManager* pManager = CManager::GetInstance();

	//�|�C���^��null�Ȃ�
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pManager->GetRenderer()->GetDevice(),
			"data\\TEXTURE\\bullet000.png",
			&m_pTextureTemp);
	}

	return S_OK;
}

//======================================
//�A�����[�h
//======================================
void CBulletEnemy::Unload()
{
	//�e�N�X�`�����g�p���Ă�����j��
	if (m_pTextureTemp != nullptr)
	{
		//null�ɂ���
		m_pTextureTemp = nullptr;
	}
}
//======================================
// �e�̐ݒ�
//======================================
void CBulletEnemy::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}
