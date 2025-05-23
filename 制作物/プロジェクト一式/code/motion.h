//===========================================
// 
// モーション[motion.h]
// Auther:UedaKou    シェーダー部分  Kida Ibuki
// 
//===========================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "objectX.h"

#define MAX_MOTION (64)			// 最大モーション
#define MAX_KYE (32)			// 最大キーフレーム数
#define MAX_MOTION_MODEL (64)	// モーションに使えるモデル数
#define MAX_PARTS (64)			// 最大パーツ数
#define TAU (D3DX_PI*2)         // 2π
/*
全体モーション管理
	モーション(ニュートラル, 歩きなど)
		現在キー
		キーフレーム


	パーツ
	現在モーション
	


*/
typedef struct {
	D3DXVECTOR3 pos;    // 位置
	D3DXVECTOR3 rot;    // 向き
	D3DXVECTOR3 siz;    // 大きさ(倍率)
}Transform;

// トランスフォーム
class X : public Transform
{
public:
	X() {}
	X(D3DXVECTOR3 Vec3pos, D3DXVECTOR3 Vec3rot, D3DXVECTOR3 Vec3siz) {
		pos = Vec3pos;
		rot = Vec3rot;
		siz = Vec3siz;
	}

	X& operator+= (const X& transform)
	{
		pos.x += transform.pos.x;
		pos.y += transform.pos.y;
		pos.z += transform.pos.z;

		rot.x += transform.rot.x;
		rot.y += transform.rot.y;
		rot.z += transform.rot.z;

		siz.x += transform.siz.x;
		siz.y += transform.siz.y;
		siz.z += transform.siz.z;
		return *this;
	}
	X& operator-= (const X& transform)
	{
		pos.x -= transform.pos.x;
		pos.y -= transform.pos.y;
		pos.z -= transform.pos.z;

		rot.x -= transform.rot.x;
		rot.y -= transform.rot.y;
		rot.z -= transform.rot.z;

		siz.x -= transform.siz.x;
		siz.y -= transform.siz.y;
		siz.z -= transform.siz.z;
		return *this;
	}
	X& operator*= (const X& transform)
	{
		pos.x *= transform.pos.x;
		pos.y *= transform.pos.y;
		pos.z *= transform.pos.z;

		rot.x *= transform.rot.x;
		rot.y *= transform.rot.y;
		rot.z *= transform.rot.z;

		siz.x *= transform.siz.x;
		siz.y *= transform.siz.y;
		siz.z *= transform.siz.z;
		return *this;
	}
	X& operator/= (const X& transform)
	{
		pos.x /= transform.pos.x;
		pos.y /= transform.pos.y;
		pos.z /= transform.pos.z;

		rot.x /= transform.rot.x;
		rot.y /= transform.rot.y;
		rot.z /= transform.rot.z;

		siz.x /= transform.siz.x;
		siz.y /= transform.siz.y;
		siz.z /= transform.siz.z;
		return *this;
	}
};
class CPartsData
{
public:
	CPartsData();
	~CPartsData();

	void SetPosTarget(D3DXVECTOR3 pos) { m_x.pos = pos; }
	void SetRotTarget(D3DXVECTOR3 rot) { m_x.rot = rot; }
	void SetSizTarget(D3DXVECTOR3 siz) { m_x.siz = siz; }

	D3DXVECTOR3 GetPosTarget() { return m_x.pos; }
	D3DXVECTOR3 GetRotTarget() { return m_x.rot; }
	D3DXVECTOR3 GetSizTarget() { return m_x.siz; }
private:
	X m_x;	// トランスフォーム

};

// キーフレーム
class CKye
{
public:
	CKye();
	~CKye();
	void SetFrame(int nFrame) { m_nFrame = nFrame; }

	CPartsData* GetPartsData(int nParts) { return m_pParts[nParts]; }
	int GetFrame() { return m_nFrame; }
	CPartsData* creatPartsData();

private:
	CPartsData* m_pParts[MAX_PARTS];	// パーツ
	int m_nFrame;
};

