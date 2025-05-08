//=================================
// 
// �L�����E�{�b�N�X �N���X�@obb.h
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

// �L�����E�{�b�N�X�N���X
class OBB
{
public:
	OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfwidths, const D3DXMATRIX& rotationMatrix);
	D3DXVECTOR3 GetCenter() const { return center; }  // ���S���擾
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // �����擾
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // �������擾
	D3DXVECTOR3 GetVertex(int index) const;   // ���_���擾
	bool CheckOverlap(const OBB& other) const;  // OBB���m�̏Փ˔���
	std::vector<D3DXVECTOR3> GetCorners() const;   // 8�̒��_���擾

	static void DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color);  // OBB�̃��C���̕`��

private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // �w�莲�ւ̓��e�������v�Z

	D3DXVECTOR3 center;   // ���S�ʒu
	D3DXVECTOR3 axes[3];  // ���[�J����(x,y,z)
	D3DXVECTOR3 halfWidths;  // �e�������̔����̒���

};

// ���̃N���X
class Sphere
{
public:
	Sphere(const D3DXVECTOR3& center, float radius);

	D3DXVECTOR3 GetCenter() const { return center; }   // ���S�̎擾
	float GetRadius() const { return radius; }         // ���a�̎擾

	bool CheckOverlap(const Sphere& other) const;   // �����m�̏Փ˔���
	bool CheckOverlap(const OBB& box) const;        // ���� OBB �̏Փ˔���

	static void DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color);  // ���̂̃��C���`��

private:
	D3DXVECTOR3 center;  // ���̒��S���W
	float radius;        // ���̔��a


};

void ProjectOntoAxis(const D3DXVECTOR3& axis, const std::vector<D3DXVECTOR3>& points, float& outMin, float& outMax);   // ���e�͈͂��v�Z
bool Overlaps(float minA, float maxA, float minB, float maxB);   // ���e�͈͂��d�Ȃ邩�`�F�b�N


// �J�v�Z���N���X
class Capsule
{
public:

	Capsule(const D3DXVECTOR3& center, float radius, float height, const D3DXMATRIX& rotationMatrix);

	void GetEndpoints(D3DXVECTOR3& outStart, D3DXVECTOR3& outEnd) const;   // �J�v�Z���̗��[���擾
	void DrawCapsule(IDirect3DDevice9* device, int segments, D3DXCOLOR color) const;  // �J�v�Z���̃��C���`��
	bool CapsuleVsOBB_SAT(const OBB& obb) const;   // �J�v�Z�� vs OBB �̏Փ˔���

private:

	D3DXVECTOR3 center;    // �J�v�Z���̒��S
	float radius;          // ���̔��a
	float height;          // �J�v�Z���̍���
	D3DXMATRIX rotationMatrix;   // ��]�}�g���b�N�X

};

#endif