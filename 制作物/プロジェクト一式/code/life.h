//==================================
// 
// �v���C���[���C�t �N���X�@life.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "object2D.h"   // �I�u�W�F�N�g2D
#include "pch.h"    // �v���R���p�C���ς݃w�b�_�[

class CLife :public CObject2D
{
public:
	CLife();
	~CLife();
	HRESULT Init()override;		//�����ݒ�
	void Uninit()override;      //�I������
	void Update()override;      //�X�V����
	void Draw()override;		//�`�揈��
	static CLife* Create(D3DXVECTOR2 pos);

	static void SubLife(int nDamage);
private:
	static float m_fTexHeight;   // �c
	static float m_fTexWidth;    // ��
	static int m_nFrame;   // �t���[���̃J�E���g
	static int m_nLife;   // ���C�t

	static const float TEX_HEIGHT;  // �e�N�X�`���̏c�̏����l
	static const float TEX_WIDTH;   // �e�N�X�`���̉��̏����l
	static const float TEX_SIZE_X;   // �e�N�X�`���̃T�C�Y
	static const float TEX_SIZE_Y;   // �e�N�X�`���̃T�C�Y
	static const float TEX_MOVE_H;   // �e�N�X�`���̈ړ�
	static const float TEX_MOVE_W;   // �e�N�X�`���̈ړ�

	static const int FRAME;         // �t���[��
	static const int LIFE;          // ���C�t
};
#endif