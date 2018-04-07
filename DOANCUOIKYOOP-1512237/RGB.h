#pragma once

#include <iostream>
using namespace std;

class MyRGB{
private:
	unsigned char m_RGB[3];
public:
	MyRGB() {
		m_RGB[0] = 0;
		m_RGB[1] = 0;
		m_RGB[2] = 0;
	}
	MyRGB(unsigned char R, unsigned char G, unsigned char B) {
		m_RGB[0] = R;
		m_RGB[1] = G;
		m_RGB[2] = B;
	}
	unsigned char getR() {
		return m_RGB[0];
	}
	unsigned char getG() {
		return m_RGB[1];
	}
	unsigned char getB() {
		return m_RGB[2];
	}
	unsigned char* data() {
		return m_RGB;
	}
};