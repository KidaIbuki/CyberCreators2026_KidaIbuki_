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
	static const int OVER;
	static const int OVER_UP;
	static const int OVER_DOWN;
};

#endif