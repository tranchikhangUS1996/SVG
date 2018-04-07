#include "MyCircle.h"
// set class XCenter 
XCenter::XCenter() : XCoordinates() {
	Attribute::addSample(this);
}
XCenter::XCenter(XCenter &obj) : XCoordinates(obj) {

}
char* XCenter::GetName() {
	return "cx";
}
Attribute* XCenter::Clone() {
	return new XCenter(*this);
}
void XCenter::SetAtribute(char* attr) {
	if (NULL == attr) return;
	// goi lop cha cua no cai dat thuoc tinh
	XCoordinates::SetAtribute(attr);
}
void XCenter::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "cx=\"" << XCoordinates::getX() << "\" ";
}
XCenter::~XCenter() {

}

// set class YCenter 

YCenter::YCenter() : YCoordinates() {
	Attribute::addSample(this);
}
YCenter::YCenter(YCenter &obj) : YCoordinates(obj) {

}
char* YCenter::GetName() {
	return "cy";
}
Attribute* YCenter::Clone() {
	return new YCenter(*this);
}
void YCenter::SetAtribute(char* attr) {
	if (NULL == attr) return;
	// goi lop cha cua no caci dat thuoc tinh
	YCoordinates::SetAtribute(attr);
}
void YCenter::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "cy=\"" << YCoordinates::getY() << "\" ";
}
YCenter::~YCenter() {

}

// set class MyCircle

MyCircle::MyCircle() : DrawAttribute(){
	Figure::AddSample(this);
}


MyCircle::MyCircle(MyCircle &obj) : DrawAttribute(obj) {

}

char* MyCircle::ClassName() {
	return "circle";
}

Figure* MyCircle::Clone() {
	return new MyCircle(*this);
}

void MyCircle::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<circle ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}


void MyCircle::RegisterAttribute() {
	XCenter();
	YCenter();
	Radius();
	Attribute::RegisterDrawAttribute();
}

void MyCircle::DrawGDIPlus(HDC hdc){
	Pen *pen = DrawAttribute::getPen();
	Brush *brush = DrawAttribute::getBrush();
	XCenter *xcenter = (XCenter*)DrawAttribute::findAttributeByName("cx");
	YCenter *ycenter = (YCenter*)DrawAttribute::findAttributeByName("cy");
	Radius *radius = (Radius*)DrawAttribute::findAttributeByName("r");
	int cx = (xcenter == NULL) ? 0 : xcenter->getX();
	int cy = (ycenter == NULL) ? 0 : ycenter->getY();
	int r = (radius == NULL) ? 0 : radius->getR();
	Graphics graphics(hdc);
	DrawAttribute::transform(graphics);
	graphics.FillEllipse(brush, cx - r, cy - r, 2 * r, 2 * r);
	graphics.DrawEllipse(pen, cx - r, cy - r, 2 * r, 2 * r);
	delete pen;
	delete brush;
}

void MyCircle::DrawCImg(CImg <int> &Frame) {
	// lay cac thuoc tinh thong qua ten
	XCenter *xcenter = (XCenter*)DrawAttribute::findAttributeByName("cx");
	YCenter *ycenter = (YCenter*)DrawAttribute::findAttributeByName("cy");
	Radius *radius = (Radius*)DrawAttribute::findAttributeByName("r");
	int cx = (xcenter == NULL) ? 0 : xcenter->getX();
	int cy = (ycenter == NULL) ? 0 : ycenter->getY();
	int r = (radius == NULL) ? 0 : radius->getR();
	StrokeWidth* S_width = (StrokeWidth*)DrawAttribute::findAttributeByName("stroke-width");
	StrokeOpacity* S_opacity = (StrokeOpacity*)DrawAttribute::findAttributeByName("stroke-opacity");
	FillOpacity* f_Opacity = (FillOpacity*)DrawAttribute::findAttributeByName("fill-opacity");
	float width = (S_width == NULL) ? 1 : S_width->getStrokeWidth();
	float opacity = (S_opacity == NULL) ? 1 : S_opacity->getStrokeOpacity();
	float fillOpacity = (f_Opacity == NULL) ? 1 : f_Opacity->getFillOpacity();
	StrokeColor* S_color = (StrokeColor*) DrawAttribute::findAttributeByName("stroke");
	FillColor* f_color = (FillColor*)DrawAttribute::findAttributeByName("fill");
	//mau mac dinh  strokeColor la black
	Color color = (S_color == NULL) ? Color(1, 0, 0, 0) : S_color->getStrokeColor();
	// mau mac dinh fillColor la white
	Color fillColor = (f_color == NULL) ? Color(1, 255, 255, 255) : f_color->getFillColor();
	MyRGB mycolor(color.GetR(), color.GetG(), color.GetB());
	MyRGB FillColor(fillColor.GetR(), fillColor.GetG(),fillColor.GetB());
	// ve len man hinh
	DrawAttribute::transform(Frame);
	Frame.draw_circle(cx,cy, r + width, mycolor.data(), opacity);
	Frame.draw_circle(cx,cy, r, FillColor.data(),fillOpacity);
}

void MyCircle::LoadAttribute(xml_node<> *node) {
	if (NULL == node) return;
	DrawAttribute::Load(node);
}

void MyCircle::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}
MyCircle::~MyCircle() {

}