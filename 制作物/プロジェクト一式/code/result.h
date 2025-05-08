//=================================
// 
// リザルトクラス　result.h
// Auther kida ibuki 
// 
//==================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include <string>
#include "object2D.h"  // オブジェクト2D

#define MAX_CNT (2)  // 桁数の最大数

class CResult :public CScene
{
public:
    CResult();			//コンストラクタ
    ~CResult()override;			//デストラクタ
    HRESULT Init()override;		//初期設定
    void Uninit()override;      //終了処理
    void Update()override;      //更新処理

    void Draw()override;		//描画処理
    static CResult* Create();     //生成

private:
};


#endif