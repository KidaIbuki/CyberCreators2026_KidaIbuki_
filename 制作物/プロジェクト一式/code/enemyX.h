//=================================
// 
// �G�N���X�@enemyX.h
//outher kida ibuki 
// 
//==================================
#ifndef _ENEMYX_H_
#define _ENEMYX_H_


#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "objectX.h"  // �I�u�W�F�N�gX
#include "playerM.h"
#include "obb.h"
// �ʏ�̓G�N���X
class CEnemyX :public CObjectX
{
public:
	enum ENEMYSTATE
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_MAX,
	};

	CEnemyX();							// �R���X�g���N�^
	~CEnemyX() override;				// �f�X�g���N�^
	HRESULT Init() override;			// �����ݒ�
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��
	static CEnemyX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1);

	ENEMYSTATE GetState() { return m_state; }

	void DrawOBB(ID3DXLine* pLine, const OBB& obb, IDirect3DDevice9* pDevice, D3DCOLOR color);  // ID3DXLine���g����OBB��`�悷��֐�
	void ProjectVertices(const std::vector<D3DXVECTOR3>& vertices, std::vector<D3DXVECTOR2>& projectedVertices, IDirect3DDevice9* pDevice);  // 3D���W��2D�X�N���[�����W�ɕϊ�����֐�


private:

	bool m_bMove;     // �����Ă��邩�ۂ�x��
	bool m_bMove1;     // �����Ă��邩�ۂ�y��
	bool m_bTouch;  // �G��Ă��邩�ǂ���

	//�ړ��ʂȂǂ��i�[����ϐ�
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;	// �����̊i�[�ϐ�1
    float m_fSpeedStorage1; // �����̊i�[�ϐ�2

	ENEMYSTATE m_state;
	int m_nFrameCnt;       // �e���΂��t���[���̃J�E���g
	int m_nFrame;          // �t���[���ێ��p�ϐ�

	ID3DXLine* m_pLine;

};

// �{�X�G�N���X
class CEnemyBoss :public CEnemyX
{
public:
	CEnemyBoss();
	~CEnemyBoss();
	HRESULT Init() override;			// �����ݒ�
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��
	static CEnemyBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void DamageEnemy(int nDamage);
private:
	int m_nFrameCntBoss;       // �e���΂��t���[���̃J�E���g
	int m_nFrame;          // �t���[���ێ��p�ϐ�
	bool m_bMoveBoss;     // �����Ă��邩�ۂ�
	int m_nLife;
	int m_nFrameEnemy;
};

#endif