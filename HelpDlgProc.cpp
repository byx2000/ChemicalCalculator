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
        AddString(hEdit, "��ʹ��˵��\r\n");
        AddString(hEdit, "     ��ѧʽ��д����\r\n");
        AddString(hEdit, "         ��.��ѧʽ�е�Ԫ�ط��Ű���ԭ�����룬ע�����ִ�Сд���磺Mg��\r\n");
        AddString(hEdit, "         ��.�ж��ԭ��ʱ����Ԫ�ط��ź���������֣��磺Cu2��\r\n");
        AddString(hEdit, "         ��.�ж��ԭ����ʱ����ԭ�������������𣬲������ź�������֣��磺(OH)2��\r\n");
        AddString(hEdit, "         ��.��ѧʽ�е�����Ҫʹ��Ӣ�����뷨������\r\n");
        AddString(hEdit, "         ��.Ҫ��ƽ��ѧ����ʽ���������뷴Ӧ����������ͬ����֮�����һ�������ո����\r\n");
        AddString(hEdit, "         ��.��������Ҫ��Ļ�ѧʽ��\r\n");
        AddString(hEdit, "             Mg(OH)2��������þ����CuCl2���Ȼ�ͭ����H2����������Fe2(SO4)3������������C��̼����NaHCO3��̼�����ƣ�\r\n");
        AddString(hEdit, "\r\n");
        return TRUE;
    case WM_CTLCOLORSTATIC:
        if (GetDlgCtrlID((HWND)lParam) == IDS_TITLE)
        {

            hFont = CreateFont(40, 20, 0, 0, FW_THIN, FALSE, FALSE, FALSE, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, TEXT("������"));
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
            /*���������*/
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
