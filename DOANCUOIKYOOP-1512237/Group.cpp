#include "Group.h"


Group::Group() {
	// them vao mau
	Figure::AddSample(this);
}
Group::Group(Group &obj) : DrawAttribute(obj) {
	for (int i = 0; i < obj.m_ListFigure.size(); i++) {
		if (obj.m_ListFigure[i]!=NULL)
		m_ListFigure.push_back(obj.m_ListFigure[i]->Clone());
	}
}
char* Group::ClassName() {
	return "g";
}
Figure* Group::Clone() {
	return new Group(*this);
}
void Group::DrawGDIPlus(HDC hdc) {
	// goi cac con cua no ve
	for (int i = 0; i < m_ListFigure.size(); i++) {
		if (m_ListFigure[i] != NULL) m_ListFigure[i]->DrawGDIPlus(hdc);
	}
}

int Group::getNumAttribute() {
	// tra ve so luong Attribute trong DrawAttribute
	return DrawAttribute::getNumAttribute();
}

void Group::WriteSVGFile(ofstream &ofs, int startAttribute) {
	if (!ofs) return;
	ofs << "<g ";
	// ghi cac attribute chung ra file
	DrawAttribute::WriteAttribute(ofs,startAttribute);
	ofs << ">\n";
	// goi cac con cua no ghi ra file, laoi bo bot cac Attribute ma group da ghi
	for (int i = 0; i < m_ListFigure.size(); i++) {
		if (m_ListFigure[i] != NULL) m_ListFigure[i]->WriteSVGFile(ofs,DrawAttribute::getNumAttribute());
		ofs << "\n";
	}
	ofs << "</g> ";
}

void Group::RegisterAttribute() {
	// dang ki cac Attribute
	Attribute::RegisterDrawAttribute();
}
void Group::DrawCImg(CImg<int> &Frame) {
	// goi cac con cua no ve
	for (int i = 0; i < m_ListFigure.size(); i++) {
		if (m_ListFigure[i] != NULL) m_ListFigure[i]->DrawCImg(Frame);
	}
}
void Group::LoadAttribute(xml_node<> *node) {
	if (NULL == node) return;
	// load cac Attribute chung
	DrawAttribute::Load(node);
	xml_node<> *subnode = node->first_node();
	do {
		// khoi tao cac doi tuong Figure ma group chua thong qua ten
		Figure* object = Figure::CreateObject(subnode->name());
		if (object != NULL) {
			// dang ki Attribute
			object->RegisterAttribute();
			// nap cac Attribute cua group cho cac con cua no
			DrawAttribute::SetAttributeForFigure(object);
			// cho cac con cua group cai dat Attribute cua rieng no 
			object->LoadAttribute(subnode);
			// nap vao danh sach
			m_ListFigure.push_back(object);
		}
		// chuyen den node ke tiep
		subnode = subnode->next_sibling();
	} while (subnode);
}

void Group::addAttribute(Attribute* obj) {
	DrawAttribute::addAttribute(obj);
}
Group::~Group() {
	for (int i = 0; i < m_ListFigure.size(); i++) {
		if (m_ListFigure[i] != NULL) {
			delete m_ListFigure[i];
			m_ListFigure[i] = NULL;
		}
	}
	cout << "~Group" << endl;
}