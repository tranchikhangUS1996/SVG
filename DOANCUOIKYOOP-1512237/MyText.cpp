#include "MyText.h"

FontSize::FontSize() {
	m_Size = 0;
	Attribute::addSample(this);
}
FontSize::FontSize(FontSize &obj) {
	m_Size = obj.m_Size;
}
char* FontSize::GetName() {
	return "font-size";
}
// nhan ban Attribute
Attribute* FontSize::Clone() {
	return new FontSize(*this);
}
// cai dat gia tri  Attribute tu chuoi attr
void FontSize::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_Size = atof(attr);
}
// ghi gi tri Attribute ra SVG file
void FontSize::WriteSVGFile(ofstream &ofs) {
	ofs << "font-size=\"" << m_Size << "\" ";
}
// tra ve gia tri fontsize
int FontSize::GetFontSize() {
	return m_Size;
}

FontSize::~FontSize() {

}

/* set up class MyText*/
MyText::MyText() {
	m_Text.resize(0);
	Figure::AddSample(this);
}

MyText::MyText(MyText &obj) {
	m_Text = obj.m_Text;
}

char* MyText::ClassName() {
	return "text";
}

Figure* MyText::Clone() {
	return new MyText(*this);
}

void MyText::RegisterAttribute() {
	Attribute::RegisterDrawAttribute();
	FontSize();
}
// ve thong bang thu vien GDI+
void MyText::DrawGDIPlus(HDC hdc) {
	Graphics graphics(hdc);
	// transform
	DrawAttribute::transform(graphics);
	// lay cac thuoc tinh
	Brush *brush = DrawAttribute::getBrush();
	XCoordinates* x = (XCoordinates*)DrawAttribute::findAttributeByName("x");
	YCoordinates* y = (YCoordinates*)DrawAttribute::findAttributeByName("y");
	FontSize* fontSize = (FontSize*)DrawAttribute::findAttributeByName("font-size");
	// chuyen sang kieu du lieu
	int Vx = (x == NULL) ? 0 : x->getX();
	int Vy = (y == NULL) ? 0 : y->getY();
	int VFontSize = (fontSize == NULL) ? 0 : fontSize->GetFontSize();
	wstring buffer(m_Text.begin(), m_Text.end());
	WCHAR *Text = (WCHAR*)buffer.c_str();
	GraphicsPath path;
	FontFamily* family = new FontFamily(L"Arial");
	path.AddString(Text,m_Text.size(), family, FontStyle::FontStyleItalic, VFontSize, Point(Vx, Vy-VFontSize), StringFormat::GenericDefault());
	graphics.FillPath(brush, &path);
	delete brush;
	delete family;
}
// xuat file SVG
// startAttribute  ghi cac thuoc tinh tu nth tro ve sau trong danh sach Attribute cua class DrawAttribute
void MyText::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<text ";
	DrawAttribute::WriteAttribute(ofs);
	ofs << "> ";
	ofs << m_Text << "</text>";
}
// ve bang CImg
void MyText::DrawCImg(CImg<int> &Frame) {
	// chua ho tro
}
// doc va cai dat gia tri cho thuoc tinh
void MyText::LoadAttribute(xml_node<> *node) {
	DrawAttribute::Load(node);
	// lay text
	m_Text = string(node->value());
}
// them attribute* vao danh sach cua lop DrawAttribute
void MyText::addAttribute(Attribute* obj) {
	if (obj == NULL) return;
	DrawAttribute::addAttribute(obj);
}

MyText::~MyText() {

}