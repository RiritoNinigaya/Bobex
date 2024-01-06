// dllmain.cpp : Defines the entry point for the DLL application.
#include "Includes.hpp"
#include <Windows.h>
#include <iostream>
#include <format>
bool hasfounded_il2cppimage = false;
void InitImGui() {
	ImGui::CreateContext();
	ImGuiIO& ioget = ImGui::GetIO();
	ioget.Fonts->AddFontFromMemoryTTF(fontfunc, sizeof(fontfunc), 12.F);
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();
	style.Colors[ImGuiCol_WindowBg] = HexToRGBA("387864");
	style.Colors[ImGuiCol_TitleBg] = HexToRGBA("8fb8ab");
	style.Colors[ImGuiCol_TitleBgActive] = HexToRGBA("a3f3ff");
	style.Colors[ImGuiCol_TitleBgCollapsed] = HexToRGBA("245b63");
	style.Colors[ImGuiCol_Button] = HexToRGBA("e3bf8d");
	style.Colors[ImGuiCol_ButtonHovered] = HexToRGBA("a3712a");
	style.Colors[ImGuiCol_ButtonActive] = HexToRGBA("d6d01e");
	style.Colors[ImGuiCol_CheckMark] = HexToRGBA("ed8e79");
	style.Colors[ImGuiCol_FrameBg] = HexToRGBA("b04a33");
	style.Colors[ImGuiCol_FrameBgActive] = HexToRGBA("fafafa");
	style.Colors[ImGuiCol_FrameBgHovered] = HexToRGBA("6cebc0");
	style.Colors[ImGuiCol_Header] = HexToRGBA("6518d9");
	style.Colors[ImGuiCol_HeaderActive] = HexToRGBA("6518d9");
	style.Colors[ImGuiCol_HeaderHovered] = HexToRGBA("0c5925");
	style.Colors[ImGuiCol_Tab] = HexToRGBA("3eb8d6");
	style.Colors[ImGuiCol_TabActive] = HexToRGBA("20c1e8");
	style.Colors[ImGuiCol_TabHovered] = HexToRGBA("169e1d");
	style.Colors[ImGuiCol_Text] = HexToRGBA("d9e851");
	style.Colors[ImGuiCol_TextDisabled] = HexToRGBA("1d9629");
	style.Colors[ImGuiCol_MenuBarBg] = HexToRGBA("ced938");
	style.Colors[ImGuiCol_PopupBg] = HexToRGBA("121f52");
	style.Alpha = 1.0F;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	//Init ImGui Hook Function :D
}

void Render_ImGui() {
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Bobex By RiritoNinigaya", 0, flags);
	ImGui::SetWindowSize(ImVec2(330.F, 330.F));
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Donation")) 
		{
			ImGui::Text("Soon!!!");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::TextColored(HexToRGBA("b83018"), "Welcome to My New IL2Cpp Mod For Game PCBS2... Enjoy!!!");
	if (ImGui::Button("Unlimited Money", ImVec2(125.F, 125.F))) {
		PrintCMD("Soon!!!");
	}
	ImGui::End();
	ImGui::Render();
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView); //C6387 is False Positive Warning D3D11 Device
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	Render_ImGui();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}
DWORD WINAPI Thr() {
    bool init_hook = false;
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    AllocConsole();
    SetConsoleTitleA("Bobex Debugger");
    std::string format_func = std::format("{}", "Welcome to my new IL2Cpp Mod For Game PCBS2");
    std::string cmd_command = (std::string)"echo " + format_func;
    system(cmd_command.c_str());
    MinHookInit();
    UnityResolve::Init(GetModuleHandle(L"GameAssembly.dll"), UnityResolve::Mode::Il2Cpp); //IL2Cpp Resolver :D
    UnityResolve::ThreadAttach();
    do {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thr, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

