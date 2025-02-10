//==============================================
// 
//オブジェクト(xファイルの読み込み)　objectX.h
//outher kida ibuki 
// 
//==============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"   // オブジェクト
#include "pch.h"     // プリコンパイル済みヘッダー
#include "main.h"    // メイン

#define MAX_CHAR (256)
#define NUM_MODEL (10) //モデルの種類
#define MAX_TEX_X (16) // 1モデルのテクスチャの最大数
class CCamera;

//オブジェクトXクラスの定義
class CObjectX :public CObject
{
public:
	//**==================基本処理====================**
	CObjectX();		//コンストラクタ
	CObjectX(int nPriority);		//コンストラクタ
	~CObjectX() override;		//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

	void DrawFrame(LPDIRECT3DDEVICE9 pDevice);
	//**=================各生成の処理==================**
	static CObjectX* Create();		//オブジェクトの生成
	void SetModel(std::string sPath);		//モデルのセット
	void SizeVtx();						// オブジェクトのサイズの最大最小を求める
	//**===============各設定の取得======================**
	D3DXVECTOR3 GetPos() { return m_pos; }			//位置の取得
	D3DXVECTOR3 GetSize() { return m_size; }		//サイズの取得
	D3DXVECTOR3 GetRot() { return m_rot; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };			//各オブジェクトの位置設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	void SetSize(float fWidth, float fHeight, float fDepth);	//各オブジェクトのサイズ設定

	D3DXMATRIX GetWorldMatrix() { return m_mtxWorld; }  //ワールドマトリックスを取得(階層構造に必要)
	void SetWorldMatrix(D3DXMATRIX mat) { m_mtxWorld = mat; }
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_size;							//サイズ

	LPD3DXMESH GetMesh() { return m_pMesh; }
protected:

	//**==============描画の情報=================**
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	LPD3DXMESH m_pMesh;			//メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;    //マテリアルへのポインタ
	DWORD m_dwNumMat;           //マテリアルの数

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	//LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX_X];				//テクスチャ

private:

	//**===========モデルのメッシュ情報取得=============**
	D3DXVECTOR3 m_vtxMinModel;		//モデルの頂点の最小値
	D3DXVECTOR3 m_vtxMaxModel;		//モデルの頂点の最大値
	int m_nNumVtx;					//頂点数
	DWORD m_sizeFVF;				//頂点フォーマットのサイズ
	BYTE* m_bpVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3 m_nMaxVtx;					//モデルの最大値
	D3DXVECTOR3 m_nMinVtx;					//モデルの最小値

};
#endif
