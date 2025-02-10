//=================================
// 
// �G�t�F�N�g�N���X�@effect.h
//outher kida ibuki 
// 
//==================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object.h"   // �I�u�W�F�N�g
#include "pch.h"    // �v���R���p�C���ς݃w�b�_�[

//�}�N����`
#define MAX_EFFECT (256) //�G�t�F�N�g�ő吔
#define NUM_EFFECT (1) //�G�t�F�N�g�e�N�X�`���̎��
#define INTERVAL_EFFECT (60.f) //�C���^�[�o������
#define COUNT_EFFECT (60) //�C���^�[�o����(int)����

class CEffect :public CObject
{
public:
    CEffect();			//�R���X�g���N�^
    ~CEffect()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����
    void Draw()override;		//�`�揈��
    static CEffect* Create(D3DXVECTOR3 pos, D3DCOLOR col, int nType, float fRadius, float fSplit, float fAlpha, int nLife);
	void SetTexture(std::string sPath);

private:
	D3DXVECTOR3 m_pos;   //�ʒu
	D3DXCOLOR m_col;     //�F
	int  m_nType;        //��ގ���
	float m_fRadius;     //���a�i�傫���j
	int m_nLife;         //�����i�\�����ԁj
	bool m_bUse;         //�g�p���Ă��邩�ǂ����̊m�F
	bool m_bStartTexture; //�����e�N�X�`���̍��W�ݒ�
	float m_Interval;  //�C���^�[�o���`�F�b�N
	int m_EffectCnt;   //UV���W�̍X�V�Ɏg���J�E���^�[;
	float m_fSplit;       //��������
	float m_fAlpha;       //�����������l�̐ݒ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��

};


#endif