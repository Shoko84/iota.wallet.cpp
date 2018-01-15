#include "mainwindow.h"
#include "UISystem.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
	QMainWindow(parent, Qt::FramelessWindowHint),
	_ui(std::make_shared<Ui::MainWindow>()),
	_uiSystem(uiSystem),
	_walletsLabelClicked(true),
	_sendLabelClicked(false),
	_timer(std::make_shared<QTimer>(this)),
	_isClosing(false)
{
	this->_ui->setupUi(this);

	if (!this->_init())
	{
		// Throw an error;
	}

	QSizeGrip *grip = new QSizeGrip(this);

	this->statusBar()->hide();
	this->_ui->DataContent->addWidget(grip, 0, Qt::AlignBottom | Qt::AlignRight);

	// Window background color
	this->setStyleSheet("background-color: rgb(240, 240, 240);");

	// Signal functions call
	QObject::connect(this->_listWidgets["WalletsLabel"].get(), SIGNAL(clicked()), this, SLOT(WalletsLabelClicked()));
	QObject::connect(this->_listWidgets["WalletsLabel"].get(), SIGNAL(entered()), this, SLOT(WalletsLabelEntered()));
	QObject::connect(this->_listWidgets["WalletsLabel"].get(), SIGNAL(left()), this, SLOT(WalletsLabelLeft()));
	QObject::connect(this->_listWidgets["SendLabel"].get(), SIGNAL(clicked()), this, SLOT(SendLabelClicked()));
	QObject::connect(this->_listWidgets["SendLabel"].get(), SIGNAL(entered()), this, SLOT(SendLabelEntered()));
	QObject::connect(this->_listWidgets["SendLabel"].get(), SIGNAL(left()), this, SLOT(SendLabelLeft()));
	QObject::connect(this->_listWidgets["LogoClose"].get(), SIGNAL(clicked()), this, SLOT(QuitApplication()));
	QObject::connect(this->_listWidgets["LogoClose"].get(), SIGNAL(entered()), this, SLOT(CloseLabelEntered()));
	QObject::connect(this->_listWidgets["LogoClose"].get(), SIGNAL(left()), this, SLOT(CloseLabelLeft()));
}

MainWindow::~MainWindow()
{

}

/********************\
|*  PUBLIC METHODS  *|
\********************/

// Moving mouse event to move the MainWindow
void MainWindow::mousePressEvent(QMouseEvent *evt)
{
	this->_oldMovingPos = (evt->localPos().y() <= 35) ? evt->globalPos() : QPointF(-1, -1);
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
	if (this->_oldMovingPos.x() != -1 && this->_oldMovingPos.y() != -1)
	{
		const QPointF delta = evt->globalPos() - this->_oldMovingPos;

		this->move(this->x() + delta.x(), this->y() + delta.y());
		this->_oldMovingPos = evt->globalPos();
	}
}

/***********\
|*  SLOTS  *|
\***********/

// Triggered when the WALLETS label is clicked
void MainWindow::WalletsLabelClicked()
{
	InteractiveLabel *walletsLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["WalletsLabel"].get());
	InteractiveLabel *sendLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["SendLabel"].get());

	this->_walletsLabelClicked = true;
	this->_sendLabelClicked = false;

	walletsLabel->setColor(QColor(QString::fromStdString(nx::REDFLAT)));
	sendLabel->setColor(QColor(0, 0, 0, 140));
}

// Triggered when the mouse is entering the WALLETS label
void MainWindow::WalletsLabelEntered()
{
	if (!this->_walletsLabelClicked)
	{
		this->_walletsLabelAnim->setDuration(250);
		this->_walletsLabelAnim->setStartValue(QColor(0, 0, 0, 140));
		this->_walletsLabelAnim->setEndValue(QColor(QString::fromStdString(nx::REDFLAT)));
		this->_walletsLabelAnim->start();
	}
	this->_listWidgets["WalletsLabel"]->setCursor(Qt::PointingHandCursor);
}

// Triggered when the mouse is leaving the WALLETS label
void MainWindow::WalletsLabelLeft()
{
	if (!this->_walletsLabelClicked)
	{
		this->_walletsLabelAnim->setDuration(0);
		this->_walletsLabelAnim->setStartValue(QColor(0, 0, 0, 140));
		this->_walletsLabelAnim->setEndValue(QColor(0, 0, 0, 140));
		this->_walletsLabelAnim->start();
	}
	this->_listWidgets["WalletsLabel"]->setCursor(Qt::ArrowCursor);
}

// Triggered when the SEND label is clicked
void MainWindow::SendLabelClicked()
{
	InteractiveLabel *walletsLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["WalletsLabel"].get());
	InteractiveLabel *sendLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["SendLabel"].get());

	this->_walletsLabelClicked = false;
	this->_sendLabelClicked = true;

	walletsLabel->setColor(QColor(0, 0, 0, 140));
	sendLabel->setColor(QColor(QString::fromStdString(nx::REDFLAT)));
}

// Triggered when the mouse is entering the SEND label
void MainWindow::SendLabelEntered()
{
	if (!this->_sendLabelClicked)
	{
		this->_sendLabelAnim->setDuration(250);
		this->_sendLabelAnim->setStartValue(QColor(0, 0, 0, 140));
		this->_sendLabelAnim->setEndValue(QColor(QString::fromStdString(nx::REDFLAT)));
		this->_sendLabelAnim->start();
	}
	this->_listWidgets["SendLabel"]->setCursor(Qt::PointingHandCursor);
}

