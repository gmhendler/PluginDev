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

	void setValue(float v);

	float getPeak();

private:

	float peak;	

	float minPeak;

};


#endif  // FILMSTRIPMETER_H_INCLUDED