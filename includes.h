#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <thread>
#include "Gui.h"
#include "Vector3.h"
#include "Vector2.h"
#include "BoneMatrix.h"
#include <d3dx9core.h>
#define WINDOW_NAME "LimpChimp"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);