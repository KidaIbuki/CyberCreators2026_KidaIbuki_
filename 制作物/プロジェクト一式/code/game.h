//=================================
// 
// �Q�[�������N���X�@gaem.h
//outher kida ibuki 
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
};

#endif