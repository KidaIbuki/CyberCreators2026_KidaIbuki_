//=================================
// 
// 有向境界ボックス クラス　obb.cpp
//outher kida ibuki 
// 
//==================================

#include "obb.h"

// [処理の仕組み]
// 1.OBBの定義
//   ・OBBは中心座標(center)
//   ・OBBのローカル軸(axes)
//   ・OBBの各軸方向の半幅(halfWidths)
//     で定義
// 2.頂点座標の計算
//   ・GetVector(int index)により、OBBの8頂点を計算
// 3.衝突判定(SAT)
//   ・分離軸定理(SAT)を用いた判定
//   ・15本の判定軸(6本のOBB軸 + 9本の外積軸)
//   ・各軸の投影して分離があるか確認
// 4.投影距離の計算
//   ・ProjectOntoAxisにより、OBBの各軸を投影し、長さを取得

//========================================
// コンストラクタ
//========================================
OBB::OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfWidths, const D3DXMATRIX& rotationMatrix)
{
	this->center = center;
	this->halfWidths = halfWidths;

	// 回転行列からローカル軸を設定
	axes[0] = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);  // x軸
	axes[1] = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);  // y軸
	axes[2] = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);  // z軸

}
//========================================
// 頂点を取得
//========================================
D3DXVECTOR3 OBB::GetVertex(int index) const
{
	D3DXVECTOR3 vertex = center;

	// 1.index のビット演算を利用し、各軸の正負方向を決定
	int signX = (index & 1) ? 1 : -1;
	int signY = (index & 2) ? 1 : -1;
	int signZ = (index & 4) ? 1 : -1;

	// 2.OBBの中心(center)に対し、各軸方向(axes[0],axes[1],axes[2])の影響を加算
	vertex += axes[0] * (signX * halfWidths.x);
	vertex += axes[1] * (signY * halfWidths.y);
	vertex += axes[2] * (signZ * halfWidths.z);

	return vertex;
}
//========================================
// OBB同士の衝突判定
//========================================
bool OBB::CheckOverlap(const OBB& other) const
{
    D3DXVECTOR3 axesToTest[15];
    int axisIndex = 0;

	// 1.判定する軸のリストを作成
	//   ・this OBBの3軸(axes[0], axes[1], axes[2])
    //   ・other OBBの3軸(other.axes[0], other.axes[1], other.axes[2])
    //   ・両OBBの軸のクロス積(外積)から9つの新しい軸を計算

    // 自身と他のOBBの軸
    for (int i = 0; i < 3; ++i) 
    {
        axesToTest[axisIndex++] = axes[i];
        axesToTest[axisIndex++] = other.axes[i];
    }

    // 軸のクロス積
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) 
        {
            D3DXVECTOR3 crossAxis;
            D3DXVec3Cross(&crossAxis, &axes[i], &other.axes[j]);
            if (D3DXVec3Length(&crossAxis) > 0.0001f)
            { // 有効な軸
                axesToTest[axisIndex++] = crossAxis;
            }
        }
    }

	// 2.各軸に対して分離軸のチェック
	// this OBBとother OBBをaxisに投影し、その合計投影距離をと中心間距離を比較
	
    // 中心間の距離
    D3DXVECTOR3 t = other.center - center;

    // 分離軸ごとに判定
    for (int i = 0; i < axisIndex; ++i)
    {
        const D3DXVECTOR3& axis = axesToTest[i];
        D3DXVECTOR3 normAxis;
        D3DXVec3Normalize(&normAxis, &axis);

        // 各OBBを軸に投影
        float projection1 = ProjectOntoAxis(normAxis);
        float projection2 = other.ProjectOntoAxis(normAxis);
        float centerDistance = fabs(D3DXVec3Dot(&t, &normAxis));

        // 投影が分離している場合
        if (centerDistance > projection1 + projection2)
        {
			// 分離が確認されたらfalseを返す(衝突していない)
            return false;
        }
    }
	// 3.すべての軸で分離が確認できなかったらtrueを返す(衝突している)
    return true;  // 分離していない -> 衝突
}
//========================================
// 指定軸への投影距離を計算
//========================================
float OBB::ProjectOntoAxis(const D3DXVECTOR3& axis) const
{
	// 1.OBBの各軸(axes[0],axes[1],axes[2])をaxisに投影
    return fabs(D3DXVec3Dot(&axes[0], &axis) * halfWidths.x) +
        fabs(D3DXVec3Dot(&axes[1], &axis) * halfWidths.y) +
        fabs(D3DXVec3Dot(&axes[2], &axis) * halfWidths.z);
	// 2.各軸ごとのスカラー値を合計し、全体の投影距離を計算
}
//========================================
// コンストラクタ
//========================================
Sphere::Sphere(const D3DXVECTOR3& center, float radius)
{
	this->center = center;
	this->radius = radius;
}

