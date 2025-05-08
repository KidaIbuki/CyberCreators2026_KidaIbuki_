//=================================
// 
//�����_���[�N���X(DirectX�`��)renderer.cpp
//Auther kida ibuki 
// 
//==================================
#include "renderer.h"   // �����_���[
#include "manager.h"   // �}�l�[�W���[
#include "sound.h"     // �T�E���h
#include "main.h"      // ���C��

bool g_isSwitch = false;

//==========================
//�R���X�g���N�^
//==========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pFont = nullptr;
}

//===========================
//�f�X�g���N�^
//===========================
CRenderer::~CRenderer()
{

}

//============================
//�������ݒ�
//============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;		//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^
	HRESULT hr;

	//DirectX�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h�̎擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʂ̃T�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʂ̃T�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;		//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;				//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;//�f�u�X�o�b�t�@�ƃX�e���V���o�b�t�@�𐶐�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�u�X�o�b�t�@�Ƃ���16bit���g�p
	d3dpp.Windowed = bWindow;				//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;    // �A���`�G�C���A�X�L����

	////D3DPRESENT_PARAMETERS�\���̂ɐݒ肵�����e�ŃA���`�G�C���A�V���O���g�p�\���`�F�b�N����B
	//hr = CheckAntialias(D3DMULTISAMPLE_16_SAMPLES);

	//DIrectX�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DIrectX�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A���_������CPU�ōs���j
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//DIrectX�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	////�A���`�G�C���A�V���O���g�p�\�ȂƂ��̓����_�[�X�e�[�g�̃A���`�G�C���A�V���O��L���ɂ���B
	//if (SUCCEEDED(hr))
	//{
	//	m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	//}
	//else
	//{
	//	m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	//}

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	return S_OK;

}
//============================
//�I������
//============================
void CRenderer::Uninit()
{

	//DirectX�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//DirectX�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}


}
//============================
//�X�V����
//============================
void CRenderer::Update()
{
	CObject::UpdateAll();
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pManager->GetKeyboard();



#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F10))g_isSwitch = !g_isSwitch;
#endif
}
//============================
//�`�揈��
//============================
void CRenderer::Draw()
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�j
	m_pD3DDevice->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(50, 50, 50, 0), 1.0f, 0);  //�F�ς����


	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		CManager* pManager = CManager::GetInstance();
		LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		// �f�o�C�X���擾

		//���C���[�t���[��
		g_isSwitch ? pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

#ifdef _DEBUG
		DrawFPS();
#endif
		//�J�����̐ݒ�
		pManager->GetCamera()->SetCamera();

		pManager->GetInstance()->GetScene()->Draw();


		//�e��I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();
		//�`��I��
		m_pD3DDevice->EndScene();

	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
void CRenderer::DrawFPS()
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int nCntFps = GetFPS();
	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", nCntFps);

	//�e�L�X�g�`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//===========================
//�f�o�C�X�̎擾
//===========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;

}

#if 0
HRESULT CRenderer::CheckAntialias(D3DMULTISAMPLE_TYPE AntialiasMode)
{
	HRESULT hr = E_FAIL;
	DWORD QualityBackBuffer = 0;
	DWORD QualityZBuffer = 0;
	DWORD m = (DWORD)AntialiasMode;
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^


	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	while (m)
	{
		//�����_�����O�^�[�Q�b�g�ŃA���`�G�C���A�V���O���T�|�[�g����Ă��邩���`�F�b�N
		hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dpp.BackBufferFormat,
			d3dpp.Windowed,
			(D3DMULTISAMPLE_TYPE)m,
			&QualityBackBuffer);
		if (SUCCEEDED(hr))
		{
			//�[�x�X�e���V�� �T�[�t�F�C�X�ŃA���`�G�C���A�V���O���T�|�[�g����Ă��邩���`�F�b�N
			hr = m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				d3dpp.AutoDepthStencilFormat,
				d3dpp.Windowed,
				(D3DMULTISAMPLE_TYPE)m,
				&QualityZBuffer);
			if (SUCCEEDED(hr))
			{
				//�A���`�G�C���A�V���O���g�p�ł���̂�D3DPRESENT_PARAMETERS�Ƀ^�C�v���Z�b�g����B
				d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)m;

				//QualityBackBuffer��QualityZBuffer�ŏ��������̒l��L���ɂ���B�ǂ�ȃp�^�[���Œl���Ԃ�̂��킩���̂ŁA���������ق������S���ƁB
				if (QualityBackBuffer < QualityZBuffer)
					d3dpp.MultiSampleQuality = QualityBackBuffer - 1;
				else
					d3dpp.MultiSampleQuality = QualityZBuffer - 1;

				break;
			}
		}

		//���݂̃^�C�v�ŃA���`�G�C���A�V���O���g�p�ł��Ȃ��̂ŁA�P�i�K�Ⴂ�^�C�v�ōă`�F�b�N����B
		m--;
	}

	return hr;
}
#endif