//=================================
// 
// �L�����E�{�b�N�X �N���X�@obb.cpp
//outher kida ibuki 
// 
//==================================

#include "obb.h"

// [�����̎d�g��]
// 1.OBB�̒�`
//   �EOBB�͒��S���W(center)
//   �EOBB�̃��[�J����(axes)
//   �EOBB�̊e�������̔���(halfWidths)
//     �Œ�`
// 2.���_���W�̌v�Z
//   �EGetVector(int index)�ɂ��AOBB��8���_���v�Z
// 3.�Փ˔���(SAT)
//   �E�������藝(SAT)��p��������
//   �E15�{�̔��莲(6�{��OBB�� + 9�{�̊O�ώ�)
//   �E�e���̓��e���ĕ��������邩�m�F
// 4.���e�����̌v�Z
//   �EProjectOntoAxis�ɂ��AOBB�̊e���𓊉e���A�������擾

//========================================
// �R���X�g���N�^
//========================================
OBB::OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfWidths, const D3DXMATRIX& rotationMatrix)
{
	this->center = center;
	this->halfWidths = halfWidths;

	// ��]�s�񂩂烍�[�J������ݒ�
	axes[0] = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);  // x��
	axes[1] = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);  // y��
	axes[2] = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);  // z��

}
//========================================
// ���_���擾
//========================================
D3DXVECTOR3 OBB::GetVertex(int index) const
{
	D3DXVECTOR3 vertex = center;

	// 1.index �̃r�b�g���Z�𗘗p���A�e���̐�������������
	int signX = (index & 1) ? 1 : -1;
	int signY = (index & 2) ? 1 : -1;
	int signZ = (index & 4) ? 1 : -1;

	// 2.OBB�̒��S(center)�ɑ΂��A�e������(axes[0],axes[1],axes[2])�̉e�������Z
	vertex += axes[0] * (signX * halfWidths.x);
	vertex += axes[1] * (signY * halfWidths.y);
	vertex += axes[2] * (signZ * halfWidths.z);

	return vertex;
}
//========================================
// OBB���m�̏Փ˔���
//========================================
bool OBB::CheckOverlap(const OBB& other) const
{
    D3DXVECTOR3 axesToTest[15];
    int axisIndex = 0;

	// 1.���肷�鎲�̃��X�g���쐬
	//   �Ethis OBB��3��(axes[0], axes[1], axes[2])
    //   �Eother OBB��3��(other.axes[0], other.axes[1], other.axes[2])
    //   �E��OBB�̎��̃N���X��(�O��)����9�̐V���������v�Z

    // ���g�Ƒ���OBB�̎�
    for (int i = 0; i < 3; ++i) 
    {
        axesToTest[axisIndex++] = axes[i];
        axesToTest[axisIndex++] = other.axes[i];
    }

    // ���̃N���X��
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) 
        {
            D3DXVECTOR3 crossAxis;
            D3DXVec3Cross(&crossAxis, &axes[i], &other.axes[j]);
            if (D3DXVec3Length(&crossAxis) > 0.0001f)
            { // �L���Ȏ�
                axesToTest[axisIndex++] = crossAxis;
            }
        }
    }

	// 2.�e���ɑ΂��ĕ������̃`�F�b�N
	// this OBB��other OBB��axis�ɓ��e���A���̍��v���e�������ƒ��S�ԋ������r
	
    // ���S�Ԃ̋���
    D3DXVECTOR3 t = other.center - center;

    // ���������Ƃɔ���
    for (int i = 0; i < axisIndex; ++i)
    {
        const D3DXVECTOR3& axis = axesToTest[i];
        D3DXVECTOR3 normAxis;
        D3DXVec3Normalize(&normAxis, &axis);

        // �eOBB�����ɓ��e
        float projection1 = ProjectOntoAxis(normAxis);
        float projection2 = other.ProjectOntoAxis(normAxis);
        float centerDistance = fabs(D3DXVec3Dot(&t, &normAxis));

        // ���e���������Ă���ꍇ
        if (centerDistance > projection1 + projection2)
        {
			// �������m�F���ꂽ��false��Ԃ�(�Փ˂��Ă��Ȃ�)
            return false;
        }
    }
	// 3.���ׂĂ̎��ŕ������m�F�ł��Ȃ�������true��Ԃ�(�Փ˂��Ă���)
    return true;  // �������Ă��Ȃ� -> �Փ�
}
//========================================
// �w�莲�ւ̓��e�������v�Z
//========================================
float OBB::ProjectOntoAxis(const D3DXVECTOR3& axis) const
{
	// 1.OBB�̊e��(axes[0],axes[1],axes[2])��axis�ɓ��e
    return fabs(D3DXVec3Dot(&axes[0], &axis) * halfWidths.x) +
        fabs(D3DXVec3Dot(&axes[1], &axis) * halfWidths.y) +
        fabs(D3DXVec3Dot(&axes[2], &axis) * halfWidths.z);
	// 2.�e�����Ƃ̃X�J���[�l�����v���A�S�̂̓��e�������v�Z
}
//========================================
// �R���X�g���N�^
//========================================
Sphere::Sphere(const D3DXVECTOR3& center, float radius)
{
	this->center = center;
	this->radius = radius;
}

