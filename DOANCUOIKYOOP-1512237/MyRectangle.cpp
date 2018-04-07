#include "MyRectangle.h"

MyRectangle::MyRectangle() : DrawAttribute() {

	Figure::AddSample(this);
}

MyRectangle::MyRectangle(MyRectangle &obj) : DrawAttribute(obj){
}

char* MyRectangle::ClassName() {
	return "rect";
}

Figure* MyRectangle::Clone() {
	return new MyRectangle(*this);
}

void MyRectangle::RegisterAttribute() {
	// dang ki cac thuoc tinh cua hinh chu nhat
	Width();
	Height();
	XCoordinates();
	YCoordinates();
	Attribute::RegisterDrawAttribute();
}

void MyRectangle::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<rect ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}

void MyRectangle::DrawGDIPlus(HDC hdc){
	Pen *pen = DrawAttribute::getPen();
	Brush *brush = DrawAttribute::getBrush();
	XCoordinates* Ox = (XCoordinates*)DrawAttribute::findAttributeByName("x");
	YCoordinates* Oy = (YCoordinates*)DrawAttribute::findAttributeByName("y");
	Width* Owidth = (Width*)DrawAttribute::findAttributeByName("width");
	Height* Oheight = (Height*)DrawAttribute::findAttributeByName("height");
	int x = (Ox == NULL) ? 0 : Ox->getX();
	int y = (Oy == NULL) ? 0 : Oy->getY();
	int width = (Owidth == NULL) ? 0 : Owidth->getWidth();
	int height = (Oheight == NULL) ? 0 : Oheight->getHeight();
	Graphics graphics(hdc);
	DrawAttribute::transform(graphics);
		graphics.FillRectangle(brush, x, y, width, height);
		graphics.DrawRectangle(pen, x, y, width, height);
	delete pen;
	delete brush;
}

void MyRectangle::DrawCImg(CImg<int> &Frame) {
	//lay thuoc tinh thong qua ten
	XCoordinates* Ox = (XCoordinates*)DrawAttribute::findAttributeByName("x");
	YCoordinates* Oy = (YCoordinates*)DrawAttribute::findAttributeByName("y");
	Width* Owidth = (Width*)DrawAttribute::findAttributeByName("width");
	Height* Oheight = (Height*)DrawAttribute::findAttributeByName("height");
	int x = (Ox == NULL) ? 0 : Ox->getX();
	int y = (Oy == NULL) ? 0 : Oy->getY();
	int Rwidth = (Owidth == NULL) ? 0 : Owidth->getWidth();
	int Rheight = (Oheight == NULL) ? 0 : Oheight->getHeight();
	StrokeWidth* S_width = (StrokeWidth*)DrawAttribute::findAttributeByName("stroke-width");
	StrokeOpacity* S_opacity = (StrokeOpacity*)DrawAttribute::findAttributeByName("stroke-opacity");
	FillOpacity* f_Opacity = (FillOpacity*)DrawAttribute::findAttributeByName("fill-opacity");
	float width = (S_width == NULL) ? 1 : S_width->getStrokeWidth();
	float opacity = (S_opacity == NULL) ? 1 : S_opacity->getStrokeOpacity();
	float fillOpacity = (f_Opacity == NULL) ? 1 : f_Opacity->getFillOpacity();
	StrokeColor* S_color = (StrokeColor*)DrawAttribute::findAttributeByName("stroke");
	FillColor* f_color = (FillColor*)DrawAttribute::findAttributeByName("fill");
	//mau mac dinh  strokeColor la black
	Color color = (S_color == NULL) ? Color(1, 0, 0, 0) : S_color->getStrokeColor();
	// mau mac dinh fillColor la white
	Color fillColor = (f_color == NULL) ? Color(1, 255, 255, 255) : f_color->getFillColor();
	MyRGB mycolor(color.GetR(), color.GetG(), color.GetB());
	MyRGB FillColor(fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	DrawAttribute::transform(Frame);
	Frame.draw_rectangle(x - width, y - width, x + Rwidth + width, y + Rheight + width, mycolor.data(), opacity);
	Frame.draw_rectangle(x, y, x + Rwidth, y + Rheight, FillColor.data(), fillOpacity);
}
void MyRectangle::LoadAttribute(xml_node<> *node) {
	if (NULL == node) return;
	DrawAttribute::Load(node);
}

void MyRectangle::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}

MyRectangle::~MyRectangle() {

}