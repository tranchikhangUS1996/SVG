#include "Attribute.h"

// cai dat cac thuoc tinh co ban
// strokewidth
// strokeColor
// strokeopacity
// fillColor
// fillopacity
// x
// y
// radius
// width
// height
// point
// translate
// rotate


// nap mau Attribute vao danh sach
void Attribute::addSample(Attribute* obj) {
	if (NULL == obj) return;
	int pos = AttributeSampleObject.size();
	while (--pos >= 0) {
		Attribute* temp = AttributeSampleObject[pos];
		if (NULL == temp) continue;
		// so sanh ten obj voi ten cau mau trong danh sach
		if (strcmp(obj->GetName(), temp->GetName()) == 0) break;
	}
	// neu trong danh sach mau chua co obj thi nap vao danh sach
	if (pos < 0) {
		AttributeSampleObject.push_back(obj->Clone());
	}
}

// tao doi tuong Attribute thong qua ten
Attribute* Attribute::CreateObject(char* name) {
	if (name == NULL) return NULL;
	int pos = AttributeSampleObject.size();
	while (--pos >= 0) {
		Attribute *temp = AttributeSampleObject[pos];
		if (temp == NULL) continue;
		// so sanh name voi ten doi tuong trong danh sach mau
		if (strcmp(name, temp->GetName()) == 0) break;
	}
	// neu tim thay trong mau thi tra ve ban sao cua no
	if (pos >= 0) return AttributeSampleObject[pos]->Clone();
	// neu khong tim thay tra ve NULL
	return NULL;
}

// xoa cac doi tuong ra kho danh sach mau
void Attribute::DeleteRegister() {
	for (int i = 0; i < AttributeSampleObject.size(); i++) {
		if (AttributeSampleObject[i] != NULL) {
			delete AttributeSampleObject[i];
			AttributeSampleObject[i] = NULL;
		}
	}
}

// chuyen doi char*  sang Color
Color Attribute::StringToRGB(char* s) {
	string StringRGB(s);
	// neu chuoi mau la none thi tra ve mau trong suot
	if (StringRGB == "none") return Color(0, 0, 0, 0);
	// khoi tao cac gia tri R G B mac dinh la 0
	int R = 0, G = 0, B = 0;
	// tim vi tri dau (
	std::size_t Start = StringRGB.find("(");
	// tim vi tri dau phay thu 1
	std::size_t Comma1 = StringRGB.find(",");
	// tim vi tri dau phay thu 2
	std::size_t Comma2 = StringRGB.find(",", Comma1 + 1);
	// tim vi tri dau )
	std::size_t End = StringRGB.find(")");
	// neu cac vi tri khong thoa do sai cau truc thi tra ve Black Color
	if (Start == StringRGB.npos || Comma1 == StringRGB.npos || Comma2 == StringRGB.npos || End == StringRGB.npos) return Color(1, 0, 0, 0);
	// lay chuoi con chua gia tri Red
	string RedValue = StringRGB.substr(Start + 1, Comma1 - Start - 1);
	// lay chuoi con chua gia tri Grren
	string GreenValue = StringRGB.substr(Comma1 + 1, Comma2 - Comma1 - 1);
	// lay chuoi con chua gia tri Blue
	string BlueValue = StringRGB.substr(Comma2 + 1, End - Comma2 - 1);
	// thuc hien chuyen tu string sang int
	R = stoi(RedValue);
	G = stoi(GreenValue);
	B = stoi(BlueValue);
	Color ret(1,R, G, B);
	return ret;
}

// dang ki cac Attribute vao mau
void Attribute::RegisterDrawAttribute() {
	StrokeColor();
	StrokeOpacity();
	StrokeWidth();
	FillColor();
	FillOpacity();
	Transform(); 
	XCoordinates();
	YCoordinates();
}

Attribute::~Attribute() {

}

/* Class StrokeWidth */

StrokeWidth::StrokeWidth() {
	// them vao mau
	Attribute::addSample(this);
}

