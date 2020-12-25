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

void ImageProc::AddElement(IP_Object* obj) {
	RenderList.push_back(nullptr);

	ObjectProps *Obj = nullptr, **PTR = &Obj;

	int Index = RenderList.size() - 1;
	obj->Index(Index, this->DynamicCode, PTR);
	Obj = *PTR;
	if ((Obj->next == nullptr))
		(Obj)->next = new IP_Object;
	RenderList[Index] = Obj;
	
	memcpy(RenderList[Index]->next, RenderList[Index]->Obj, sizeof(IP_Object));
}

ImageProc& ImageProc::operator<<(IP_Object& obj) {
	this->AddElement(&obj);
	return *this;
}

void ImageProc::RemoveElement(IP_Object* obj) {
	RenderList[obj->Index(_RETURN_CODE_, this->DynamicCode, nullptr)]->Valid = false;
}

void ImageProc::RecoverElement(IP_Object* obj, bool ToTop) {
	if (ToTop) {
		this->AddElement(obj);
	} else {
		RenderList[obj->Index(_RETURN_CODE_, this->DynamicCode, nullptr)]->Valid = true;
	}
}

void ImageProc::ClearRenderList() {
	RenderList.clear();
}

void ImageProc::Render(bool* Key, ImageProc* parent) {
	int ListSize;
	static IP_Object* ptr_Object;
	static IP_Object* ptr_Object_next;
	static IP_Object CalculatedValues;
	long double Statement;
	
	using namespace std::chrono;

	steady_clock::time_point BeginCount, EndCount;

	duration<unsigned long long, std::micro> BeginEpoch;
	duration<unsigned long long, std::micro> EndEpoch;
	duration<unsigned long long, std::micro> Duration;

	BeginCount = steady_clock::now();
	BeginEpoch = duration_cast<duration<unsigned long long, std::micro>>(BeginCount.time_since_epoch());

	unsigned long long ElementTimepoint;
	unsigned long long ElementTimeDistance;
	int order;
	
	while (*Key) {
		ListSize = parent->RenderList.size();

		setbkcolor(parent->BackgroundColor);
		cleardevice();
		for (order = 0; order < ListSize; ++order) {
			if (parent->RenderList[order] != nullptr && parent->RenderList[order]->Valid) {
				switch (parent->RenderList[order]->TYPE) {
				case Obj_Object: {
					ptr_Object = (IP_Object*)parent->RenderList[order]->Obj;
					if (	/* If now is inTime */
						(ElementTimeDistance = (
							BeginEpoch.count() - 
							(ElementTimepoint = (
								duration_cast<duration<unsigned long long, std::micro>>(parent->RenderList[order]->startPoint.time_since_epoch())
									).count()
								)
							)
						) < (ptr_Object->TransitionDuration * 1000)
					) {
						Statement = 1.0 - (((ptr_Object->TransitionDuration * 1000.0) - ElementTimeDistance) / 1000000.0);
						Statement = parent->BEZIER(
							Statement, 
							ptr_Object->TransitionTimingAnimation.X1, 
							ptr_Object->TransitionTimingAnimation.Y1,
							ptr_Object->TransitionTimingAnimation.X2, 
							ptr_Object->TransitionTimingAnimation.Y2
						);
						memcpy(&CalculatedValues, parent->RenderList[order]->Obj, sizeof(IP_Object));
						parent->ProcessObject(Obj_Object, Statement, &CalculatedValues, ptr_Object, parent->RenderList[order]->next);
					} else if (ElementTimeDistance >= (ptr_Object->TransitionDuration * 1000)) {
						memcpy(parent->RenderList[order]->Obj, parent->RenderList[order]->next, sizeof(IP_Object));
						memcpy(&CalculatedValues, parent->RenderList[order]->Obj, sizeof(IP_Object));
					}

					if (CalculatedValues._BackgroundImage != nullptr) {
						putimage(
							CalculatedValues._Coordinate.X,
							CalculatedValues._Coordinate.Y,
							CalculatedValues._Width,
							CalculatedValues._Height,
							CalculatedValues._BackgroundImage,
							0, 0
						);
					}

					setfillcolor(CalculatedValues._ElemColor);
					if (CalculatedValues._Border) {
						setlinecolor(CalculatedValues._BorderColor);
					}
					fillroundrect(
						CalculatedValues._Coordinate.X,
						CalculatedValues._Coordinate.Y,
						CalculatedValues._Coordinate.X + CalculatedValues._Width,
						CalculatedValues._Coordinate.Y + CalculatedValues._Height,
						CalculatedValues._CornerRadiusWidth,
						CalculatedValues._CornerRadiusHeight
					);

					

					if (CalculatedValues._String != nullptr) {
						settextcolor(CalculatedValues._FontColor);
						settextstyle(
							CalculatedValues._FontSize,
							0,
							CalculatedValues._FontFamily,
							0, 0, 0, 0, 0, 0,
							DEFAULT_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CalculatedValues._TextAntialiased ? ANTIALIASED_QUALITY : DEFAULT_QUALITY,
							DEFAULT_PITCH
						);

						outtextxy(CalculatedValues._Coordinate.X, CalculatedValues._Coordinate.Y, CalculatedValues._String);
					}

 				} break;

				}
			}
		}

		FlushBatchDraw();
		
		EndCount = steady_clock::now();
		Duration = duration_cast<duration<unsigned long long, std::micro>>(EndCount - BeginCount);
		BeginCount = steady_clock::now();
		BeginEpoch = duration_cast<duration<unsigned long long, std::micro>>(BeginCount.time_since_epoch());

		parent->CurrentFPS = 1000000.0 / Duration.count();
		parent->AverageFPS = (parent->AverageFPS + parent->CurrentFPS) / 2;
		
		/*
		if (parent->ConstantFPS != 0) {
			Sleep(DWORD(((1000000 / parent->ConstantFPS) - Duration.count()) / 1000));
		}*/
	}
}

