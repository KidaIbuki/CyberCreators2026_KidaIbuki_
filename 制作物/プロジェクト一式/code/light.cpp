//=================================
// 
//ライトクラス　　light.cpp
//Auther kida ibuki 
// 
//==================================
#include "light.h"   // ライト
#include "manager.h"  // マネージャー

//==============================
//コンストラクタ
//==============================
CLight::CLight()
{
	//ライト情報をクリアする
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

}
//==============================
//デストラクタ
//==============================
CLight::~CLight()
{
}
//==============================
//初期設定
//==============================
HRESULT CLight::Init()
{
	CManager* pManager = CManager::GetInstance();

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pManager->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;		//設定用方向ベクトル

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの情報をクリアする

		//ライトの種類を設定
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCntLight)
		{
		case 0:
			vecDir = VEC_DIR;
			break;
		case 1:
			vecDir = VEC_DIR1;
			break;
		case 2:
			vecDir = VEC_DIR2;
			break;
		}
		//ライトの方向を設定
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCntLight].Direction = vecDir;

		//ライトの設定する
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

}
//==============================
//終了処理
//==============================
void CLight::Uninit()
{
}
//==============================
//更新処理
//==============================
void CLight::Update()
{
}