StrokeWidth::StrokeWidth(StrokeWidth &obj) {
	m_Value = obj.m_Value;
}
char* StrokeWidth::GetName() {
	// tra ve ten lop
	return "stroke-width";
}
// nhan ban doi tuong
Attribute* StrokeWidth::Clone(){
	return new StrokeWidth(*this);
}

// cai dat gia tri tu chuoi attr
void StrokeWidth::SetAtribute(char* attr){
	if (NULL == attr) return;
	m_Value = atoi(attr);
}

// xuat ra file SVG
void StrokeWidth::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "stroke-width=\"" << m_Value << "\" ";
}

// tra ve gia tri width
int StrokeWidth::getStrokeWidth() {
	return m_Value;
}

StrokeWidth::~StrokeWidth() {

}

/*  set Class StrokeColor */

StrokeColor::StrokeColor() {
	// mau mac dinh la black
	m_Value = Color(1,0, 0, 0);
	// them doi tuong vao danh sach mau
	Attribute::addSample(this);
}
StrokeColor::StrokeColor(StrokeColor &obj) {
	m_Value = obj.m_Value;
}

char* StrokeColor::GetName(){
	return "stroke";
}
Attribute* StrokeColor::Clone(){
	return new StrokeColor(*this);
}
void StrokeColor::SetAtribute(char* attr){
	if (NULL == attr) return;
	m_Value = Attribute::StringToRGB(attr);
}

void StrokeColor::WriteSVGFile(ofstream &ofs){
	if (!ofs) return;
	// neu alpha bang 0 thi gia tri mau la none
	if (m_Value.GetA() == 0) ofs << "stroke=\"none\" ";
	else {
		int R = m_Value.GetR();
		int G = m_Value.GetG();
		int B = m_Value.GetB();
		ofs << "stroke=\"rgb(" << R << "," << G << "," << B << ")\" ";
	}
}
// tra ve strokeColor
Color StrokeColor::getStrokeColor() {
	return m_Value;
}

StrokeColor::~StrokeColor() {

}

/* Set Class Stroke opacity*/

StrokeOpacity::StrokeOpacity() {
	m_value = 0;
	Attribute::addSample(this);
}
StrokeOpacity::StrokeOpacity(StrokeOpacity &obj) {
	m_value = obj.m_value;
}
char* StrokeOpacity::GetName(){
	return "stroke-opacity";
}
Attribute* StrokeOpacity::Clone(){
	return new StrokeOpacity(*this);
}
void StrokeOpacity::SetAtribute(char* attr){
	if (NULL == attr) return;
	m_value = atof(attr);
}

void StrokeOpacity::WriteSVGFile(ofstream &ofs){
	if (!ofs) return;
	ofs << "stroke-opacity=\"" << m_value << "\" ";
}

float StrokeOpacity::getStrokeOpacity() {
	return m_value;
}

StrokeOpacity::~StrokeOpacity() {

}

/* set Class FillColor*/

FillColor::FillColor() {
	m_value = Color(1,0, 0, 0);
	Attribute::addSample(this);
}
FillColor::FillColor(FillColor &obj){
	m_value = obj.m_value;
}
char* FillColor::GetName() {
	return "fill";
}
Attribute*FillColor::Clone() {
	return new FillColor(*this);
}
void FillColor::SetAtribute(char* attr) {
	m_value = Attribute::StringToRGB(attr);
}

void FillColor::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	// alpha =0 thi gia tri mau la none
	if (m_value.GetA() == 0) ofs << "fill=\"none\" ";
	else {
		int R = m_value.GetR();
		int G = m_value.GetG();
		int B = m_value.GetB();
		ofs << "fill=\"rgb(" << R << ", " << G << ", " << B << ")\" ";
	}
}
Color FillColor::getFillColor() {
	return m_value;
}

FillColor::~FillColor() {

}

/* set Class FillOpacity */

