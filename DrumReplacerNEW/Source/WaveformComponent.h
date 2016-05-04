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
	{
		clear();
	}

	void clearWaveformBuffer()
	{
		clear();
	}

	void updateBuffer(AudioSampleBuffer buffer, int numSamples) {
		buff = buffer;
		length = numSamples;
		loaded = true;
		repaint();
	}

	void setZoom(float z) {
		zoom = z;
		repaint();
	}

    
private:
    
	int length, lengthZoomed;

	float zoom; 
	AudioSampleBuffer buff;

	bool loaded = false;
    
    void clear()
    {

		buff.clear();
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::black);
        
        const float midY = getHeight() * 0.5f;

		float sampWidth = getWidth() / ((float)length * zoom);

		float ** ppfBuffer = buff.getArrayOfWritePointers();

		float amp = 0;

		if (loaded) {
			g.setColour(Colours::grey);
			for (int i = 0; i < length; i++) {
				amp = ppfBuffer[0][i];
				int xLoc = (int)(sampWidth * i);
				float h = amp * getHeight() / 2;
				if (h < 0) {
					float top = midY + h;
					g.drawVerticalLine(xLoc, top, midY);
				}
				else if (h > 0) {
					float btm = midY + h;
					g.drawVerticalLine(xLoc, midY, btm);
				}

			}
		}

    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformComponent);
};

#endif  // WAVEFORMCOMPONENT_H_INCLUDED
