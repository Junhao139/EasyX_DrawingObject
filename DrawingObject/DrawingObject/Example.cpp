#include <conio.h>
#include <atlstr.h>
#include "ImageProc.h"

int wmain(int argc, wchar_t** argv, wchar_t** envp) {
	ImageProc img(640, 480, 0xffffff, NULL);
	IP_Text txt((WCHAR*)L"Hello world!", 10, 10, 0x000000, 20, (WCHAR*)L"Microsoft YaHei");
	IP_Rectangle rect(10, 40, 100, 20, 0xbfbfbf, 5);
	
	img.AddElement(&txt);
	img.AddElement(&rect);

	CString formatStr;
	formatStr.Format(L"%d FPS", (int)img.GetFPS());
	IP_Text fps((WCHAR*)(const WCHAR*)formatStr, 100, 10, 0x000000, 20);

	img.AddElement(&fps);

	img.Start();	// ESSENTIAL!!!!

	while (true) {
		if (_kbhit()) {
			if (_getch() == ' ') {
				break;
			}
		}

		formatStr.Format(L"%d FPS", (int)img.GetFPS());
		fps = IP_Text((WCHAR*)(const WCHAR*)formatStr, 100, 10, 0x000000, 20);
	}

	_getch();
	return 0;
}