//========================================
// �����m�̏Փ˔���
//========================================
bool Sphere::CheckOverlap(const Sphere& other) const
{
	D3DXVECTOR3 difference = center - other.center;
    // 2�̒��S�_�̋������v�Z
	float distanceSquared = D3DXVec3LengthSq(&difference);    // ���a�̍��v�Ɣ�r
    float radiusSum = radius + other.radius;

    return distanceSquared <= (radiusSum * radiusSum);
}
//========================================
// ����OBB�̏Փ˔���
//========================================
bool Sphere::CheckOverlap(const OBB& box) const
{
    D3DXVECTOR3 closestPoint = box.GetCenter();  // OBB �̒��S����n�߂�
    D3DXVECTOR3 sphereToBox = center - box.GetCenter();
    for (int i = 0; i < 3; ++i)
    {
		D3DXVECTOR3 axis = box.GetAxis(i);

		float distance = D3DXVec3Dot(&sphereToBox, &axis);
        // OBB �͈͓̔��ɐ���
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

    // �ŋߐړ_�Ƌ��̒��S�̋������r
    D3DXVECTOR3 diff = center - closestPoint;
    return D3DXVec3LengthSq(&diff) <= (radius * radius);
}
//=============================================
// OBB�̃��C����`��(�f�o�b�N�p)
//=============================================
void OBB::DrawOBB(IDirect3DDevice9* device, const D3DXVECTOR3& center, const D3DXVECTOR3 halfSize, const D3DXVECTOR3 axis[3], D3DCOLOR color)
{

	// OBB��8�̒��_���v�Z
	D3DXVECTOR3 corners[8];
	for (int i = 0; i < 8; i++) {
		corners[i] = center;
		corners[i] += axis[0] * (halfSize.x * ((i & 1) ? 1.0f : -1.0f));
		corners[i] += axis[1] * (halfSize.y * ((i & 2) ? 1.0f : -1.0f));
		corners[i] += axis[2] * (halfSize.z * ((i & 4) ? 1.0f : -1.0f));
	}

	// OBB �̃G�b�W�����ԃ��C�����X�g�i12�{�̐��j
	int indices[] = {
		0,1,  1,3,  3,2,  2,0,  // �O��
		4,5,  5,7,  7,6,  6,4,  // �w��
		0,4,  1,5,  2,6,  3,7   // �O����Ȃ���
	};

	Vertex lines[24];
	for (int i = 0; i < 12; i++) {
		lines[i * 2] = { corners[indices[i * 2]], color };
		lines[i * 2 + 1] = { corners[indices[i * 2 + 1]], color };
	}

	// ���_�t�H�[�}�b�g�ݒ�
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ���C���`��
	device->DrawPrimitiveUP(D3DPT_LINELIST, 12, lines, sizeof(Vertex));
}

//=============================================
// ���̂̃��C����`��(�f�o�b�N�p)
//=============================================
void Sphere::DrawSphere(IDirect3DDevice9* device, const D3DXVECTOR3& center, float radius, int slices, int stacks, D3DCOLOR color)
{
	int numLines = (slices + 1) * stacks + (stacks + 1) * slices;  // �ܓx���� + �o�x����
	int numVertices = numLines * 2;  // �e���C����2�̒��_

	// ���_�z����m��
	Vertex* lines = new Vertex[numVertices];

	// �C���f�b�N�X�̏�����
	int index = 0;
	// �o�x�����i�c���C���j
	for (int i = 0; i <= slices; i++) 
	{
		// �Ɓitheta�j�� 0�� ���� 360���i0 ���� 2�΁j�܂� slices ��������B
		float theta = (float)i / slices * 2.0f * D3DX_PI;
		// �ܓx�����i�����C���j
		for (int j = 0; j < stacks; j++)
		{
			// �e ��(�t�@�C) �ɑ΂��āA0�� ���� 360�� �܂� �� ����]�����ĉ��̃��C���𐶐��B
			float phi1 = (float)j / stacks * D3DX_PI - (D3DX_PI / 2.0f);
			float phi2 = (float)(j + 1) / stacks * D3DX_PI - (D3DX_PI / 2.0f);

			// ���ʍ��W�̌v�Z
			lines[index++] = { center + D3DXVECTOR3(radius * cosf(phi1) * cosf(theta),
													 radius * sinf(phi1),
													 radius * cosf(phi1) * sinf(theta)), color };

			lines[index++] = { center + D3DXVECTOR3(radius * cosf(phi2) * cosf(theta),
													 radius * sinf(phi2),
													 radius * cosf(phi2) * sinf(theta)), color };
		}
	}
	// ���_�t�H�[�}�b�g�ݒ�
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ���C���`��
	device->DrawPrimitiveUP(D3DPT_LINELIST, numLines, lines, sizeof(Vertex));

	delete[] lines;
}