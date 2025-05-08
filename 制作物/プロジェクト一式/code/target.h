//=================================
// 
// �Ə��N���X�@target.h
// Auther kida ibuki 
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

	static const D3DXCOLOR INIT_COLOR;   // �J���[�̏�����
	static const D3DXCOLOR CHANGE_COLOR;   // �J���[�̕ύX
	static const D3DXCOLOR CHANGE_COLOR_ELSE;   // �J���[��߂�

	static constexpr float LEFT = 250.0f;  // �e�����̈ړ��̍ő�l
	static constexpr float RIGHT = 250.0f;
	static constexpr float UP = 100.0f;
	static constexpr float DOWN = 170.0f;

	static constexpr float BILLSIZE_X = 20.0f;   // �e�r���{�[�h�T�C�Y
	static constexpr float BILLSIZE_Y = 40.0f;
	static constexpr float BILLSIZE_Z = 20.0f;

	// �X�e�B�b�N�̈ړ���
	static constexpr float STICK_MOVE_X = 0.0001f;
	static constexpr float STICK_MOVE_Y = 0.0001f;

	static constexpr float POS_DISTANS = 150.0f;  // pos����ǂꂭ�炢������


};

#endif