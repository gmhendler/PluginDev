#if !defined(__PPM_hdr__)
#define __PPM_hdr__

#include "ErrorDef.h"

class CPPM
{
public:
	/*! version number */
	enum Version_t
	{
		kMajor, //!< major version number
		kMinor, //!< minor version number
		kPatch, //!< patch version number

		kNumVersionInts
	};

	static const int getVersion(const Version_t eVersionIdx);
	static const char* getBuildDate();

	static Error_t createInstance(CPPM*& pCVibrato);
	static Error_t destroyInstance(CPPM*& pCVibrato);

	Error_t initInstance(float fSampleRateInHz, int iNumChannels);
	Error_t resetInstance();

	Error_t allocate();
	Error_t deallocate();

	Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

	float getPPMValue();

	void setAttack(float a);

	void setRelease(float r);

	float getPPMChannelValue(int channel);

protected:
	CPPM();
	virtual ~CPPM();

private:
	bool m_bIsInitialized;

	float m_fAttack;
	float m_fRelease;

	float m_fAlphaA;
	float m_fAlphaR;

	float *m_pfTempBuffer;
	float *m_pfPPMValues;


	float m_fPPMValue;
	float m_fPPMValueTemp;

	float   m_fSampleRate;
	int     m_iNumChannels;

	bool polled;
};

#endif // #if !defined(__PPM_hdr__)