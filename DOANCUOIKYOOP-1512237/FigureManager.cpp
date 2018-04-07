#pragma once
#include "FigureManager.h"

FigureManager::FigureManager() {
	m_list.resize(0);
}
FigureManager::FigureManager(vector<Figure*> list) {
	for (int i = 0; i < list.size(); i++) {
		Figure* add = list[i];
		if (NULL != add) {
			m_list.push_back(add->Clone());
		}
	}
}

FigureManager::FigureManager(FigureManager &obj) {
	for (int i = 0; i < obj.m_list.size(); i++) {
		Figure* add = obj.m_list[i];
		if (NULL != add) {
			m_list.push_back(add->Clone());
		}
	}
}

void FigureManager::registerFigure() {
	MyCircle();
	MyLine();
	MyPolygon();
	MyPolyline();
	MyEllipse();
	MyRectangle();
	MyPath();
	Group();
	MyText();
}

void FigureManager::DeRegisterStaticIngredient() {
	Attribute::DeleteRegister();
	Figure::DeleteRegister();
	TransformAttribute::DeleteRegister();
	MyPathIngredient::DeleteRegister();
}
void FigureManager::Load(WCHAR*Link) {
	if (Link == NULL) return;
	for (int i = 0; i < m_list.size(); i++) {
		if (m_list[i] != NULL) {
			delete m_list[i];
			m_list[i] = NULL;
		}
	}
	m_list.resize(0);
	// xoa cac mau truoc khi load
	DeRegisterStaticIngredient();
	// dang ki cac mau hinh
	registerFigure();

	string input_xml;
	string line;
	ifstream in(Link);
	CoTaskMemFree(Link);
	if (!in) return;

	// đọc toàn bộ nội dung file vào string input_xml
	while (getline(in, line))
		input_xml += line;

	in.close();

	// tạo một mảng (vector) char từ input_xml
	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');	// thêm kí tự kết thúc chuỗi

	// dùng doc để dọc trên xml_copy
	xml_document<> doc;
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	// lấy thẻ svg đầu tiên, gán vào node
	xml_node<> *node = doc.first_node("svg");

	// node->first_node() lấy thẻ (tag) con đầu tiên của svg

	node = node->first_node();
	do
	{
		// tao doi tuong figure thong qua ten
		Figure* object = Figure::CreateObject(node->name());
		if (object != NULL) {
			// dang ki cac thuoc tinh
			object->RegisterAttribute();
			// cai dat cac thuoc tinh
			object->LoadAttribute(node);
			// them vao danh sach
			m_list.push_back(object);
		}
		node = node->next_sibling();
	} while (node);

}

void FigureManager::DrawGdiPlus(HDC &hdc) {
	for (int i = 0; i < m_list.size(); i++) {
		m_list[i]->DrawGDIPlus(hdc);
	}
}

void FigureManager::DrawCImg(){
	CImg<int> Frame(1000, 800, 1, 255);
	for (int i = 0; i < m_list.size(); i++) {
		m_list[i]->DrawCImg(Frame);
	}
	CImgDisplay display(Frame, "CImg",0);
	while (!display.is_closed()) display.wait();
}

void FigureManager::WriteSVG(WCHAR* link){
	if (link == NULL) return;
	ofstream ofs;
	ofs.open(link, ios::binary);
	CoTaskMemFree(link);
	if (!ofs) return;
	ofs << "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";
	for (int i = 0; i < m_list.size(); i++) {
		m_list[i]->WriteSVGFile(ofs);
		ofs << "\n";
	}
	ofs << "</svg>";
	ofs.close();
}

FigureManager::~FigureManager() {
	int pos = m_list.size();
	if (pos > 0) {
		for (int i = 0; i < pos; i++) {
			if (m_list[i] != NULL) {
				delete m_list[i];
				m_list[i] = NULL;
			}
		}
	}
}