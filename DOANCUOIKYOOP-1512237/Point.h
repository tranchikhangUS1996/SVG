#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class MyPoint {
private: 
	int m_x;
	int m_y;
public:
	MyPoint();
	MyPoint(int x, int y);
	int getX();
	int getY();
	MyPoint& operator = (MyPoint &obj);
};


class ScaleRatio {
private:
	float m_XRatio;
	float m_YRatio;
public:
	ScaleRatio();
	ScaleRatio(float x, float y);
	float getXRatio();
	float getYRatio();
	ScaleRatio& operator=(ScaleRatio &obj);
};