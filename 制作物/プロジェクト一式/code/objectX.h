//==============================================
// 
//�I�u�W�F�N�g(x�t�@�C���̓ǂݍ���)�@objectX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"   // �I�u�W�F�N�g
#include "pch.h"     // �v���R���p�C���ς݃w�b�_�[
#include "main.h"    // ���C��

#define MAX_CHAR (256)
#define NUM_MODEL (10) //���f���̎��
#define MAX_TEX_X (16) // 1���f���̃e�N�X�`���̍ő吔
class CCamera;

//�I�u�W�F�N�gX�N���X�̒�`
class CObjectX :public CObject
{
public:
	//**==================��{����====================**
	CObjectX();		//�R���X�g���N�^
	CObjectX(int nPriority);		//�R���X�g���N�^
	~CObjectX() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	void DrawFrame(LPDIRECT3DDEVICE9 pDevice);
	//**=================�e�����̏���==================**
	static CObjectX* Create();		//�I�u�W�F�N�g�̐���
	void SetModel(std::string sPath);		//���f���̃Z�b�g
	void SizeVtx();						// �I�u�W�F�N�g�̃T�C�Y�̍ő�ŏ������߂�
	//**===============�e�ݒ�̎擾======================**
	D3DXVECTOR3 GetPos() { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetSize() { return m_size; }		//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };			//�e�I�u�W�F�N�g�̈ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	void SetSize(float fWidth, float fHeight, float fDepth);	//�e�I�u�W�F�N�g�̃T�C�Y�ݒ�

	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //���[���h�}�g���b�N�X���擾(�K�w�\���ɕK�v)
	void SetWorldMatrix(D3DXMATRIX mat) { m_mtxWorld = mat; }
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_size;							//�T�C�Y

	LPD3DXMESH GetMesh() { return m_pMesh; }
protected:

	//**==============�`��̏��=================**
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	LPD3DXMESH m_pMesh;			//���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;    //�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;           //�}�e���A���̐�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	//LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX_X];				//�e�N�X�`��

private:

	//**===========���f���̃��b�V�����擾=============**
	D3DXVECTOR3 m_vtxMinModel;		//���f���̒��_�̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel;		//���f���̒��_�̍ő�l
	int m_nNumVtx;					//���_��
	DWORD m_sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* m_bpVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_nMaxVtx;					//���f���̍ő�l
	D3DXVECTOR3 m_nMinVtx;					//���f���̍ŏ��l

};
#endif
