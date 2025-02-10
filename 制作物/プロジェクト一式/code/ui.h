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

};
#endif