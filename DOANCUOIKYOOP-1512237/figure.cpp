#include "figure.h"

/*
	Set up Figure class
*/

void Figure::AddSample(Figure* obj) {
	if (obj == NULL) return;
	int pos = SampleObject.size();
	while (--pos >= 0) {
		Figure *temp = SampleObject[pos];
		if (NULL == temp) continue;
		// so sanh ten obj voi ten cac doi tuong trong mau, neu trung ten thi break
		if (strcmp(temp->ClassName(), obj->ClassName()) == 0)
			break;
	}
	if (pos < 0) {
		// neu trong danh sach mau chua co thi them vao
		SampleObject.push_back(obj->Clone());
	}
}

Figure* Figure::CreateObject(char* name) {
	if (name == NULL) return NULL;
	int pos = SampleObject.size();
	while (--pos >= 0) {
		Figure *temp = SampleObject[pos];
		if (temp == NULL) continue;
		if (strcmp(name, temp->ClassName()) == 0) break;
	}
	if (pos >= 0) return SampleObject[pos]->Clone();
	return NULL;
}

Figure::~Figure() {

}

void Figure::DeleteRegister() {
	for (int i = 0; i < SampleObject.size(); i++) {
		if (SampleObject[i] != NULL) {
			delete SampleObject[i];
			SampleObject[i] = NULL;
		}
	}
}



/*
	Set up DrawAttribute class
*/

DrawAttribute::DrawAttribute() {
	m_Attrs.resize(0);
}

DrawAttribute::DrawAttribute(DrawAttribute &obj) {
	m_Attrs.resize(0);
	for (int i = 0; i < obj.m_Attrs.size(); i++) {
		if (NULL != obj.m_Attrs[i]) {
			Attribute* temp = m_Attrs[i]->Clone();
			m_Attrs.push_back(temp);
		}
	}
}


Pen* DrawAttribute::getPen() {
	// lay cac thuoc tinh thong qua ten
	StrokeOpacity* strokeOpacity = (StrokeOpacity*) DrawAttribute::findAttributeByName("stroke-opacity");
	StrokeColor* strokeColor = (StrokeColor*) findAttributeByName("stroke");
	StrokeWidth* strokeWidth = (StrokeWidth*)findAttributeByName("stroke-width");
	float width = 0; // do day mac dinh la 0
	float sOpacity = 1; // opacity mac dinh la 0
	Color sColor = Color(0, 0, 0, 0); // mac dinh cho mau la black
	if (strokeWidth != NULL) width = strokeWidth->getStrokeWidth();
	if (strokeOpacity != NULL) sOpacity = strokeOpacity->getStrokeOpacity();
	if (strokeColor != NULL) sColor = strokeColor->getStrokeColor();
	// cai Color cho Pen tu cac Attribute lay ra o tren
	Color temp((sOpacity * 255 )* sColor.GetA(), sColor.GetR(), sColor.GetG(), sColor.GetB()); 
	// tao pen voi do day width va Color temp
	Pen *ret = new Pen(temp, width);
	return ret;
}

int DrawAttribute::getNumAttribute() {
	return m_Attrs.size();
}

void DrawAttribute::WriteAttribute(ofstream &ofs, int start) {
	if (!ofs||start<0) return;
	// duyet danh sach Attribute tu start va goi cac Attribute ghi gia tri cua no ra File Svg
	for (int i = start; i < m_Attrs.size(); i++) {
		m_Attrs[i]->WriteSVGFile(ofs);
	}
}
void DrawAttribute::Load(xml_node<> *node) {
	if (NULL == node) return;
	// duyet cac Attribte trong node
	for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		// tao Doi tuong Attribute thong qua ten , bang cach so sanh  attr->name voi className cua cac lop con Attribute trong danh sach mau lop Attribute
		Attribute* add = Attribute::CreateObject(attr->name());
		if (NULL != add){
			// cho doi tuong Attribute vua tao cai dat gia tri tu chuoi Attr->Value
			add->SetAtribute(attr->value());
			// them vao danh sach thuoc tinh
			m_Attrs.push_back(add);
		}
	}
}

