//=================================
// 
// �p�[�e�B�N�� �N���X�@particle.h
//outher kida ibuki 
// 
//==================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "object3D.h"    // �I�u�W�F�N�g3D
#include "pch.h"     // �v���R���p�C���ς݃w�b�_�[

class CExplosion :public CObject3D
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init()override;		//�����ݒ�
	void Uninit()override;      //�I������
	void Update()override;      //�X�V����
	void Draw()override;		//�`�揈��
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static HRESULT Load();													//�e�N�X�`���̃��[�h
	static void Unload();													//�e�N�X�`���̃A�����[�h

private:
	bool m_bUse;         // �g�p����Ă��邩�ǂ���
	float m_fRadius;     // ���a
	D3DXCOLOR m_col;     // �J���[
	int m_nLife;         // ���C�t
	DWORD m_dwLifeTime;    // ���C�t�̃^�C�}�[
	static const int LIFE;				//���C�t
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g

};



#endif