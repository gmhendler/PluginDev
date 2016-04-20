#include "PPM.h"

#include "ErrorDef.h"

#include "Util.h"

#include "Vector.h"

static const char*  kCVibratoBuildDate = __DATE__;

CPPM::CPPM() :
	m_bIsInitialized(false),
	m_fSampleRate(44100),
	m_iNumChannels(0),
	m_fAttack(.01),
	m_fRelease(1.5)
{

	// this never hurts
	// this->resetInstance ();
}

CPPM::~CPPM()
{
	this->resetInstance();
	deallocate();
}

Error_t CPPM::allocate() 
{

	m_pfTempBuffer = new float[m_iNumChannels];
	CVectorFloat::setZero(m_pfTempBuffer, m_iNumChannels);
	
	return kNoError;
}

Error_t CPPM::deallocate()
{
	if (m_pfTempBuffer) {
		delete[] m_pfTempBuffer;
		m_pfTempBuffer = 0;
	}
	return kNoError;
}

const int  CPPM::getVersion(const Version_t eVersionIdx)
{
	int iVersion = 0;

	switch (eVersionIdx)
	{
	case kMajor:
		//   iVersion    = MUSI8903_VERSION_MAJOR; 
		break;
	case kMinor:
		//  iVersion    = MUSI8903_VERSION_MINOR; 
		break;
	case kPatch:
		//  iVersion    = MUSI8903_VERSION_PATCH; 
		break;
	case kNumVersionInts:
		iVersion = -1;
		break;
	}

	return iVersion;
}
const char*  CPPM::getBuildDate()
{
	return kCVibratoBuildDate;
}

Error_t CPPM::createInstance(CPPM*& pCPPM)
{
	pCPPM = new CPPM();

	if (!pCPPM)
		return kUnknownError;

	return kNoError;
}

Error_t CPPM::destroyInstance(CPPM*& pCPPM)
{
	if (!pCPPM)
		return kUnknownError;

	pCPPM->resetInstance();

	delete pCPPM;
	pCPPM = 0;

	return kNoError;
}

Error_t CPPM::initInstance(float fSampleRateInHz, int iNumChannels)
{

	m_fAlphaA = 1 - exp(-2.2 / (m_fSampleRate * m_fAttack));
	m_fAlphaR = 1 - exp(-2.2 / (m_fSampleRate * m_fRelease));

	m_fPPMValue = 0;
	m_fPPMValueTemp = 0;

	m_iNumChannels = iNumChannels;

	allocate();

	return kNoError;
}

Error_t CPPM::resetInstance()
{
	for (int c = 0; c < m_iNumChannels; c++)
	{
		m_pfTempBuffer[c] = 0;
	}
	m_pfTempBuffer = 0;

	return kNoError;
}

Error_t CPPM::process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) 
{
	if (!ppfInputBuffer || iNumberOfFrames < 0)
		return kFunctionInvalidArgsError;

	m_fPPMValue = 0;

	for (int i = 0; i < iNumberOfFrames; i++)
	{
		for (int c = 0; c < m_iNumChannels; c++)
		{
			if (m_pfTempBuffer[c] > ppfInputBuffer[c][i]) {
				m_fPPMValueTemp = (1 - m_fAlphaR) * m_pfTempBuffer[c];
			}
			else {
				m_fPPMValueTemp = m_fAlphaA * ppfInputBuffer[c][i] + (1 - m_fAlphaA) * m_pfTempBuffer[c];
			}
			m_pfTempBuffer[c] = m_fPPMValueTemp;
			if (ppfOutputBuffer != NULL) {
				ppfInputBuffer[c][i] = m_fPPMValueTemp;
			}
			if (m_fPPMValueTemp > m_fPPMValue) {
				m_fPPMValue = m_fPPMValueTemp;
			}
		}
	}

	return kNoError;
}


float CPPM::analyze(float **ppfInputBuffer, int iNumberOfFrames)
{
	if (!ppfInputBuffer || iNumberOfFrames < 0)
		return kFunctionInvalidArgsError;

	m_fPPMValue = 0;

	for (int i = 0; i < iNumberOfFrames; i++)
	{
		for (int c = 0; c < m_iNumChannels; c++)
		{
			if (m_pfTempBuffer[c] > ppfInputBuffer[c][i]) {
				m_fPPMValueTemp = (1 - m_fAlphaR) * m_pfTempBuffer[c];
			}
			else {
				m_fPPMValueTemp = m_fAlphaA * ppfInputBuffer[c][i] + (1 - m_fAlphaA) * m_pfTempBuffer[c];
			}
			m_pfTempBuffer[c] = m_fPPMValueTemp;
			if (m_fPPMValueTemp > m_fPPMValue) {
				m_fPPMValue = m_fPPMValueTemp;
			}
		}
	}

	return m_fPPMValue;
}


float CPPM::getPPMValue() {
	return m_fPPMValue;
}
