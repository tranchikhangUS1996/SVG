#include"MyEllipse.h"


Rx::Rx() : Radius() {
	Attribute::addSample(this);
}
Rx::Rx(Rx &obj) : Radius(obj) {

}
char* Rx::GetName() {
	return "rx";
}
Attribute* Rx::Clone() {
	return new Rx(*this);
}
void Rx::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "rx=\"" << Radius::getR() << "\" ";
}
Rx::~Rx() {

}

Ry::Ry() : Radius() {
	Attribute::addSample(this);
}
Ry::Ry(Ry &obj) : Radius(obj) {

}
char* Ry::GetName() {
	return "ry";
}
Attribute* Ry::Clone() {
	return new Ry(*this);
}
void Ry::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "ry=\"" << Radius::getR() << "\" ";
}
Ry::~Ry() {

}

MyEllipse::MyEllipse() : DrawAttribute() {
	Figure::AddSample(this);
}

MyEllipse::MyEllipse(MyEllipse &obj) : DrawAttribute(obj) {
}

char* MyEllipse::ClassName() {
	return "ellipse";
}

Figure* MyEllipse::Clone() {
	return new MyEllipse(*this);
}

void MyEllipse::RegisterAttribute() {
	Attribute::RegisterDrawAttribute();
	XCenter();
	YCenter();
	Rx();
	Ry();
}

void MyEllipse::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<ellipse ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}

void MyEllipse::DrawGDIPlus(HDC hdc) {
	Pen *pen = DrawAttribute::getPen();
	Brush *brush = DrawAttribute::getBrush();
	XCenter *xcenter = (XCenter*)DrawAttribute::findAttributeByName("cx");
	YCenter *ycenter = (YCenter*)DrawAttribute::findAttributeByName("cy");
	Radius *Xradius = (Radius*)DrawAttribute::findAttributeByName("rx");
	Radius *Yradius = (Radius*)DrawAttribute::findAttributeByName("ry");
	int cx = (xcenter == NULL) ? 0 : xcenter->getX();
	int cy = (ycenter == NULL) ? 0 : ycenter->getY();
	int rx = (Xradius == NULL) ? 0 : Xradius->getR();
	int ry = (Yradius == NULL) ? 0 : Yradius->getR();
	Graphics graphics(hdc);
	DrawAttribute::transform(graphics);
	graphics.FillEllipse(brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
	graphics.DrawEllipse(pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
	delete pen;
	delete brush;
}

void MyEllipse::DrawCImg(CImg<int> &Frame) {
	// lay cac thuoc tinh thong qua ten
	XCenter *xcenter = (XCenter*)DrawAttribute::findAttributeByName("cx");
	YCenter *ycenter = (YCenter*)DrawAttribute::findAttributeByName("cy");
	Radius *Xradius = (Radius*)DrawAttribute::findAttributeByName("rx");
	Radius *Yradius = (Radius*)DrawAttribute::findAttributeByName("ry");
	int cx = (xcenter == NULL) ? 0 : xcenter->getX();
	int cy = (ycenter == NULL) ? 0 : ycenter->getY();
	int rx = (Xradius == NULL) ? 0 : Xradius->getR();
	int ry = (Yradius == NULL) ? 0 : Yradius->getR();
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
	Frame.draw_ellipse(cx,cy, (rx + width), (ry + width), 1, mycolor.data(), opacity);
	Frame.draw_ellipse(cx, cy, rx, ry, 1, FillColor.data(), fillOpacity);
}

void MyEllipse::LoadAttribute(xml_node<> *node) {
	if (NULL == node) return;
	DrawAttribute::Load(node);
}

void MyEllipse::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}

MyEllipse::~MyEllipse() {

}