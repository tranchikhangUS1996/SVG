#pragma once
#include "figure.h"

// ke thua lop Xccoordinates
class XCenter : public XCoordinates {
public:
	XCenter();
	XCenter(XCenter &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~XCenter();
};

// ke thua lop Yccoordinates
class YCenter : public YCoordinates {
public:
	YCenter();
	YCenter(YCenter &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~YCenter();
};



class MyCircle : public DrawAttribute, public Figure {
public:
	MyCircle();
	MyCircle(MyCircle &obj);
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	// dang ki cac thuoc tinh cau rieng Circle
	void RegisterAttribute();
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyCircle();
};