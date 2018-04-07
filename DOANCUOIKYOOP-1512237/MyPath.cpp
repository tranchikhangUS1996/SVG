#include "MyPath.h"

/* setup class MyPathIngredient */

void MyPathIngredient::addSample(MyPathIngredient* obj) {
	if (NULL == obj) return;
	int pos = SamplePath.size();
	while (--pos >= 0) {
		MyPathIngredient* add = SamplePath[pos];
		if (add == NULL) continue;
		// so sanh obj name voi ten cac doi tuong trong mau, neu trung ten thi thoat ra
		if (strcmp(add->getName(), obj->getName()) == 0) break;
	}
	if (pos < 0) {
		// neu trong danh sach mau chua co thi them vao mau
		SamplePath.push_back(obj->Clone());
	}
}

// tao doi tuong voi con cua MypathIngredient thong qua ten
vector<MyPathIngredient*> MyPathIngredient::CreateObject(char *name) {
	vector<MyPathIngredient*>  ret;
	if (NULL == name) return ret;
	string s(name);
	int length = s.size();
	int pos = SamplePath.size();
	// duyet tat ca cac ki tu cua chuoi
	for (int i = 0; i < length ; i++) {
		// neu la ki tu la chu cai
		if (isalpha(s[i])) {
			int temp = i;
			while (temp < length&&isalpha(s[temp])) temp++;
			if (temp < length)  {
				// lay ra ten lenh cua path
				string sub = s.substr(i, temp-i);
				// duyet danh sach mau
				for (int j = 0; j < pos; j++) {
					MyPathIngredient* object = SamplePath[j];
					if (object != NULL) {
						// so sanh ten cua doi tuong trong mau va sub
						string objectname(object->getName());
						// neu trung ten thi tao doi tuong
						if (sub == objectname) {
							MyPathIngredient* add = object->Clone();
							// cho doi tuong add cai dat cac gia tri 
							add->LoadAttribute(name, i);
							// push vao danh sach
							ret.push_back(add);
							break;
						}
					}
				}
			}
			// lui lai 1 vi tri de tiep tuc
			i = temp-1;
		}
	}
	return ret;
}


// dang ki cac lenh trong path
void MyPathIngredient::RegisterPathIngredient() {
	MoveTo();
	AbsoluteLineTo();
	HorizontalLineTo();
	VerticalLineTo();
	ClosePath();
	CubicBenzierCurve();
}

MyPathIngredient::~MyPathIngredient() {
	
}

void MyPathIngredient::DeleteRegister() {
	for (int i = 0; i < SamplePath.size(); i++) {
		if (SamplePath[i] != NULL) {
			delete SamplePath[i];
			SamplePath[i] = NULL;
		}
	}
}

/* setup class MoveTo */

MoveTo::MoveTo() {
	m_Pos = PointF(0, 0);
	MyPathIngredient::addSample(this);
}
MoveTo::MoveTo(MoveTo &obj) {
	m_Pos = obj.m_Pos;
}
char* MoveTo::getName() {
	return "M";
}
MyPathIngredient* MoveTo::Clone() {
	return new MoveTo(*this);
}
void MoveTo::LoadAttribute(char* s, std::size_t start) { // start: vi tri bat dau cua ten thuoc tinh
	if (start<0 || NULL==s||start > strlen(s)) return;
	string attr(s);
	// tim dau phay dau sau start
	std::size_t comma = attr.find(",", start);
	// tim dau space dau sau start
	std::size_t space = attr.find(" ", start);
	if (comma >= space) return; // truong hop khong tim thay , va ' '  thi vi tri cung nam tai npos
	string x = attr.substr(start + 1, comma - start - 1); //cat chuoi con chua hoanh do
	string y = attr.substr(comma + 1, space - comma - 1); // cat chuoi con chua tung do
	m_Pos = PointF(stof(x), stof(y)); 
}
PointF MoveTo::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint, PointF*  StartPoint ) {
	return m_Pos; // tra ve vi tri doi den;
}
void MoveTo::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "M" << m_Pos.X << "," << m_Pos.Y << " ";
}
MoveTo::~MoveTo() {

}

