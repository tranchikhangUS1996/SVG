#pragma once
#include "figure.h"

class MyRectangle : public DrawAttribute, public Figure {
public:
	MyRectangle();
	MyRectangle(MyRectangle &obj);
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void DrawCImg(CImg<int> &Frame);
	void RegisterAttribute();
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyRectangle();
};