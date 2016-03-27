

// project headers
#include "ErrorDef.h"
#include "Ringbuffer.h"

#include "MyProject.h"

static const char*  kCMyProjectBuildDate             = __DATE__;


CMyProject::CMyProject ()
{
    // this never hurts
    this->reset ();
}


CMyProject::~CMyProject ()
{
   // this->reset ();
}

const int  CMyProject::getVersion (const Version_t eVersionIdx)
{
    int iVersion = 0;


    return iVersion;
}
const char*  CMyProject::getBuildDate ()
{
    return kCMyProjectBuildDate;
}

Error_t CMyProject::create (CMyProject*& pCMyProject)
{
    pCMyProject = new CMyProject ();

    if (!pCMyProject)
        return kUnknownError;


    return kNoError;
}

Error_t CMyProject::destroy (CMyProject*& pCMyProject)
{
    if (!pCMyProject)
        return kUnknownError;
    
    pCMyProject->reset ();
    
    delete pCMyProject;
    pCMyProject = 0;

    
    
    return kNoError;

}

Error_t CMyProject::init(int numChannels,int sampleRate, int maxDelay, float LFOFreq, float LFODepth) //add delay
{
    // allocate memory
    
    // initialize variables and buffers
    
    numChan = numChannels;
    
    freq = LFOFreq;
    depth = (LFODepth * (maxDelay-1)/2);
    
    //std::cout << depth<< std::endl;
    
    fs = sampleRate;
    
    count = 0;
    
    m_ppCRingBuffer = new CRingBuffer<float>*[numChan];
    for (int c = 0; c < numChannels; c++)
        m_ppCRingBuffer[c]  = new CRingBuffer<float>(maxDelay);
    
    for (int c = 0; c < numChan; c++)
    {
        m_ppCRingBuffer[c]->reset ();
        
    }
    
    return kNoError;
}

Error_t CMyProject::reset ()
{
    // reset buffers and variables to default values
    count = 0;

    if (m_ppCRingBuffer)
    {
        for (int c = 0; c < numChan; c++)
            delete m_ppCRingBuffer[c];
    }
    m_ppCRingBuffer = 0;

    delete [] m_ppCRingBuffer;
    
    
    return kNoError;
}


Error_t CMyProject::process (const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    
    for (int n = 0; n < iNumberOfFrames; n++)
    {
        mod = sin(2 * pi * freq * count/fs);
        count++;
        for (int c = 0; c < numChan; c++)
        {
            
            m_ppCRingBuffer[c]->putPostInc(ppfInputBuffer[c][n]);
            ppfOutputBuffer[c][n] = m_ppCRingBuffer[c]->getFracOffset(1+depth + depth*mod);
            
            //ppfOutputBuffer[c][n] = ppfInputBuffer[c][n];
            
        }
    }

    
    
    return kNoError;
    
}

float CMyProject::getFreq() {
	return freq;
}

float CMyProject::getDepth() {
	return depth;
}

void CMyProject::setFreq(float f) {
	freq = f;
}
void CMyProject::setDepth(float d) {
	depth = d;
}

