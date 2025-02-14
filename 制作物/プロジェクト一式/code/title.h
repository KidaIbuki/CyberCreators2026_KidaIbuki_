//=================================
// 
// タイトルクラス　title.h
//outher kida ibuki 
// 
//==================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"  // シーン
#include <string>
#include "save_object.h"

#define NUM_OBJECT_NUM (512)// 配置したいモデルの数
#define POSITION_NUM_1 (300.0f)  // チュートリアル用テクスチャ1の表示位置
#define POSITION_NUM_2 (303.0f)  // チュートリアル用テクスチャ1の表示位置

#define POSITION_NUM_3 (1300.0f)  // チュートリアル用テクスチャ2の表示位置
#define POSITION_NUM_4 (1303.0f)  // チュートリアル用テクスチャ2の表示位置

#define POSITION_NUM_5 (2300.0f)  // チュートリアル用テクスチャ3の表示位置
#define POSITION_NUM_6 (2303.0f)  // チュートリアル用テクスチャ3の表示位置

#define POSITION_NUM_7 (3300.0f)  // チュートリアル用テクスチャ4の表示位置
#define POSITION_NUM_8 (3303.0f)  // チュートリアル用テクスチャ4の表示位置

#define POSITION_NUM_9 (4300.0f)  // 画面遷移位置
#define POSITION_NUM_10 (4303.0f)  // 画面遷移位置

class CTitle:public CScene
{
public:
    class CTitleSaveObject:public CSaveObject
    {// 保存しておきたいオブジェクトを入れる
    public:
        CTitleSaveObject() = delete;
        CTitleSaveObject(CObject* pObject);
        ~CTitleSaveObject();
        HRESULT Init();
        void Uninit();
        void Update();
        void Draw();
    };
    CTitle();			//コンストラクタ
    ~CTitle()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理

    void Draw()override;		//描画処理
    static CTitle* Create();     //生成
private:
    void SetModel_File_Title();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

    // UIの位置
    static const float UI_POS_X;
    static const float UI_POS_Y;
    static const int TIMECNT;

};

class CTitleSecond :public CTitle
{
public:
    class CTitleSecondSaveObject :public CSaveObject
    {// 保存しておきたいオブジェクトを入れる
    public:
        CTitleSecondSaveObject() = delete;
        CTitleSecondSaveObject(CObject* pObject);
        ~CTitleSecondSaveObject();
        HRESULT Init();
        void Uninit();
        void Update();
        void Draw();
    };

    // 現在のプレイヤーの位置にテクスチャを張る
    typedef enum
    {
        POSITION_NONE = 0,
        POSITION_1,
        POSITION_2,
        POSITION_3,
        POSITION_4,
        POSITION_MAX
    }POSITION;
    CTitleSecond();			//コンストラクタ
    ~CTitleSecond()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理

    void Draw()override;		//描画処理
    static CTitleSecond* Create();     //生成

private:
    void SetTitle_File();
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];

    POSITION m_Position;
    int m_nFrame;       // ボス出現のフレーム

    static const int TIMECNT_2;
    static const float TARGET_POS_Z;
    static const float UI_POS_X_2;
    static const float UI_POS_Y_2;



};


#endif