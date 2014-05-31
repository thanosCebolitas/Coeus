#include "CustomTabBar.h"

CustomTabbedButtonBar::CustomTabbedButtonBar()
: index(1) 
{
	customers = new CustomMenuBarButton(CustomMenuBarButton::CustomersType);
	suppliers = new CustomMenuBarButton(CustomMenuBarButton::SuppliersType);
	accountChart = new CustomMenuBarButton(CustomMenuBarButton::EventsType);
	accounts = new CustomMenuBarButton(CustomMenuBarButton::AccountChartType);
	companies = new CustomMenuBarButton(CustomMenuBarButton::CompaniesType);

	reporting = new CustomMenuBarButton(CustomMenuBarButton::ReportingTabType);
	accounting = new CustomMenuBarButton(CustomMenuBarButton::AccountingTabType);
	logout = new CustomMenuBarButton(CustomMenuBarButton::LogoutType);

	businessModel = new CustomMenuBarButton(CustomMenuBarButton::BusinessModelType);
	businessPlan = new CustomMenuBarButton(CustomMenuBarButton::BusinessPlanType);
	financialRatios = new CustomMenuBarButton(CustomMenuBarButton::FinancialRatiosType);
	openSourceInnovation = new CustomMenuBarButton(CustomMenuBarButton::OpenSourceInnovationType);
	reportGenerator = new CustomMenuBarButton(CustomMenuBarButton::ReportGeneratorTytpe);

	customers->addListener(this);
	suppliers->addListener(this);
	accountChart->addListener(this);
	accounts->addListener(this);
	companies->addListener(this);
	reporting->addListener(this);
	accounting->addListener(this);
	logout->addListener(this);
	businessModel->addListener(this);
	businessPlan->addListener(this);
	financialRatios->addListener(this);
	openSourceInnovation->addListener(this);
	reportGenerator->addListener(this);

	addAndMakeVisible(customers);
	addAndMakeVisible(suppliers);
	addAndMakeVisible(accountChart);
	addAndMakeVisible(accounts);
	addAndMakeVisible(companies);
	addAndMakeVisible(reporting);
	addAndMakeVisible(accounting);
	addAndMakeVisible(companies);
	addAndMakeVisible(logout);
	addChildComponent(businessModel);
	addChildComponent(businessPlan);
	addChildComponent(financialRatios);
	addChildComponent(openSourceInnovation);
	addChildComponent(reportGenerator);
}

CustomTabbedButtonBar::~CustomTabbedButtonBar()
{
	reporting = nullptr;
	accounting = nullptr;
	customers = nullptr;
	suppliers = nullptr;
	accountChart = nullptr;
	accounts = nullptr;
	companies = nullptr;
	logout = nullptr;
	businessModel = nullptr;
	businessPlan = nullptr;
	financialRatios = nullptr;
	openSourceInnovation = nullptr;
	reportGenerator = nullptr;
}

void CustomTabbedButtonBar::paint(Graphics &g)
{
	Path rect = Theme::createRectPath(0, 0, getWidth(), getHeight(), 0, 0, 10);

	g.setColour(Colours::grey);
	g.fillPath(rect);
}

void CustomTabbedButtonBar::resized() 
{
	customers->setBounds(0, 67, getWidth(), 75);
	suppliers->setBounds(0, 167, getWidth(), 75);
	accountChart->setBounds(0, 267, getWidth(), 75);
	accounts->setBounds(0, 367, getWidth(), 75);
	companies->setBounds(0, 467, getWidth(), 75);

	businessModel->setBounds(0, 67, getWidth(), 75);
	businessPlan->setBounds(0, 167, getWidth(), 75);
	financialRatios->setBounds(0, 267, getWidth(), 75);
	openSourceInnovation->setBounds(0, 367, getWidth(), 75);
	reportGenerator->setBounds(0, 467, getWidth(), 75);


	reporting->setBounds(65, 0, 56, 28);
	accounting->setBounds(0, 0, 65, 28);

	logout->setBounds(0, getHeight() - 34, 120, 34);
}

int CustomTabbedButtonBar::getCurrentTabIndex() const
{
	return index;
}

void CustomTabbedButtonBar::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == reporting) {
		customers->setVisible(false);
		suppliers->setVisible(false);
		accountChart->setVisible(false);
		accounts->setVisible(false);
		companies->setVisible(false);

		businessModel->setVisible(true);
		businessPlan->setVisible(true);
		financialRatios->setVisible(true);
		openSourceInnovation->setVisible(true);
		reportGenerator->setVisible(true);
	}
	else if (buttonThatWasClicked == accounting) {
		customers->setVisible(true);
		suppliers->setVisible(true);
		accountChart->setVisible(true);
		accounts->setVisible(true);
		companies->setVisible(true);

		businessModel->setVisible(false);
		businessPlan->setVisible(false);
		financialRatios->setVisible(false);
		openSourceInnovation->setVisible(false);
		reportGenerator->setVisible(false);
	}
	else if (buttonThatWasClicked == customers) {
		index = 1;
	}
	else if (buttonThatWasClicked == suppliers) {
		index = 2;
	}
	else if (buttonThatWasClicked == accountChart) {
		index = 3;
	}
	else if (buttonThatWasClicked == accounts) {
		index = 4;
	}
	else if (buttonThatWasClicked == companies) {
		index = 5;
	}
	else if (buttonThatWasClicked == businessModel) {
		index = 6;
	}
	else if (buttonThatWasClicked == businessPlan) {
		index = 7;
	}
	else if (buttonThatWasClicked == financialRatios) {
		index = 8;
	}
	else if (buttonThatWasClicked == openSourceInnovation) {
		index = 9;
	}
	else if (buttonThatWasClicked == reportGenerator) {
		index = 10;
	}
	else if (buttonThatWasClicked == logout) {
		index = 11;
	}
	else {
		index = 1;
	}
	sendChangeMessage();
}