// モーション
class CMotion 
{
public:
	CMotion();
	virtual ~CMotion();
	void SetNumKye(int nNumKye) { m_nNumKye = nNumKye; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void creatKye();

	CKye* GetKye(int nKye) { return m_pKye[nKye]; }
	int GetNumKye() { return m_nNumKye; }
	bool GetLoop() { return m_bLoop; }
private:
	CKye* m_pKye[MAX_KYE];	// キーフレーム
	int m_nNumKye;	// キー数
	bool m_bLoop;	// このモーションをループするか
};

// 現在モーション
class CNowMotion
{
public:
	CNowMotion();
	~CNowMotion();
	// 設定
	void SetMotion(int nMosyon) { m_nCntMotion = nMosyon; }		// モーションカウント
	void SetKye(int nKye) { m_nCntKye = nKye; }			// キーカウント
	void SetFrame(int nFrame) { m_nCntFrame = nFrame; }		// フレーム

	// 取得
	int GetMotion() { return m_nCntMotion; }	// モーションカウント
	int GetKye() { return m_nCntKye; }		// キーカウント
	int GetFrame() { return m_nCntFrame; }		// フレーム

	// データ追加
	void AddMotion(int nNum) { m_nCntMotion += nNum; }	// モーションカウント
	void AddKye(int nNum) { m_nCntKye += nNum; }		// キーカウント
	void AddFrame(int nNum) { m_nCntFrame += nNum; }		// フレーム

private:
	int m_nCntMotion;	// モーションカウント
	int m_nCntKye;		// キーカウント
	int m_nCntFrame;	// フレーム
};

// パーツ
class CParts : public CObjectX
{
public:
	CParts();
	CParts(int nPriority);
	~CParts()					override;
	virtual HRESULT Init()		override; // 初期化
	virtual void Uninit()	override; // 終了
	virtual void Update()	override; // 更新
	virtual void Draw()		override; // 描画

	// トゥーン&アウトライン用シェーダー関数
	bool LoadEffect(LPDIRECT3DDEVICE9 device, const char* fxFile);
	void UninitEffect();
	void UpdateEffect(LPDIRECT3DDEVICE9 device);
	void DrawEffect(LPDIRECT3DDEVICE9 device);


	// 基本位置設定
	void SetBasicX(X x) {
		m_xBasic.pos = x.pos;
		m_xBasic.rot = x.rot;
		m_xBasic.siz = x.siz;
	}
	void SetBasicX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xBasic.pos = pos;
		m_xBasic.rot = rot;
		m_xBasic.siz = siz;
	}
	void SetBasicPos(D3DXVECTOR3 pos) { m_xBasic.pos = pos; }
	void SetBasicRot(D3DXVECTOR3 rot) { m_xBasic.rot = rot; }
	void SetBasicSiz(D3DXVECTOR3 siz) { m_xBasic.siz = siz; }

	// 追加位置
	void SetAddX(X x) {
		m_xOffset.pos = x.pos;
		m_xOffset.rot = x.rot;
		m_xOffset.siz = x.siz;
	}
	void SetAddX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xOffset.pos = pos;
		m_xOffset.rot = rot;
		m_xOffset.siz = siz;
	}
	void SetOffsetPos(D3DXVECTOR3 pos) { m_xOffset.pos = pos; }
	void SetOffsetRot(D3DXVECTOR3 rot) { m_xOffset.rot = rot; }
	void SetOffsetSiz(D3DXVECTOR3 siz) { m_xOffset.siz = siz; }

	// 動き設定
	void SetMoveX(X x, int nFrame) { SetMoveX(x.pos, x.rot, x.siz, nFrame); };
	void SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame); 

	// データ設定
	void SetParentID(int nParent) { m_nParent = nParent; }
	void SetParentMtx(D3DXMATRIX pParent) { m_mtxParent = pParent; }
	void SetDisplay(bool bDesplay) { m_bDisplay = bDesplay; }	// 表示するかどうか

	void SetMotion(int nMotion);

	// 位置取得
	X GetBasicX() {
		return m_xBasic;
	}
	D3DXVECTOR3 GetBasicPos() { return m_xBasic.pos; }
	D3DXVECTOR3 GetBasicRot() { return m_xBasic.rot; }
	D3DXVECTOR3 GetBasicSiz() { return m_xBasic.siz; }

	// 追加位置
	X GetAddX() {
		return m_xOffset;
	}
	D3DXVECTOR3 GetAddPos() { return m_xOffset.pos; }
	D3DXVECTOR3 GetAddRot() { return m_xOffset.rot; }
	D3DXVECTOR3 GetAddSiz() { return m_xOffset.siz; }

	// データ取得
	int GetParentID() { return m_nParent; }				// 親ID取得
	D3DXMATRIX GetParentMtx() { return m_mtxParent; }	// 親マトリクス取得
	bool GetDisplay() { return m_bDisplay; }			// 表示するかどうか
	CNowMotion* GetNowMotion() { return m_pNowMotion; }	// 現在モーション

	//void SetDoMotion(bool bDoMotion) { m_bDoMotion = bDoMotion; }	// モーションするか設定

	LPDIRECT3DTEXTURE9 m_pToonMap;  // トゥーンマップ

