#include <conio.h>
#include <atlstr.h>
#include "ImageProc.h"

int wmain(int argc, wchar_t** argv, wchar_t** envp) {
	ImageProc img(640, 480, 0xf9f9f9, EW_SHOWCONSOLE);
	
	IP_Object obj = IP_Object();
	IP_Object fps = IP_Object();
	img.Start();	// 开始渲染

	obj._ElemColor = 0x33bbff;

	img << obj << fps;  // 将 obj 对象和 fps 对象添加到渲染流内
	
	obj.X(50)
		.Y(50)
		.Width(50)
		.Height(50)
		.ElemColor(0xaaaaaa)
		.CornerRadiusWidth(16)
		.CornerRadiusHeight(16)
		.FontSize(30)
		.FontColor(0x555555)
		.String((WCHAR*)L"带噶好啊");

	fps.X(150)
		.Y(10)
		.ElemColor(0xaaaaaa)
		.FontColor(0x0)
		.FontSize(20);
	
	Sleep(1000);	// 等待动画播放完毕
	obj.X(250);

	Sleep(1000);
	obj.X(0)
		.Y(0)
		.CornerRadiusHeight(0)
		.CornerRadiusWidth(0)
		.Width(640)
		.Height(480)
		.TextDependent_X(true)
		.TextDependent_Y(true)
		.ElemColor(0xff55bb)
		.FontColor(0x000000);
	
	CString formatStr;
	formatStr.Format(L"%d FPS", (int)img.GetFPS());	// 格式化字符串
	fps.UNI_TransitionDuration(0);
	
	int FPS = 0;

	while (true) {		// 格式化字符串
		FPS = img.GetFPS();
		formatStr.Format(L"%d FPS", FPS);
		if (FPS < 300)
			fps._ElemColor = 0x5555ff;
		else if (FPS < 600)
			fps._ElemColor = 0x55ff55;
		else
			fps._ElemColor = 0xdddddd;
		fps.String((WCHAR*)(const WCHAR*)formatStr);
	}

	_getch();
	return 0;
}