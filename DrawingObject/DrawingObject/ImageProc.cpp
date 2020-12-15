#include "ImageProc.h"

void ImageProc::Start() {
	this->RenderProcess = std::thread(Render, &(this->MsgKey), this);
}

void ImageProc::Close() {
	if (!this->_AutoClose) {
		this->MsgKey = false;
		this->RenderProcess.join();
		EndBatchDraw();
		closegraph();
	}
}

void ImageProc::AddElement(IP_Rectangle* rect) {
	rect->Index(RenderList.size());
	RenderList.push_back({ Obj_Rectangle, std::chrono::steady_clock::now(), true, rect });
}

void ImageProc::RemoveElement(IP_Rectangle* rect) {
	RenderList[rect->Index(-2)].Valid = false;
}

void ImageProc::RecoverElement(IP_Rectangle* rect, bool ToTop) {
	if (ToTop) {
		this->AddElement(rect);
	} else {
		RenderList[rect->Index(-2)].Valid = true;
	}
}

void ImageProc::AddElement(IP_Circle* circle) {
	circle->Index(RenderList.size());
	RenderList.push_back({ Obj_Circle, std::chrono::steady_clock::now(), true, circle });
}

void ImageProc::RemoveElement(IP_Circle* circle) {
	RenderList[circle->Index(-2)].Valid = false;
}

void ImageProc::RecoverElement(IP_Circle* circle, bool ToTop) {
	int Index;
	if (ToTop) {
		this->AddElement(circle);
	} else {
		RenderList[circle->Index(-2)].Valid = true;
	}
}

void ImageProc::AddElement(IP_Image* img) {
	img->Index(RenderList.size());
	RenderList.push_back({ Obj_Image, std::chrono::steady_clock::now(), true, img });
}

void ImageProc::RemoveElement(IP_Image* img) {
	RenderList[img->Index(-2)].Valid = false;
}

void ImageProc::RecoverElement(IP_Image* img, bool ToTop) {
	if (ToTop) {
		this->AddElement(img);
	} else {
		RenderList[img->Index(-2)].Valid = true;
	}
}

void ImageProc::AddElement(IP_Text* txt) {
	txt->Index(RenderList.size());
	RenderList.push_back({ Obj_Text, std::chrono::steady_clock::now(), true, txt });
}

void ImageProc::RemoveElement(IP_Text* txt) {
	RenderList[txt->Index(-2)].Valid = false;
}

void ImageProc::RecoverElement(IP_Text* txt, bool ToTop) {
	if (ToTop) {
		this->AddElement(txt);
	} else {
		RenderList[txt->Index(-2)].Valid = true;
	}
}

void ImageProc::ClearRenderList() {
	RenderList.clear();
}

void ImageProc::Render(bool* Key, ImageProc* parent) {
	int ListSize;
	IP_Rectangle* ptr_Rectangle;
	IP_Circle* ptr_Circle;
	IP_Image* ptr_Image;
	IP_Text* ptr_Text;

	using namespace std::chrono;
	steady_clock::time_point BeginCount, EndCount;

	duration<unsigned long long, std::micro> BeginEpoch;
	duration<unsigned long long, std::micro> EndEpoch;
	duration<unsigned long long, std::micro> Duration;

	BeginCount = steady_clock::now();
	while (*Key) {
		ListSize = parent->RenderList.size();

		setbkcolor(parent->BackgroundColor);
		cleardevice();
		for (int order = 0; order < ListSize; ++order) {
			if (parent->RenderList[order].Valid) {
				switch (parent->RenderList[order].TYPE) {
				case Obj_Rectangle: {
					ptr_Rectangle = (IP_Rectangle*)parent->RenderList[order].Obj;
					setfillcolor(ptr_Rectangle->_Color);
					solidroundrect(
						ptr_Rectangle->_Coordinate.X,
						ptr_Rectangle->_Coordinate.Y,
						ptr_Rectangle->_Coordinate.X + ptr_Rectangle->_Width,
						ptr_Rectangle->_Coordinate.Y + ptr_Rectangle->_Height,
						ptr_Rectangle->_CornerRadius, ptr_Rectangle->_CornerRadius
					);
				} break;

				case Obj_Circle: {
					ptr_Circle = (IP_Circle*)parent->RenderList[order].Obj;
					setfillcolor(ptr_Circle->_Color);
					solidellipse(
						ptr_Circle->_Coordinate.X,
						ptr_Circle->_Coordinate.Y,
						ptr_Circle->_Coordinate.X + ptr_Circle->_Width,
						ptr_Circle->_Coordinate.Y + ptr_Circle->_Height
					);
				} break;

				case Obj_Image: {
					ptr_Image = (IP_Image*)parent->RenderList[order].Obj;
					putimage(
						ptr_Image->_Coordinate.X,
						ptr_Image->_Coordinate.Y,
						ptr_Image->_Width,
						ptr_Image->_Height,
						ptr_Image->_Image,
						0, 0
					);
				} break;

				case Obj_Text: {
					ptr_Text = (IP_Text*)parent->RenderList[order].Obj;
					settextstyle(
						ptr_Text->_Height,
						0,
						ptr_Text->_FontFamily,
						0, 0, 0, 0, 0, 0,
						DEFAULT_CHARSET,
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						DEFAULT_PITCH
					);
					settextcolor(ptr_Text->_Color);
					outtextxy(ptr_Text->_Coordinate.X, ptr_Text->_Coordinate.Y, ptr_Text->_String);
				} break;

				}
			}
		}

		FlushBatchDraw();
		if (parent->ConstantFPS != 0) {
			while (Duration.count() < (1000000 / parent->ConstantFPS)) {
				EndCount = steady_clock::now();
				Duration = duration_cast<duration<unsigned long long, std::micro>>(EndCount - BeginCount);
			}
		}

		EndCount = steady_clock::now();
		Duration = duration_cast<duration<unsigned long long, std::micro>>(EndCount - BeginCount);
		BeginCount = steady_clock::now();

		parent->CurrentFPS = 1000000.0 / Duration.count();
	}
}

void ImageProc::AutomaticClose(bool ifTrue) {
	this->_AutoClose = false;
}

ImageProc::~ImageProc() {
	if (this->_AutoClose) {
		this->MsgKey = false;
		this->RenderProcess.join();
		EndBatchDraw();
		closegraph();
	}
}