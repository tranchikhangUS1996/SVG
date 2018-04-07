#pragma once;
#include "figure.h"

class MyPolyline : public DrawAttribute, public Figure {
public:
	MyPolyline();
	MyPolyline(MyPolyline &obj);
	// trien khai cac method cua Figure
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void RegisterAttribute();
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyPolyline();
};