FillOpacity::FillOpacity() {
	m_Value = 0;
	Attribute::addSample(this);
}
FillOpacity::FillOpacity(FillOpacity &obj){
	m_Value = obj.m_Value;
}
char* FillOpacity::GetName(){
	return "fill-opacity";
}
Attribute*FillOpacity::Clone(){
	return new FillOpacity(*this);
}
void FillOpacity::SetAtribute(char* attr){
	if (NULL == attr) return;
	m_Value = atof(attr);
}

void FillOpacity::WriteSVGFile(ofstream &ofs){
	if (!ofs) return;
	ofs << "fill-opacity=\"" << m_Value << "\" ";
}
float FillOpacity::getFillOpacity(){
	return m_Value;
}

FillOpacity::~FillOpacity() {

}

/* set class tranformAttribute */

void TransformAttribute::addSample(TransformAttribute* obj) {
	if (NULL == obj) return;
	int pos = TransSampleObject.size();
	while (--pos >= 0) {
		TransformAttribute* temp = TransSampleObject[pos];
		if (NULL == temp) continue;
		// so sanh ten obj voi ten cac doi tuong trong mau
		if (strcmp(obj->GetName(), temp->GetName()) == 0) break;
	}
	if (pos < 0) {
		// neu trong danh sach ma chua co thi them vao danh sach mau
		TransSampleObject.push_back(obj->Clone());
	}
}

TransformAttribute* TransformAttribute::CreateObject(char *name) {
	if (NULL == name) return NULL;
	string check(name);
	int pos = TransSampleObject.size();
	while (--pos >= 0) {
		TransformAttribute* temp = TransSampleObject[pos];
		if (NULL == temp) continue;
		// so sanh name voi ten cua doi tuong trong danh sach mau, hoac tim kiem su xuat hien ten doi tuong cua mau trong name
		if (strcmp(name, temp->GetName()) == 0||(check.find(temp->GetName())!=check.npos)) break;
	}
	if (pos >= 0) return TransSampleObject[pos]->Clone();
	return NULL;
}

TransformAttribute::~TransformAttribute() {

}
void TransformAttribute::DeleteRegister() {
	for (int i = 0; i < TransSampleObject.size(); i++) {
		if (TransSampleObject[i] != NULL) {
			delete TransSampleObject[i];
			TransSampleObject[i] = NULL;
		}
	}
}

/*  set class Transform */

Transform::Transform() {
	m_List.resize(0);
	Attribute::addSample(this);
}
Transform::Transform(Transform &obj) {
	for (int i = 0; i < obj.m_List.size() ; i++) {
		TransformAttribute* temp = obj.m_List[i]->Clone();
		m_List.push_back(temp);
	}
}
char* Transform::GetName() {
	return "transform";
}
Attribute* Transform::Clone() {
	return new Transform(*this);
}

void Transform::registerTransformAttribute() {
	Rotate();
	Translate();
	Scale();
}

void Transform::SetAtribute(char* attr) {
	if (NULL == attr) return;
	// dang ki cac doi tuong Translate
	registerTransformAttribute();
	string trans(attr);
	// them dau ) va cuoi chuoi
	trans.push_back(')');
	// them dau ( vao dau chuoi
	trans.insert(0,"(");
	std::size_t start = 0;
	// tim dau )
	std::size_t end = trans.find(")", start + 1);
	while (end != trans.npos&&end>start) {
		// lay chuoi con chua thong tin  TrasformAttribute
		string sub = trans.substr(start + 1, end - start);
		sub.push_back('\0');
		// tao doi tuong ransformAttribute tu chuoi con sub
		TransformAttribute* add =  TransformAttribute::CreateObject(&sub[0]);
		if (add != NULL) {
			// goi doi tuong TrasformAttribute cai dat gia tri tu chuoi attr
			add->SetAtribute(attr);
			// them vao danh sach
			m_List.push_back(add);
		}
		start = end+1;
		// tim ci tri dau ) tiep theo
		end = trans.find(")", start + 1);
	}
}