//========================================
// 球同士の衝突判定
//========================================
bool Sphere::CheckOverlap(const Sphere& other) const
{
	D3DXVECTOR3 difference = center - other.center;
    // 2つの中心点の距離を計算
	float distanceSquared = D3DXVec3LengthSq(&difference);    // 半径の合計と比較
    float radiusSum = radius + other.radius;

    return distanceSquared <= (radiusSum * radiusSum);
}
//========================================
// 球とOBBの衝突判定
//========================================
bool Sphere::CheckOverlap(const OBB& box) const
{
    D3DXVECTOR3 closestPoint = box.GetCenter();  // OBB の中心から始める
    D3DXVECTOR3 sphereToBox = center - box.GetCenter();
    for (int i = 0; i < 3; ++i)
    {
		D3DXVECTOR3 axis = box.GetAxis(i);

		float distance = D3DXVec3Dot(&sphereToBox, &axis);
        // OBB の範囲内に制限
        if (distance > box.GetHalfwidths()[i])
        {
            distance = box.GetHalfwidths()[i];
        }
        else if (distance < -box.GetHalfwidths()[i])
        {
            distance = -box.GetHalfwidths()[i];
        }
        closestPoint += box.GetAxis(i) * distance;
    }

    // 最近接点と球の中心の距離を比較
    D3DXVECTOR3 diff = center - closestPoint;
    return D3DXVec3LengthSq(&diff) <= (radius * radius);
}
//=============================================
// OBBのラインを描画(デバック用)
//=============================================
void OBB::DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color)
{

	// OBBの8つの頂点を計算
	D3DXVECTOR3 corners[8];
	for (int i = 0; i < 8; i++) {
		corners[i] = center;
		corners[i] += axis[0] * (halfSize.x * ((i & 1) ? 1.0f : -1.0f));
		corners[i] += axis[1] * (halfSize.y * ((i & 2) ? 1.0f : -1.0f));
		corners[i] += axis[2] * (halfSize.z * ((i & 4) ? 1.0f : -1.0f));
	}

	// OBB のエッジを結ぶラインリスト（12本の線）
	int indices[] = {
		0,1,  1,3,  3,2,  2,0,  // 前面
		4,5,  5,7,  7,6,  6,4,  // 背面
		0,4,  1,5,  2,6,  3,7   // 前後をつなぐ線
	};

	Vertex lines[24];
	for (int i = 0; i < 12; i++) {
		lines[i * 2] = { corners[indices[i * 2]], color };
		lines[i * 2 + 1] = { corners[indices[i * 2 + 1]], color };
	}

	// 頂点フォーマット設定
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ライン描画
	device->DrawPrimitiveUP(D3DPT_LINELIST, 12, lines, sizeof(Vertex));
}

//=============================================
// 球体のラインを描画(デバック用)
//=============================================
void Sphere::DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color)
{
	int numLines = (slices + 1) * stacks + (stacks + 1) * slices;  // 緯度方向 + 経度方向
	int numVertices = numLines * 2;  // 各ラインに2つの頂点

	// 頂点配列を確保
	Vertex* lines = new Vertex[numVertices];

	// インデックスの初期化
	int index = 0;
	// 経度方向（縦ライン）
	for (int i = 0; i <= slices; i++) 
	{
		// θ（theta）は 0° から 360°（0 から 2π）まで slices 分割する。
		float theta = (float)i / slices * 2.0f * D3DX_PI;
		// 緯度方向（横ライン）
		for (int j = 0; j < stacks; j++)
		{
			// 各 φ(ファイ) に対して、0° から 360° まで θ を回転させて横のラインを生成。
			float phi1 = (float)j / stacks * D3DX_PI - (D3DX_PI / 2.0f);
			float phi2 = (float)(j + 1) / stacks * D3DX_PI - (D3DX_PI / 2.0f);

			// 球面座標の計算
			lines[index++] = { center + D3DXVECTOR3(radius * cosf(phi1) * cosf(theta),
													 radius * sinf(phi1),
													 radius * cosf(phi1) * sinf(theta)), color };

			lines[index++] = { center + D3DXVECTOR3(radius * cosf(phi2) * cosf(theta),
													 radius * sinf(phi2),
													 radius * cosf(phi2) * sinf(theta)), color };
		}
	}
	// 頂点フォーマット設定
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ライン描画
	device->DrawPrimitiveUP(D3DPT_LINELIST, numLines, lines, sizeof(Vertex));

	delete[] lines;
}