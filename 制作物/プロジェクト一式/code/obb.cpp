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
// 8つの頂点を取得
//=============================================
std::vector<D3DXVECTOR3> OBB::GetCorners() const
{
    std::vector<D3DXVECTOR3> corners;
    corners.reserve(8); // 頂点は8つ

    D3DXVECTOR3 center = this->center;
    const D3DXVECTOR3& A0 = this->axes[0];
    const D3DXVECTOR3& A1 = this->axes[1];
    const D3DXVECTOR3& A2 = this->axes[2];
    const D3DXVECTOR3& h = this->halfWidths;

    // 8頂点の計算
    for (int i = 0; i < 8; ++i) {
        D3DXVECTOR3 corner = center;
        corner += A0 * h.x * ((i & 1) ? 1.0f : -1.0f);
        corner += A1 * h.y * ((i & 2) ? 1.0f : -1.0f);
        corner += A2 * h.z * ((i & 4) ? 1.0f : -1.0f);
        corners.push_back(corner);
    }

    return corners;
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
//=========================================
// コンストラクタ
//=========================================
Capsule::Capsule(const D3DXVECTOR3& center, float radius, float height, const D3DXMATRIX& rotationMatrix)
    : center(center), radius(radius), height(height), rotationMatrix(rotationMatrix) {}

//=========================================
// **カプセルの両端を取得**
//=========================================
void Capsule::GetEndpoints(D3DXVECTOR3& outStart, D3DXVECTOR3& outEnd) const
{
    D3DXVECTOR3 localStart(0, -height * 0.5f, 0);
    D3DXVECTOR3 localEnd(0, height * 0.5f, 0);

    // 回転を適用
    D3DXVec3TransformCoord(&outStart, &localStart, &rotationMatrix);
    D3DXVec3TransformCoord(&outEnd, &localEnd, &rotationMatrix);

    // ワールド座標へ
    outStart += center;
    outEnd += center;
}

//=========================================
// **カプセルの描画**
//=========================================
void Capsule::DrawCapsule(IDirect3DDevice9* device, int segments, D3DXCOLOR color) const
{
    std::vector<Vertex> vertices;
    D3DXVECTOR3 start, end;
    GetEndpoints(start, end);

    // 軸方向
    D3DXVECTOR3 axis = end - start;
    if (D3DXVec3LengthSq(&axis) < 0.0001f)
    {
        return;
    }
    D3DXVec3Normalize(&axis, &axis);

    // 直交する基準ベクトル
    D3DXVECTOR3 up = fabs(axis.y) < 0.99f ? D3DXVECTOR3(0, 1, 0) : D3DXVECTOR3(1, 0, 0);
    D3DXVECTOR3 right;
    D3DXVec3Cross(&right, &up, &axis);
    D3DXVec3Normalize(&right, &right);
    D3DXVECTOR3 newUp;
    D3DXVec3Cross(&newUp, &axis, &right);

    // **円柱部分**
    std::vector<D3DXVECTOR3> topCircle;
    std::vector<D3DXVECTOR3> bottomCircle;

    for (int i = 0; i < segments; ++i)
    {
        float theta = (D3DX_PI * 2.0f * i) / segments;
        float x = cosf(theta) * radius;
        float y = sinf(theta) * radius;
        D3DXVECTOR3 circlePoint = right * x + newUp * y;

        topCircle.push_back(end + circlePoint);
        bottomCircle.push_back(start + circlePoint);

        vertices.push_back({ start + circlePoint, color });
        vertices.push_back({ end + circlePoint, color });
    }

    // **円柱のリング**
    for (int i = 0; i < segments; ++i)
    {
        int next = (i + 1) % segments;
        vertices.push_back({ topCircle[i], color });
        vertices.push_back({ topCircle[next], color });
        vertices.push_back({ bottomCircle[i], color });
        vertices.push_back({ bottomCircle[next], color });
    }

    // **半球のリング**
    int hemisphereSegments = segments / 2;
    for (int i = 1; i <= hemisphereSegments; ++i)
    {
        float phi = (D3DX_PI * 0.5f * i) / hemisphereSegments; // 0 〜 90 度
        float sinPhi = sinf(phi);
        float cosPhi = cosf(phi);

        std::vector<D3DXVECTOR3> upperRing;
        std::vector<D3DXVECTOR3> lowerRing;

        for (int j = 0; j < segments; ++j)
        {
            float theta = (D3DX_PI * 2.0f * j) / segments;
            float x = cosf(theta) * sinPhi * radius;
            float y = sinf(theta) * sinPhi * radius;
            float z = cosPhi * radius;

            // **修正：z の符号を逆にする**
            upperRing.push_back(end + right * x + newUp * y + axis * z); // 修正
            lowerRing.push_back(start + right * x + newUp * y - axis * z); // 修正
        }

        for (int j = 0; j < segments; ++j)
        {
            int next = (j + 1) % segments;

            vertices.push_back({ upperRing[j], color });
            vertices.push_back({ upperRing[next], color });

            vertices.push_back({ lowerRing[j], color });
            vertices.push_back({ lowerRing[next], color });
        }
    }
    // **Direct3D で描画**
    device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
    device->DrawPrimitiveUP(D3DPT_LINELIST, vertices.size() / 2, vertices.data(), sizeof(Vertex));

}
//=========================================
// **カプセル vs OBB の衝突判定**
//=========================================
bool Capsule::CapsuleVsOBB_SAT(const OBB& obb) const
{
    D3DXVECTOR3 start, end;
    GetEndpoints(start, end);

    std::vector<D3DXVECTOR3> obbAxes = { obb.GetAxis(0), obb.GetAxis(1), obb.GetAxis(2) };
    D3DXVECTOR3 capsuleAxis = end - start;
    D3DXVec3Normalize(&capsuleAxis, &capsuleAxis);

    std::vector<D3DXVECTOR3> testAxes = obbAxes;
    testAxes.push_back(capsuleAxis);

    for (const auto& obbAxis : obbAxes)
    {
        D3DXVECTOR3 cross;
        D3DXVec3Cross(&cross, &obbAxis, &capsuleAxis);
        if (D3DXVec3LengthSq(&cross) > 1e-6f)
        {
            D3DXVec3Normalize(&cross, &cross);
            testAxes.push_back(cross);
        }
    }

    std::vector<D3DXVECTOR3> obbVertices = obb.GetCorners();
    std::vector<D3DXVECTOR3> capsulePoints = { start, end };

    for (const auto& axis : testAxes)
    {
        float minObb, maxObb, minCapsule, maxCapsule;
        ProjectOntoAxis(axis, obbVertices, minObb, maxObb);
        ProjectOntoAxis(axis, capsulePoints, minCapsule, maxCapsule);

        minCapsule -= radius;
        maxCapsule += radius;

        if (!Overlaps(minObb, maxObb, minCapsule, maxCapsule))
        {
            return false;
        }
    }

    return true;
}
//========================================
// 投影範囲を計算
//========================================
void ProjectOntoAxis(const D3DXVECTOR3& axis, const std::vector<D3DXVECTOR3>& points, float& outMin, float& outMax)
{
    outMin = outMax = D3DXVec3Dot(&points[0], &axis);  // 最初の点を基準に

    for (size_t i = 1; i < points.size(); ++i) {
        float projection = D3DXVec3Dot(&points[i], &axis);
        if (projection < outMin) outMin = projection;
        if (projection > outMax) outMax = projection;
    }
}
//========================================
// 投影範囲が重なるかチェック
//========================================
bool Overlaps(float minA, float maxA, float minB, float maxB)
{
    return !(maxA < minB || maxB < minA);
}