// goi cac doi tuong TransformAttribute thuc hien Transform
void Transform::transform(Graphics &graphics) {
	for (int i = 0; i < m_List.size(); i++) {
		m_List[i]->transform(graphics);
	}
}

void Transform::transform(CImg<int> &Frame) {
	for (int i = 0; i < m_List.size(); i++) {
		m_List[i]->transform(Frame);
	}
}

void Transform::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "transform=\"";
	// goi doi tuong trong danhs sach viet ra  file SVG
	for (int i = 0; i < m_List.size(); i++) {
		m_List[i]->WriteSVGFile(ofs);
	}
	ofs << "\" ";
}

// tra ve danh sach cac TrasformAttribute
vector<TransformAttribute*> Transform::getTransform() {
	vector<TransformAttribute*> ret;
	for (int i = 0; i < m_List.size(); i++) {
		TransformAttribute* temp = m_List[i]->Clone();
		ret.push_back(temp);
	}
	return ret;
}

Transform::~Transform() {
	for (int i = 0; i < m_List.size(); i++) {
		if (m_List[i] != NULL) {
			delete m_List[i];
			m_List[i] = NULL;
		}
	}
	cout << "~Transform"<<endl;
}

/* set Class Translate */

Translate::Translate() {
	m_Original = MyPoint(0, 0);
	TransformAttribute::addSample(this);
}
Translate::Translate(Translate &obj) {
	m_Original = obj.m_Original;
}
char* Translate::GetName() {
	return "translate";
}
TransformAttribute* Translate::Clone() {
	return new Translate(*this);
}

//cai dat gia tri cho Translate thong qua chuoi attr
void Translate::SetAtribute(char* attr) {
	string Transform(attr);
	// tim kiem vi tri bat dau cua chuoi translate
	std::size_t start = Transform.find("translate");
	if (start != Transform.npos) {
		// tim kiem vi tri dau (
		std::size_t parenthesis = Transform.find("(", start);
		// tim kiem vi tri dau phay
		std::size_t Comma = Transform.find(",", start);
		//tim kiem vi tri dau )
		std::size_t Closingparenthesis = Transform.find(")", start);
		// lay cac chuoi con chua gia tri hoanh do
		string XValue = Transform.substr(parenthesis + 1, Comma - parenthesis - 1);
		// lay chuoi con chua gia tri tung do
		string YValue = Transform.substr(Comma + 1, Closingparenthesis - Comma - 1);
		// tao doi tuong MyPoint
		m_Original = MyPoint(stoi(XValue), stoi(YValue));
	}
}

void Translate::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "translate(" << m_Original.getX() << ", " << m_Original.getY() << ") ";
}
void Translate::transform(Graphics &graphic) {
	graphic.TranslateTransform(m_Original.getX(), m_Original.getY(), MatrixOrderPrepend);
}

void Translate::transform(CImg<int> &Frame) {
	// chua ho tro
}

MyPoint Translate::getTranslate() {
	return m_Original;
}

Translate::~Translate() {

}

/*  set Class Rotate */

Rotate::Rotate() {
	m_Value = 0;
	TransformAttribute::addSample(this);
}
Rotate::Rotate(Rotate &obj) {
	m_Value = obj.m_Value;
}
char* Rotate::GetName() {
	return "rotate";
}
TransformAttribute* Rotate::Clone() {
	return new Rotate(*this);
}
void Rotate::SetAtribute(char* attr) {
	string Transform(attr);
	// tim vi tri cua chuoi rotate
	std::size_t start = Transform.find("rotate");
	if (start != Transform.npos) {
		// tim vi tri dau (
		std::size_t parenthesis = Transform.find("(", start);
		// tim vi tri dau )
		std::size_t Closingparenthesis = Transform.find(")", start);
		// lay chuoi con chua gia tri rotate
		string RotateValue = Transform.substr(parenthesis + 1, Closingparenthesis - parenthesis - 1);
		// chuyen doi string sang float
		m_Value = stof(RotateValue);
	}
}

