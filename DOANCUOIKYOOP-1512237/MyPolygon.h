#pragma once;
#include "figure.h"

class MyPolygon : public DrawAttribute, public Figure {
public:
	MyPolygon();
	MyPolygon(MyPolygon &obj);
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void RegisterAttribute();
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyPolygon();
};