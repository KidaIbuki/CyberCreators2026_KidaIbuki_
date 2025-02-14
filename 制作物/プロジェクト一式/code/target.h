//=================================
// 
// �Ə��N���X�@target.h
//outher kida ibuki 
// 
//==================================
#ifndef _TARGET_H_
#define _TARGET_H_

#include "billboard.h"  // �r���{�[�h
#include "pch.h"  // �v���R���p�C���ς݃w�b�_�[
#include "enemyX.h"   // �G

class CTarget :public CBillboard
{
public:
	CTarget();		//�R���X�g���N�^
	~CTarget() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CTarget* Create(D3DXVECTOR3 pos);		//�I�u�W�F�N�g�̐���
	void MoveTatget();
private:
	void CollisionTarget();
	int m_nTargetFrame;         // �^�[�Q�b�g���o��������J�E���g
	bool m_bColor;
	static const float LEFT;   // �e�����̈ړ�����ő�l
	static const float RIGHT;
	static const float UP;
	static const float DOWN;

	static const float BILLSIZE_X;   // �r���{�[�h�T�C�Y
	static const float BILLSIZE_Y;   // �r���{�[�h�T�C�Y
	static const float BILLSIZE_Z;   // �r���{�[�h�T�C�Y

	static const D3DXCOLOR INIT_COLOR;   // �J���[�̏�����
	static const D3DXCOLOR CHANGE_COLOR;   // �J���[�̕ύX
	static const D3DXCOLOR CHANGE_COLOR_ELSE;   // �J���[��߂�

	static const float STICK_MOVE_X;   // �X�e�B�b�N�̈ړ���
	static const float STICK_MOVE_Y;   // �X�e�B�b�N�̈ړ���

	static const float POS_DISTANS;    // pos����ǂꂭ�炢������
};

#endif