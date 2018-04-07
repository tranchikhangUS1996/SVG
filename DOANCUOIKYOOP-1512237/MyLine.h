#pragma once
#include "figure.h"

class X1 : public XCoordinates {
public:
	X1();
	X1(X1 &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~X1();
};

class Y1 : public YCoordinates {
public:
	Y1();
	Y1(Y1 &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~Y1();
};

class X2 : public XCoordinates {
public:
	X2();
	X2(X2 &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~X2();
};

class Y2 : public YCoordinates {
public:
	Y2();
	Y2(Y2 &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual ~Y2();
};

class MyLine : public DrawAttribute, public Figure {
public:
	MyLine();
	MyLine(MyLine &obj);
	virtual char* ClassName();
	virtual Figure* Clone();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute);
	void RegisterAttribute();
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	virtual ~MyLine();
};
