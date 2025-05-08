//=================================
// 
// �Q�[�������N���X�@gaem.h
// Auther kida ibuki 
// 
//==================================
#ifndef _GAME_H_
#define _GAME_H_

#include "game.h"
#include "pause_select.h"  // �|�[�Y
#include "scene.h"

#define NUM_OBJECT_NUM (512)// �z�u���������f���̐�
#define NUM_ENEMY (100)  // �z�u�������G�̐�

class CGame :public CScene
{
public:
    typedef enum
    {
        CONTINUE = 0,
        RETRY,
        QUIT,
        MAX
    }SELECT;
    CGame();			//�R���X�g���N�^
    ~CGame()override;			//�f�X�g���N�^
    HRESULT Init()override;
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����

    void Draw()override;		//�`�揈��
    static CGame* Create();     //����

    // �u���b�N�̊O���t�@�C���o��
    void SetModel_File();
    void SetEnemy_File();  // �G�̊O���t�@�C���o��

private:
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];
    ENEMY_FILENAME g_aEnemyData[NUM_ENEMY];
    bool m_bUseBoss;    // �{�X���g���Ă��邩
    int m_nFrame;       // �{�X�o���̃t���[��
    int m_nSelect;           // �|�[�Y�̃Z���N�g�ϐ�
    CPause_Select* m_pPause_Select[MAX];
    int m_nFrameTime;
    int m_nCnt;
    int m_nCntCreateMap;    // �}�b�v�̐����J�E���g
    int m_nCntCreateMap1;    // �}�b�v�̐����J�E���g

    static constexpr float LIFEPOS_X = 1200.0f;    // ���C�t�ʒu
    static constexpr float LIFEPOS_Y = 520.0f;    // ���C�t�ʒu
    static constexpr float UIPOS_X = 1200.0f;    // UI�ʒu
    static constexpr float UIPOS_Y = 320.0f;    // UI�ʒu
    static constexpr int FRAMETIME = 20;       // �t���[���̃^�C��

    static constexpr float PAUSEPOS_FOR = 80.0f;    // �|�[�Y�ʒu�𕡐��ɂ���
    static constexpr float PAUSEPOS_Y = 300.0f;    // �|�[�Y�ʒu
    static constexpr float PAUSESIZE_X = 200.0f;   // �|�[�Y�T�C�Y
    static constexpr float PAUSESIZE_Y = 50.0f;    // �|�[�Y�T�C�Y

    static constexpr float LEAVE = 810.0f;    // �|�[�Y�T�C�Y

    static constexpr float BGPOS_X_1 = 350.0f;   // �{�X�̈ʒu
    static constexpr float BGPOS_Y_1 = 175.0f;	 // �{�X�̈ʒu
    static constexpr float BGPOS_Z_1 = 7000.0f;	 // �{�X�̈ʒu
    static constexpr float BGPOS_Z_2 = 13000.0f; // �{�X�̈ʒu

    static constexpr float BOSSPOS_X = 200.0f;

    static constexpr float BLOCKPOS_X_1 = 170.0f;  // �u���b�N�̈ʒu
    static constexpr float BLOCKPOS_X_2 = 340.0f;  // �u���b�N�̈ʒu
    static constexpr float BLOCKPOS_Y_1 = 280.0f;  // �u���b�N�̈ʒu
    static constexpr float BLOCKPOS_Y_2 = 140.0f;  // �u���b�N�̈ʒu
    static constexpr float BLOCK_DIVITE = 330.0f;  // �u���b�N�𗣂��Ă���

};

#endif