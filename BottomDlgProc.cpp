#include <windows.h>
#include "resource.h"
#include "MainPanelDlgProc.h"

extern HINSTANCE hInst;
HWND hBottomDlg;

BOOL CALLBACK BottomDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hMainPanelDlg;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        /*����ͼ��*/
        SendMessage(hwndDlg, WM_SETICON, 0, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON)));

        /*��ʾ�����Ի���*/
        hMainPanelDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAINPANEL), hwndDlg, MainPanelDlgProc);
        ShowWindow(hMainPanelDlg, SW_MAXIMIZE);

        /*����ײ��ĶԻ�����*/
        hBottomDlg = hwndDlg;
        return TRUE;
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    }
    return FALSE;
}
