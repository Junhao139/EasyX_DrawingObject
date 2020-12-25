#include "IP_Object.h"
#include <iostream>

IP_Object::IP_Object() {
	this->_Coordinate.X = 0;
	this->_Coordinate.Y = 0;
	this->_Width = 5;
	this->_Height = 5;
	this->_Border = 0;
	this->_BorderColor = 0x000000;

	this->_ElemColor = 0x0;
	this->_CornerRadiusWidth = 2;
	this->_CornerRadiusHeight = 2;

	this->_BackgroundImage = nullptr;

	this->_String = nullptr;
	this->_FontFamily = (wchar_t*)L"Microsoft YaHei";
	this->_FontColor = 0x0;
	this->_FontSize = 10;
	this->_TextAntialiased = true;
	this->_TextDependent_X = false;
	this->_TextDependent_Y = false;

	this->TransitionDuration = 1000;

	this->FirstTime = true;
	this->TransitionTimingAnimation = { 1, 0, 0, 1 };

	this->_MyParent.TYPE = Obj_Object;
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	this->_MyParent.Valid = true;
	this->_MyParent.Obj = this;
}

COLORREF IP_Object::ColorrefFromRGB(BYTE R, BYTE G, BYTE B) {
	return RGB(R, G, B);
}

IP_Object& IP_Object::X(int x) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();

	IP_Object* next = (IP_Object*)(this->_MyParent.next);
	if (next != nullptr) { 
		next->_Coordinate.X = x;
	}
	else this->_Coordinate.X = x;
	return *this;
}

IP_Object& IP_Object::Y(int y) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_Coordinate.Y = y;
	else this->_Coordinate.Y = y;
	return *this;
}

IP_Object& IP_Object::Width(int width) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_Width = width;
	else this->_Width = width;
	return *this;
}

IP_Object& IP_Object::Height(int height) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_Height = height;
	else this->_Height = height;
	return *this;
}

IP_Object& IP_Object::Border(int border) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_Border = border;
	else this->_Border = border;
	return *this;
}

IP_Object& IP_Object::ElemColor(COLORREF elemColor) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_ElemColor = elemColor;
	else this->_ElemColor = elemColor;
	return *this;
}

IP_Object& IP_Object::CornerRadiusWidth(int cornerRadiusWidth) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_CornerRadiusWidth = cornerRadiusWidth;
	else this->_CornerRadiusWidth = cornerRadiusWidth;
	return *this;
}

IP_Object& IP_Object::CornerRadiusHeight(int cornerRadiusHeight) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_CornerRadiusHeight = cornerRadiusHeight;
	else this->_CornerRadiusHeight = cornerRadiusHeight;
	return *this;
}

IP_Object& IP_Object::BackgroundImage(IMAGE* img) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_BackgroundImage = img;
	else this->_BackgroundImage = img;
	return *this;
}

IP_Object& IP_Object::String(WCHAR* str) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_String = str;
	else this->_String = str;
	return *this;
}

IP_Object& IP_Object::FontFamily(WCHAR* fontFamily) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_FontFamily = fontFamily;
	else this->_FontFamily = fontFamily;
	return *this;
}

IP_Object& IP_Object::FontColor(COLORREF fontColor) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_FontColor = fontColor;
	else this->_FontColor = fontColor;
	return *this;
}

IP_Object& IP_Object::FontSize(int fontSize) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_FontSize = fontSize;
	else this->_FontSize = fontSize;
	return *this;
}

IP_Object& IP_Object::TextAntialiased(bool antialise) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr) next->_TextAntialiased = antialise;
	else this->_TextAntialiased = antialise;
	return *this;
}

IP_Object& IP_Object::TextDependent_X(bool dependenceX) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (this->_String != nullptr) {
		if (next != nullptr) { 
			next->_TextDependent_X = dependenceX; 
			next->_Width = textwidth(this->_String);
		}
		else {
			this->_TextDependent_X = dependenceX;
			this->_Width = textwidth(this->_String);
		}
	}
	return *this;
}

IP_Object& IP_Object::TextDependent_Y(bool dependenceY) {
	this->_MyParent.startPoint = std::chrono::steady_clock::now();
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (this->_String != nullptr) {
		if (next != nullptr) {
			next->_TextDependent_Y = dependenceY;
			next->_Height = textheight(this->_String);
		}
		else {
			this->_TextDependent_Y = dependenceY;
			this->_Height = textheight(this->_String);
		}
	}
	return *this;
}

IP_Object& IP_Object::UNI_TransitionTimingAnimation(BezierLine animation) {
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr)
		next->TransitionTimingAnimation = animation;
	else
		this->TransitionTimingAnimation = animation;
	return *this;
}

IP_Object& IP_Object::UNI_TransitionDuration(unsigned long long milliseconds) {
	IP_Object* next = (IP_Object*)this->_MyParent.next;
	if (next != nullptr)
		next->TransitionDuration = milliseconds;
	else
		this->TransitionDuration = milliseconds;
	return *this;
}

unsigned int IP_Object::Index(int input, int dynamicCode, _Out_ ObjectProps** myParent) { 
	if (input == _RETURN_CODE_) {
		return this->_Index;
	} else {
		if (this->FirstTime) {
			this->_Index = input;
			this->DynamicCode = dynamicCode;
			*myParent = &(this->_MyParent);
			this->FirstTime = false;
		} else if (this->DynamicCode == dynamicCode) {
			this->_Index = input;
		}
		return 0;
	}
}

IP_Object& IP_Object::fromObject(IP_Object& _rightObj) {
	int Index = _rightObj._Index;
	memcpy(this, &_rightObj, sizeof(IP_Object));
	this->_Index = Index;
	return *this;
}

IP_Object::~IP_Object() {
	delete (this->_MyParent.next);
}