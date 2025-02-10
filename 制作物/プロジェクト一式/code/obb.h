//=================================
// 
// �L�����E�{�b�N�X �N���X�@obb.h
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
	D3DXVECTOR3 GetCenter() const { return center; }  // ���S���擾
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // �����擾
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // �������擾
	D3DXVECTOR3 GetVertex(int index) const;   // ���_���擾
	bool CheckOverlap(const OBB& other) const;  // OBB���m�̏Փ˔���

	static void DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color);  // OBB�̃��C���̕`��

private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // �w�莲�ւ̓��e�������v�Z

	D3DXVECTOR3 center;   // ���S�ʒu
	D3DXVECTOR3 axes[3];  // ���[�J����(x,y,z)
	D3DXVECTOR3 halfWidths;  // �e�������̔����̒���

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

	bool CheckOverlap(const Sphere& other) const;   // �����m�̏Փ˔���
	bool CheckOverlap(const OBB& box) const;        // ���� OBB �̏Փ˔���

	static void DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color);  // ���̂̃��C���`��

private:
	D3DXVECTOR3 center;  // ���̒��S���W
	float radius;        // ���̔��a

	struct Vertex {
		D3DXVECTOR3 pos;
		D3DCOLOR color;
	};

};
#endif