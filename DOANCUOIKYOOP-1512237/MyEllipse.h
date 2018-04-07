#pragma once
#include "MyCircle.h"

// ke thua lp radius
class Rx : Radius {
public:
	Rx();
	Rx(Rx &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~Rx();
};

// lop Ry ke thua Radius
class Ry : Radius {
public:
	Ry();
	Ry(Ry &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~Ry();
};

class MyEllipse : public DrawAttribute, public Figure {
public:
	MyEllipse();
	MyEllipse(MyEllipse &obj);
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	// dang ki cac thuoc tinh cua rieng  elippse
	void RegisterAttribute();
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyEllipse();
};