/* setup class ClosePath */

ClosePath::ClosePath() {
	MyPathIngredient::addSample(this);
}
ClosePath::ClosePath(ClosePath &obj) {

}
char* ClosePath::getName() {
	return "Z";
}
MyPathIngredient* ClosePath::Clone() {
	return new ClosePath(*this);
}
void ClosePath::LoadAttribute(char* s, std::size_t start) {
	// none
}
PointF ClosePath::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint , PointF*  StartPoint) {
	if (StartPoint == NULL || LastPoint == NULL) return PointF(0, 0);
	graphics.DrawLine(pen, *StartPoint, *LastPoint);
	return *LastPoint;
}
void ClosePath::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "Z";
}
ClosePath::~ClosePath() {

}

/* setup class AbsoluteLineTo */ 

AbsoluteLineTo::AbsoluteLineTo() {
	m_End = PointF(0, 0);
	MyPathIngredient::addSample(this);
}
AbsoluteLineTo::AbsoluteLineTo(AbsoluteLineTo &obj) {
	m_End = obj.m_End;
}
char* AbsoluteLineTo::getName() {
	return "L";
}
MyPathIngredient* AbsoluteLineTo::Clone() {
	return new AbsoluteLineTo(*this);
}
void AbsoluteLineTo::LoadAttribute(char* s, std::size_t start) {
	if (start<0 || NULL == s || start > strlen(s)) return;
	string attr(s);
	std::size_t comma = attr.find(",", start);
	std::size_t space = attr.find(" ", start);
	if (comma >= space) return; // truong hop khong tim thay , va ' '  thi vi tri cung nam tai npos
	string x = attr.substr(start + 1, comma - start - 1); //cat chuoi con chua hoanh do
	string y = attr.substr(comma + 1, space - comma - 1); // cat chuoi con chua tung do
	m_End = PointF(stof(x), stof(y));
}
PointF AbsoluteLineTo::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen, Brush* brush, PointF* LastPoint , PointF*  StartPoint ) {
	graphics.DrawLine(pen, *LastPoint, m_End); // ve tu diem hien tai den diem m_End
	return m_End; // tra ve diem cuoi cung ve
}
void AbsoluteLineTo::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "L" << m_End.X << "," << m_End.Y<<" ";
}
AbsoluteLineTo::~AbsoluteLineTo() {

}
/* setup class HorizontalLineTo */

HorizontalLineTo::HorizontalLineTo() {
	m_X = 0;
	MyPathIngredient::addSample(this);
}
HorizontalLineTo::HorizontalLineTo(HorizontalLineTo &obj) {
	m_X = obj.m_X;
}
char* HorizontalLineTo::getName() {
	return "H";
}
MyPathIngredient* HorizontalLineTo::Clone() {
	return new HorizontalLineTo(*this);
}

void HorizontalLineTo::LoadAttribute(char* s, std::size_t start){
	if (start<0 || NULL == s || start > strlen(s)) return;
	string attr(s);
	std::size_t space = attr.find(" ", start);
	if (space == attr.npos) return;
		string sx = attr.substr(start + 1, space - start - 1); //cat chuoi con chua hoanh do
		m_X = stof(sx);
}
PointF HorizontalLineTo::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint, PointF*  StartPoint) {
	graphics.DrawLine(pen, *LastPoint, PointF(m_X, LastPoint->Y));
	return PointF(m_X, LastPoint->Y);
}
void HorizontalLineTo::WriteSVGFile(ofstream &ofs) {
	ofs << "H" << m_X << " ";
}
HorizontalLineTo::~HorizontalLineTo() {

}

/* setup class VerticalLineTo */