void DrawAttribute::addAttribute(Attribute* obj) {
	if (obj != NULL) {
		// them obj  vao danh sach thuoc tinh
		m_Attrs.push_back(obj); 
	}
}

// nap tat cac Attribute trong danh sach vao doi tuong Figure
void DrawAttribute::SetAttributeForFigure(Figure* fig) {
	if (NULL == fig) return;
	for (int i = 0; i < m_Attrs.size(); i++) {
		if (m_Attrs[i] != NULL) {
			// sao chep doi tuong Atttribte de nap vao fig
			Attribute* temp = m_Attrs[i]->Clone();
			fig->addAttribute(temp);
		}
	}
}

// tim kiem va tra ve doi tuog Attribute thong qua name
// nth : tim Attribute thu nth trong danh sach, mac dinh nth=0 khi do tim va tra ve Attribute o cuoi danh sach  
Attribute* DrawAttribute::findAttributeByName(char* name, int nth) {
	if (NULL == name||nth<0) return NULL;
		// lay do dai danh sach
		int pos = m_Attrs.size();
		// truong hop nth=0 tim Attribute co ten name o cuoi danh sach
		if (nth == 0) {
			while (--pos >= 0) {
				Attribute* temp = m_Attrs[pos];
				if (temp == NULL) continue;
				// so sanh name va className cua doi tuong con Attribute
				if (strcmp(name, temp->GetName()) == 0) break;
			}
			if (pos >= 0) return m_Attrs[pos];
		}
		// tim Attribute co ten name xuat hien lan thu nth trong danh sach
		else {
			int m_nth = nth;
			int i = 0;
			while (i < pos &&m_nth>0) {
				Attribute* temp = m_Attrs[i];
				// so sanh name va className cua doi tuong con Attribute
				if (strcmp(name, temp->GetName()) == 0) {
					m_nth--;
					if (m_nth == 0) break;
				}
				i++;
			}
			if (i < pos &&m_nth == 0) {
				return m_Attrs[i];
			}
		}
		// khong tim thay tra ve NULL
	return NULL;
}

DrawAttribute::~DrawAttribute() {
	// gia phong vung nho cac con tro Attribute* trong danh sach
	for (int i = 0; i < m_Attrs.size(); i++) {
		if (NULL != m_Attrs[i]) {
			delete m_Attrs[i];
			m_Attrs[i] = NULL;
		}
	}
}

Brush* DrawAttribute::getBrush() {
	FillColor* fillClor = (FillColor*) DrawAttribute::findAttributeByName("fill");
	FillOpacity* fillOpacity = (FillOpacity*) DrawAttribute::findAttributeByName("fill-opacity");
	// mac dinh fill Color la mau den
	Color fColor = Color(0, 0, 0, 0);
	// mac dinh fillOpacity = 1
	float fOpacity = 1;
	if (NULL != fillClor) fColor = fillClor->getFillColor();
	if (NULL != fillOpacity) fOpacity = fillOpacity->getFillOpacity();
	// tao Color cho Brush tu cac thuoc tinh lay duoc
	Color temp((fOpacity * 255)*fColor.GetA(), fColor.GetR(), fColor.GetG(), fColor.GetB());
	SolidBrush *ret = new SolidBrush(temp);
	return ret;
}

// tim va thuc hien lenh transform tat cac cac doi tuong Attribute trong danh sach
void DrawAttribute::transform(Gdiplus::Graphics &graphics) {
	int m_nth = 1;
	// tim doi tuong thuoc tinh Transform dau tien trong danh sach
	Transform* Transformer = (Transform*) DrawAttribute::findAttributeByName("transform", m_nth);
	while (Transformer != NULL) {
			Transformer->transform(graphics);
			Transformer = (Transform*)DrawAttribute::findAttributeByName("transform", ++m_nth);
	}
}

void DrawAttribute::transform(CImg<int> &Frame) {
	int m_nth = 1;
	// tim doi tuong thuoc tinh Transform dau tien trong danh sach
	Transform* Transformer = (Transform*)DrawAttribute::findAttributeByName("transform", m_nth);
	while (Transformer != NULL) {
		Transformer->transform(Frame);
		Transformer = (Transform*)DrawAttribute::findAttributeByName("transform", ++m_nth);
	}
}