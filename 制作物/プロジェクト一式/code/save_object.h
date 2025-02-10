//=================================
// 
// オブジェクト保存 クラス　save_object.h
//outher kida ibuki 
// 
//==================================
#ifndef _SAVE_OBJECT_H_
#define _SAVE_OBJECT_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "object.h"   // オブジェクト

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