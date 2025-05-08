//=================================
// 
// ゲーム処理クラス　gaem.h
// Auther kida ibuki 
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

    static constexpr float LIFEPOS_X = 1200.0f;    // ライフ位置
    static constexpr float LIFEPOS_Y = 520.0f;    // ライフ位置
    static constexpr float UIPOS_X = 1200.0f;    // UI位置
    static constexpr float UIPOS_Y = 320.0f;    // UI位置
    static constexpr int FRAMETIME = 20;       // フレームのタイム

    static constexpr float PAUSEPOS_FOR = 80.0f;    // ポーズ位置を複数にする
    static constexpr float PAUSEPOS_Y = 300.0f;    // ポーズ位置
    static constexpr float PAUSESIZE_X = 200.0f;   // ポーズサイズ
    static constexpr float PAUSESIZE_Y = 50.0f;    // ポーズサイズ

    static constexpr float LEAVE = 810.0f;    // ポーズサイズ

    static constexpr float BGPOS_X_1 = 350.0f;   // ボスの位置
    static constexpr float BGPOS_Y_1 = 175.0f;	 // ボスの位置
    static constexpr float BGPOS_Z_1 = 7000.0f;	 // ボスの位置
    static constexpr float BGPOS_Z_2 = 13000.0f; // ボスの位置

    static constexpr float BOSSPOS_X = 200.0f;

    static constexpr float BLOCKPOS_X_1 = 170.0f;  // ブロックの位置
    static constexpr float BLOCKPOS_X_2 = 340.0f;  // ブロックの位置
    static constexpr float BLOCKPOS_Y_1 = 280.0f;  // ブロックの位置
    static constexpr float BLOCKPOS_Y_2 = 140.0f;  // ブロックの位置
    static constexpr float BLOCK_DIVITE = 330.0f;  // ブロックを離しておく

};

#endif