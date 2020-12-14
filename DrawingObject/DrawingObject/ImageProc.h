#pragma once

#include <Windows.h>
#include <chrono>
#include <easyx.h>
#include <vector>
#include <thread>

enum OBJ_TYPES { Obj_Rectangle, Obj_Circle, Obj_Image, Obj_Text };
struct ObjectProps {
	int TYPE;
	std::chrono::steady_clock::time_point startPoint;
	void* Obj;
};

class IP_Rectangle {
public:
	COORD _Coordinate;
	int _Width;
	int _Height;
	COLORREF _Color;
	int _CornerRadius;
	unsigned long long TransitionDuration = 1000;	// Milliseconds

	IP_Rectangle(int X = 0, int Y = 0, int Width = 20, int Height = 20, COLORREF Color = 0, int CornerRadius = 0)
		: _Coordinate({ (short)X, (short)Y }), _Width(Width), _Height(Height), _Color(Color), _CornerRadius(CornerRadius) {}

	~IP_Rectangle() {};
private:

};

class IP_Circle {
public:
	COORD _Coordinate;
	int _Width;
	int _Height;
	COLORREF _Color;

	unsigned long long TransitionDuration = 1000;	// Milliseconds

	IP_Circle(int X = 0, int Y = 0, int Width = 20, int Height = 20, COLORREF Color = 0)
		: _Coordinate({ (short)X, (short)Y }), _Width(Width), _Height(Height), _Color(Color) {}

	~IP_Circle() {};
private:
};

class IP_Image {
public:
	COORD _Coordinate;
	int _Width;
	int _Height;
	IMAGE* _Image;

	unsigned long long TransitionDuration = 1000;	// Milliseconds

	IP_Image(IMAGE* Img, int X = 0, int Y = 0, int Width = 20, int Height = 20)
		: _Image(Img), _Coordinate({ (short)X, (short)Y }), _Width(Width), _Height(Height) {}

	~IP_Image() {};
private:
};

class IP_Text {
public:
	COORD _Coordinate;
	int _Height;
	WCHAR* _String;
	WCHAR* _FontFamily;
	COLORREF _Color;

	unsigned long long TransitionDuration = 1000;	// Milliseconds

	IP_Text(WCHAR* Str, int X = 0, int Y = 0, COLORREF Color = 0, int Height = 20, WCHAR* FontFamily = nullptr)
		: _String(Str), _Coordinate({ (short)X, (short)Y }), _Height(Height), _FontFamily(FontFamily), _Color(Color) {
		if (FontFamily == nullptr) {
			_FontFamily = (WCHAR*)L"Microsoft YaHei";
		}
	}

	~IP_Text() {};
private:
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
	};

	void Start();
	void AddElement(IP_Rectangle* rect);
	void AddElement(IP_Circle* circle);
	void AddElement(IP_Image* img);
	void AddElement(IP_Text* txt);

	int GetViewportWidth() { return this->_ViewportWidth; }
	int GetViewportHeight() { return this->_ViewportHeight; }
	void SetViewportWidth(int Width) { this->_ViewportWidth = Width; }
	void SetViewportHeight(int Height) { this->_ViewportHeight = Height; }

	HDC GetHDC() { return this->_hDC; }
	HWND GetImageHWnd() { return this->_hWnd; }
	HINSTANCE GetHInstance() { return this->_hInstance; }

	double GetFPS() const { return this->CurrentFPS; }
	void SetConstFPS(double fps) { this->ConstantFPS = fps; }

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
};