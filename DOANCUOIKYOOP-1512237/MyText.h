#pragma once
#include "figure.h"

class FontSize : public Attribute {
private:
	int m_Size;
public:
	FontSize();
	FontSize(FontSize &obj);
	char* GetName();
	// nhan ban Attribute
	Attribute* Clone();
	// cai dat gia tri  Attribute tu chuoi attr
	void SetAtribute(char* attr);
	// ghi gi tri Attribute ra SVG file
	void WriteSVGFile(ofstream &ofs);
	// tra ve gia tri fontsize
	int GetFontSize();
	~FontSize();
};


class MyText : public DrawAttribute, public Figure {
private:
	string m_Text;
public:
	MyText();
	MyText(MyText &obj);
	// phuong thuc ao lay ten cua class 
	char* ClassName();
	// phuong thuc nhan ban doi tuong
	 Figure* Clone();
	// dang ki cac mau hinh vao danh sach SampleObject
	 void RegisterAttribute();
	// ve thong bang thu vien GDI+
	 void DrawGDIPlus(HDC hdc);
	// xuat file SVG
	// startAttribute  ghi cac thuoc tinh tu nth tro ve sau trong danh sach Attribute cua class DrawAttribute
	 void WriteSVGFile(ofstream &ofs, int startAttribute = 0);
	// ve bang CImg
	 void DrawCImg(CImg<int> &Frame);
	// doc va cai dat gia tri cho thuoc tinh
	 void LoadAttribute(xml_node<> *node);
	// them attribute* vao danh sach cua lop DrawAttribute
	 void addAttribute(Attribute* obj);
	 ~MyText();
};