VerticalLineTo::VerticalLineTo() {
	m_Y = 0;
	MyPathIngredient::addSample(this);
}
VerticalLineTo::VerticalLineTo(VerticalLineTo &obj) {
	m_Y = obj.m_Y;
}
char* VerticalLineTo::getName() {
	return "V";
}
MyPathIngredient* VerticalLineTo::Clone() {
	return new VerticalLineTo(*this);
}

void VerticalLineTo::LoadAttribute(char* s, std::size_t start){
	if (start<0 || NULL == s || start > strlen(s)) return;
	string attr(s);
	std::size_t space = attr.find(" ", start);
	if (space == attr.npos) return;
	string sy = attr.substr(start + 1, space - start - 1); //cat chuoi con chua  tung do
	m_Y = stof(sy);
}
PointF VerticalLineTo::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen , Brush* brush, PointF* LastPoint , PointF*  StartPoint ) {
	graphics.DrawLine(pen, *LastPoint, PointF (LastPoint->X,m_Y));
	return PointF(LastPoint->X,m_Y);
}
void VerticalLineTo::WriteSVGFile(ofstream &ofs) {
	ofs << "V" << m_Y << " ";
}
VerticalLineTo::~VerticalLineTo() {

}

/* setup class CubicbenzierCurve */

CubicBenzierCurve::CubicBenzierCurve() {
	m_p1 = PointF(0, 0);
	m_p2 = PointF(0, 0);
	m_p3 = PointF(0, 0);
	MyPathIngredient::addSample(this);
}
CubicBenzierCurve::CubicBenzierCurve(CubicBenzierCurve &obj) {
	m_p1 = obj.m_p1;
	m_p2 = obj.m_p2;
	m_p3 = obj.m_p3;
}
char* CubicBenzierCurve::getName() {
	return "C";
}
MyPathIngredient* CubicBenzierCurve::Clone() {
	return new CubicBenzierCurve(*this);
}
void CubicBenzierCurve::LoadAttribute(char* s, std::size_t start) {
	if (start<0 || NULL == s || start > strlen(s)) return;
	string attr(s);
	std::size_t comma1 = attr.find(",", start);
	std::size_t comma2 = attr.find(",", comma1 + 1);
	std::size_t comma3 = attr.find(",", comma2 + 1);
	if (comma1 == comma2 == comma3) return; // truong hop khong im ra dau phay
	std::size_t space1 = attr.find(" ", comma1);
	std::size_t space2 = attr.find(" ", comma2);
	std::size_t space3 = attr.find(" ", comma3);
	if (space1 == space2 == space3) return; //truong hop khong tim ra dau space
	float x1 = stof(attr.substr(start + 1, comma1 - start - 1));
	float y1 = stof(attr.substr(comma1 + 1, space1 - comma1 - 1));
	float x2 = stof(attr.substr(space1 + 1, comma2 - space1 - 1));
	float y2 = stof(attr.substr(comma2 + 1, space2 - comma2 - 1));
	float x3 = stof(attr.substr(space2 + 1, comma3 - space2 - 1));
	float y3 = stof(attr.substr(comma3 + 1, space3 - comma3 - 1));
	m_p1 = PointF(x1, y1);
	m_p2 = PointF(x2, y2);
	m_p3 = PointF(x3, y3);
}
PointF CubicBenzierCurve::DrawGdiplus(Gdiplus::Graphics &graphics, Pen* pen, Brush* brush, PointF* LastPoint , PointF*  StartPoint ) {
	GraphicsPath path;
	// add benzier voi 4 diem ( lastPoint va  3 diem p1,p2,p3 )
	path.AddBezier(*LastPoint, m_p1, m_p2, m_p3);
	graphics.FillPath(brush, &path);
	graphics.DrawPath(pen, &path);
	return m_p3;
}
void CubicBenzierCurve::WriteSVGFile(ofstream &ofs) {
	ofs << "C" << m_p1.X << "," << m_p1.Y << " " <<
				  m_p2.X << "," << m_p2.Y << " " <<
				  m_p3.X << "," << m_p3.Y << " ";
}
CubicBenzierCurve::~CubicBenzierCurve() {

}

