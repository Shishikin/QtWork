#ifndef _FIGUREWIDGET
#define _FIGUREWIDGET

#include <QWidget>

enum class FigureType {
	line,
	rectangle,
	triangle,
};

class FigureWidget : public QWidget {
	Q_OBJECT

private:
	int m_width = 0;
	int m_angle = 0;
	FigureType m_figType = FigureType::line;
	Qt::PenStyle m_penStyle{ Qt::SolidLine };

public:
	explicit FigureWidget(QWidget* parent = nullptr) : QWidget(parent) {}

	int getWidth() const { return m_width; }
	int getAngle() const { return m_angle; }
	Qt::PenStyle getPenStyle() const { return m_penStyle; }
	FigureType getFigType() const { return m_figType; }

protected:
	// Перегруженная виртуальная функция для обработки события отрисовки виджета
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

public slots:
	void setWidth(int);	// При изменении переменных-членов m_width и m_angle из
	void setAngle(int);	// слотов посылаются соответствующие сигналы.
	void setFigType(FigureType);
	void setPenStyle(Qt::PenStyle);

signals:
	void widthChanged(int);
	void angleChanged(int);
	void figTypeChanged(FigureType);
	void penStyleChanged(Qt::PenStyle);
};

#endif