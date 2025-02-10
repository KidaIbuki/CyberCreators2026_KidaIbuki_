//=================================
// 
// ゲーム処理クラス　gaem.h
//outher kida ibuki 
// 
//==================================
#ifndef _GAME_H_
#define _GAME_H_

#include "game.h"
#include "pause_select.h"  // ポーズ
#include "scene.h"

#define NUM_OBJECT_NUM (512)// 配置したいモデルの数
#define NUM_ENEMY (100)  // 配置したい敵の数

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
    CGame();			//コンストラクタ
    ~CGame()override;			//デストラクタ
    HRESULT Init()override;
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理

    void Draw()override;		//描画処理
    static CGame* Create();     //生成

    // ブロックの外部ファイル出力
    void SetModel_File();
    void SetEnemy_File();  // 敵の外部ファイル出力

private:
    MODEL_FILENAME m_gModelData[NUM_OBJECT_NUM];
    ENEMY_FILENAME g_aEnemyData[NUM_ENEMY];
    bool m_bUseBoss;    // ボスが使われているか
    int m_nFrame;       // ボス出現のフレーム
    int m_nSelect;           // ポーズのセレクト変数
    CPause_Select* m_pPause_Select[MAX];
    int m_nFrameTime;
    int m_nCnt;
    int m_nCntCreateMap;    // マップの生成カウント
    int m_nCntCreateMap1;    // マップの生成カウント
};

#endif