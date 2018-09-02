#include <windows.h>
#include "resource.h"
#include "GetMrDlgProc.h"
#include "EqualExpDlgProc.h"
#include "HelpDlgProc.h"
#include "AboutDlgProc.h"
///#include "SwitchWnd.h"

extern HINSTANCE hInst;
extern HWND hBottomDlg;

BOOL CALLBACK MainPanelDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HFONT hFont;
    ///HBITMAP hBitmap;

    HWND hwnd;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_CTLCOLORSTATIC:
        /*���ñ��⾲̬�ı�����*/
        hFont = CreateFont(40, 20, 0, 0, FW_THIN, FALSE, FALSE, FALSE, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, TEXT("������"));
        hdc = (HDC)wParam;
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
        ///SetBkMode(hdc, TRANSPARENT);
        ///DeleteObject(hFont);
        return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_3DFACE));
        ///return (INT_PTR)GetStockObject(NULL_BRUSH);
    /*case WM_CTLCOLORBTN:
        hdc = (HDC)wParam;
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 255, 0));
        return (INT_PTR)GetStockObject(NULL_BRUSH);
    case WM_CTLCOLORDLG:
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP));
        return (INT_PTR)CreatePatternBrush(hBitmap);*/
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDB_GETMR:
            /*��������ʾ�Ӵ���*/
            hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_GETMR), hBottomDlg, GetMrDlgProc);
            ShowWindow(hwnd, SW_MAXIMIZE);
            /*���������*/
            DestroyWindow(hwndDlg);
            break;
        case IDB_EQUALEXP:
            /*��������ʾ�Ӵ���*/
            hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EQUALEXP), hBottomDlg, EqualExpDlgProc);
            ShowWindow(hwnd, SW_MAXIMIZE);
            /*���������*/
            DestroyWindow(hwndDlg);
            break;
        case IDB_HELP:
            /*��������ʾ�Ӵ���*/
            hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_HELP), hBottomDlg, HelpDlgProc);
            ShowWindow(hwnd, SW_MAXIMIZE);
            /*���������*/
            DestroyWindow(hwndDlg);
            break;
        case IDB_ABOUT:
            /*��������ʾ�Ӵ���*/
            hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ABOUT), hBottomDlg, AboutDlgProc);
            ShowWindow(hwnd, SW_MAXIMIZE);
            /*���������*/
            DestroyWindow(hwndDlg);
            break;
        default:
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
