//=================================
// 
//���C�g�N���X�@�@light.h
//outher kida ibuki 
// 
//==================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"   // ���C��

#define MAX_LIGHT (3) //���C�g�̐�
#define VEC_DIR (D3DXVECTOR3(0.22f, -0.87f, 0.44f))    // 1�ڂ̃��C�g�̕����x�N�g���̐ݒ�
#define VEC_DIR1 (D3DXVECTOR3(-0.18f, 0.88f, -0.44f))  // 2�ڂ̃��C�g�̕����x�N�g���̐ݒ�
#define VEC_DIR2 (D3DXVECTOR3(0.89f, 0.11f, 0.44f))    // 3�ڂ̃��C�g�̕����x�N�g���̐ݒ�

//���C�g�̃N���X��`
class CLight
{
public:
	CLight();		    //�R���X�g���N�^
	~CLight();		    //�f�X�g���N�^
	HRESULT Init();     //�����ݒ�
	void Uninit();		//�I������
	void Update();      //�X�V����
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //���C�g�\����

};

#endif