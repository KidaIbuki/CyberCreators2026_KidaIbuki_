//================================
//
//x�t�@�C���Ńu���b�N(blockX.h)
//Auther kida ibuki
//================================
#ifndef _BLOCKX_H_
#define _BLOCKX_H_

#include "objectX.h"   // �I�u�W�F�N�gX
#include "object.h"    // �I�u�W�F�N�g

//�u���b�N�̃N���X��`
class CBlockX : public CObjectX
{
public:
	CBlockX();												//�R���X�g���N�^
	~CBlockX();												//�f�X�g���N�^
	HRESULT Init();											//�����ݒ�
	void Uninit();											//�I������
	void Update();											//�X�V����
	void Draw();											//�`�揈��
	static CBlockX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1);					//�u���b�N�̐���

	static CBlockX* Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static CBlockX* Create3(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);
private:
	bool m_bMove;     // �����Ă��邩�ۂ�x��
	bool m_bMove1;     // �����Ă��邩�ۂ�y��

	//�ړ��ʂȂǂ��i�[����ϐ�
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;
	float m_fSpeedStorage1;

	int m_nType;  // �u���b�N�̎��
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//�e�N�X�`���̃e���v���[�g

};

#endif
