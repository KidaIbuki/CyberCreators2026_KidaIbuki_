//==================================
// 
// �v���C���[���C�t �N���X�@life.h
// Auther kida ibuki 
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


	static constexpr float TEX_HEIGHT = 0.0f;   // �e�N�X�`���̏c�̏����l
	static constexpr float TEX_WIDTH = 0.1f;    // �e�N�X�`���̉��̏����l
	static constexpr float TEX_SIZE_X = 120.0f;   // �e�N�X�`���T�C�Yx
	static constexpr float TEX_SIZE_Y = 350.0f;   // �e�N�X�`���T�C�Yy
	static constexpr float TEX_MOVE_H = 0.1f;   // �e�N�X�`���ړ�height
	static constexpr float TEX_MOVE_W = 0.1f;   // �e�N�X�`���ړ�width

	static constexpr int FRAME = 3;     // �J�E���g�t���[��
	static constexpr int LIFE = 100;    // ���C�t

};
#endif