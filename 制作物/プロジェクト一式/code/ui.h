//=================================
// 
// ui�N���X�@ui.h
//outher kida ibuki 
// 
//==================================
#ifndef _UI_H_
#define _UI_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "object2D.h"  // �I�u�W�F�N�g2D

class CUi :public CObject2D
{
public:
	CUi();
	~CUi()override;
	HRESULT Init()override;		//�����ݒ�
	void Uninit()override;      //�I������
	void Update()override;      //�X�V����
	void Draw()override;		//�`�揈��
	static CUi* Create(D3DXVECTOR2 pos, int nType);
	static void SubTime();
	int GetType() { return m_nType; }  // �^�C�v�̎擾
private:
	int m_nType;   // ���
	static int m_nFrame;
	static float m_fTexHeight;   // �c
	static float m_fTexWidht;    // ��

	static const int FRAME;  // �t���[���̃J�E���g
	static const float REDUCE_POS;  // �e�N�X�`�����W�����炷

	static const float INITIAL_VALUE;   // �ʒu�̏����l
	static const float TEX_RANGE;      // �e�N�X�`���͈̔�

	// �e�N�X�`���̃T�C�Y
	static const float TEX_SIZE_X_1;   
	static const float TEX_SIZE_Y_1;

	static const float TEX_SIZE_X_2;
	static const float TEX_SIZE_Y_2;

	static const float TEX_SIZE_X_3;
	static const float TEX_SIZE_Y_3;

	static const float TEX_SIZE_X_4;
	static const float TEX_SIZE_Y_4;

};
#endif