private:

	X m_xBasic;			// 基本位置
	X m_xOffset;			// 追加位置
	X m_xMove;			// 動き

	int m_nParent;			// 親ID
	D3DXMATRIX m_mtxParent;	// 親マトリクス

	bool m_bDisplay;	// 表示するかどうか

	CNowMotion* m_pNowMotion;	// 現在モーション

	//bool m_bDoMotion;	// モーションするかどうか

	LPD3DXEFFECT m_pEffect;     // シェーダー
	std::string m_fxFilePath;             // 読み込む.fxファイルのパス

};

// モーション管理
class CObjectMotion : public CObject
{
public:
	CObjectMotion();
	virtual ~CObjectMotion()		override;
	virtual HRESULT Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	
	// 現在の位置設定
	void SetX(X x) { m_x = x; }
	void SetPos(D3DXVECTOR3 pos) { m_x.pos = pos; }// 位置設定
	void SetRot(D3DXVECTOR3 rot) { m_x.rot = rot; }// 向き設定
	void SetSiz(D3DXVECTOR3 siz) { m_x.siz = siz; }// 大きさ設定

	X GetX() { return m_x; }
	D3DXVECTOR3 GetPos() { return m_x.pos; }// 運動量設定
	D3DXVECTOR3 GetRot() { return m_x.rot; }// 回転量設定
	D3DXVECTOR3 GetSiz() { return m_x.siz; }// 膨張量設定

	void AddX(X x) { m_x += x; }
	void AddPos(D3DXVECTOR3 pos) { m_x.pos += pos; }// 位置設定
	void AddRot(D3DXVECTOR3 rot) { m_x.rot += rot; }// 向き設定
	void AddSiz(D3DXVECTOR3 siz) { m_x.siz += siz; }// 大きさ設定



	// 1f前の位置設定
	void SetOldX(X x) { m_xold = x; }
	void SetOldPos(D3DXVECTOR3 pos) { m_xold.pos = pos; }// 位置設定
	void SetOldRot(D3DXVECTOR3 rot) { m_xold.rot = rot; }// 向き設定
	void SetOldSiz(D3DXVECTOR3 siz) { m_xold.siz = siz; }// 大きさ設定

	X GetOldX() { return m_xold; }
	D3DXVECTOR3 GetOldPos() { return m_xold.pos; }// 運動量設定
	D3DXVECTOR3 GetOldRot() { return m_xold.rot; }// 回転量設定
	D3DXVECTOR3 GetOldSiz() { return m_xold.siz; }// 膨張量設定

	void AddOldX(X x) { m_xold += x; }
	void AddOldPos(D3DXVECTOR3 pos) { m_xold.pos += pos; }// 位置設定
	void AddOldRot(D3DXVECTOR3 rot) { m_xold.rot += rot; }// 向き設定
	void AddOldSiz(D3DXVECTOR3 siz) { m_xold.siz += siz; }// 大きさ設定


	CMotion* GetMotion(int nNum) { return m_pMotion[nNum]; }// モーションデータ取得

	int GetNumParts() { return m_nParts; }
	CParts* GetParts(int nNum) { return m_pParts[nNum]; }	// パーツ取得
	static CObjectMotion* creat(const char* FileName);
	static CObjectMotion* creat(string FileName);

protected:
	bool Load(const char* aFileName);	// モーション読み込み
	void SetMotion(int nMotion);	// モーション設定

	virtual int GetNextMotion() { return 0; };	// 次取得
private:
	void creatMotion();// モーション生成
private:

	X m_x;             // トランスフォーム
	int m_nModel;							// モデル数

	int m_nNumMotion;						// モーション数
	CMotion* m_pMotion[MAX_MOTION];	// モーションデータ

	int m_nParts;				// パーツ数
	CParts* m_pParts[MAX_PARTS];

	int m_nNextMotion;
	X m_xold;		// 1f前位置
	D3DXMATRIX m_mtxWorld;	// ワールドマトリクス
};




#endif // !_MOTION_H_