#include"MyPolyLine.h"

MyPolyline::MyPolyline() : DrawAttribute() {
	Figure::AddSample(this);
}

MyPolyline::MyPolyline(MyPolyline &obj) : DrawAttribute(obj) {
}

char* MyPolyline::ClassName() {
	return "polyline";
}

Figure* MyPolyline::Clone() {
	return new MyPolyline(*this);
}

void MyPolyline::RegisterAttribute() {
	Attribute::RegisterDrawAttribute();
	Points();
}

void MyPolyline::WriteSVGFile(ofstream &ofs, int startAttribute){
	if (!ofs) return;
	ofs << "<polyline ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}

void MyPolyline::DrawGDIPlus(HDC hdc){
	Pen *pen = DrawAttribute::getPen();
	Brush *brush = DrawAttribute::getBrush();
	Graphics graphics(hdc);
	DrawAttribute::transform(graphics);
	Points* pointsObject = (Points*)DrawAttribute::findAttributeByName("points");
	vector<MyPoint> m_list;
	if (pointsObject != NULL) m_list = pointsObject->getListPoint();
	vector<Point> points;
	for (int i = 0; i < m_list.size(); i++) {
		points.push_back(Point(m_list[i].getX(), m_list[i].getY()));
	}
	GraphicsPath path;
	path.AddLines((Point*)points.data(), points.size());
	graphics.FillPath(brush, &path);
	graphics.DrawPath(pen, &path);
	delete brush;
	delete pen;
}

void MyPolyline::DrawCImg(CImg<int> &Frame) {
	// lay cac Attribute thong qua ten
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
	Points* pointsObject = (Points*)DrawAttribute::findAttributeByName("points");
	vector<MyPoint> list;
	if (pointsObject != NULL) list = pointsObject->getListPoint();
	CImg<int> points(list.size(), 2);
	for (int i = 0; i <list.size(); i++) {
		points(i, 0) = list[i].getX();
		points(i, 1) = list[i].getY();
	}
	DrawAttribute::transform(Frame);
	Frame.draw_polygon(points, FillColor.data());
}

void MyPolyline::LoadAttribute(xml_node<> *node) {
	if (NULL == node) return;
	DrawAttribute::Load(node);
}

void MyPolyline::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}
MyPolyline::~MyPolyline() {

}