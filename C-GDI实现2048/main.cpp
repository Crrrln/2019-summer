#include<Windows.h>
#include<time.h>
#include"square_operation.h"
#include"game_operation.h"
int a[4][4] = { 0 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
void add_rand_num(HDC hdc,int a[4][4],HWND hwnd);
int Paint(HDC hdc, HWND hwnd, HDC hdcmem, HBITMAP hbmMem);
void Paintall(HDC hdc, int a[4][4]);
void Done(HDC hdc,HWND hwnd,HDC hdcmem,HBITMAP hbmMem,int a[4][4]);
void GamePaint(HWND hwnd, HDC hdcmem,
HBITMAP hbmMem);
void CreateGame(HWND hwnd,int score,int a[4][4],int if_game_over,int if_need_add_num,int if_game_win);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;        //����һ�����������

	//����Ϊ���������wndclass������
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //������ʽ
	wndclass.lpszClassName = szAppName;                               //��������
	wndclass.lpszMenuName = NULL;                                     //���ڲ˵�:��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    //���ڱ�����ɫ
	wndclass.lpfnWndProc = WndProc;                                   //���ڴ�����
	wndclass.cbWndExtra = 0;                                          //����ʵ����չ:��
	wndclass.cbClsExtra = 0;                                          //��������չ:��
	wndclass.hInstance = hInstance;                                   //����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //������С��ͼ��:ʹ��ȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //���ڲ��ü�ͷ���

	if (!RegisterClass(&wndclass))
	{    //ע�ᴰ����, ���ע��ʧ�ܵ���������ʾ
		MessageBox(NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(                   //��������
		szAppName,                 //��������
		TEXT("2048!!"),           //���ڱ���
		WS_OVERLAPPEDWINDOW,       //���ڵķ��
		CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��x:ʹ��ȱʡֵ
		CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��y:ʹ��ȱʡֵ
		476,
		530,                     //���ڵĸ߶�:ʹ��ȱʡֵ
		NULL,                      //������:��
		NULL,                      //�Ӳ˵�:��
		hInstance,                 //�ô���Ӧ�ó����ʵ����� 
		NULL                       //
	);

	ShowWindow(hwnd, iCmdShow);        //��ʾ����
	UpdateWindow(hwnd);                //���´���

	while (GetMessage(&msg, NULL, 0, 0))        //����Ϣ�����л�ȡ��Ϣ
	{
		TranslateMessage(&msg);                 //���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);                  //�ַ����ص�����(���̺���)
	}
	return msg.wParam;
}
HDC hdc;    //�豸�������
HDC hdcmem;
HBITMAP hbmMem;
PAINTSTRUCT ps;         //���ƽṹ
RECT rect;          //���νṹ

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int count = 0;
	hdc = GetDC(hwnd);
	//	hdc = BeginPaint(hwnd, &ps);
	hdcmem = CreateCompatibleDC(hdc);//������һ�����ݵ�dc��getDC��õ��������DC
	hbmMem = CreateCompatibleBitmap(hdc,
		100, 100);
	GetClientRect(hwnd, &rect);//�õ����ھ�������
	switch (message)        //����õ�����Ϣ
	{
	case WM_CREATE: 
		CreateGame(hwnd, score, a, if_game_over, if_need_add_num,if_game_win);
        GamePaint(hwnd,hdcmem,hbmMem);
		return 0;

	case WM_PAINT:           //������������Чʱ��������Ϣ
		GamePaint(hwnd,hdcmem,hbmMem);
		
		if (count == 0)
		{
			Paintall(hdc, a);
			Paint(hdc, hwnd, hdcmem, hbmMem);
			Paintall(hdc, a);
			Paint(hdc, hwnd, hdcmem, hbmMem);
			count=1;
		}
		else
		{
			Paintall(hdc, a);
			Paint(hdc, hwnd, hdcmem, hbmMem);
		}
		return 0;
	case WM_KEYDOWN:
		GamePaint(hwnd,hdcmem,hbmMem);
		
		switch (wParam) {
		case VK_LEFT:
			check_game_win(a);
			check_game_over(a);
			move_left(a);
			Done(hdc, hwnd, hdcmem, hbmMem, a);
			break;
		case VK_RIGHT:
			check_game_win(a);
			check_game_over(a);
			move_right(a);
			Done(hdc, hwnd, hdcmem, hbmMem, a);
			break;
		case VK_UP:
			check_game_win(a);
			check_game_over(a);
			move_up(a);
			Done(hdc, hwnd, hdcmem, hbmMem, a);
			break;
		case VK_DOWN:
			check_game_win(a);
			check_game_over(a);
			move_down(a);
			Done(hdc, hwnd, hdcmem, hbmMem, a);
			break;
		case WM_DESTROY:
			ExitProcess(0);
			break;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}
void GamePaint(HWND hwnd, HDC hdcmem,
	HBITMAP hbmMem)
{
	RECT clientRect;
	HRGN bgRgn;
	HBRUSH hBrush;
	HPEN hPen;
	HDC hdc;    //�豸�������
	PAINTSTRUCT ps;         //���ƽṹ
	RECT rect;               //���νṹ

	hdc = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &rect);//�õ����ھ�������
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientRect);
	bgRgn = CreateRectRgnIndirect(&clientRect);
	hBrush = CreateSolidBrush(RGB(255, 182, 193));
	FillRgn(hdc, bgRgn, hBrush);//��RGB��0��255��0�������ɫ

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);

	hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, 30, 130, NULL);
	LineTo(hdc, 430, 130);
	MoveToEx(hdc, 130, 30, NULL);
	LineTo(hdc, 130, 430);
	MoveToEx(hdc, 30, 230, NULL);
	LineTo(hdc, 430, 230);
	MoveToEx(hdc, 30, 330, NULL);
	LineTo(hdc, 430, 330);
	MoveToEx(hdc, 230, 30, NULL);
	LineTo(hdc, 230, 430);
	MoveToEx(hdc, 330, 30, NULL);
	LineTo(hdc, 330, 430);
	MoveToEx(hdc, 30, 30, NULL);
	LineTo(hdc, 430, 30);
	MoveToEx(hdc, 30, 30, NULL);
	LineTo(hdc, 30, 430);
	MoveToEx(hdc, 430, 30, NULL);
	LineTo(hdc, 430, 430);
	MoveToEx(hdc, 30, 430, NULL);
	LineTo(hdc, 430, 430);

	DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	
	ReleaseDC(hwnd, hdc);
}
void add_rand_num(HDC hdc, int a[4][4], HWND hwnd) {
	HBRUSH hBrush;
	int n,i;
	if (get_null_count(a) == 0)
	{
		if (if_game_over == 1)
		{
			MessageBox(hwnd, TEXT("Game over!!"), TEXT("����"), MB_OK | MB_ICONINFORMATION);
				ExitProcess(0);
		}
		else
			return;

	}
	else
	{
		if (if_game_win == 1)
		{
			MessageBox(hwnd, TEXT("You win!!"), TEXT("����"), MB_OK);
			ExitProcess(0);
		}
		srand((unsigned int)time(NULL));
		n = rand() % get_null_count(a); /* ȷ���ںδ���λ����������� */
	}
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 4; ++j) {
			/* ��λ�����ɵ�λ�� */
			if (a[i][j] == 0 && n-- == 0) {
				a[i][j] = (rand() % 10 ? 2 : 4);
				if (a[i][j] == 2)
				{
					hBrush = CreateSolidBrush(RGB(245, 222, 179));
					SelectObject(hdc, hBrush);
					Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
				}
				else if (a[i][j] == 4)
				{
					hBrush = CreateSolidBrush(RGB(255, 222, 173));
					SelectObject(hdc, hBrush);
					Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
				}

				return;
			}
		}
	}
}
int count = 0;
int Paint(HDC hdc,HWND hwnd, HDC hdcmem, HBITMAP hbmMem)
{
	
	HFONT hFont;
	SelectObject(hdcmem, hbmMem);
	GetClientRect(hwnd, &rect);
	if (count < 2)
	{
		add_rand_num(hdc, a, hwnd);
		count++;
	}
	if (if_need_add_num) {
		add_rand_num(hdc, a, hwnd);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] != 0)
			{
				char temp[1024];
				wsprintf(temp, "%d", a[i][j]);
				wsprintf(temp, "%d", a[i][j]);
				hFont = CreateFont(30, 0, 0, 0,400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
					CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DECORATIVE, TEXT("Consolas"));
				SelectObject(hdc, hFont);
				int nOldMode = SetBkMode(hdc, TRANSPARENT);
				TextOut(hdc,
					80 + j * 100, 80 + i * 100, temp,                      //ʹ�ַ����ڴ����д�ֱ����      
					lstrlen(temp)     //lstrlen������ȡ�ַ����ĳ���
				);
				SetBkMode(hdc, nOldMode);
				EndPaint(hwnd, &ps);
			}
			else
				continue;
		}
	}
	char sc[1024];
	wsprintf(sc,"%d",score);
	hFont = CreateFont(30, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DECORATIVE, TEXT("Consolas"));
	SelectObject(hdc, hFont);
	int nOldMode = SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc,120, 445, TEXT("Score:"),6 );
	TextOut(hdc, 215, 445,sc,lstrlen(sc));

	SetBkMode(hdc, nOldMode);
	EndPaint(hwnd, &ps);
	
	return 0;
}
void Paintall(HDC hdc, int a[4][4])
{
	int i; HBRUSH hBrush;
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 4; ++j) {
			if (a[i][j] == 2)
			{
				hBrush = CreateSolidBrush(RGB(245, 222, 179));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 4)
			{
				hBrush = CreateSolidBrush(RGB(255, 222, 173));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 8)
			{
				hBrush = CreateSolidBrush(RGB(255, 165, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 16)
			{
				hBrush = CreateSolidBrush(RGB(255, 140, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 32)
			{
				hBrush = CreateSolidBrush(RGB(255, 127, 80));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 64)
			{
				hBrush = CreateSolidBrush(RGB(255, 69, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 128)
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 256)
			{
				hBrush = CreateSolidBrush(RGB(255, 215, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 512)
			{
				hBrush = CreateSolidBrush(RGB(255, 230, 140));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 1024)
			{
				hBrush = CreateSolidBrush(RGB(152, 251, 152));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			else if (a[i][j] == 2048)
			{
				hBrush = CreateSolidBrush(RGB(127, 255, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//���� paint ��� brush/* ��������2��4�����ɸ���Ϊ9:1 */
			}
			//DeleteObject(hBrush);

		}
	}
}
void Done(HDC hdc, HWND hwnd, HDC hdcmem, HBITMAP hbmMem, int a[4][4])
{
	Paintall(hdc, a);
	Paint(hdc, hwnd, hdcmem, hbmMem);

	if (get_null_count == 0)
	{
		if (if_game_over == 1)
		{
			MessageBox(hwnd, TEXT("��Ϸ������"), TEXT("����"), MB_OK | MB_ICONINFORMATION);
			PostQuitMessage(0);
		}
	}
}

void CreateGame(HWND hwnd, // �����ھ��
	
	int score, int a[4][4],
	int if_game_over, int if_need_add_num,int if_game_win
	)
{
	// �������������
	// ��Ҫʹ�����������ʳ���λ�õȡ�
	a[4][4] = { 0 };
	score = 0;
	if_game_over = 0;
	if_need_add_num = 0;
	if_game_win = 0;
}//�����������һ��
