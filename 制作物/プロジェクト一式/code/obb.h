//=================================
// 
// 有向境界ボックス クラス　obb.h
//outher kida ibuki 
// 
//==================================
#ifndef _OBB_H_
#define _OBB_H_
#include "pch.h"



class OBB
{
public:
	OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfwidths, const D3DXMATRIX& rotationMatrix);
	D3DXVECTOR3 GetCenter() const { return center; }  // 中心を取得
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // 軸を取得
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // 半幅を取得
	D3DXVECTOR3 GetVertex(int index) const;   // 頂点を取得
	bool CheckOverlap(const OBB& other) const;  // OBB同士の衝突判定

	static void DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color);  // OBBのラインの描画

private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // 指定軸への投影距離を計算

	D3DXVECTOR3 center;   // 中心位置
	D3DXVECTOR3 axes[3];  // ローカル軸(x,y,z)
	D3DXVECTOR3 halfWidths;  // 各軸方向の半分の長さ

	struct Vertex {
		D3DXVECTOR3 pos;
		D3DCOLOR color;
	};

};
class Sphere
{
public:
	Sphere(const D3DXVECTOR3& center, float radius);

	D3DXVECTOR3 GetCenter() const { return center; }
	float GetRadius() const { return radius; }

	bool CheckOverlap(const Sphere& other) const;   // 球同士の衝突判定
	bool CheckOverlap(const OBB& box) const;        // 球と OBB の衝突判定

	static void DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color);  // 球体のライン描画

private:
	D3DXVECTOR3 center;  // 球の中心座標
	float radius;        // 球の半径

	struct Vertex {
		D3DXVECTOR3 pos;
		D3DCOLOR color;
	};

};
#endif