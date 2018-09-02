#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "BottomDlgProc.h"

HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_BOTTOM), NULL, (DLGPROC)BottomDlgProc);
}