void Rotate::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "rotate(" << m_Value << ") ";
}
void Rotate::transform(Graphics &graphics) {
	graphics.RotateTransform(m_Value);
}
void Rotate::transform(CImg<int> &Frame) {
	// chua ho tro
}

float Rotate::getRotate() {
	return m_Value;
}

Rotate::~Rotate() {

}

/*  setup class Scale */

Scale::Scale() {
	m_XRatio = 0;
	m_YRatio = 0;
	TransformAttribute::addSample(this);
}
Scale::Scale(Scale &obj) {
	m_XRatio = obj.m_XRatio;
	m_YRatio = obj.m_YRatio;
}
char* Scale::GetName() {
	return "scale";
}
TransformAttribute* Scale::Clone() {
	return new Scale(*this);
}
void Scale::SetAtribute(char* attr) {
	string ScaleString(attr);
	// tim vi tri cua chuoi scale
	std::size_t start = ScaleString.find("scale");
	if (start != ScaleString.npos) {
		// tim vi tri dau (
		std::size_t parenthesis = ScaleString.find("(", start);
		// tim vi tri dau )
		std::size_t Closingparenthesis = ScaleString.find(")", start);
		// tim vi tri dau phay
		std::size_t comma = ScaleString.find(",", start);
		// neu cau truc chua ca Xratio va Yratio
		if (comma>parenthesis && comma < Closingparenthesis && comma != ScaleString.npos) {
			// lay chuoi con chua Xratio
			string Xratio = ScaleString.substr(parenthesis + 1, comma - parenthesis - 1);
			// lay chuoi con cua Yratio
			string Yratio = ScaleString.substr(comma + 1, Closingparenthesis - comma - 1);
			// chuyen doi tu string sang float
			m_XRatio = stof(Xratio);
			m_YRatio = stof(Yratio);
		}
		// neu cau truc chi chua 1 gia tri chung cho ca Xratio va Yratio
		else if (parenthesis < Closingparenthesis) {
			string ratio = ScaleString.substr(parenthesis + 1, Closingparenthesis - parenthesis - 1);
			m_XRatio = m_YRatio = stof(ratio);
		}
	}
}

void Scale::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	if (m_XRatio == m_YRatio) ofs << "scale(" << m_XRatio << ") ";
	else ofs << "scale(" << m_XRatio << "," << m_YRatio << ") ";
}
void Scale::transform(Gdiplus::Graphics &graphics) {
	graphics.ScaleTransform(m_XRatio, m_YRatio, MatrixOrderPrepend);
}

void Scale::transform(CImg<int> &Frame) {
	// chua ho tro
}

ScaleRatio Scale::getScale() {
	return ScaleRatio(m_XRatio, m_YRatio);
}
Scale::~Scale() {

}

/* setup class XCoordinates */

XCoordinates::XCoordinates() {
	m_x = 0;
	Attribute::addSample(this);
}
XCoordinates::XCoordinates(XCoordinates &obj) {
	m_x = obj.m_x;
}
char* XCoordinates::GetName(){
	return "x";
}
Attribute* XCoordinates::Clone() {
	return new XCoordinates(*this);
}
void XCoordinates::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_x = atoi(attr);
}

void XCoordinates::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "x=\"" << m_x << "\" ";
}
int XCoordinates::getX() {
	return m_x;
}
XCoordinates::~XCoordinates() {

}

/* set class YCoordinates  */

YCoordinates::YCoordinates() {
	m_Y;
	Attribute::addSample(this);
}
YCoordinates::YCoordinates(YCoordinates &obj) {
	m_Y = obj.m_Y;
}
char* YCoordinates::GetName(){
	return "y";
}
Attribute* YCoordinates::Clone() {
	return new YCoordinates(*this);
}
void YCoordinates::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_Y = atoi(attr);
}

void YCoordinates::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "y=\"" << m_Y << "\" ";
}
int YCoordinates::getY() {
	return m_Y;
}

