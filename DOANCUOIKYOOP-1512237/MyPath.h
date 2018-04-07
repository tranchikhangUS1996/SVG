#pragma once
#include "figure.h"


class MyPathIngredient {
private:
	// danh sach mau cac loai lenh trong path
	static vector<MyPathIngredient*> SamplePath;
protected:
	// them mau
	static void addSample(MyPathIngredient* obj);
public:
	// tao doi tuong bang ten
	static vector<MyPathIngredient*> CreateObject(char *name);
	// xoa danh sach mau
	static void DeleteRegister();
	// tra ve ten cac lenh cua path
	virtual char* getName() = 0;
	// nhan ban doi tuong
	virtual MyPathIngredient* Clone() = 0;
	// loat thuoc tinh cho Attribute
	virtual void LoadAttribute(char* s, std::size_t start) = 0;
	// dang ki cac loai lenh cua path
	static void RegisterPathIngredient();
	// ve gdi+ voi diem  hien tai lastPooint
	virtual PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush , PointF* LastPoint = NULL, PointF*  StartPoint = NULL) = 0;
	// viet ra file SVG
	virtual void WriteSVGFile(ofstream &ofs) = 0;
	virtual ~MyPathIngredient();
};


class MoveTo : public MyPathIngredient {
	// vi tri dich
	PointF m_Pos;
public:
	MoveTo();
	MoveTo(MoveTo &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~MoveTo();
};

class ClosePath : public MyPathIngredient {
public:
	ClosePath();
	ClosePath(ClosePath &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush , PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~ClosePath();
};

class AbsoluteLineTo : public MyPathIngredient {
	// diem cuoi
	PointF m_End;
public:
	AbsoluteLineTo();
	AbsoluteLineTo(AbsoluteLineTo &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics,Pen* pen ,Brush* brush, PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~AbsoluteLineTo();
};

class HorizontalLineTo : public MyPathIngredient {
	// toa do X
	float m_X;
public:
	HorizontalLineTo();
	HorizontalLineTo(HorizontalLineTo &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~HorizontalLineTo();
};

class VerticalLineTo : public MyPathIngredient {
	//toa do Y
	float m_Y;
public:
	VerticalLineTo();
	VerticalLineTo(VerticalLineTo &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~VerticalLineTo();
};

class CubicBenzierCurve : public MyPathIngredient {
	// 3 diem cua duong cong
private:
	PointF m_p1;
	PointF m_p2;
	PointF m_p3;
public:
	CubicBenzierCurve();
	CubicBenzierCurve(CubicBenzierCurve &obj);
	// trien khai cac phuong thuc cua MyPathIngredient
	char* getName();
	MyPathIngredient* Clone();
	void LoadAttribute(char* s, std::size_t start);
	PointF DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen, Brush* brush, PointF* LastPoint = NULL, PointF*  StartPoint = NULL);
	void WriteSVGFile(ofstream &ofs);
	~CubicBenzierCurve();
};


class MyPathData : public Attribute {
private:
	// danh sach cac doi tuong con MyPathIngredient
	vector<MyPathIngredient*> m_list;
public:
	MyPathData();
	MyPathData(MyPathData &obj);
	char* GetName();
	Attribute* Clone();
	vector<MyPathIngredient*> getPathData();
	void SetAtribute(char* attr);
	void WriteSVGFile(ofstream &ofs);
	~MyPathData();
};




class MyPath : public DrawAttribute , public Figure {
private:
	// diem bat dau cua net ve truoc do
	PointF m_StartPoint;
	// diem hien tai
	PointF m_LastPoint;
public:
	MyPath();
	MyPath(MyPath &obj);
	// trien khai cac phuong thuc cua lop Figure
	char* ClassName();
	Figure* Clone();
	void RegisterAttribute();
	void DrawGDIPlus(HDC hdc);
	void WriteSVGFile(ofstream &ofs, int startAttribute=0);
	void DrawCImg(CImg<int> &Frame);
	void LoadAttribute(xml_node<> *node);
	void addAttribute(Attribute* obj);
	~MyPath();
};
