#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include "MainPanelDlgProc.h"
#include "chemistry.h"

extern HINSTANCE hInst;
extern HWND hBottomDlg;

char bf1[1024];

BOOL CALLBACK GetMrDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HFONT hFont;

    HWND hMainPanelDlg;

    char bf2[1024];
    double Mw;

    static int flag = 0;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        SetWindowTextA(GetDlgItem(hwndDlg, IDE_EXP), bf1);
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
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDB_CAL:
            GetWindowTextA(GetDlgItem(hwndDlg, IDE_EXP), bf1, sizeof(bf1));
            if (strlen(bf1) == 0)
            {
                sprintf(bf2, "您的输入为空！");
                MessageBeep(MB_ICONERROR);
                SetWindowTextA(GetDlgItem(hwndDlg, IDE_RES), bf2);
                break;
            }
            Mw = GetMw(bf1);
            if (Mw == -1)
            {
                sprintf(bf2, "输入错误！");
            }
            else
            {
                sprintf(bf2, "%s的相对分子质量为：%lf", bf1, Mw);
            }
            SetWindowTextA(GetDlgItem(hwndDlg, IDE_RES), bf2);
            break;
        default:
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
