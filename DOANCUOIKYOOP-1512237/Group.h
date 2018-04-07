#pragma once

#include "figure.h"

class Group : public DrawAttribute, public Figure {
private:
	// danh sach cac Figure con cua group
	vector<Figure*> m_ListFigure;
public:
	Group();
	Group(Group &obj);
	// trien khai cac phuong thuc cua Figure
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	int getNumAttribute();
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void RegisterAttribute();
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~Group();
};