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
	static float m_fTexWidht;    // ��
	static int m_nFrame;   // �t���[���̃J�E���g
	static int m_nLife;   // ���C�t
};
#endif