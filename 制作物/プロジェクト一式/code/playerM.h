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
	int m_nFrameCnt;            // �e�̃t���[���J�E���g 

	int m_nDeathCnt;           // �ǂꂭ�炢�Ŏ��ʂ��J�E���g
	int m_nSceneCnt;           // ��ʑJ�ڂ��鎞��
	static bool m_bMove;          // ���������ǂ���
	static bool m_bPlayerDeath;         // ���񂾂��ǂ���

	//**=================c++�Ń}�N��====================**
	static constexpr  float HALF2 = 0.75f;        //3.14�̔����̂Q����
	static constexpr  float HALF1 = 0.5f;		  //3.14�̔����̂R����
	static constexpr  float HALF = 0.25f;		  //��̔���
	static constexpr  float MOVE_SPEED = 0.25f;   	//�ړ��̑��x

	static constexpr  int OVER = 190;   // ���E
	static constexpr  int OVER_UP = 200;  // ��
	static constexpr  int OVER_DOWN = 100;  // ��
	static constexpr  int FRAMECNT = 40;   // �t���[���̃J�E���g(�e�̔��ˊԊu��ς����)

	static const D3DXCOLOR COL;   // �F

	static constexpr float RADIUS = 3.0f;   // ���a
	static constexpr float SPLIT = 1.0f;    // ����
	static constexpr int EFFECTLIFE = 5;   // �G�t�F�N�g���C�t

	static constexpr float MOVE_PALYER = 4.0f;   // �v���C���[�̈ړ���
	static constexpr float MOVE_PALYER_Z = 2.0f;   // �v���C���[�̎��񂾂Ƃ��̈ړ���
	static constexpr float MOVE_PALYER_Y = 1.0f;   // �v���C���[�̎��񂾂Ƃ��̈ړ���

	static constexpr int SHAKE_FRAME = 30;   // ��ʂ̗h��̃t���[��
	static constexpr int SHAKE_VOLUME_DEATH = 3;   // ���񂾂ƂƂ��̗h��̋���
	static constexpr int SHAKE_VOLUME = 10;   // �_���[�W���󂯂��Ƃ��̗h��̋���
	static constexpr int LIFE_REDUCE = 10;   // ���C�t�����炷��

};

#endif

