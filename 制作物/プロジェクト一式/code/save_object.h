//=================================
// 
// �I�u�W�F�N�g�ۑ� �N���X�@save_object.h
//outher kida ibuki 
// 
//==================================
#ifndef _SAVE_OBJECT_H_
#define _SAVE_OBJECT_H_

#include "pch.h"   // �v���R���p�C���ς݃w�b�_�[
#include "object.h"   // �I�u�W�F�N�g

class CSaveObject
{
public:
	CSaveObject() = delete;
	CSaveObject(CObject*pObject);
	~CSaveObject();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	CObject* GetMyObject() { return m_pObject; }
	CSaveObject* Create(CSaveObject* pTop, CSaveObject* pCur);
public:
	CSaveObject* m_pNext;
	CSaveObject* m_pPrev;
private:
	CObject* m_pObject;
};

#endif