//
//  OnsetTrigger.hpp
//  MUSI8903
//
//  Created by Keshav Venkat on 4/27/16.
//
//

#ifndef OnsetTrigger_hpp
#define OnsetTrigger_hpp

#include <stdio.h>

#include "ErrorDef.h"

class COnsetTrigger
{
public:


	static Error_t createInstance(COnsetTrigger*& pCOnsetTrigger);
	static Error_t destroyInstance(COnsetTrigger*& pCOnsetTrigger);


	Error_t resetInstance();


	void setThreshold(float t);
	float getThreshold();

	Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

	Error_t initInstance(float fSampleRateInHz, int iNumChannels, float fThreshold, float seconds);

	void setDelayTime(float time);

protected:
	COnsetTrigger();
	virtual ~COnsetTrigger();

private:
	float m_fThreshold;
	int m_iNumChannels;
	float m_fSampleRate;
	int m_iCounter;
	int m_iDelayInSamples;
	int m_iTrigger;


};

#endif /* OnsetTrigger_hpp */