// Triggered when the mouse is leaving the SEND label
void MainWindow::SendLabelLeft()
{
	if (!this->_sendLabelClicked)
	{
		this->_sendLabelAnim->setDuration(0);
		this->_sendLabelAnim->setStartValue(QColor(0, 0, 0, 140));
		this->_sendLabelAnim->setEndValue(QColor(0, 0, 0, 140));
		this->_sendLabelAnim->start();
	}
	this->_listWidgets["SendLabel"]->setCursor(Qt::ArrowCursor);
}

// Triggered when the mouse is entering the CloseLogo label
void MainWindow::CloseLabelEntered()
{
	this->_closeLabelAnim->setDuration(250);
	this->_closeLabelAnim->setStartValue(QColor(0, 0, 0, 140));
	this->_closeLabelAnim->setEndValue(QColor(QString::fromStdString(nx::REDFLAT)));
	this->_closeLabelAnim->start();
	this->_listWidgets["LogoClose"]->setCursor(Qt::PointingHandCursor);
}

// Triggered when the mouse is leaving the CloseLogo label
void MainWindow::CloseLabelLeft()
{
	this->_closeLabelAnim->setDuration(0);
	this->_closeLabelAnim->setStartValue(QColor(0, 0, 0, 140));
	this->_closeLabelAnim->setEndValue(QColor(0, 0, 0, 140));
	this->_closeLabelAnim->start();
	this->_listWidgets["LogoClose"]->setCursor(Qt::ArrowCursor);
}

void MainWindow::QuitApplication()
{
	this->_isClosing = true;
	QApplication::quit();
}

/*********************\
|*  PRIVATE METHODS  *|
\*********************/

// Initialize everything in the MainWindow
bool MainWindow::_init()
{
	this->_initListWidgets();
	this->_initAnimators();
	if (!this->_displayLogo() || !this->_displayCloseIcon() || !this->_displayInteractiveLabels())
		return (false);
	this->show();
	return (true);
}

// Initializing Navbar Widgets
bool MainWindow::_initListWidgets()
{
	this->_listWidgets = {
		{ "LogoLabel", std::make_shared<QLabel>(this->_ui->NavBarFrame) },
		{ "WalletsLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "WALLETS", 12) },
		{ "SendLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "SEND", 12) },
		{ "LogoClose", std::make_shared<InteractiveLabel>(this, u8"\uf00d") }
	};
	return (true);
}

// Initializing Animators
bool MainWindow::_initAnimators()
{
	this->_walletsLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["WalletsLabel"].get(), "color");
	this->_sendLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["SendLabel"].get(), "color");
	this->_closeLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["LogoClose"].get(), "color");
	return (true);
}

// Adding the Nexus logo
bool MainWindow::_displayLogo()
{
	/*QLabel *logo = dynamic_cast<QLabel *>(this->_listWidgets["LogoLabel"].get());

	if (!logo)
		return (false);

	QPixmap img(QString::fromStdString(this->_uiSystem.getRoot().getBinaryAbsolutePath() + "/../ressources/images/icons/nexuslogo.png"));

	logo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	logo->setPixmap(img.scaled(160, 90, Qt::KeepAspectRatio));
	logo->setGeometry(15, 0, 160, 90);*/
	return (true);
}

// Adding the Close icon
bool MainWindow::_displayCloseIcon()
{
	InteractiveLabel *logo = dynamic_cast<InteractiveLabel *>(this->_listWidgets["LogoClose"].get());

	if (!logo)
		return (false);

	logo->setContentsMargins(0, 10, 10, 0);
	logo->setFixedSize(32, 32);
	logo->setAlignment(Qt::AlignRight | Qt::AlignTop);

	if (QFontDatabase::addApplicationFont(QString::fromStdString(this->_uiSystem.getRoot().getBinaryAbsolutePath() + "/../ressources/fonts/fontawesome-webfont.ttf")) < 0)
		std::cout << "couldn't load FA" << std::endl;

	QFont font;

	font.setFamily("FontAwesome");
	font.setPixelSize(24);

	logo->setFont(font);
	logo->setColor(QColor(0, 0, 0, 140));
	
	this->_ui->CloseLogoLayout->addWidget(logo);
	this->_ui->CloseLogoLayout->setAlignment(logo, Qt::AlignRight | Qt::AlignTop);
	return (true);
}

// Adding InteractiveLabels into the Navbar
bool MainWindow::_displayInteractiveLabels()
{
	InteractiveLabel *walletsLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["WalletsLabel"].get());
	InteractiveLabel *sendLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["SendLabel"].get());

	if (!walletsLabel || !sendLabel)
		return (false);

	this->_listWidgets["WalletsLabel"]->setGeometry(230, 35, 70, 26);
	walletsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	walletsLabel->setColor(QColor(QString::fromStdString(nx::REDFLAT)));
	this->_listWidgets["SendLabel"]->setGeometry(330, 35, 60, 26);
	sendLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	sendLabel->setColor(QColor(0, 0, 0, 140));
	return (true);
}


QString	MainWindow::_createUrlLabelData(std::string const& url)
{
	return (QString::fromStdString("<html><head/><body><p>More informations on <a href=\"" + url +
								   "\"><span style=\" text-decoration: underline; color:#007af4;\">" + url +
								   "</span></a></p></body></html>"));
}

QString MainWindow::_createAuthorLabelData(std::string const& author)
{
	return (QString::fromStdString("<html><head/><body><p>By <span style=\"font-weight:600;color:#e74c3c;\">" +
									author + "</span></p></body></html>"));
}