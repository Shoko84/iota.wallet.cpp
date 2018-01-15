#ifndef INTERACTIVELABEL_HPP
#define INTERACTIVELABEL_HPP

#include <QLabel>
#include <QString>
#include <QFont>
#include <QColor>

class InteractiveLabel : public QLabel {
	Q_OBJECT
	Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
	InteractiveLabel(QWidget *parent, std::string const& label = "", int const fontSize = 0);
	~InteractiveLabel();

	void			setColor(QColor const& color);
	const QColor	&getColor() const;

signals:
	void	clicked();
	void	entered();
	void	left();

protected:
	void	mousePressEvent(QMouseEvent *);
	void	enterEvent(QEvent *);
	void	leaveEvent(QEvent *);

};

#endif // INTERACTIVELABEL_HPP