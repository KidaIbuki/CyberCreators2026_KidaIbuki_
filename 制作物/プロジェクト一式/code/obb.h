//=================================
// 
// 有向境界ボックス クラス　obb.h
// Auther kida ibuki 
// 
//==================================
#ifndef _OBB_H_
#define _OBB_H_
#include "pch.h"


struct Vertex {
	D3DXVECTOR3 pos;
	D3DCOLOR color;
};

// 有向境界ボックスクラス
class OBB
{
public:
	OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfwidths, const D3DXMATRIX& rotationMatrix);
	D3DXVECTOR3 GetCenter() const { return center; }  // 中心を取得
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // 軸を取得
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // 半幅を取得
	D3DXVECTOR3 GetVertex(int index) const;   // 頂点を取得
	bool CheckOverlap(const OBB& other) const;  // OBB同士の衝突判定
	std::vector<D3DXVECTOR3> GetCorners() const;   // 8つの頂点を取得

	static void DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color);  // OBBのラインの描画

private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // 指定軸への投影距離を計算

	D3DXVECTOR3 center;   // 中心位置
	D3DXVECTOR3 axes[3];  // ローカル軸(x,y,z)
	D3DXVECTOR3 halfWidths;  // 各軸方向の半分の長さ

};

// 球体クラス
class Sphere
{
public:
	Sphere(const D3DXVECTOR3& center, float radius);

	D3DXVECTOR3 GetCenter() const { return center; }   // 中心の取得
	float GetRadius() const { return radius; }         // 半径の取得

	bool CheckOverlap(const Sphere& other) const;   // 球同士の衝突判定
	bool CheckOverlap(const OBB& box) const;        // 球と OBB の衝突判定

	static void DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color);  // 球体のライン描画

private:
	D3DXVECTOR3 center;  // 球の中心座標
	float radius;        // 球の半径


};

void ProjectOntoAxis(const D3DXVECTOR3& axis, const std::vector<D3DXVECTOR3>& points, float& outMin, float& outMax);   // 投影範囲を計算
bool Overlaps(float minA, float maxA, float minB, float maxB);   // 投影範囲が重なるかチェック


// カプセルクラス
class Capsule
{
public:

	Capsule(const D3DXVECTOR3& center, float radius, float height, const D3DXMATRIX& rotationMatrix);

	void GetEndpoints(D3DXVECTOR3& outStart, D3DXVECTOR3& outEnd) const;   // カプセルの両端を取得
	void DrawCapsule(IDirect3DDevice9* device, int segments, D3DXCOLOR color) const;  // カプセルのライン描画
	bool CapsuleVsOBB_SAT(const OBB& obb) const;   // カプセル vs OBB の衝突判定

private:

	D3DXVECTOR3 center;    // カプセルの中心
	float radius;          // 球の半径
	float height;          // カプセルの高さ
	D3DXMATRIX rotationMatrix;   // 回転マトリックス

};

#endif