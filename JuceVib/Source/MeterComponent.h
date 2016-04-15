#if !defined(__MeterComponent_hdr__)
#define __MeterComponent_hdr__

#include "ErrorDef.h"

#include "../JuceLibraryCode/JuceHeader.h"

class MeterComponent : public Component
{
public:
	MeterComponent();
	~MeterComponent();

	void paint(Graphics&);

	void setPosX(int x);

	void setPosY(int y);

	void setWidth(int w);

	void setHeight(int h);

	void setValue(float v);

	float getPeak();

private:

	int posX;
	int posY;

	int width;
	int height;

	float peak;	

};


#endif  // FILMSTRIPMETER_H_INCLUDED