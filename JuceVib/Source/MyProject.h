#if !defined(__MyProject_hdr__)
#define __MyProject_hdr__

#include "ErrorDef.h"
#include "RingBuffer.h"

#define pi 3.14159

class CMyProject
{
public:
    /*! version number */
    enum Version_t
    {
        kMajor,                         //!< major version number
        kMinor,                         //!< minor version number
        kPatch,                         //!< patch version number

        kNumVersionInts
    };
    
    int dly;  //delay
    
    CRingBuffer<float>  **m_ppCRingBuffer; 
    
    
    int numChan;
    
    float freq;
    float depth;
    float mod;
    
    int fs;
    
    int count;
    
    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();

    static Error_t create (CMyProject*& pCKortIf);
    static Error_t destroy (CMyProject*& pCKortIf);
    
    Error_t init (int numChannels,int sampleRate, int maxDelay, float LFOFreq, float LFODepth);
    Error_t reset ();
    
    virtual Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

	float getFreq();
	float getDepth();
	void setFreq(float f);
	void setDepth(float d);

protected:
    CMyProject ();
    virtual ~CMyProject ();
};

#endif // #if !defined(__MyProject_hdr__)



