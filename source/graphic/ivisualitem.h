#ifndef IVISUALITEM_H
#define IVISUALITEM_H

class IVisualItem {

public:
	virtual ~IVisualItem() = default;
	virtual void colorChanged() = 0;
	virtual void select() = 0;
	virtual void deselect() = 0;
	virtual void changeGeometry() = 0;
	virtual bool isOverMouse() = 0;
	
};
#endif