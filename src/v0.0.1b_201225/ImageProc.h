#pragma once

#include <Windows.h>
#include <easyx.h>
//#include <ObjIdl.h>
//#include <gdiplus.h>
//#pragma comment(lib, "Gdiplus.lib")

#include <vector>
#include <thread>
#include <iostream>

#include "IP_Object.h"
#include "ObjectProps.h"

class ImageProc {
public:
	ImageProc(int Width, int Height, COLORREF BgColor, int Cmd = NULL)
		: _ViewportWidth(Width), _ViewportHeight(Height) {
		initgraph(Width, Height, Cmd);
		this->BackgroundColor = BgColor;
		setbkcolor(BgColor);
		setbkmode(TRANSPARENT);
		cleardevice();
		BeginBatchDraw();
		this->ConstantFPS = 0;

		this->_hDC = GetImageHDC(nullptr);
		this->_hWnd = GetHWnd();
		this->_hInstance = GetModuleHandle(NULL);

		this->_AutoClose = true;
		this->AverageFPS_CalcTimes = 1;
		this->AverageFPS = 0;

		//this->_graphics = new Gdiplus::Graphics(GetImageHDC());
		//this->_SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 0));

		srand(time(0));
		this->DynamicCode = rand();
	};

	void Start();
	void Close();	// Only when AutoClose is set as false

	void AddElement(IP_Object* obj);
	ImageProc& operator<<(IP_Object& obj);
	void RemoveElement(IP_Object* obj);
	void RecoverElement(IP_Object* obj, bool ToTop = false);

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
	std::vector<ObjectProps*> RenderList;
	std::thread RenderProcess;

	//Gdiplus::SolidBrush* _SolidBrush;
	//Gdiplus::Graphics* _graphics;

	int _ViewportWidth;
	int _ViewportHeight;

	double ConstantFPS;
	double CurrentFPS;
	double AverageFPS;
	unsigned int AverageFPS_CalcTimes;

	bool MsgKey = true;
	static void Render(bool* Key, ImageProc* parent);
	void ProcessObject(int ObjType, double Statement, void* RetVal, void* Original, void* FinalState);
	
	double BEZIER(double Time, double x1, double y1, double x2, double y2);
	double Get_Bezier(double process, double param1, double param2) { return param1 + (process * (param2 - param1)); }

	HINSTANCE _hInstance;
	HWND _hWnd;
	HDC _hDC;

	bool _AutoClose;
	int DynamicCode;
};
