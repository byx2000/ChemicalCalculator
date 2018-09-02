#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include "MainPanelDlgProc.h"
#include "chemistry.h"

extern HINSTANCE hInst;
extern HWND hBottomDlg;

char s1[1024];
char s2[1024];

BOOL CALLBACK EqualExpDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HFONT hFont;

    HWND hMainPanelDlg;

    char s3[1024];
    int len;
    double res[1024];

    static int flag = 0;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        SetWindowTextA(GetDlgItem(hwndDlg, IDE_REACTANT), s1);
        SetWindowTextA(GetDlgItem(hwndDlg, IDE_PRODUCT), s2);
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
            GetWindowTextA(GetDlgItem(hwndDlg, IDE_REACTANT), s1, sizeof(s1));
            GetWindowTextA(GetDlgItem(hwndDlg, IDE_PRODUCT), s2, sizeof(s2));
            if (strlen(s1) == 0 || strlen(s2) == 0)
            {
                sprintf(s3, "您的输入为空！");
                SetWindowTextA(GetDlgItem(hwndDlg, IDE_RES), s3);
                MessageBeep(MB_ICONERROR);
                break;
            }

            len = Equal(s1, s2, res);
            if (len == -1)
            {
                sprintf(s3, "无法配平！");
                MessageBeep(MB_ICONERROR);
            }
            else
            {
                FormatString(s1, s2, res, len, s3);
            }

            SetWindowTextA(GetDlgItem(hwndDlg, IDE_RES), s3);
            break;
        default:
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
