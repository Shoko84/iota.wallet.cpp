#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <unordered_map>
#include <string>
#include <experimental/filesystem>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QTimer>
#include <QListWidget>
#include <QSizeGrip>
#include <QProcess>
#include <QImageReader>
#include <QFontDatabase>
#include "ui_mainwindow.h"
#include "InteractiveLabel.hpp"

namespace fs = std::experimental::filesystem;

#if defined(__GNUC__) || defined(__GNUG__)
	static const std::string BINARY_EXTENSION = "";
#elif defined(_MSC_VER)
	static const std::string BINARY_EXTENSION = ".exe";
#endif

namespace Ui {
	class MainWindow;
}

namespace nx {
	class UISystem;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, nx::UISystem &uiSystem);
    ~MainWindow();

	void mousePressEvent(QMouseEvent * evt);
	void mouseMoveEvent(QMouseEvent * evt);
	
private:
	bool	_initListWidgets();
	bool	_initAnimators();
	bool	_displayLogo();
	bool	_displayCloseIcon();
	bool	_displayInteractiveLabels();

	bool	_init();

	QString	_createUrlLabelData(std::string const& url);
	QString	_createAuthorLabelData(std::string const& author);

public slots:
	void WalletsLabelEntered();
	void WalletsLabelClicked();
	void WalletsLabelLeft();
	void SendLabelClicked();
	void SendLabelEntered();
	void SendLabelLeft();
	void CloseLabelEntered();
	void CloseLabelLeft();
	void QuitApplication();

private:
	std::shared_ptr<Ui::MainWindow>										_ui;
	nx::UISystem														&_uiSystem;
	std::unordered_map<std::string, std::shared_ptr<QWidget>>			_listWidgets;
	bool																_walletsLabelClicked;
	bool																_sendLabelClicked;
	std::shared_ptr<QPropertyAnimation>									_walletsLabelAnim;
	std::shared_ptr<QPropertyAnimation>									_sendLabelAnim;
	std::shared_ptr<QPropertyAnimation>									_closeLabelAnim;

	QPointF																_oldMovingPos;
	std::shared_ptr<QTimer>												_timer;
	bool																_isClosing;
};

#endif // MAINWINDOW_H
