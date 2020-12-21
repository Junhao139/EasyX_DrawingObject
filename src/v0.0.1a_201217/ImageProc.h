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
		this->AverageFPS_CalcTimes = 1;
		this->AverageFPS = 0;
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

	int GetViewportWidth() const { return this->_ViewportWidth; }
	int GetViewportHeight() const { return this->_ViewportHeight; }
	void SetViewportWidth(int Width) { this->_ViewportWidth = Width; }
	void SetViewportHeight(int Height) { this->_ViewportHeight = Height; }
	void SetBgColor(COLORREF Color) { this->BackgroundColor = Color; }

	HDC GetHDC() const { return this->_hDC; }
	HWND GetImageHWnd() const { return this->_hWnd; }
	HINSTANCE GetHInstance() const { return this->_hInstance; }

	double GetFPS() const { return this->CurrentFPS; }
	double GetAverageFPS() const { return this->AverageFPS; }
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
	double AverageFPS;
	unsigned int AverageFPS_CalcTimes;

	bool MsgKey = true;
	static void Render(bool* Key, ImageProc* parent);

	HINSTANCE _hInstance;
	HWND _hWnd;
	HDC _hDC;

	bool _AutoClose;
};
