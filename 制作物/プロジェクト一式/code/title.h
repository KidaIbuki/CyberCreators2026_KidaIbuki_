//=================================
// 
// �^�C�g���N���X�@title.h
//outher kida ibuki 
// 
//==================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"  // �V�[��
#include <string>
#include "save_object.h"

#define NUM_OBJECT_NUM (512)// �z�u���������f���̐�
#define POSITION_NUM_1 (300.0f)  // �`���[�g���A���p�e�N�X�`��1�̕\���ʒu
#define POSITION_NUM_2 (303.0f)  // �`���[�g���A���p�e�N�X�`��1�̕\���ʒu

#define POSITION_NUM_3 (1300.0f)  // �`���[�g���A���p�e�N�X�`��2�̕\���ʒu
#define POSITION_NUM_4 (1303.0f)  // �`���[�g���A���p�e�N�X�`��2�̕\���ʒu

#define POSITION_NUM_5 (2300.0f)  // �`���[�g���A���p�e�N�X�`��3�̕\���ʒu
#define POSITION_NUM_6 (2303.0f)  // �`���[�g���A���p�e�N�X�`��3�̕\���ʒu

#define POSITION_NUM_7 (3300.0f)  // �`���[�g���A���p�e�N�X�`��4�̕\���ʒu
#define POSITION_NUM_8 (3303.0f)  // �`���[�g���A���p�e�N�X�`��4�̕\���ʒu

#define POSITION_NUM_9 (4300.0f)  // ��ʑJ�ڈʒu
#define POSITION_NUM_10 (4303.0f)  // ��ʑJ�ڈʒu

class CTitle:public CScene
{
public:
    class CTitleSaveObject:public CSaveObject
    {// �ۑ����Ă��������I�u�W�F�N�g������
    public:
        CTitleSaveObject() = delete;
        CTitleSaveObject(CObject* pObject);
        ~CTitleSaveObject();
        HRESULT Init();
        void Uninit();
        void Update();
        void Draw();
    };
    CTitle();			//�R���X�g���N�^
    ~CTitle()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����

    void Draw()override;		//�`�揈��
    static CTitle* Create();     //����
private:
    void SetModel_File_Title();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

};

class CTitleSecond :public CTitle
{
public:
    class CTitleSecondSaveObject :public CSaveObject
    {// �ۑ����Ă��������I�u�W�F�N�g������
    public:
        CTitleSecondSaveObject() = delete;
        CTitleSecondSaveObject(CObject* pObject);
        ~CTitleSecondSaveObject();
        HRESULT Init();
        void Uninit();
        void Update();
        void Draw();
    };

    // ���݂̃v���C���[�̈ʒu�Ƀe�N�X�`���𒣂�
    typedef enum
    {
        POSITION_NONE = 0,
        POSITION_1,
        POSITION_2,
        POSITION_3,
        POSITION_4,
        POSITION_MAX
    }POSITION;
    CTitleSecond();			//�R���X�g���N�^
    ~CTitleSecond()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����

    void Draw()override;		//�`�揈��
    static CTitleSecond* Create();     //����

private:
    void SetTitle_File();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

    POSITION m_Position;
    int m_nFrame;       // �{�X�o���̃t���[��

};


#endif