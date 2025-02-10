//=================================
// 
// �G�N���X�@enemyX.h
//outher kida ibuki 
// 
//==================================
#include "manager.h"   // �}�l�[�W���[
#include "enemyX.h"  // �G
#include "bullet.h"  // �e
#include "blockX.h"  // �u���b�N

//int CEnemyBoss::m_nFrameEnemy = 0;
//int CEnemyBoss::m_nLife = 0;
//==================================
// �R���X�g���N�^
//==================================
CEnemyX::CEnemyX()
{
	// �G�̊�{�p�����[�^�[
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_bMove = true;   // �����Ă��邩�ǂ���x��
	m_bMove1 = true;   // y��
	m_bTouch = false;
	m_fMoveStorage1 = 0.0f;
	m_fMoveStorage2 = 0.0f;
	m_fMoveStorage3 = 0.0f;
	m_fMoveStorage4 = 0.0f;

	m_fSpeedStorage = 0.0f;
	m_fSpeedStorage1 = 0.0f;
	m_state = ENEMYSTATE_NONE;
	m_nFrameCnt = 0;
	m_nFrame = 100;
	m_pLine = nullptr;

}
//==================================
// �f�X�g���N�^
//==================================
CEnemyX::~CEnemyX()
{
}
//==================================
// �����ݒ�
//==================================
HRESULT CEnemyX::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_X);

	return S_OK;
}
//==================================
// �I������
//==================================
void CEnemyX::Uninit()
{
	CObjectX::Uninit();

	if (m_pLine != nullptr)
	{
		m_pLine->Release();
		m_pLine = nullptr;
	}

}
//==================================
// �X�V����
//==================================
void CEnemyX::Update()
{
	// �G�̍s������
    m_pos += m_move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	// �w�肵�����W�̊Ԃ��s�������鏈��
	//x��
	if (m_pos.x > m_fMoveStorage1)//��
	{
		m_bMove = true;
	}
	else if (m_pos.x < m_fMoveStorage2)//��O
	{
		m_bMove = false;
	}
	if (m_bMove == true)
	{
		m_pos.x -= m_fSpeedStorage;
	}
	else if (m_bMove == false)
	{
		m_pos.x += m_fSpeedStorage;
	}

	//y��
	if (m_pos.y > m_fMoveStorage3)//��
	{
		m_bMove1 = true;
	}
	else if (m_pos.y < m_fMoveStorage4)//��
	{
		m_bMove1 = false;
	}
	if (m_bMove1 == true)
	{
		m_pos.y -= m_fSpeedStorage1;
	}
	else if (m_bMove1 == false)
	{
		m_pos.y += m_fSpeedStorage1;
	}
	//�ړ��ʂ�����
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.y += (0.0f - m_move.y) * 0.3f;

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
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					if (m_nFrameCnt <= 0)
					{
						// �v���C���[�Ɍ������ēG���e���΂�
						D3DXVECTOR3 bulletAngle, position;
						bulletAngle = D3DXVECTOR3(playerPos.x * 0.5f, playerPos.y * 0.5f, playerPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // �G�̈ʒu����v���C���[�̃x�N�g�������߂�
						position = playerPos - m_pos;   // �G�ƃv���C���[�̃x�N�g�������߂�
						D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // ������1�ɂȂ�

						// �G�����ɍs������e�͌����Ȃ�
						if(playerPos.z > m_pos.z ||
							D3DXVec3Length(&position) >= 300)   // �G�����苗������Ă�����ȉ��̏��������Ȃ�(�e���΂��Ȃ�)
						{
							pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
							continue;
						}
						CBulletEnemy::Create(m_pos, bulletAngle * 10.0f);

						m_nFrameCnt = m_nFrame;
					}
					if (m_nFrameCnt > 0)
					{
						m_nFrameCnt--;
					}
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}
}
//==================================
// �`�揈��
//==================================
void CEnemyX::Draw()
{

	CObjectX::Draw();
#if 0
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

	D3DXCreateLine(pDevice, &m_pLine);

	// OBB������
	D3DXVECTOR3 center(m_pos.x, m_pos.y, m_pos.z), halfWidths(m_size.x, m_size.y, m_size.z);
	D3DXMATRIX rotation;
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(45), 0, 0); // Y���𒆐S��45�x��]	OBB obb(center, halfWidths, rotation);
	OBB obb(center, halfWidths, rotation);


	 //OBB��`��
	DrawOBB(m_pLine, obb, pDevice, D3DCOLOR_XRGB(255, 0, 0));


	m_pLine->Release();
    // TODO : ���C���͂܂��o�O�����邩��v�C��
