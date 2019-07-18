#include<Windows.h>
#include<time.h>
#include"square_operation.h"
#include"game_operation.h"
int a[4][4] = { 0 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //声明用来处理消息的函数
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
	WNDCLASS wndclass;        //声明一个窗口类对象

	//以下为窗口类对象wndclass的属性
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //窗口样式
	wndclass.lpszClassName = szAppName;                               //窗口类名
	wndclass.lpszMenuName = NULL;                                     //窗口菜单:无
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    //窗口背景颜色
	wndclass.lpfnWndProc = WndProc;                                   //窗口处理函数
	wndclass.cbWndExtra = 0;                                          //窗口实例扩展:无
	wndclass.cbClsExtra = 0;                                          //窗口类扩展:无
	wndclass.hInstance = hInstance;                                   //窗口实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //窗口最小化图标:使用缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //窗口采用箭头光标

	if (!RegisterClass(&wndclass))
	{    //注册窗口类, 如果注册失败弹出错误提示
		MessageBox(NULL, TEXT("窗口注册失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(                   //创建窗口
		szAppName,                 //窗口类名
		TEXT("2048!!"),           //窗口标题
		WS_OVERLAPPEDWINDOW,       //窗口的风格
		CW_USEDEFAULT,             //窗口初始显示位置x:使用缺省值
		CW_USEDEFAULT,             //窗口初始显示位置y:使用缺省值
		476,
		530,                     //窗口的高度:使用缺省值
		NULL,                      //父窗口:无
		NULL,                      //子菜单:无
		hInstance,                 //该窗口应用程序的实例句柄 
		NULL                       //
	);

	ShowWindow(hwnd, iCmdShow);        //显示窗口
	UpdateWindow(hwnd);                //更新窗口

	while (GetMessage(&msg, NULL, 0, 0))        //从消息队列中获取消息
	{
		TranslateMessage(&msg);                 //将虚拟键消息转换为字符消息
		DispatchMessage(&msg);                  //分发到回调函数(过程函数)
	}
	return msg.wParam;
}
HDC hdc;    //设备环境句柄
HDC hdcmem;
HBITMAP hbmMem;
PAINTSTRUCT ps;         //绘制结构
RECT rect;          //矩形结构

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int count = 0;
	hdc = GetDC(hwnd);
	//	hdc = BeginPaint(hwnd, &ps);
	hdcmem = CreateCompatibleDC(hdc);//创建了一个兼容的dc，getDC获得的是物理的DC
	hbmMem = CreateCompatibleBitmap(hdc,
		100, 100);
	GetClientRect(hwnd, &rect);//得到窗口矩形区域
	switch (message)        //处理得到的消息
	{
	case WM_CREATE: 
		CreateGame(hwnd, score, a, if_game_over, if_need_add_num,if_game_win);
        GamePaint(hwnd,hdcmem,hbmMem);
		return 0;

	case WM_PAINT:           //处理窗口区域无效时发来的消息
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
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}
void GamePaint(HWND hwnd, HDC hdcmem,
	HBITMAP hbmMem)
{
	RECT clientRect;
	HRGN bgRgn;
	HBRUSH hBrush;
	HPEN hPen;
	HDC hdc;    //设备环境句柄
	PAINTSTRUCT ps;         //绘制结构
	RECT rect;               //矩形结构

	hdc = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &rect);//得到窗口矩形区域
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientRect);
	bgRgn = CreateRectRgnIndirect(&clientRect);
	hBrush = CreateSolidBrush(RGB(255, 182, 193));
	FillRgn(hdc, bgRgn, hBrush);//用RGB（0，255，0）填充颜色

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
			MessageBox(hwnd, TEXT("Game over!!"), TEXT("结束"), MB_OK | MB_ICONINFORMATION);
				ExitProcess(0);
		}
		else
			return;

	}
	else
	{
		if (if_game_win == 1)
		{
			MessageBox(hwnd, TEXT("You win!!"), TEXT("结束"), MB_OK);
			ExitProcess(0);
		}
		srand((unsigned int)time(NULL));
		n = rand() % get_null_count(a); /* 确定在何处空位置生成随机数 */
	}
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 4; ++j) {
			/* 定位待生成的位置 */
			if (a[i][j] == 0 && n-- == 0) {
				a[i][j] = (rand() % 10 ? 2 : 4);
				if (a[i][j] == 2)
				{
					hBrush = CreateSolidBrush(RGB(245, 222, 179));
					SelectObject(hdc, hBrush);
					Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
				}
				else if (a[i][j] == 4)
				{
					hBrush = CreateSolidBrush(RGB(255, 222, 173));
					SelectObject(hdc, hBrush);
					Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
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
					80 + j * 100, 80 + i * 100, temp,                      //使字符串在窗口中垂直居中      
					lstrlen(temp)     //lstrlen函数获取字符串的长度
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
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 4)
			{
				hBrush = CreateSolidBrush(RGB(255, 222, 173));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 8)
			{
				hBrush = CreateSolidBrush(RGB(255, 165, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 16)
			{
				hBrush = CreateSolidBrush(RGB(255, 140, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 32)
			{
				hBrush = CreateSolidBrush(RGB(255, 127, 80));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 64)
			{
				hBrush = CreateSolidBrush(RGB(255, 69, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 128)
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 256)
			{
				hBrush = CreateSolidBrush(RGB(255, 215, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 512)
			{
				hBrush = CreateSolidBrush(RGB(255, 230, 140));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 1024)
			{
				hBrush = CreateSolidBrush(RGB(152, 251, 152));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
			}
			else if (a[i][j] == 2048)
			{
				hBrush = CreateSolidBrush(RGB(127, 255, 0));
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 30 + 100 * j, 30 + 100 * i, 30 + 100 * (j + 1), 30 + 100 * (i + 1));//勾边 paint 填充 brush/* 生成数字2或4，生成概率为9:1 */
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
			MessageBox(hwnd, TEXT("游戏结束！"), TEXT("结束"), MB_OK | MB_ICONINFORMATION);
			PostQuitMessage(0);
		}
	}
}

void CreateGame(HWND hwnd, // 主窗口句柄
	
	int score, int a[4][4],
	int if_game_over, int if_need_add_num,int if_game_win
	)
{
	// 设置随机数种子
	// 需要使用随机数生成食物的位置等。
	a[4][4] = { 0 };
	score = 0;
	if_game_over = 0;
	if_need_add_num = 0;
	if_game_win = 0;
}//可以添加再来一次
