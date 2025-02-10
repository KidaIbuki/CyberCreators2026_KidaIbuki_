//=================================
// 
// �V�[���N���X�@scene.h
//outher kida ibuki 
// 
//==================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "pch.h"  // �v���R���p�C���ς݃w�b�_�[
#include "object.h"  // �I�u�W�F�N�g
#include "save_object.h"  // �Z�[�u�I�u�W�F�N�g

class CScene
{
public:
	//��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TITLE2,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;

	CScene();			//�R���X�g���N�^
	virtual ~CScene();			//�f�X�g���N�^
	virtual HRESULT Init();		//�����ݒ�
	virtual void Uninit();      //�I������
	virtual void Update();      //�X�V����
	virtual void Draw();		//�`�揈��
	void SetTexture(std::string sPath);  // �e�N�X�`���̐ݒ�
	void UpdateVertex();
	static CScene* Create(MODE mode);   //����
	void SetSize(float fWidth, float fHeight);//�e�e�N�X�`���̃T�C�Y�ݒ�
	void SetPos(float x, float y);			//�e�e�N�X�`���̈ʒu�ݒ�
	CSaveObject* CreateSaveObject(CObject* pObject);
	CSaveObject* CreateSaveObjectPause(CObject* pObject);   // �|�[�Y���̃I�u�W�F�N�g
	MODE GetMode() { return m_Mode; }
	int m_nTimerCnt;
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
private:
	MODE m_Mode;   // ���[�h���̎擾
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_pos;

	CSaveObject* m_pTop;
	CSaveObject* m_pCur;

	CSaveObject* m_pPauseTop;
	CSaveObject* m_pPauseCur;


};

#endif