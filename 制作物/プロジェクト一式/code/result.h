//=================================
// 
// ���U���g�N���X�@result.h
//outher kida ibuki 
// 
//==================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include <string>
#include "object2D.h"  // �I�u�W�F�N�g2D

#define MAX_CNT (2)  // �����̍ő吔

class CResult :public CScene
{
public:
    CResult();			//�R���X�g���N�^
    ~CResult()override;			//�f�X�g���N�^
    HRESULT Init()override;		//�����ݒ�
    void Uninit()override;      //�I������
    void Update()override;      //�X�V����

    void Draw()override;		//�`�揈��
    static CResult* Create();     //����

private:
};


#endif