YCoordinates::~YCoordinates() {

}

/* set class Radius */

Radius::Radius() {
	m_R = 0;
	Attribute::addSample(this);
}
Radius::Radius(Radius &obj) {
	m_R = obj.m_R;
}
char* Radius::GetName() {
	return "r";
}
Attribute* Radius::Clone() {
	return new Radius(*this);
}
void Radius::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_R = atoi(attr);
}

void Radius::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "r=\"" << m_R << "\" ";
}
int Radius::getR() {
	return m_R;
}

Radius::~Radius() {

}

/* set class Width */ 

Width::Width() {
	m_Width = 0;
	Attribute::addSample(this);
}
Width::Width(Width &obj) {
	m_Width = obj.m_Width;
}
char* Width::GetName() {
	return "width";
}
Attribute* Width::Clone() {
	return new Width(*this);
}
void Width::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_Width = atoi(attr);
}

void Width::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "width=\"" << m_Width << "\" ";
}
int Width::getWidth() {
	return m_Width;
}

Width::~Width() {

}

/* set class Height*/

Height::Height() {
	m_Height = 0;
	Attribute::addSample(this);
}
Height::Height(Height &obj) {
	m_Height = obj.m_Height;
}
char* Height::GetName() {
	return "height";
}
Attribute* Height::Clone() {
	return new Height(*this);
}
void Height::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_Height = atoi(attr);
}

void Height::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "height=\"" << m_Height << "\" ";
}
int Height::getHeight() {
	return m_Height;
}

Height::~Height() {

}

/* set Class Points */
Points::Points() {
	m_List.resize(0);
	Attribute::addSample(this);
}
Points::Points(Points &obj) {
	m_List = obj.m_List;
}
char* Points::GetName() {
	return "points";
}
Attribute* Points::Clone() {
	return new Points(*this);
}
void Points::SetAtribute(char* attr) {
	if (NULL == attr) return;
	m_List = ReadPoint(attr);
}

void Points::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "points=\"";
	for (int i = 0; i < m_List.size(); i++) {
		ofs << m_List[i].getX() << "," << m_List[i].getY();
		if (i != m_List.size() - 1) ofs << " ";
	}
	ofs << "\" ";
}
vector<MyPoint> Points::getListPoint() {
	return m_List;
}

vector<MyPoint> Points::ReadPoint(char*s) {
	vector<MyPoint> ret;
	string StringPoints(s);
	// cat bo cac space thua
	TrimSpace(StringPoints);
	// chen them dau sapce vao dua chuoi
	StringPoints.insert(0, " ");
	// chem them ki tu space vao cuoi chuoi
	StringPoints.push_back(' ');
	std::size_t Start = 0;
	// tim kiem vi tri ki tu space dau tien
	std::size_t space = StringPoints.find(" ", Start + 1);
	while (space != StringPoints.npos) {
		// tim kiem ki tu phay sau ki tu space
		std::size_t comma = StringPoints.find(",", Start);
		if (comma < space) {
			// lay chuoi con chua gia tri x
			string Xvalue = StringPoints.substr(Start + 1, comma - Start - 1);
			// lay chuoi con chua gia tri y
			string Yvalue = StringPoints.substr(comma + 1, space - comma - 1);
			// chuyen doi tu string sang int
			int x = stoi(Xvalue);
			int y = stoi(Yvalue);
			MyPoint add(x, y);
			// chen vao danh sach chuoi
			ret.push_back(add);
		}
		Start = space;
		// tim kiem vi tri space ke tiep
		space = StringPoints.find(" ", Start + 1);
	}
	return ret;
}

void Points::TrimSpace(string &s) {
	for (int i = 0; i < s.size(); i++) {
		if (isspace(s[i])) {
			int j = i + 1;
			// xoa cac space thua
			while (j < s.size() && isspace(s[j])) {
				s.erase(s.begin() + j);
			}
		}
	}
}

Points::~Points() {

}