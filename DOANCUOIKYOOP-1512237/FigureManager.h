#pragma once
#include "MyCircle.h"
#include "MyEllipse.h"
#include "MyLine.h"
#include "MyPolygon.h"
#include "MyPolyline.h"
#include "MyRectangle.h"
#include "Group.h"
#include "MyPath.h"
#include "MyText.h"

class FigureManager {
private:
	vector<Figure*> m_list;
public:
	FigureManager();
	FigureManager(FigureManager &obj);
	FigureManager(vector<Figure*> list);
	void registerFigure();
	void DeRegisterStaticIngredient();
	void Load(WCHAR*Link);
	void DrawGdiPlus(HDC &hdc);
	void DrawCImg();
	void WriteSVG(WCHAR* link);
	virtual ~FigureManager();
};