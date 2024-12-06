#include "objPosArrayList.h"
#include <cstdlib>

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList() //constructor
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; //200 by default
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    for (int i = 0; i < listSize; i++) {
        delete aList[i].pos;  
        aList[i].pos = nullptr;
    }
    delete[] aList;
    aList = nullptr;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    int i;
    for (i = listSize; i > 0; i--)
    {
       aList[i] = aList[i-1]; 
    }

    aList[0] = thisPos;
    listSize++;

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    aList[listSize] = thisPos;
    listSize++;

}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
    {
        return;
    }

    int i;
    for (i = 0; i < listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }
    
    listSize--;

}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    objPos copy(aList[0]);  // Create a deep copy
    return copy;
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize)
    {
        return objPos();
    }

    return aList[index];

}