#include "InteractiveLabel.hpp"

InteractiveLabel::InteractiveLabel(QWidget *parent, std::string const& label, int const fontSize) :
	QLabel(parent)
{
	QFont font("MS Shell Dig 2", fontSize, QFont::Normal);

	this->setText(QString::fromStdString(label));
	this->setFont(font);
}

InteractiveLabel::~InteractiveLabel()
{
	
}

void			InteractiveLabel::setColor(QColor const &color)
{
	this->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
}

const QColor	&InteractiveLabel::getColor() const
{
	return (this->palette().color(QPalette::Window));
}

void			InteractiveLabel::mousePressEvent(QMouseEvent *)
{
	emit clicked();
}

void			InteractiveLabel::enterEvent(QEvent *)
{
	emit entered();
}

void			InteractiveLabel::leaveEvent(QEvent *)
{
	emit left();
}