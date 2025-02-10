//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA     クラス化 : ibuki kida
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"   //　メイン
#include "renderer.h"  // レンダラー
#include "pch.h"       // プリコンパイル済みヘッダー

class CSound
{
public:
	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// タイトルbgm
		SOUND_LABEL_BGM001,		    // チュートリアルbgm
		SOUND_LABEL_BGM002,		    // ゲームbgm
		SOUND_LABEL_BGM003,		    // リザルトbgm
		SOUND_LABEL_SE_SHOT,        // PL弾SE
		SOUND_LABEL_SE_DAMAGE,      // PLダメージSE
		SOUND_LABEL_SE_SELECT,      // ポーズ中選択SE
		SOUND_LABEL_SE_OK,          // ポーズ中決定SE
		SOUND_LABEL_SE_OPEN,        // ポーズ開く
		SOUND_LABEL_SE_E_DAMAGE,    // ENダメージSE
		SOUND_LABEL_SE_EXPLOSION,   // 墜落音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif
