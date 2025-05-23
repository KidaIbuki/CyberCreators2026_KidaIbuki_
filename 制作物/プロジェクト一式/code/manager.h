//=================================
// 
// マネージャ　manager.h
// Auther kida ibuki 
// 
//==================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "pch.h"   // プリコンパイル済みヘッダー
#include "renderer.h"      // レンダラー
#include "camera.h"        // カメラ
#include "light.h"         // ライト
#include "input.h"         // 入力
#include "sound.h"         // サウンド
#include "fog.h"           // フォグ
#include "scene.h"         // シーン
#include "fade.h"          // フェード

class CManager;

// マネージャクラスの定義
class CManager
{
private:
	CManager();															//コンストラクタ
public:
	~CManager();														//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);			//初期設定
	void Uninit();														//終了処理
	void Update();														//更新処理
	void Draw();	                                                    //描画処理

	//シングルトン
	static CManager* GetInstance()
	{
		static CManager instance; // 静的インスタンス
		return &instance;
	}
	
	CRenderer* GetRenderer();			// レンダラーの取得
	CCamera* GetCamera();				// カメラの取得
	CLight* GetLight();					// ライトの取得
	CInputKeyboard* GetKeyboard();	    // キーボード入力の取得
	CInputJoypad* GetJoypad();		    // コントローラー入力の取得
	CInputMouse* GetMouse();		    // マウス入力の取得

	void SetMode(CScene::MODE mode);	// シーンの取得
	void SetPause(bool bPause) { m_bPause = bPause; }   // ポーズを設定
	void SetSwitch(bool bSwitch) { m_bSwitchimg = bSwitch; }   // ポーズを設定

	CScene* GetScene();

	CFade* GetFade();					// フェードの取得
	CSound* GetSound();                 // サウンドの取得
	CFog* GetFog();                     // フォグ取得
	bool GetPause() { return m_bPause; }   //ポーズ中か取得
	bool GetSwitching() { return m_bSwitchimg; }   // 切り替えたか取得

private:
	CRenderer* m_pRenderer;				// レンダラー情報
	CCamera* m_pCamera;					// ビュー情報
	CLight* m_pLight;                   // ライト情報
	CInputKeyboard* m_pKeyboard;		// キーボード情報
	CInputJoypad* m_pKeyJoypad;		    // コントローラー情報
	CInputMouse* m_pKeyMouse;		    // マウス情報
										   
	CScene* m_pScene;					// シーン情報

	CFade* m_pFade;						// フェードの情報
	CScene::MODE m_mode;
	CSound* m_pSound;                   // サウンドの情報
	CFog* m_pFog;                       // フォグ情報
	bool m_bPause;
	bool m_bSwitchimg;    // 通常の弾とホーミングの切り替え


};

#endif 
