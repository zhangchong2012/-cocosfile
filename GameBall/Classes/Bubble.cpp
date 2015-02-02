#include "Bubble.h"


Bubble::Bubble(void)
{
}


Bubble::~Bubble(void)
{
}

bool Bubble::init(){
	m_color = COLOR_COUNT;
	m_ColIndex = -1;
	m_RowIndex = -1;
	return true;
}

void Bubble::setBubbleColor(BUBBLE_COLOR color){
	m_color = color;
}

BUBBLE_COLOR Bubble::getBubbleColor(){
	return m_color;
}

void Bubble::setRowIndex(int row){
	m_RowIndex = row;
}

int Bubble::getRowIndex(){
	return m_RowIndex;
}

void Bubble::setColIndex(int col){
	m_ColIndex = col;
}

int Bubble::getColIndex(){
	return m_ColIndex;
}

BUBBLE_COLOR Bubble::randomColor(){
	m_color = static_cast<BUBBLE_COLOR>(rand() % COLOR_COUNT);
	return m_color;
}
