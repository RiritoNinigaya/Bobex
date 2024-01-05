#pragma once
#include "../Bobex/InternalLibs/UnityResolve.hpp"
#include "../Bobex/InternalLibs/CMDFix/CMDFix.h"
#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>
#include <iostream>
#include "../Bobex/InternalLibs/kiero/kiero.h"
#include "../Bobex/InternalLibs/imgui/imconfig.h"
#include "../Bobex/InternalLibs/imgui/imgui.h"
#include "../Bobex/InternalLibs/imgui/imgui_impl_dx11.h"
#include "../Bobex/InternalLibs/imgui/imgui_impl_win32.h"
#include "../Bobex/hex2rgba.hpp"
#include "fontfunction.h"
#include <MinHook.h>
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
FILE* fp;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
using I = UnityResolve;
using IM = UnityResolve::Method;
using IC = UnityResolve::Class;
using IT = UnityResolve::Type;
using IF = UnityResolve::Field;
using IA = UnityResolve::Assembly;
using II = UnityResolve::UnityType;



void MinHookInit() {
	MH_Initialize();
}