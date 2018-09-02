#include <windows.h>
#include "resource.h"
#include "MainPanelDlgProc.h"
///#include "SwitchWnd.h"

extern HINSTANCE hInst;
extern HWND hBottomDlg;

BOOL CALLBACK AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HFONT hFont;

    HWND hMainPanelDlg;

    static int flag = 0;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_CTLCOLORSTATIC:
        if (GetDlgCtrlID((HWND)lParam) == IDS_TITLE)
        {

            hFont = CreateFont(40, 20, 0, 0, FW_THIN, FALSE, FALSE, FALSE, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, TEXT("新宋体"));
            hdc = (HDC)wParam;
            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
            ///DeleteObject(hFont);
            return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_3DFACE));
        }
        else
            return FALSE;
    case WM_LBUTTONDOWN:
        if (LOWORD(lParam) <= 32 && HIWORD(lParam) <= 32)
            flag = 1;
        break;
    case WM_LBUTTONUP:
        if (LOWORD(lParam) <= 32 && HIWORD(lParam) <= 32 && flag)
        {
            /*返回主面板*/
            hMainPanelDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAINPANEL), hBottomDlg, MainPanelDlgProc);
            ShowWindow(hMainPanelDlg, SW_MAXIMIZE);
            DestroyWindow(hwndDlg);
        }
        flag = 0;
        return TRUE;
    }
    return FALSE;
}
