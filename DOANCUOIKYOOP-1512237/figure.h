#pragma once
#include "CImg.h"
#include "RGB.h"
using namespace cimg_library;
#include "Point.h"
#include <vector>
#include "string"
#include "Attribute.h"
#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#include "rapidxml.hpp"
using namespace rapidxml;

class Figure {
private:
	//  danh sach luu mau cac loai hinh
	static vector<Figure*> SampleObject;
protected:
	// them mau vao SampleObject
	static void AddSample(Figure* obj);
public:
	// tao doi tuong thong qua ten
	static Figure* CreateObject(char* name);
	// xoa cac mau hinh khoi danh sach
	static void DeleteRegister();
	// phuong thuc ao lay ten cua class 
	virtual char* ClassName() = 0;
	// phuong thuc nhan ban doi tuong
	virtual Figure* Clone() = 0;
	// dang ki cac mau hinh vao danh sach SampleObject
	virtual void RegisterAttribute() = 0;
	// ve thong bang thu vien GDI+
	virtual void DrawGDIPlus(HDC hdc) = 0;
	// xuat file SVG
	// startAttribute  ghi cac thuoc tinh tu nth tro ve sau trong danh sach Attribute cua class DrawAttribute
	virtual void WriteSVGFile(ofstream &ofs,int startAttribute=0) = 0;
	// ve bang CImg
	virtual void DrawCImg(CImg<int> &Frame) = 0;
	// doc va cai dat gia tri cho thuoc tinh
	virtual void LoadAttribute(xml_node<> *node) = 0;
	// them attribute* vao danh sach cua lop DrawAttribute
	virtual void addAttribute(Attribute* obj) = 0;
	virtual ~Figure();
};

class DrawAttribute {
private:
	// danh sach cac thuoc tinh
	vector<Attribute*> m_Attrs;
public:
	DrawAttribute();
	DrawAttribute(DrawAttribute &obj);
	// thuc hien transform (rotate, scale, Translate);
	void transform(Graphics &graphics);
	// ghi cac thuoc tinh trong danh sach ra file SVG
	// start : bat dau ghi tu thuoc tinh thu start  trong danh sach, mac dinh start = 0
	void WriteAttribute(ofstream &ofs , int start=0);
	// tao cac doi tuong con cua Attribute ,cai dat gia tri va them vao danh sach 
	void Load(xml_node<> *node);
	// tra ve so luong Attribute trong danh sach
	int getNumAttribute();
	//them mot Attribute vao danh sach
	void addAttribute(Attribute* obj);
	// trasform by CIMG
	void transform(CImg<int> &Frame);
	//  them tat ca Attribute trong danh sach vao doi tuong fig
	void SetAttributeForFigure(Figure* fig);
	// tra ve pen
	Pen* getPen();
	// tra ve Brush
	Brush* getBrush();
	// tim kiem va tra ve Attribute thong qua ten Attribute
	virtual Attribute* findAttributeByName(char *name, int nth=0);
	virtual ~DrawAttribute();
};
