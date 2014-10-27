//
//  CoeusList.cpp
//  Coeus
//
//  Created by - on 8/10/14.
//
//

#include "CoeusList.h"

//================================================

CoeusHeap::CoeusHeap()
:   heap(0)
{
    heapSize = 0;
    numEl = 0;
}

void CoeusHeap::update()
{
    std::cout << "=================" << std::endl;
    for(int i=heapSize/2 - 1; i>=0; --i) {
        heap[i] = heap[2*i+1] + heap[2*i+2];
        std::cout << i << "wtf: " << heap[i] << std::endl;
    }
}

int CoeusHeap::findIndexForSum(int sum)
{
    int next = 0;
    
    if (heapSize == 0 ){
        return -1;
    }
    else if (heap[0] < sum) {
        return numEl-1;
    }

    
    while(next >=0 && next < heapSize/2) {
        const int lchld = 2*next+1;
        const int rchld = 2*next+2;
        next = heap[lchld] >= sum ? lchld : rchld;
        sum -= heap[lchld] >= sum ? 0 : heap[lchld];
        sum = jmax(sum, 0);
    }
    
    return next - heapSize/2;
}

int CoeusHeap::findSumForIndex(int index)
{
    if (index < 0 || index >= numEl) {
        std::cout << "---------------" << std::endl;
        std::cout << index << " in -> sum : " << 0 << std::endl;
        return 0;
    }

    int sum = 0;
    int next = heapSize/2 + index;
    sum += next % 2 ? 0 : heap[next-1];
    next = (next - 1) >> 1;
    
    while(next > 0) {
        sum += next % 2 ? 0 : heap[next-1];
        next = (next - 1) >> 1;
    }
    
    std::cout << "---------------" << std::endl;
    std::cout << index << " in -> sum : " << sum << std::endl;

    return sum;
}

void CoeusHeap::setNewValueAtIndex(int value, int index)
{
    if (index < 0 || index >= numEl) {
        return;
    }

    int next = (heapSize/2 + index);
    heap[next] = value;
    next = (next - 1) >> 1;
    while(next > 0) {
        heap[next] = heap[2*next+1] + heap[2*next+2];
        next = (next - 1) >> 1;
    }
    
}

void CoeusHeap::setNewValues(int *values, int size)
{
    numEl = size;
    int exp = 1;
    while(size > 0) {
        size >>= 1;
        ++exp;
    }
    
    heapSize = pow(2.0, exp) - 1;
    heap.realloc(heapSize);
    
    heap.clear(heapSize);
    memcpy(heap + heapSize/2, values, numEl*sizeof(int));
}

int CoeusHeap::getValueAt(int index)
{
    return heapSize ? heap[heapSize/2 + index] : 0;
}

int CoeusHeap::getSum()
{
    return heapSize ? heap[0] : 0;
}

//===============================================================================

CoeusList::CoeusList()
:   sb(true), selectedRow(-1)
{
    sb.setRangeLimits(0.0, 1.0);
    sb.setCurrentRange(0.0, 0.5, dontSendNotification);
    sb.setAutoHide(true);
    sb.addListener(this);
    sb.setAlwaysOnTop(true);
    addAndMakeVisible(&sb);
}

CoeusList::~CoeusList()
{
    for(int i=0; i < items.size(); i++) {
        if (items[i] != nullptr) {
            delete items[i];
            items.set(i, nullptr);
        }
    }
    
    for(int i=0; i < pool.size(); i++) {
        if (pool[i] != nullptr) {
            delete pool[i];
            pool.set(i, nullptr);
        }
    }
}

void CoeusList::rowChangedSize(int rowNumber, int newSize)
{
    heap.setNewValueAtIndex(newSize, rowNumber);
    updateComponents();
    positionComponents();
}

void CoeusList::update()
{
    HeapBlock<int> hb(getNumRows());
    for(int i=0; i<getNumRows(); i++) {
        hb[i] = getRowSize(i);
    }
    
    heap.setNewValues(hb, getNumRows());
    heap.update();
    
    for(int i=0; i<items.size(); i++) {
        if (items[i] != nullptr) {
            removeChildComponent(items[i]);
            items[i]->setVisible(false);
        }
    }
    
    pool.addArray(items);
    items.clear();
    itemsToRows.clear();
    
    double sbsize = getHeight()/static_cast<double>(heap.getSum());
    sb.setCurrentRange(0.0, sbsize, dontSendNotification);
    
    updateComponents();
    positionComponents();
}

void CoeusList::resized()
{
    sb.setBounds(getWidth() - 10, 0, 10, getHeight());
    double sbsize = getHeight()/static_cast<double>(heap.getSum());
    sb.setCurrentRange(0.0, sbsize, dontSendNotification);
    
    updateComponents();
    
    positionComponents();
    
}

void CoeusList::selectRow(int rowNumber)
{
    repaintRow(selectedRow);
    repaintRow(rowNumber);
    selectedRow = rowNumber;
}

void CoeusList::repaintRow(int rowNumber)
{
    
}

int CoeusList::getRowIndexAt(int y)
{
    return heap.findIndexForSum(y);
}

int CoeusList::getYStartForRow(int index)
{
    return heap.findSumForIndex(index);
}

void CoeusList::updateComponents()
{
    const int viewHeight = sb.getCurrentRangeStart()*heap.getSum();
    const int startRow = getRowIndexAt(viewHeight);
    const int endRow = jmax(getRowIndexAt(viewHeight+getHeight()), startRow);
    
    // refresh children content
    for(int r = startRow; r <= endRow; r++) {
        if (items.size() <= r-endRow) {
            CoeusListRowComponent *res = refreshComponentForRow(r, r == selectedRow, nullptr);
            addAndMakeVisible(res);
            items.add(res);
            itemsToRows.add(r);
            res->repaint();            
        }
        else {
            CoeusListRowComponent *res = refreshComponentForRow(r, r == selectedRow, items[r-startRow]);
            if (res != items[r-startRow]) {
                removeChildComponent(items[r-startRow]);
                addAndMakeVisible(res);
            }
            items.set(r-startRow, res);
            itemsToRows.set(r-startRow, r);
            res->repaint();
        }
    }
    
    
}

void CoeusList::positionComponents()
{
    const int viewHeight = sb.getCurrentRangeStart()*heap.getSum();
    const int startRow = getRowIndexAt(viewHeight);
    const int endRow = jmax(getRowIndexAt(viewHeight+getHeight()), startRow);
    
    // set bounds
    for(int i=0; i<=endRow; i++) {
        if (items[i] != nullptr) {
            int itemStartHeight = getYStartForRow(itemsToRows[i]) - viewHeight;
            const int height = heap.getValueAt(startRow+i);
            items[i]->setBounds(0, itemStartHeight, getWidth()-sb.getWidth(), height);
        }
    }
}

void CoeusList::scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart)
{
    // update children content
    // if needed
    updateComponents();
    
    // update children position
    positionComponents();
}
