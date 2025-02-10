//=================================
// 
// �r���{�[�h�N���X�@object3D.h
//outher kida ibuki 
// 
//==================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"    // �I�u�W�F�N�g

class CBillboard :public CObject
{
public:
	CBillboard();		//�R���X�g���N�^
	~CBillboard() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CBillboard* Create();		//�I�u�W�F�N�g�̐���

	//**===========�e�N�X�`���̐ݒ�=============**
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);	//�e�N�X�`���̐ݒ�
	void SetTexture(std::string sPath);

	//================�e�I�u�W�F�N�g�ݒ�==================
	D3DXVECTOR3 GetPos() { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetSize() { return m_size; }		//�T�C�Y�̎擾

	void SetPos(D3DXVECTOR3 pos);			//�e�I�u�W�F�N�g�̈ʒu�ݒ�
	void SetSize(D3DXVECTOR3 size);//�e�I�u�W�F�N�g�̃T�C�Y�ݒ�
	void SetBillboard(float fWidth, float fHeight, float fDepth);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetColor(D3DXCOLOR col); // �J���[�ݒ�  �ԁiMax1.0���j,�΁iMax1.0���j, �iMax1.0���j, ���iMax1.0���j
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_move;                         // �ړ���
	D3DXVECTOR3 m_size;                         // �T�C�Y
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@
private:

	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`��
	D3DXMATRIX m_mtxWorld;						// ���[���h�ϊ��s��
	D3DXCOLOR m_col;
};

#endif