// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject2.h"
#include "Table.h"
#include <string.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
Table* table;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void DrawTable(HDC hdc, Table* table, int windowWidth, int windowHeight);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    std::vector<std::vector<tstring>> vector{
        {_T("and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum"), _T("iure repr qui in"), _T("ea volupt velit esse quam nihil"), _T("molestiae consequatur"), _T("vel illum qui dolorem") },
        {_T("Ut enim ad"), _T("minim veniam"), _T("qui in ea"), _T("voluptate velit"), _T("esse, quam")},
        {_T("nihil molestiae"), _T("consequatur, vel"), _T("illum, nisi ut aliquid"), _T("ex ea commodi consequatur.") },
        {_T("Except sint occaecat cupidatat"), _T("non proident,"), _T("consectetur adipiscing elit,"), _T("obcaecati cupiditate non"), _T("provident, similique sunt")},
        {_T("in culpa, qui officia"), _T("deserunt mollitia animi,"), _T("id est laborum et dolorum"), _T("fuga.Itaque earum rerum"), _T("hic tenetur a sapiente")},
        {_T("delectus, unde omnis"), _T("laudantium, totam rem"), _T("aperiam eaque ipsa")},
        {},
        { _T("iste natus error"), _T("sit voluptatem ac doloremque")}
    };
    table = new Table(vector);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND listView;
    switch (message)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rect;
        GetWindowRect(hWnd, &rect);

        DrawTable(hdc, table, rect.right - rect.left, rect.bottom - rect.top);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawTable(HDC hdc, Table* table, int windowWidth, int windowHeight) {  
    auto tableData = table->GetTable();

    int maxColumnCount = 1;

    for (auto row : tableData) {
        if (row.size() > maxColumnCount) {
            maxColumnCount = row.size();
        }
    }

    int columnWidth = windowWidth / maxColumnCount;

    int tableHeight = 0;
    int rowCount = table->GetRowCount();

    RECT rect;

    for (int i = 0; i < rowCount; i++)
    {
        int columnCount = tableData.at(i).size();
        int maxColumnHeight = 2;

        for (int j = 0; j < columnCount; j++)
        {
            auto dataItem = tableData.at(i).at(j);

            SetRect(&rect, j * columnWidth + 2, tableHeight + 2, (j + 1) * columnWidth - 2, windowHeight);
            int textHeight = DrawText(hdc, dataItem.c_str(), dataItem.length(), &rect, DT_CENTER | DT_WORDBREAK);

            if (textHeight > maxColumnHeight)
                maxColumnHeight = textHeight;
        }

        tableHeight += maxColumnHeight;

        MoveToEx(hdc, 0, tableHeight, NULL);
        LineTo(hdc, windowWidth, tableHeight);
    }

    for (int i = 1; i < maxColumnCount; i++)
    {
        int columnPosition = i * columnWidth;
        MoveToEx(hdc, columnPosition, 0, NULL);
        LineTo(hdc, columnPosition, tableHeight);
    }
}
