#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterComponent.h"

MeterComponent::MeterComponent() {

}

MeterComponent::~MeterComponent() {

}

void MeterComponent::paint(Graphics& g)
{
	g.setColour(Colours::black);
	g.fillRect(posX, posY, width, height);
	if (peak > -12) {
		g.setColour(Colours::green);
		g.fillRect(posX, height - (int)((peak / -12.0)*height), width, (int)((peak/-12.0)*height));
	}
}

void MeterComponent::setPosX(int x) {
	posX = x;
}

void MeterComponent::setPosY(int y) {
	posY = y;
}

void MeterComponent::setHeight(int h) {
	height = h;
}

void MeterComponent::setWidth(int w) {
	width = w;
}

void MeterComponent::setValue(float val) {
	peak = 20 * log10(val);
}

float MeterComponent::getPeak() {
	return peak;
}