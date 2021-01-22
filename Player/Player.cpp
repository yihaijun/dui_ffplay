#include <Windows.h>
#include "UFPlayer.h"
#include "FFMPEGDef.h"


#ifdef _DEBUG
	#pragma comment(lib,"..\\lib\\DuiLib_d.lib")
	#pragma comment(lib,"..\\lib\\UFlib_d.lib")
	#pragma comment(lib,"..\\lib\\MedioPlayer_d.lib")
#else
	#pragma comment(lib,"..\\lib\\DuiLib.lib")
	#pragma comment(lib,"..\\lib\\UFlib.lib")
	#pragma comment(lib,"..\\lib\\MedioPlayer.lib")
#endif // _DEBUG

#include <windows.h>
#include <DbgHelp.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <Shlwapi.h>
#include <string>

#pragma comment(lib,"DbgHelp.lib")
#pragma comment(lib,"Shlwapi.lib")
void Console()
{
	AllocConsole();
	int nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	FILE *fp = _fdopen(nCrt, "w");

	*stdout = *fp;
	*stderr = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int WINAPI WinMain( __in HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nShowCmd )

{
	//Console();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	FFMPEG_Init();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken ,&gdiplusStartupInput ,NULL);

	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

	DuiLib::UFPlayer  *pPlayer = new DuiLib::UFPlayer();
	pPlayer->SetMovable(true);
	pPlayer->Create(NULL,_T(""),UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
	pPlayer->Center();
	pPlayer->ShowWindow();
	
	DuiLib::CPaintManagerUI::MessageLoop();
	Gdiplus::GdiplusShutdown(gdiplusToken);
	::CoUninitialize();

	return 0;
}