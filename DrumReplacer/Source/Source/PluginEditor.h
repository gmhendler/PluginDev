/*
 ==============================================================================
 
 This file was auto-generated by the Introjucer!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//#include "../modules/juce_audio_utils/gui/juce_AudioVisualiserComponent.h"
//#include "../modules/juce_audio_utils/juce_audio_utils.h"
#include "MeterComponent.h"
#include "WaveformComponent.h"

//==============================================================================
/**
 */
class DrumReplacerAudioProcessorEditor : public AudioProcessorEditor,
private Button::Listener,
private Slider::Listener,
private Timer
{
public:
    DrumReplacerAudioProcessorEditor (DrumReplacerAudioProcessor&);
    ~DrumReplacerAudioProcessorEditor();
    
    //==============================================================================
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };
    
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* s);
    
    void openButtonClicked();
    void playButtonClicked();
    
    void timerCallback();
    
    float zoom;
    float waveLen;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    DrumReplacerAudioProcessor& processor;
    
    TextButton openButton;
    TextButton playButton;
    TextButton displayButton;
    
    ToggleButton filterButton, phaseButton;
    
    AudioFormatManager formatManager;
    
    AudioSampleBuffer clipBufferOrig;
    
    Slider gain1, gainThru, threshSlider, recoverySlider, HPF, LPF, zoomSlider, offsetSlider;
    
    MeterComponent meterL, meterR;
    
    WaveformComponent waveform1, triggerWave;
    
    Label retrigLabel, zoomLabel, gainlabel1, gainlabel2, offsetLabel, filterLabel1, filterLabel2;
    
    Image bg;
    
    LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumReplacerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
