//=================================
// 
// �|�[�Y�p �N���X�@pause_select.h
//outher kida ibuki 
// 
//==================================
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "select.h"  // �Z���N�g

class CGame;
class CPause_Select :public CSelect
{
public:
	CPause_Select();
	~CPause_Select()override;
	HRESULT Init()override;		//�����ݒ�
	void Uninit()override;      //�I������
	void Update()override;      //�X�V����
	void Draw()override;		//�`�揈��
	void SetType(int type)override;
	static CPause_Select* Create(D3DXVECTOR2 pos, D3DXVECTOR2 siz, int type);
private:
};

#endif