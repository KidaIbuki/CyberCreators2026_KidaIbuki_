//=================================
// 
// �t�H�O�N���X�@�@fog.h
//outher kida ibuki 
// 
//==================================
#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"


class CFog
{
public:
	CFog();		    // �R���X�g���N�^
	~CFog();		    // �f�X�g���N�^
	HRESULT Init();     // �����ݒ�
	void Uninit();		// �I������
	void Update();      // �X�V����
	void Draw();        // �`�揈�� 
private:
	float m_fFogDensity;  // ���x�w��

	float m_fFogStartPos;  // �t�H�O�̊J�n�ʒu
	float m_fFogEndPos;    // �t�H�O�̏I���ʒu
};

#endif