#include <windows.h>
#include <string.h>
#include "resource.h"
#include "MainPanelDlgProc.h"
///#include "SwitchWnd.h"

extern HINSTANCE hInst;
extern HWND hBottomDlg;

void AddString(HWND hEdit, const char* buf);

BOOL CALLBACK HelpDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HFONT hFont;

    HWND hMainPanelDlg;
    HWND hEdit;

    static int flag = 0;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        hEdit = GetDlgItem(hwndDlg, IDE_HELPTEXT);
        AddString(hEdit, "●使用说明\r\n");
        AddString(hEdit, "     化学式书写规则\r\n");
        AddString(hEdit, "         ①.化学式中的元素符号按照原样输入，注意区分大小写（如：Mg）\r\n");
        AddString(hEdit, "         ②.有多个原子时，在元素符号后面加上数字（如：Cu2）\r\n");
        AddString(hEdit, "         ③.有多个原子团时，将原子团用括号括起，并在括号后加上数字（如：(OH)2）\r\n");
        AddString(hEdit, "         ④.化学式中的括号要使用英文输入法的括号\r\n");
        AddString(hEdit, "         ⑤.要配平化学方程式，请先输入反应物和生成物，不同物质之间可用一个或多个空格隔开\r\n");
        AddString(hEdit, "         ⑥.几个符合要求的化学式：\r\n");
        AddString(hEdit, "             Mg(OH)2（氢氧化镁）、CuCl2（氯化铜）、H2（氢气）、Fe2(SO4)3（硫酸铁）、C（碳）、NaHCO3（碳酸氢钠）\r\n");
        AddString(hEdit, "\r\n");
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

void AddString(HWND hEdit, const char* buf)
{
    TCHAR s[2014];
    GetWindowTextA(hEdit, s, sizeof(s));
    strcat(s, buf);
    SetWindowTextA(hEdit, s);
}
