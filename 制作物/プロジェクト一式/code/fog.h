//=================================
// 
// �t�H�O�N���X�@�@fog.h
// Auther kida ibuki 
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

	static const D3DXCOLOR COL;  // �t�H�O�J���[
	static constexpr float DENSITY = 0.0005f;  // ���x
};

#endif