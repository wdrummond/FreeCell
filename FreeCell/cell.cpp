
//Cell implementation file

#include "stdafx.h"
#include "cell.h"
#pragma once

Cell::Cell(int l, int t, int r, int b)
	:mLeft(l),mTop(t), mRight(r), mBottom(b)
{
}

void Cell::Draw(CPaintDC &dc)
{
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	if (mCards.size() > 0)
	{
		bool highlighted = false;
		DrawCard(dc, mLeft, mTop, mCards.back(), highlighted);
	}

}

bool Cell::CanRemoveCard()
{
	return false;
}


bool Cell::CanAcceptCard(int index)
{
	return false;
}

void Cell::AddCard(int index)
{
	mCards.push_back(index);
}
	
int Cell::RemoveCard()
{
	return 0;
}
	
bool Cell::IsPointWithinCell(CPoint point)
{
	return false;
}
	
int Cell::GetCardOnTop() // or -1 if none there.
{
	return 0;
}
	
void Cell::SetSelected(bool selected)
{

}


TempCell::TempCell(int l, int t, int r, int b)
	:Cell(l, t, r, b)
{
	//constructor
}

EndCell::EndCell(int l, int t, int r, int b)
	:Cell(l, t, r, b)
{

}
bool EndCell::CanRemoveCard()
{
	return false;
}

bool EndCell::CanAcceptCard(int index)
{
	return false;
}

StartCell::StartCell(int l, int t, int r, int b)
	:Cell(l, t, r, b)
{

}

void StartCell::Draw(CPaintDC &dc)
{
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	if (mCards.size() > 0)
	{
		bool highlighted = false;
		for(unsigned int i=0; i<mCards.size(); i++)
		{
			DrawCard(dc, mLeft, mTop+verticalDropBetweenCards*i, mCards[i], highlighted);
		}
	}
}

bool StartCell::CanAcceptCard(int index)
{
	return false;
}