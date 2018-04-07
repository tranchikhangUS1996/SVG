#include "Point.h"

MyPoint::MyPoint() {
	m_x = 0;
	m_y = 0;
}
MyPoint::MyPoint(int x, int y){
	m_x = x;
	m_y = y;
}
int MyPoint::getX(){
	return m_x;
}
int MyPoint::getY(){
	return m_y;
}

MyPoint& MyPoint::operator = (MyPoint &obj) {
	m_x = obj.m_x;
	m_y = obj.m_y;
	return *this;
}

ScaleRatio::ScaleRatio() {
	m_XRatio = 0;
	m_YRatio = 0;
}
ScaleRatio::ScaleRatio(float x, float y) {
	m_XRatio = x;
	m_YRatio = y;
}
float ScaleRatio::getXRatio() {
	return m_XRatio;
}
float ScaleRatio::getYRatio() {
	return m_YRatio;
}
ScaleRatio& ScaleRatio::operator=(ScaleRatio &obj) {
	m_XRatio = obj.m_XRatio;
	m_YRatio = obj.m_YRatio;
	return *this;
}