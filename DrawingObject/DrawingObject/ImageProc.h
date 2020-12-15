#pragma once

#include <Windows.h>
#include <chrono>
#include <easyx.h>
#include <vector>
#include <thread>

#include "IP_Object.h"

enum OBJ_TYPES { Obj_Rectangle, Obj_Circle, Obj_Image, Obj_Text };
struct ObjectProps {
	int TYPE;
	std::chrono::steady_clock::time_point startPoint;
	bool Valid;
	void* Obj;
};

class ImageProc {
public:
	ImageProc(int Width, int Height, COLORREF BgColor, int Cmd = NULL)
		: _ViewportWidth(Width), _ViewportHeight(Height) {
		initgraph(Width, Height, Cmd);
		this->BackgroundColor = BgColor;
		setbkcolor(BgColor);
		cleardevice();
		BeginBatchDraw();
		this->ConstantFPS = 0;

		this->_hDC = GetImageHDC(nullptr);
		this->_hWnd = GetHWnd();
		this->_hInstance = GetModuleHandle(NULL);

		this->_AutoClose = true;
	};

	void Start();
	void Close();	// Only when AutoClose is set as false

	void AddElement(IP_Rectangle* rect);
	void RemoveElement(IP_Rectangle* rect);
	void RecoverElement(IP_Rectangle* rect, bool ToTop = false);

	void AddElement(IP_Circle* circle);
	void RemoveElement(IP_Circle* circle);
	void RecoverElement(IP_Circle* circle, bool ToTop = false);

	void AddElement(IP_Image* img);
	void RemoveElement(IP_Image* img);
	void RecoverElement(IP_Image* img, bool ToTop = false);

	void AddElement(IP_Text* txt);
	void RemoveElement(IP_Text* txt);
	void RecoverElement(IP_Text* txt, bool ToTop = false);

	void ClearRenderList();

	int GetViewportWidth() { return this->_ViewportWidth; }
	int GetViewportHeight() { return this->_ViewportHeight; }
	void SetViewportWidth(int Width) { this->_ViewportWidth = Width; }
	void SetViewportHeight(int Height) { this->_ViewportHeight = Height; }
	void SetBgColor(COLORREF Color) { this->BackgroundColor = Color; }

	HDC GetHDC() { return this->_hDC; }
	HWND GetImageHWnd() { return this->_hWnd; }
	HINSTANCE GetHInstance() { return this->_hInstance; }

	double GetFPS() const { return this->CurrentFPS; }
	void SetConstFPS(double fps) { this->ConstantFPS = fps; }

	void AutomaticClose(bool ifTrue);

	~ImageProc();
private:
	COLORREF BackgroundColor;
	std::vector<ObjectProps> RenderList;
	std::thread RenderProcess;

	int _ViewportWidth;
	int _ViewportHeight;

	double ConstantFPS;
	double CurrentFPS;

	bool MsgKey = true;
	static void Render(bool* Key, ImageProc* parent);

	HINSTANCE _hInstance;
	HWND _hWnd;
	HDC _hDC;

	bool _AutoClose;
};