//=======================================================================

CustomTabComponent::CustomTabComponent()
{
	setWantsKeyboardFocus(false);
	
	accountChartComponent = new AccountChartComponent();
	accountsComponent = new AccountsComponent();
	suppliersComponent = new SuppliersComponent();
	customersComponent = new CustomersComponent();
	companiesComponent = new CompaniesComponent();

	tabButtons = new CustomTabbedButtonBar();
	tabButtons->addChangeListener(this);
	tabButtons->sendChangeMessage();

	addChildComponent(accountChartComponent);
	addChildComponent(accountsComponent);
	addChildComponent(suppliersComponent);
	addChildComponent(customersComponent);
	addChildComponent(companiesComponent);

	addAndMakeVisible(tabButtons);

	startTimer(100);
}

CustomTabComponent::~CustomTabComponent() 
{
	accountChartComponent = nullptr;
	accountsComponent = nullptr;
	suppliersComponent = nullptr;
	customersComponent = nullptr;
	companiesComponent = nullptr;
}

void CustomTabComponent::resized()
{
	const float width = getWidth();
	const float height = getHeight();
	accountChartComponent->setBounds(0, 0, getWidth(), getHeight());
	accountsComponent->setBounds(120, 0, getWidth(), getHeight());
	suppliersComponent->setBounds(120, 0, getWidth(), getHeight());
	customersComponent->setBounds(120, 0, getWidth(), getHeight());
	companiesComponent->setBounds(120, 0, getWidth(), getHeight());
	tabButtons->setBounds(0, (getHeight()-575) / 2, 120, 575);
}

void CustomTabComponent::timerCallback()
{
	ComponentAnimator &an = Desktop::getInstance().getAnimator();
	Rectangle<int> finalBoundsVisible = Rectangle<int>(0, tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());
	Rectangle<int> finalBoundsHidden = Rectangle<int>(-tabButtons->getWidth(), tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());

	if (getMouseXYRelative().getY() > 0 && getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() < 120 && tabButtons->getX() < 0 && an.getComponentDestination(tabButtons) == finalBoundsHidden) {
		an.cancelAnimation(tabButtons, false);
		an.animateComponent(tabButtons, finalBoundsVisible, 1.0f, 400, false, 0.0f, 1.0f);
	}
	else if ((getMouseXYRelative().getY() < 0 || (getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() > tabButtons->getWidth())) && tabButtons->getX() == 0) {
		an.cancelAnimation(tabButtons, false);
		an.animateComponent(tabButtons, finalBoundsHidden, 1.0f, 400, false, 0.0f, 1.0f);
	}
}

void CustomTabComponent::changeListenerCallback(ChangeBroadcaster *source)
{
	if (source == tabButtons) {
		switch (tabButtons->getCurrentTabIndex()) {
		case 0:
			break;
		case 1:
			accountChartComponent->setVisible(false);
			accountsComponent->setVisible(false);
			suppliersComponent->setVisible(false);
			customersComponent->setVisible(true);
			companiesComponent->setVisible(false);
			break;
		case 2:
			accountChartComponent->setVisible(false);
			accountsComponent->setVisible(false);
			suppliersComponent->setVisible(true);
			customersComponent->setVisible(false);
			companiesComponent->setVisible(false);
			break;
		case 3:
			accountChartComponent->setVisible(true);
			accountsComponent->setVisible(false);
			suppliersComponent->setVisible(false);
			customersComponent->setVisible(false);
			companiesComponent->setVisible(false);
			break;
		case 4:
			accountChartComponent->setVisible(false);
			accountsComponent->setVisible(true);
			suppliersComponent->setVisible(false);
			customersComponent->setVisible(false);
			companiesComponent->setVisible(false);
			break;
		case 5:
			accountChartComponent->setVisible(false);
			accountsComponent->setVisible(false);
			suppliersComponent->setVisible(false);
			customersComponent->setVisible(false);
			companiesComponent->setVisible(true);
			break;
		case 6:
			accountChartComponent->setVisible(false);
			accountsComponent->setVisible(false);
			suppliersComponent->setVisible(false);
			customersComponent->setVisible(false);
			companiesComponent->setVisible(false);
			break;

		default:
			break;
		}
	}
}