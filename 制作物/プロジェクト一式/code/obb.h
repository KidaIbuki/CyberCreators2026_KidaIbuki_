//=================================
// 
// Lü«E{bNX NX@obb.h
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
	D3DXVECTOR3 GetCenter() const { return center; }  // Sðæ¾
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // ²ðæ¾
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // ¼ðæ¾
	D3DXVECTOR3 GetVertex(int index) const;   // ¸_ðæ¾
	bool CheckOverlap(const OBB& other) const;  // OBB¯mÌÕË»è

	static void DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color);  // OBBÌCÌ`æ

private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // wè²ÖÌe£ðvZ

	D3DXVECTOR3 center;   // SÊu
	D3DXVECTOR3 axes[3];  // [J²(x,y,z)
	D3DXVECTOR3 halfWidths;  // e²ûüÌ¼ªÌ·³

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

	bool CheckOverlap(const Sphere& other) const;   // ¯mÌÕË»è
	bool CheckOverlap(const OBB& box) const;        // Æ OBB ÌÕË»è

	static void DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color);  // ÌÌC`æ

private:
	D3DXVECTOR3 center;  // ÌSÀW
	float radius;        // Ì¼a

	struct Vertex {
		D3DXVECTOR3 pos;
		D3DCOLOR color;
	};

};
#endif