/*  setup class MyPathData  */

MyPathData::MyPathData() {
	m_list.resize(0);
	Attribute::addSample(this);
}
MyPathData::MyPathData(MyPathData &obj) {
	for (int i = 0; i < obj.m_list.size(); i++) {
		if (obj.m_list[i] != NULL) m_list.push_back(obj.m_list[i]->Clone());
	}
}
char* MyPathData::GetName() {
	return "d";
}
Attribute* MyPathData::Clone() {
	return new MyPathData(*this);
}
void MyPathData::SetAtribute(char* attr) {
	// dang ki cac lenh cua Path truoc khi  cai dat gia tri
	MyPathIngredient::RegisterPathIngredient();
	// lya danh sach cac lenh thong qua len CreateObject
	m_list = MyPathIngredient::CreateObject(attr);
}
void MyPathData::WriteSVGFile(ofstream &ofs) {
	if (!ofs) return;
	ofs << "d=\"";
	for (int i = 0; i < m_list.size(); i++) {
		if (m_list[i] != NULL) m_list[i]->WriteSVGFile(ofs);
	}
	ofs << "\" ";
}

vector<MyPathIngredient*> MyPathData::getPathData() {
	vector<MyPathIngredient*> ret;
	for (int i = 0; i < m_list.size(); i++) {
		if (m_list[i] != NULL) {
			ret.push_back(m_list[i]->Clone());
		}
	}
	return ret;
}

MyPathData::~MyPathData() {
	for (int i = 0; i < m_list.size(); i++) {
		if (m_list[i] != NULL) {
			delete m_list[i];
			m_list[i] = NULL;
		}
	}
}

/* setup class MyPath */

MyPath::MyPath() {
	m_LastPoint = PointF(0, 0);
	m_StartPoint = PointF(0, 0);
	Figure::AddSample(this);
}

MyPath::MyPath(MyPath &obj) : DrawAttribute(obj) {
	m_LastPoint = obj.m_LastPoint;
	m_StartPoint = obj.m_StartPoint;
}
char* MyPath::ClassName(){
	return "path";
}
Figure* MyPath::Clone() {
	return new MyPath(*this);
}
void MyPath::RegisterAttribute() {
	// dang ki cac Attribute chung
	Attribute::RegisterDrawAttribute();
	// dang ki PathData
	MyPathData();
}
void MyPath::DrawGDIPlus(HDC hdc) {
	Graphics graphics(hdc);
	Pen* pen = DrawAttribute::getPen();
	Brush* brush = DrawAttribute::getBrush();
	// thuc hien Transform
	DrawAttribute::transform(graphics);
	// tim kiem MyPath thong qua ten;
	MyPathData* d =(MyPathData*) DrawAttribute::findAttributeByName("d");
	vector<MyPathIngredient*> data;
	// lay danh sach cac lenh cua path
	if (d != NULL) data = d->getPathData();
		for (int i = 0; i < data.size(); i++) {
			if (data[i] != NULL) {
				PointF temp = m_LastPoint;
				m_LastPoint = data[i]->DrawGdiplus(graphics,pen,brush ,&m_LastPoint, &m_StartPoint);
				m_StartPoint = temp;
				delete data[i];
			}
		}
	if (pen != NULL) delete pen;
	if (brush != NULL) delete brush;
}
void MyPath::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<path ";
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << "/>";
}
void MyPath::DrawCImg(CImg<int> &Frame) {

}
void MyPath::LoadAttribute(xml_node<> *node) {
	// loat cac thuoc tinh cua DrawAttribute
	DrawAttribute::Load(node);
}
void MyPath::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}
MyPath::~MyPath() {

}