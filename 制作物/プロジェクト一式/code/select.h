//=================================
// 
// �|�[�Y �N���X�@pause.h
//outher kida ibuki 
// 
//==================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "object2D.h"   // �I�u�W�F�N�g2D

class CSelect :public CObject2D
{
public:
	CSelect();
	~CSelect()override;
	virtual HRESULT Init() = 0;		//�����ݒ�
	virtual void Uninit() = 0;      //�I������
	virtual void Update() = 0;      //�X�V����
	virtual void Draw() = 0;		//�`�揈��
	virtual void SetType(int type) = 0;
	virtual int GetType() { return m_nType; }   // �^�C�v�̎擾
	int m_nType;
private:
};

#endif