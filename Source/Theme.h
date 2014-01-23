#ifndef __ThemeHeader__
#define __ThemeHeader__

#include "../JuceLibraryCode/JuceHeader.h"

class ThemeButton : public TextButton
{
public:
	ThemeButton(Colour &info, String txt) : infoColour(info) {
		text = String(txt);
	};

	void paint(Graphics &g) override {

		if (isMouseButtonDown()) {
			g.setColour(infoColour.contrasting());
		}
		else {
			g.setColour(infoColour);
		}
		g.fillAll();

		if (isMouseOver()) {
			g.setColour(infoColour.contrasting());
			g.drawRect(0, 0, getWidth(), getHeight(), 2);
		}

		g.setColour(infoColour.contrasting());
		g.drawText(text, 0, 0, getWidth(), getHeight(), Justification::centred, true);
	};

	void setInfoColour(Colour &colour) {
		infoColour = colour;
	};

private:
	Colour &infoColour;
	String text;
};

class ThemeComponent	:	public Component,
							public ButtonListener
{
public:
	ThemeComponent(Component &compToRefresh_);
	~ThemeComponent();

	void resized() override;

	void buttonClicked(Button *buttonThatWasClicked) override;

	void paint(Graphics &g) override;

	void userTriedToCloseWindow() override;

private:
	Component &compToRefresh;

	ScopedPointer<ThemeButton> buttonGr1ButtonButton;
	ScopedPointer<ThemeButton> buttonGr2ButtonButton;
	ScopedPointer<ThemeButton> buttonGr3ButtonButton;
	ScopedPointer<ThemeButton> buttonOutlineHoverButton;
	ScopedPointer<ThemeButton> buttonOutlineButton;
	ScopedPointer<ThemeButton> buttonTextDownButton;
	ScopedPointer<ThemeButton> buttonTextOverButton;
	ScopedPointer<ThemeButton> buttonTextButton;
	ScopedPointer<ThemeButton> tabButtonBarGr1Button;
	ScopedPointer<ThemeButton> tabButtonBarGr2Button;
	ScopedPointer<ThemeButton> tabButtonBarOutlineButton;
	ScopedPointer<ThemeButton> tabButtonFrontTabButton;
	ScopedPointer<ThemeButton> tabButtonFrontTabOutlineButton;
	ScopedPointer<ThemeButton> tabButtonBG1Button;
	ScopedPointer<ThemeButton> tabButtonBG2Button;
	ScopedPointer<ThemeButton> tabButtonOutlineButton;

	ScopedPointer<ThemeButton> tabButtonBackgroundWhenSelectedButton;
	ScopedPointer<ThemeButton> tabButtonBackgroundButton;
	ScopedPointer<ThemeButton> tabButtonTextWhenSelectedButton;
	ScopedPointer<ThemeButton> tabButtonTextMouseOverButton;
	ScopedPointer<ThemeButton> tabButtonTextOnClickButton;
	ScopedPointer<ThemeButton> tabLineFillButton;
	ScopedPointer<ThemeButton> aboveTabBarFillButton;
	ScopedPointer<ThemeButton> sideBarLeftFillButton;
	ScopedPointer<ThemeButton> sideBarRightFillButton;
	ScopedPointer<ThemeButton> workSpaceFillButton;

	ScopedPointer<ColourSelector> cs;
};

class Theme	:	public LookAndFeel_V2
{
public:
	// Button stuff
	void drawButtonBackground (Graphics &, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown); 
	Font getTextButtonFont (TextButton &button);
	void drawButtonText (Graphics &, TextButton &, bool isMouseOverButton, bool isButtonDown);
	void drawToggleButton (Graphics &, ToggleButton &, bool isMouseOverButton, bool isButtonDown);
	void changeToggleButtonWidthToFitText (ToggleButton &);
	void drawTickBox (Graphics &, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);
	void drawDrawableButton (Graphics &, DrawableButton &, bool isMouseOverButton, bool isButtonDown);

	// tabs stuff

	int getTabButtonSpaceAroundImage ();
	int getTabButtonOverlap (int tabDepth);
	int getTabButtonBestWidth (TabBarButton &, int tabDepth);
	void drawTabButton (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown);
	void drawTabButtonText (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown);
	void drawTabbedButtonBarBackground (TabbedButtonBar &, Graphics &);
	void drawTabAreaBehindFrontButton (TabbedButtonBar &, Graphics &, int w, int h);

	static Path createRectPath(int x, int y, int w, int h, int pad, int padB, int cDist);

	// scrollbars
	bool areScrollbarButtonsVisible() override;
};


class CoeusTabbedComponent :   public TabbedComponent
{
public:
    CoeusTabbedComponent();
    void paint (Graphics& g) override;
};

#endif