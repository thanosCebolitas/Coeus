/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"
#include "CacheViewer.h"
#include "CoeusCommandIDs.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  :	public Component,
						public ButtonListener,
						public ApplicationCommandTarget,
                        public ComponentBoundsConstrainer
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

	// command target
	ApplicationCommandTarget * 	getNextCommandTarget() override;
	void getAllCommands(Array< CommandID > &commands) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo &result) override;
	bool perform(const InvocationInfo &info) override;

    void resizeStart() {
        MainComponent *comp = dynamic_cast<MainComponent *>(tabs->getCurrentContentComponent());
        if (comp) {
            comp->resizeStart();
        }
    }

    void resizeEnd() {
        MainComponent *comp = dynamic_cast<MainComponent *>(tabs->getCurrentContentComponent());
        if (comp) {
            comp->resizeEnd();
        }
    }

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================

	ScopedPointer<TabbedComponent> tabs;
	ScopedPointer<ThemeComponent> tc;
	Theme theme;
	ApplicationCommandManager commandManager;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
