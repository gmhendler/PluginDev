/*
 ==============================================================================
 
 WaveformComponent.h
 Created: 30 Jun 2015 1:36:02pm
 Author:  Tal Aviram
 
 ==============================================================================
 */

#ifndef WAVEFORMCOMPONENT_H_INCLUDED
#define WAVEFORMCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/* This component scrolls a continuous waveform showing the audio that's
 coming into whatever audio inputs this object is connected to.
 */
class WaveformComponent  : public Component
{
public:
	WaveformComponent()
		: nextSample(0), subSample(0), accumulator(0)
	{
		setOpaque(true);
		clear();
	}

	void clearWaveformBuffer()
	{
		clear();
	}

	void onWaveformUpdate(AudioSampleBuffer buffer, int lastKnownBufferSize) {
		float** ppfWriteBuffer = buffer.getArrayOfWritePointers();
		for (int i = 0; i<buffer.getNumSamples(); i++) {
			pushSample(ppfWriteBuffer[0][i]);
		}
		repaint();
	}

	bool skipFrames = true;     // makes simple "interlaced" look by skipping sample frames..
    
private:
    float samples[1024];
    int nextSample, subSample;
    float accumulator;
    
    
    void clear()
    {
        zeromem (samples, sizeof (samples));
        accumulator = 0;
        subSample = 0;
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::grey.withAlpha(0.3f));
        
        const float midY = getHeight() * 0.5f;
        int samplesAgo = (nextSample + numElementsInArray (samples) - 1);
        
        RectangleList<float> waveform;
        waveform.ensureStorageAllocated ((int) numElementsInArray (samples));
        
        float sumSamples = 0;
        
        for (int x = jmin (getWidth(), (int) numElementsInArray (samples)); --x >= 0;)
        {
            sumSamples += samples[x];
            
            bool interlacedLook;
            
            if (skipFrames){
                interlacedLook = fmod(x,2)!=0;
            }
            else{
                interlacedLook = false;
            }
            
            if (interlacedLook){
                const float sampleSize = midY * samples [samplesAgo-- % numElementsInArray (samples)];
                waveform.addWithoutMerging (Rectangle<float> ((float) x, midY - sampleSize, 1.0f, sampleSize * 2.0f));
            }
        }
        
        g.setColour (Colours::whitesmoke);
        g.fillRectList (waveform);
        g.setFont (15.0f);
        
        float avgValue = sumSamples/numElementsInArray(samples);
        
        g.drawText (String::formatted("AvgBufVal: %f",avgValue), getLocalBounds(), Justification::bottomLeft, 1);
    }
    
    void pushSample (const float newSample)
    {
        accumulator += newSample;
        
        if (subSample == 0)
        {
            const int inputSamplesPerPixel = 200;
            
            samples[nextSample] = accumulator / inputSamplesPerPixel;
            nextSample = (nextSample + 1) % numElementsInArray (samples);
            subSample = inputSamplesPerPixel;
            accumulator = 0;
        }
        else
        {
            --subSample;
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformComponent);
};

#endif  // WAVEFORMCOMPONENT_H_INCLUDED