void ImageProc::ProcessObject(int ObjType, double Statement, void* RetVal, void* Original, void* FinalState) {
	IP_Object *objPtr_original, *objPtr_final, *objPtr_retVal;
	BYTE _R, _G, _B;

	switch (ObjType) {
	case Obj_Object:
		objPtr_original = (IP_Object*)Original;
		objPtr_final = (IP_Object*)FinalState;
		objPtr_retVal = (IP_Object*)RetVal;

		/* X Position */
		if (objPtr_original->_Coordinate.X != objPtr_final->_Coordinate.X) 
			objPtr_retVal->_Coordinate.X = objPtr_original->_Coordinate.X + (Statement * (objPtr_final->_Coordinate.X - objPtr_original->_Coordinate.X));
		/* Y Position */
		if (objPtr_original->_Coordinate.Y != objPtr_final->_Coordinate.Y)
			objPtr_retVal->_Coordinate.Y = objPtr_original->_Coordinate.Y + Statement * (objPtr_final->_Coordinate.Y - objPtr_original->_Coordinate.Y);
		/* Width */
		if (objPtr_original->_Width != objPtr_final->_Width)
			objPtr_retVal->_Width = objPtr_original->_Width + Statement * (objPtr_final->_Width - objPtr_original->_Width);
		/* Height */
		if (objPtr_original->_Height != objPtr_final->_Height)
			objPtr_retVal->_Height = objPtr_original->_Height + Statement * (objPtr_final->_Height - objPtr_original->_Height);
		/* Border */
		if (objPtr_original->_Border != objPtr_final->_Border)
			objPtr_retVal->_Border = objPtr_original->_Border + Statement * (objPtr_final->_Border - objPtr_original->_Border);
		/* Element color */
		if (objPtr_original->_ElemColor != objPtr_final->_ElemColor) {
			objPtr_retVal->_ElemColor = RGB(
				(_R = GetRValue(objPtr_original->_ElemColor)) + Statement * (GetRValue(objPtr_final->_ElemColor) - _R),
				(_G = GetGValue(objPtr_original->_ElemColor)) + Statement * (GetGValue(objPtr_final->_ElemColor) - _G),
				(_B = GetBValue(objPtr_original->_ElemColor)) + Statement * (GetBValue(objPtr_final->_ElemColor) - _B)
			);
		}
		/* Corner Radius Width */
		if (objPtr_original->_CornerRadiusWidth != objPtr_final->_CornerRadiusWidth)
			objPtr_retVal->_CornerRadiusWidth = objPtr_original->_CornerRadiusWidth + Statement * (objPtr_final->_CornerRadiusWidth - objPtr_original->_CornerRadiusWidth);
		/* Corner Radius Height */
		if (objPtr_original->_CornerRadiusHeight != objPtr_final->_CornerRadiusHeight)
			objPtr_retVal->_CornerRadiusHeight = objPtr_original->_CornerRadiusHeight + Statement * (objPtr_final->_CornerRadiusHeight - objPtr_original->_CornerRadiusHeight);
		/* Background Image */
		if (Statement >= 0.5)
			objPtr_retVal->_BackgroundImage = objPtr_final->_BackgroundImage;
		/* String */
		if (Statement >= 0.5)
			objPtr_retVal->_String = objPtr_final->_String;
		/* Font family */
		if (Statement >= 0.5)
			objPtr_retVal->_FontFamily = objPtr_final->_FontFamily;
		/* Font color */
		if (objPtr_original->_FontColor != objPtr_final->_FontColor) {
			objPtr_retVal->_FontColor = RGB(
				(_R = GetRValue(objPtr_original->_FontColor)) + Statement * (GetRValue(objPtr_final->_FontColor) - _R),
				(_G = GetGValue(objPtr_original->_FontColor)) + Statement * (GetGValue(objPtr_final->_FontColor) - _G),
				(_B = GetBValue(objPtr_original->_FontColor)) + Statement * (GetBValue(objPtr_final->_FontColor) - _B)
			);
		}
		/* Font Size */
		if (objPtr_original->_FontSize != objPtr_final->_FontSize)
			objPtr_retVal->_FontSize = objPtr_original->_FontSize + Statement * (objPtr_final->_FontSize - objPtr_original->_FontSize);
		/* Text antialiased */
		if (Statement >= 0.5)
			objPtr_retVal->_TextAntialiased = objPtr_final->_TextAntialiased;

		break;
	}
}

double ImageProc::BEZIER(double Time, double x1, double y1, double x2, double y2) {
	double Y;
	return this->Get_Bezier(
		Time, 
		this->Get_Bezier(
			Time, 
			this->Get_Bezier(Time, 0.0, y1), 
			(Y = this->Get_Bezier(Time, y1, y2))
		), 
		this->Get_Bezier(
			Time, 
			Y, 
			this->Get_Bezier(Time, y2, 1.0)
		)
	);
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

	delete this->_graphics;
	delete this->_SolidBrush;
}