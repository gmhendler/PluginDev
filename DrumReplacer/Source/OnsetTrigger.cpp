//
//  OnsetTrigger.cpp
//  MUSI8903
//
//  Created by Keshav Venkat on 4/27/16.
//
//

#include "OnsetTrigger.h"

#include "ErrorDef.h"

#include "Util.h"
#include <ctime>

#include "Vector.h"

COnsetTrigger::COnsetTrigger() :
	m_fSampleRate(44100),
	m_iNumChannels(1),
	m_iCounter(0),
	m_iTrigger(0)

{
	m_fThreshold = 0;
}

COnsetTrigger::~COnsetTrigger()
{
	// this->resetInstance();

}

Error_t COnsetTrigger::createInstance(COnsetTrigger*& pCOnsetTrigger)
{
	pCOnsetTrigger = new COnsetTrigger();

	if (!pCOnsetTrigger)
		return kUnknownError;

	return kNoError;
}

Error_t COnsetTrigger::destroyInstance(COnsetTrigger*& pCOnsetTrigger)
{
	if (!pCOnsetTrigger)
		return kUnknownError;

	pCOnsetTrigger->resetInstance();


	delete pCOnsetTrigger;
	pCOnsetTrigger = 0;

	return kNoError;
}


Error_t COnsetTrigger::resetInstance()
{

	return kNoError;

}


void COnsetTrigger::setThreshold(float t)
{
	m_fThreshold = t;

}
float COnsetTrigger::getThreshold()
{
	return m_fThreshold;

}

void COnsetTrigger::setDelayTime(float seconds)
{
	m_iDelayInSamples = (int)(m_fSampleRate*seconds);
}

Error_t COnsetTrigger::initInstance(float fSampleRate, int iNumChannels, float fThreshold, float seconds)
{

	COnsetTrigger::setThreshold(fThreshold);
	m_iNumChannels = iNumChannels;
	m_fSampleRate = fSampleRate;
	COnsetTrigger::setDelayTime(seconds);

	return kNoError;
}

Error_t COnsetTrigger::process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{

	for (int i = 0; i<iNumberOfFrames; i++) {

		for (int c = 0; c<m_iNumChannels; c++) {
			if (ppfInputBuffer[c][i]>m_fThreshold && m_iTrigger == 0) {
				ppfOutputBuffer[c][i] = 1;
				m_iTrigger = 1;
			}
			else {
				ppfOutputBuffer[c][i] = 0;
			}
		}

		if (m_iTrigger == 1 && m_iCounter<m_iDelayInSamples)
			m_iCounter++;
		else if (m_iTrigger == 1 && m_iCounter >= m_iDelayInSamples) {
			m_iCounter = 0;
			m_iTrigger = 0;
		}

	}

	return kNoError;

}







