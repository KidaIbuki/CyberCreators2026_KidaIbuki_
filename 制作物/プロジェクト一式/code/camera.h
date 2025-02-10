//=================================
// 
//�J�����N���X�@camera.h
//outher kida ibuki 
// 
//==================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"   // ���C��
#include "objectX.h"  // �I�u�W�F�N�gX
#include "playerM.h"   // �v���C���[
#include "enemyX.h"    // �G�l�~�[
#include "scene.h"   // �V�[��

// �J�����p�}�N����`
#define PERSPECTIVE (D3DXVECTOR3(0.0f,100.0f,-250.0f))  // ���_��Z��
#define POINT_OF_INTEREST (D3DXVECTOR3(0.0f,0.0f,40.0f)) // �����_��Z��
#define DISTANCE_LEFT (100)     // �����̍���(sqrtf�̂��)
#define DISTANCE_RIGHT (250)    // �����̉E��(sqrtf�̂��)
#define SCALEDIS (2.0f)  // �����̔{��
//�O���錾
class CObjectX;

//�J�����N���X�̒�`
class CCamera
{
public:
	// �J�����̌���
	typedef enum
	{
		ANGLE_FRONT = 0,
		ANGLE_RIGHT,
		ANGLE_MAX
	}ANGLE;
	CCamera();					//�R���X�g���N�^
	~CCamera();					//�f�X�g���N�^
	HRESULT Init();				//�����ݒ�
	void Uninit();				//�I������
	void Update();				//�X�V����
	void SetCamera();			//�J�����ݒ�

	void ResetCamera();
	void TitleCamera();
	void DebugCamera(); // �J�����ʒu���ߗp
	D3DXVECTOR3 GetRot() { return m_rot; }			//�������擾
	D3DXVECTOR3 GetPosR() { return m_posR; }		//�����_�̎擾
	D3DXVECTOR3 GetPosV() { return m_posV; }		//���_�̎擾

	void SetPos(D3DXVECTOR3 pos);
	void SetShake(int shakeFrame, float shakeVolume);
	void Controller();
private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;         // �����_
	D3DXVECTOR3 m_vecU;			// �����
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_move;         // �ړ���
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;		// �r���[�s��
	float m_fScaleDis;
	float m_fDistance;		// ����
	D3DXVECTOR3 m_rotMove;  // rot�p��move
	ANGLE m_Front;        // �O�������Ă��邩�ǂ���
	
	int m_nFrame;         // ������ς���t���[��
	int m_nCntFrame;      // ��̃t���[�����J�E���g����
	bool m_bControll;     // �J�����̒Ǐ]�̃I���I�t
	int m_nShakeFrame;     // �h�炷�t���[��
	int m_nShakeVolume;  // �h��̗�

};

#endif
