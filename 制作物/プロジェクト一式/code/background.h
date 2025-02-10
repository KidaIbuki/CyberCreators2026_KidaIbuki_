//=================================
// 
// �{�X��w�i�N���X�@background.h
//outher kida ibuki 
// 
//==================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "object3D.h"   // �I�u�W�F�N�g3D

// �{�X��w�i�N���X
class CBackGround :public CObject3D
{
public:
	CBackGround();					//�R���X�g���N�^
	~CBackGround() override;			//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CBackGround* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);    //��������
	static HRESULT Load();				//�e�N�X�`���̃��[�h
	static void Unload();				//�e�N�X�`���̃A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g

};


#endif
