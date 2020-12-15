#pragma once

#include "ImageProc.h"

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

	unsigned int Index(int input) { // You don't need it
		if (input == -2)
			return this->_Index;
		else {
			this->_Index = input;
			return 0;
		}
	}

	void operator=(IP_Rectangle& _Right) {
		int Index = this->_Index;
		memcpy(this, &_Right, sizeof(IP_Rectangle));
		this->_Index = Index;
	}

	~IP_Rectangle() {};
private:
	unsigned int _Index;
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

	unsigned int Index(int input) { // You don't need it
		if (input == -2)
			return this->_Index;
		else {
			this->_Index = input;
			return 0;
		}
	}

	void operator=(IP_Circle& _Right) {
		int Index = this->_Index;
		memcpy(this, &_Right, sizeof(IP_Circle));
		this->_Index = Index;
	}

	~IP_Circle() {};
private:
	unsigned int _Index;
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

	unsigned int Index(int input) { // You don't need it
		if (input == -2)
			return this->_Index;
		else {
			this->_Index = input;
			return 0;
		}
	}

	void operator=(IP_Image& _Right) {
		int Index = this->_Index;
		memcpy(this, &_Right, sizeof(IP_Image));
		this->_Index = Index;
	}

	~IP_Image() {};
private:
	unsigned int _Index;
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

	unsigned int Index(int input) { // You don't need it
		if (input == -2)
			return this->_Index;
		else {
			this->_Index = input;
			return 0;
		}
	}

	void operator=(IP_Text& _Right) {
		int Index = this->_Index;
		memcpy(this, &_Right, sizeof(IP_Text));
		this->_Index = Index;
	}

	~IP_Text() {};
private:
	unsigned int _Index;
};