#endif
}
//==================================
// ��������
//==================================
CEnemyX* CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
	D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1)
{
	CEnemyX* pEnemyX = new CEnemyX;
	pEnemyX->SetPos(pos);
	pEnemyX->SetRot(rot);
	pEnemyX->SizeVtx();
	pEnemyX->m_pMesh = pMesh;
	pEnemyX->m_pBuffMat = pBuffMat;
	pEnemyX->m_dwNumMat = dwNumMat;
	pEnemyX->m_fMoveStorage1 = movex1.x;
	pEnemyX->m_fMoveStorage2 = movex2.x;
	pEnemyX->m_fMoveStorage3 = movey1.y;
	pEnemyX->m_fMoveStorage4 = movey2.y;

	//y�����ǉ����邩��...
	pEnemyX->m_fSpeedStorage = fSpeed;
	pEnemyX->m_fSpeedStorage1 = fSpeed1;


	pEnemyX->Init();
	return pEnemyX;
}
//==========================================
// �R���X�g���N�^
//==========================================
CEnemyBoss::CEnemyBoss()
{
	m_move = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };

	m_nFrameCntBoss = 0;
	m_nFrame = 80;
	m_nLife = 100;
	m_nFrameEnemy = 3;
}
//==========================================
// �f�X�g���N�^
//==========================================
CEnemyBoss::~CEnemyBoss()
{
}
//==========================================
// �����ݒ�
//==========================================
HRESULT CEnemyBoss::Init()
{
	CObjectX::Init();

	SetType(CObject::TYPE::ENEMY_BOSS);  // �^�C�v�ݒ�

	return S_OK;
}
//==========================================
// �I������
//==========================================
void CEnemyBoss::Uninit()
{
	CObjectX::Uninit();
}
//==========================================
// �X�V����
//==========================================
void CEnemyBoss::Update()
{
	// �G�̍s������
	m_pos += m_move;

	m_pos.z += m_move.z;

	m_pos.z += 4.0f;  // �G�̑���

	//y��
	if (m_pos.y > 160)//��
	{
		m_bMoveBoss = true;
	}
	else if (m_pos.y < -100)//��
	{
		m_bMoveBoss = false;
	}
	if (m_bMoveBoss == true)
	{
		m_pos.y -= 0.5f;
	}
	else if (m_bMoveBoss == false)
	{
		m_pos.y += 0.5f;
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
			if (type == CObject::TYPE::PLAYER_M)
			{
				CPlayerM* pPlayer = (CPlayerM*)pObj; //�_�E���L���X�g
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 playerPos = pPlayer->GetPos();

					if (m_nFrameCntBoss <= 0)
					{

						// �v���C���[�Ɍ������ēG���e���΂�
						D3DXVECTOR3 bulletAngle, position;
						bulletAngle = D3DXVECTOR3(playerPos.x * 0.5f, playerPos.y * 0.5f, playerPos.z) - D3DXVECTOR3(m_pos.x * 0.5f, m_pos.y * 0.5f, m_pos.z);  // �G�̈ʒu����v���C���[�̃x�N�g�������߂�
						position = playerPos - m_pos;   // �G�ƃv���C���[�̃x�N�g�������߂�
						D3DXVec3Normalize(&bulletAngle, &bulletAngle);   // ������1�ɂȂ�

						if (D3DXVec3Length(&position) >= 300)   // �G�����苗������Ă�����ȉ��̏��������Ȃ�(�e���΂��Ȃ�)
						{
							pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
							continue;
						}
						// �����_���Ń{�X�̍s�������߂�
						int Random = 0;
						Random = rand() % 3;
						if (Random == 0)
						{
							CBulletEnemy::Create(m_pos, bulletAngle * 10.0f);  // �e������
						}
						else if (Random == 1)
						{
							CBlockX::Create2(m_pos, m_rot);   // ��Q�����΂�
						}
						else if (Random == 2)
						{

						}
						m_nFrameCntBoss = m_nFrame;   // �J�E���g�Ƀt���[��������
					}
					if (m_nFrameCntBoss > 0)  // �J�E���g���c���Ă�����
					{
						m_nFrameCntBoss--;   // �J�E���g�_�E��
					}
				}
			}
			pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
		}
	}


	m_move.z += (0.0f - m_move.z) * 0.3f;

}
//==========================================
// �`�揈��
//==========================================
void CEnemyBoss::Draw()
{
	CObjectX::Draw();
}
//==========================================
// ��������
//==========================================
CEnemyBoss* CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemyBoss* pBoss = new CEnemyBoss();
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
	pBoss->Init();
	pBoss->SetModel("data/MODEL/ENEMY/EnemyBoss.x");

	return pBoss;
}
void CEnemyBoss::DamageEnemy(int nDamage)
{
	m_nLife -= nDamage;  // ���C�t�����炷

	if (m_nLife <= 0)
	{// ���C�t�������Ȃ�����
		CEnemyBoss::DeathFlag();
		CFade::SetFade(CScene::MODE::MODE_RESULT);
	}
}
//========================================
// ID3DXLine���g����OBB��`�悷��֐�
//========================================
void CEnemyX::DrawOBB(ID3DXLine* pLine, const OBB& obb, IDirect3DDevice9* pDevice, D3DCOLOR color)
{
	// OBB�̒��_���擾
	std::vector<D3DXVECTOR3> vertices3D(8);
	for (int i = 0; i < 8; ++i) {
		vertices3D[i] = obb.GetVertex(i);
	}
	// OBB�̃G�b�W���`�i���C���ڑ����j
	std::vector<D3DXVECTOR3> edges3D = {
		vertices3D[0], vertices3D[1], vertices3D[1], vertices3D[3],
		vertices3D[3], vertices3D[2], vertices3D[2], vertices3D[0], // ���
		vertices3D[4], vertices3D[5], vertices3D[5], vertices3D[7],
		vertices3D[7], vertices3D[6], vertices3D[6], vertices3D[4], // ���
		vertices3D[0], vertices3D[4], vertices3D[1], vertices3D[5],
		vertices3D[2], vertices3D[6], vertices3D[3], vertices3D[7]  // ������
	};
	// 2D�X�N���[�����W�ɕϊ�
	std::vector<D3DXVECTOR2> edges2D;
	ProjectVertices(edges3D, edges2D, pDevice);
	// ���C����`��
	pLine->Begin();
	pLine->Draw(edges2D.data(), edges2D.size(), color);
	pLine->End();
}
//========================================
// 3D���W��2D�X�N���[�����W�ɕϊ�����֐�
//========================================
void CEnemyX::ProjectVertices(const std::vector<D3DXVECTOR3>& vertices, std::vector<D3DXVECTOR2>& projectedVertices, IDirect3DDevice9* pDevice)
{
	D3DVIEWPORT9 viewport;
	D3DXMATRIX viewMatrix, projMatrix;
	// �r���[�|�[�g�A�r���[�s��A�ˉe�s����擾
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
	pDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);
	projectedVertices.clear();
	// �e���_���v���W�F�N�g
	for (const auto& vertex : vertices) {
		D3DXVECTOR3 projected;
		D3DXVec3Project(&projected, &vertex, &viewport, &projMatrix, &viewMatrix, nullptr);
		projectedVertices.push_back(D3DXVECTOR2(projected.x, projected.y));
	}
}

