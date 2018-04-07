#include "MyLine.h"

X1::X1() : XCoordinates() {
	Attribute::addSample(this);
}
X1::X1(X1 &obj) : XCoordinates(obj) {

}
char* X1::GetName() {
	return "x1";
}
Attribute* X1::Clone() {
	return new X1(*this);
}
void X1::SetAtribute(char* attr) {
	if (NULL == attr) return;
	XCoordinates::SetAtribute(attr);
}
void X1::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "x1=\"" << XCoordinates::getX() << "\" ";
}
X1::~X1() {

}

// set class Y1

Y1::Y1() : YCoordinates() {
	Attribute::addSample(this);
}
Y1::Y1(Y1 &obj) : YCoordinates(obj) {

}
char* Y1::GetName() {
	return "y1";
}
Attribute* Y1::Clone() {
	return new Y1(*this);
}
void Y1::SetAtribute(char* attr) {
	if (NULL == attr) return;
	YCoordinates::SetAtribute(attr);
}
void Y1::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "y1=\"" << YCoordinates::getY() << "\" ";
}
Y1::~Y1() {

}

X2::X2() : XCoordinates() {
	Attribute::addSample(this);
}
X2::X2(X2 &obj) : XCoordinates(obj) {

}
char* X2::GetName() {
	return "x2";
}
Attribute* X2::Clone() {
	return new X2(*this);
}
void X2::SetAtribute(char* attr) {
	if (NULL == attr) return;
	XCoordinates::SetAtribute(attr);
}
void X2::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "x2=\"" << XCoordinates::getX() << "\" ";
}
X2::~X2() {

}

// set class YCenter 

Y2::Y2() : YCoordinates() {
	Attribute::addSample(this);
}
Y2::Y2(Y2 &obj) : YCoordinates(obj) {

}
char* Y2::GetName() {
	return "y2";
}
Attribute* Y2::Clone() {
	return new Y2(*this);
}
void Y2::SetAtribute(char* attr) {
	if (NULL == attr) return;
	YCoordinates::SetAtribute(attr);
}
void Y2::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "y2=\"" << YCoordinates::getY() << "\" ";
}
Y2::~Y2() {

}

MyLine::MyLine() : DrawAttribute(){
	Figure::AddSample(this);
}


MyLine::MyLine(MyLine& obj) : DrawAttribute(obj) {

}

char* MyLine::ClassName() {
	return "line";
}

Figure* MyLine::Clone() {
	return new MyLine(*this);
}

void MyLine::RegisterAttribute() {
	X1();
	X2();
	Y1();
	Y2();
	Attribute::RegisterDrawAttribute();
}


void MyLine::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<line ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}

void MyLine::DrawGDIPlus(HDC hdc) {
	Graphics graphics(hdc);
	// lay cac  thuoc tinh thong qua ten
	Pen *pen = DrawAttribute::getPen();
	X1* x1 = (X1*)DrawAttribute::findAttributeByName("x1");
	Y1* y1 = (Y1*)DrawAttribute::findAttributeByName("y1");
	X2* x2 = (X2*)DrawAttribute::findAttributeByName("x2");
	Y2* y2 = (Y2*)DrawAttribute::findAttributeByName("y2");
	// lay cac gia tri , neu NULL gan mac dinh bang 0
	int Vx1 = (x1 == NULL) ? 0 : x1->getX();
	int Vx2 = (x2 == NULL) ? 0 : x2->getX();
	int Vy1 = (y1 == NULL) ? 0 : y1->getY();
	int Vy2 = (y2 == NULL) ? 0 : y2->getY();
	// thuc hien transform
	DrawAttribute::transform(graphics);
	// ve
	graphics.DrawLine(pen, Vx1, Vy1, Vx2, Vy2);
	delete pen;
}

void MyLine::DrawCImg(CImg<int> &Frame) {
	// lay cac thuoc tinh thong qua ten
	X1* x1 = (X1*)DrawAttribute::findAttributeByName("x1");
	Y1* y1 = (Y1*)DrawAttribute::findAttributeByName("y1");
	X2* x2 = (X2*)DrawAttribute::findAttributeByName("x2");
	Y2* y2 = (Y2*)DrawAttribute::findAttributeByName("y2");
	// lay gia tri
	int Vx1 = (x1 == NULL) ? 0 : x1->getX();
	int Vx2 = (x2 == NULL) ? 0 : x2->getX();
	int Vy1 = (y1 == NULL) ? 0 : y1->getY();
	int Vy2 = (y2 == NULL) ? 0 : y2->getY();
	StrokeColor* S_color = (StrokeColor*) DrawAttribute::findAttributeByName("stroke-color");
	Color color = (S_color == NULL) ? Color(1, 0, 0, 0) : S_color->getStrokeColor();
	MyRGB rgb(color.GetR(), color.GetG(), color.GetB());
	StrokeOpacity* S_opacity = (StrokeOpacity*) DrawAttribute::findAttributeByName("stroke-opacity");
	StrokeWidth *S_width = (StrokeWidth*)DrawAttribute::findAttributeByName("stroke-width");
	float opacity = (S_opacity == NULL) ? 1 : S_opacity->getStrokeOpacity();
	float width = (S_width == NULL) ? 1 : S_width->getStrokeWidth();
	DrawAttribute::transform(Frame);
	// ve line
	for (int i = 0; i < (int)(width/2); i++) {
		Frame.draw_line(Vx1 + i, Vy1 - i, Vx2 + i, Vy2 - i, rgb.data(), opacity);
		Frame.draw_line(Vx1 - i, Vy1 + i, Vx2 - i, Vy2 + i, rgb.data(), opacity);
	}

}

void MyLine::LoadAttribute(xml_node<> *node) {
	if (node == NULL) return;
	DrawAttribute::Load(node);
}

void MyLine::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}

MyLine::~MyLine() {

}