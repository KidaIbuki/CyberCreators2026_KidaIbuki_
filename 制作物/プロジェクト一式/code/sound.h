//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA     �N���X�� : ibuki kida
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"   //�@���C��
#include "renderer.h"  // �����_���[
#include "pch.h"       // �v���R���p�C���ς݃w�b�_�[

class CSound
{
public:
	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// �^�C�g��bgm
		SOUND_LABEL_BGM001,		    // �`���[�g���A��bgm
		SOUND_LABEL_BGM002,		    // �Q�[��bgm
		SOUND_LABEL_BGM003,		    // ���U���gbgm
		SOUND_LABEL_SE_SHOT,        // PL�eSE
		SOUND_LABEL_SE_DAMAGE,      // PL�_���[�WSE
		SOUND_LABEL_SE_SELECT,      // �|�[�Y���I��SE
		SOUND_LABEL_SE_OK,          // �|�[�Y������SE
		SOUND_LABEL_SE_OPEN,        // �|�[�Y�J��
		SOUND_LABEL_SE_E_DAMAGE,    // EN�_���[�WSE
		SOUND_LABEL_SE_EXPLOSION,   // �ė���
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
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};

#endif
