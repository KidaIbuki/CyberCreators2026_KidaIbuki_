//=================================
// 
// オブジェクト保存 クラス　save_object.cpp
// Auther kida ibuki 
// 
//==================================
#include "save_object.h"  // セーブオブジェクト

//===============================
// コンストラクタ
//===============================
CSaveObject::CSaveObject(CObject* pObject)
{
	m_pObject = pObject;
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
//===============================
// デストラクタ
//===============================
CSaveObject::~CSaveObject()
{
	if (m_pObject != nullptr)
	{
		m_pObject->DeathFlag();
		m_pObject = nullptr;
	}
}
//===============================
// 初期設定
//===============================
HRESULT CSaveObject::Init()
{
	if (FAILED(Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CSaveObject::Uninit()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
	}
}
//===============================
// 更新処理
//===============================
void CSaveObject::Update()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Update();
	}
}
//===============================
// 描画処理
//===============================
void CSaveObject::Draw()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Draw();
	}
}
//===============================
// 生成処理
//===============================
CSaveObject* CSaveObject::Create(CSaveObject* pTop, CSaveObject* pCur)
{
	if (pTop == nullptr)
	{
		pTop = this;
	}
	if (pCur == nullptr)
	{
		pCur = this;
	}
	else
	{
		this->m_pPrev = pCur;
		pCur->m_pNext = this;
		pCur = this;
	}
	return this;
}
