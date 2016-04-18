#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterComponent.h"

MeterComponent::MeterComponent() {
	minPeak = -12.0;
}

MeterComponent::~MeterComponent() {

}

void MeterComponent::paint(Graphics& g)
{

	g.fillAll(Colours::black);

	if (peak > minPeak) {
		g.setColour(Colours::green);
		g.fillRect(0, (int)((peak / minPeak)*getHeight()), getWidth(), getHeight() - (int)((peak/minPeak)*getHeight()));
	}
}

void MeterComponent::setValue(float val) {
	peak = 20 * log10(val);
	repaint();
}

float MeterComponent::getPeak() {
	return peak;
}