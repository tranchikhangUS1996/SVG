#pragma once
#include "Point.h"
#include <vector>
#include "string"
#include "CImg.h"
#include "RGB.h"
using namespace cimg_library;
#include "rapidxml.hpp"
using namespace rapidxml;
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class Attribute {
private:
	// danh sach mau cac doi tuong Attribute
	static vector<Attribute*> AttributeSampleObject;
protected:
	// nap Attribute* obj vao danh sach mau
	static void addSample(Attribute* obj);
public:
	// tao doi tuong Attribute bag name
	static Attribute* CreateObject(char* name);
	// xoa tat cac cac mau ra khoi danh sach
	static void DeleteRegister();
	// tra ve ten Attribute
	virtual char* GetName() = 0;
	// nhan ban Attribute
	virtual Attribute* Clone() = 0;
	// dang ki cac loai Attribute ho tro vao Danh sach mau
	static void RegisterDrawAttribute();
	// cai dat gia tri  Attribute tu chuoi attr
	virtual void SetAtribute(char* attr) = 0;
	// ghi gi tri Attribute ra SVG file
	virtual void WriteSVGFile(ofstream &ofs) = 0;
	// chuyen doi char  ang doi tuong Color
	Gdiplus::Color StringToRGB(char* s);
	virtual ~Attribute();
};

// ke thua Attribute
class StrokeWidth : public Attribute {
private:
	// gia tri strokeWidth
	float m_Value;
public:
	StrokeWidth();
	StrokeWidth(StrokeWidth &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	// tra ve StrokeWidth
	virtual int getStrokeWidth();
	virtual ~StrokeWidth();
};

// ke thua Attibute
class StrokeColor : public Attribute {
private:
	// stroke Color
	Gdiplus::Color m_Value;
public:
	StrokeColor();
	StrokeColor(StrokeColor &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	// tra ve StrokeColor
	Gdiplus::Color getStrokeColor();
	virtual ~StrokeColor();
};

// StrokeOpacity ke thua Attribute
class StrokeOpacity : public Attribute {
private:
	// strokeOpacity
	float m_value;
public:
	StrokeOpacity();
	StrokeOpacity(StrokeOpacity &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	// tra ve StrokeOpacity
	virtual float getStrokeOpacity();
	virtual ~StrokeOpacity();
};

// FillColor ke thua Attribute
class FillColor : public Attribute {
private:
	// fillColor
	Gdiplus::Color m_value;
public:
	FillColor();
	FillColor(FillColor &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	// tra ve FillColor
	Gdiplus::Color getFillColor();
	virtual ~FillColor();
};

// fillOpacity ke thua Attribute
class FillOpacity : public Attribute{
private:
	// fillOpacity
	float m_Value;
public:
	FillOpacity();
	FillOpacity(FillOpacity &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	// tra ve Fillloapcity
	virtual float getFillOpacity();
	virtual ~FillOpacity();
};

// lop abstract TransformAttribute
class TransformAttribute {
	// danh sach mau Cac TransformAttribute (rotate , translate, scale) 
	static vector<TransformAttribute*> TransSampleObject;
protected:
	// them TransformAttribute vao danh sach mau
	static void addSample(TransformAttribute* obj);
public:
	// tao doi tuong TransformAttribute bang ten
	static TransformAttribute* CreateObject(char *name);
	// tra ve ten lop con cua TransformAttribute
	virtual char* GetName() = 0;
	// nhan ban doi tuong TransformAttribute
	virtual TransformAttribute* Clone() = 0;
	// thuc hien lenh transform
	virtual void transform(Gdiplus::Graphics &graphics) = 0;
	virtual void transform(CImg<int> &Frame) = 0;
	//gi gia tri transform ra SVG file
	virtual void WriteSVGFile(ofstream &ofs) = 0;
	// cai dat gia tri cho cac doi tuong TrasformAttribute
	virtual void SetAtribute(char* attr) = 0;
	// xoa danh sach mau
	static void  DeleteRegister();
	virtual ~TransformAttribute();
};

class Transform : public Attribute {
	// danh sach cac TrasformAttribute
	vector<TransformAttribute*> m_List;
public:
	Transform();
	Transform(Transform &obj);
	// tra ve ten lop TranSform
	virtual char* GetName();
	// nhan ban Transform
	virtual Attribute* Clone();
	// cai dat gia tri cho Transform
	virtual void SetAtribute(char* attr);
	// dang ky danh sach cac TrasformAtrribute
	void registerTransformAttribute();
	// ghi ra file SVG
	virtual void WriteSVGFile(ofstream &ofs);
	// thuc hien Transform
	virtual void transform(Gdiplus::Graphics &graphics);
	virtual void transform(CImg<int> &Frame);
	// tra ve danh sach TrasformAttribute
	virtual vector<TransformAttribute*> getTransform();
	virtual ~Transform();
};

// cai dat trien khai cac method cua TrasformAtttribute
class Translate : public TransformAttribute {
private:
	// diem Translate
	MyPoint m_Original;
public:
	Translate();
	Translate(Translate &obj);
	virtual char* GetName();
	virtual TransformAttribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual void transform(Gdiplus::Graphics &graphic);
	virtual void transform(CImg<int> &Frame);
	virtual MyPoint getTranslate();
	virtual ~Translate();
};

class Rotate : public TransformAttribute {
private:
	float m_Value;
public:
	Rotate();
	Rotate(Rotate &obj);
	virtual char* GetName();
	virtual TransformAttribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual void transform(Gdiplus::Graphics &graphics);
	virtual void transform(CImg<int> &Frame);
	virtual float getRotate();
	virtual ~Rotate();
};

class Scale : public TransformAttribute {
private:
	float m_XRatio;
	float m_YRatio;
public:
	Scale();
	Scale(Scale &obj);
	virtual char* GetName();
	virtual TransformAttribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual void transform(Gdiplus::Graphics &graphics);
	virtual void transform(CImg<int> &Frame);
	virtual ScaleRatio getScale();
	virtual ~Scale();
};

// ke thua va trien khai cac method cua lop Attribute
class XCoordinates : public Attribute {
private:
	int m_x;
public:
	XCoordinates();
	XCoordinates(XCoordinates &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual int getX();
	virtual ~XCoordinates();
};

// ke thua va trien khai cac method cua lop Attribute
class YCoordinates : public Attribute {
private:
	int m_Y;
public:
	YCoordinates();
	YCoordinates(YCoordinates &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual int getY();
	virtual ~YCoordinates();
};

// ke thua va trien khai cac method cua lop Attribute
class Radius : public Attribute{
private:
	int m_R;
public:
	Radius();
	Radius(Radius &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual int getR();
	virtual ~Radius();

};

// ke thua va trien khai cac method cua lop Attribute
class Width : public Attribute {
private:
	int m_Width;
public:
	Width();
	Width(Width &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual int getWidth();
	virtual ~Width();
};

// ke thua va trien khai cac method cua lop Attribute
class Height : public Attribute {
private:
	int m_Height;
public:
	Height();
	Height(Height &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual int getHeight();
	virtual ~Height();
};

// ke thua va trien khai cac method cua lop Attribute
class Points : Attribute {
private:
	vector<MyPoint> m_List;
public:
	Points();
	Points(Points &obj);
	virtual char* GetName();
	virtual Attribute* Clone();
	virtual void SetAtribute(char* attr);
	virtual void WriteSVGFile(ofstream &ofs);
	virtual vector<MyPoint> getListPoint();
	vector<MyPoint> ReadPoint(char* s);
	void TrimSpace(string &s);
	virtual ~Points();
};

