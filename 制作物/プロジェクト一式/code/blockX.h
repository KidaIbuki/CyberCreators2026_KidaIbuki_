//================================
//
//xファイルでブロック(blockX.h)
//Auther kida ibuki
//================================
#ifndef _BLOCKX_H_
#define _BLOCKX_H_

#include "objectX.h"   // オブジェクトX
#include "object.h"    // オブジェクト

//ブロックのクラス定義
class CBlockX : public CObjectX
{
public:
	CBlockX();												//コンストラクタ
	~CBlockX();												//デストラクタ
	HRESULT Init();											//初期設定
	void Uninit();											//終了処理
	void Update();											//更新処理
	void Draw();											//描画処理
	static CBlockX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat,
		D3DXVECTOR3 movex1, D3DXVECTOR3 movex2, D3DXVECTOR3 movey1, D3DXVECTOR3 movey2, float fSpeed, float fSpeed1);					//ブロックの生成

	static CBlockX* Create2(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static CBlockX* Create3(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);
private:
	bool m_bMove;     // 動いているか否かx軸
	bool m_bMove1;     // 動いているか否かy軸

	//移動量などを格納する変数
	float m_fMoveStorage1;
	float m_fMoveStorage2;
	float m_fMoveStorage3;
	float m_fMoveStorage4;

	float m_fSpeedStorage;
	float m_fSpeedStorage1;

	int m_nType;  // ブロックの種類
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;						//テクスチャのテンプレート

};

#endif
