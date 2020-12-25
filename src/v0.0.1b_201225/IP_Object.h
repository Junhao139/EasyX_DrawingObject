#pragma once

#include <easyx.h>

#include "ObjectProps.h"

#define _RETURN_CODE_ -2

struct BezierLine {
	double X1;
	double Y1;
	double X2;
	double Y2;
};

class IP_Object {
public:
	COORD _Coordinate;
	int _Width;
	int _Height;
	int _Border;
	COLORREF _BorderColor;

	COLORREF _ElemColor;
	int _CornerRadiusWidth;
	int _CornerRadiusHeight;

	IMAGE* _BackgroundImage;
	
	WCHAR* _String;
	WCHAR* _FontFamily;
	COLORREF _FontColor;
	int _FontSize;
	bool _TextAntialiased;
	bool _TextDependent_X;
	bool _TextDependent_Y;

	BezierLine TransitionTimingAnimation;
	unsigned long long TransitionDuration;

	IP_Object();

	COLORREF ColorrefFromRGB(BYTE R, BYTE G, BYTE B);

	IP_Object& X(int x);
	IP_Object& Y(int y);
	IP_Object& Width(int width);
	IP_Object& Height(int height);
	IP_Object& Border(int border);
	IP_Object& BorderColor(int borderColor);

	IP_Object& ElemColor(COLORREF elemColor);
	IP_Object& CornerRadiusWidth(int cornerRadiusWidth);
	IP_Object& CornerRadiusHeight(int cornerRadiusHeight);

	IP_Object& BackgroundImage(IMAGE* img);

	IP_Object& String(WCHAR* str);
	IP_Object& FontFamily(WCHAR* fontFamily);
	IP_Object& FontColor(COLORREF fontColor);
	IP_Object& FontSize(int fontSize);
	IP_Object& TextAntialiased(bool antialise);
	IP_Object& TextDependent_X(bool dependenceX);
	IP_Object& TextDependent_Y(bool dependenceY);

	IP_Object& UNI_TransitionTimingAnimation(BezierLine animation);
	IP_Object& UNI_TransitionDuration(unsigned long long milliseconds);

	unsigned int Index(int input, int dynamicCode, _Out_ ObjectProps** myParent);
	IP_Object& fromObject(IP_Object& _rightObj);
	
	~IP_Object();
private:
	unsigned int _Index;
	bool FirstTime;
	int DynamicCode;
	ObjectProps _MyParent;
};