//=================================
// 
// �K�w�\��player�@playerM.h
//outher kida ibuki 
// 
//==================================
#ifndef _PLAYERM_H_
#define _PLAYERM_H_

#include "object.h"    // �I�u�W�F�N�g
#include "life.h"      // ���C�t
#include "motion.h"

#define MAX_CHAR (256)   // �ǂݍ��ޕ��̍ő吔

class CPlayerM :public CObjectMotion
{
public:
	// �U�����
	typedef enum
	{
		BULLET_NONE = 0,
		BULLET_SHOT,
		BULLET_MAX
	}BULLET_TYPE;
    // �v���C���[�̏��
	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;
	CPlayerM();    // �R���X�g���N�^
	~CPlayerM();   // �f�X�g���N�^
	HRESULT Init() override;    // �����ݒ�
	void Uninit() override;     // �I������
	void Update() override;     // �X�V����
	void Draw() override;       // �`�揈��
	static CPlayerM* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);   // ��������
	//void SetPos(D3DXVECTOR3 pos);   // �ʒu�ݒ�
	//void SetRot(D3DXVECTOR3 rot);   // �����ݒ�
	D3DXVECTOR3 PlayerMove();   // �v���C���[�̈ړ�����
	//D3DXVECTOR3 GetPos() { return m_pos; }  // �K�w�\����pos�̎擾
	//D3DXVECTOR3 GetSize() { return m_pModel->m_size; }		//�T�C�Y�̎擾
	void ResetPlayer();   // �v���C���[��x���̈ʒu�����̈ʒu�ɖ߂�
	void Collision();         // �v���C���[�̓����蔻��
	static void MoveFlag(bool bMove) { m_bMove = bMove; }
	static void DeathMove(bool bDeath) { m_bPlayerDeath = bDeath; }
	//**=================c++�Ń}�N��====================**
	static const float HALF2;				//3.14�̔����̂Q����
	static const float HALF1;				//3.14�̔����̂R����
	static const float HALF;				//��̔���
	static const float MOVE_SPEED;			//�ړ��̑��x
	static const int OVER;         // ���E�̏��
	static const int OVER_UP;      // ��̏��
	static const int OVER_DOWN;    // ���̏��
	static const int FRAMECNT;     // �t���[���̃J�E���g

	//D3DXVECTOR3 m_pos;          // �ʒu
	//D3DXVECTOR3 m_rot;          // ����
	//D3DXVECTOR3 m_size;			//�T�C�Y
private:
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	D3DXVECTOR3 m_move;         // �ړ���
	D3DXVECTOR3 m_rotMove;      // rot�p��move(���炩��]�p)
	D3DXVECTOR3 m_collitionSize;   // �����蔻��p�̃T�C�Y
	BULLET_TYPE m_type;         // �e�̏��
	STATE m_state;              // �v���C���[�̏��
	float m_fAngle;				// ����
	int m_nFrameCnt;            // �e�̃t���[���J�E���g 
	int m_nLife;                // �v���C���[�̃��C�t

	int m_nDamegeCnt;                 // �_���[�W�̃J�E���g
	int m_nDeathCnt;           // �ǂꂭ�炢�Ŏ��ʂ��J�E���g
	int m_nSceneCnt;           // ��ʑJ�ڂ��鎞��
	static bool m_bMove;          // ���������ǂ���
	static bool m_bPlayerDeath;         // ���񂾂��ǂ���
};

#endif

