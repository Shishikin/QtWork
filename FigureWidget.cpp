#include <QtGui>
#include <QtMath>
#include "FIgureWidget.h"

void FigureWidget::setWidth(int widthPix)
{
	if (m_width != widthPix)
	{
		m_width = widthPix;
		update();						// Постановка виджета в очередь на перерисовку.
		emit widthChanged(widthPix);	// Посылка сигнала с новым значением.
	}
}

void FigureWidget::setAngle(int angleDeg)
{
	if (m_angle != angleDeg)
	{
		m_angle = angleDeg;
		update();
		emit angleChanged(angleDeg);
	}
}
// Слот для задания свойства «стиль линии» 
void FigureWidget::setPenStyle(Qt::PenStyle penStyle)
{
	if (m_penStyle != penStyle)
	{
		m_penStyle = penStyle;
		update();
		emit penStyleChanged(penStyle);
	}
}

void FigureWidget::setFigType(FigureType figType)
{
	if (m_figType != figType)
	{
		m_figType = figType;
		update();
		emit figTypeChanged(figType);
	}
}

// Перегруженная виртуальная функция – обработчик события «перерисовка виджета»
void FigureWidget::paintEvent(QPaintEvent* event)
{
	// Текущие размеры виджета (в пикселах)
	const int W = size().width(), H = size().height();

	QPainter painter(this);
	// Закраска области виджета фоновым светло-серым цветом
	painter.fillRect(0, 0, W, H, QColor(205, 205, 205));

	// QPen – свойства отображения отрезков и контуров с помощью QPainter.
	QPen pen;
	pen.setColor(Qt::red);			// Цвет: константа перечислимого типа Qt
	pen.setStyle(m_penStyle);       // Стиль отображения линии
	pen.setCapStyle(Qt::RoundCap);	// Стиль отображения концов отрезков
	pen.setWidth(m_width);			// Толщина (в пикселах)

	// Перенос и поворот системы координат QPainter.
	painter.translate(W / 2, H / 2);
	// Поворот: по часовой стрелке, в градусах.
	painter.rotate(-m_angle);
	// Установка пера
	painter.setPen(pen);

	setFigType(m_figType);

	switch (m_figType)
	{
	case FigureType::line:
		painter.drawLine(-W / 3, 0, W / 3, 0);
		break;

	case FigureType::rectangle:
		painter.drawLine(-W / 4, -W / 4, W / 4, -W / 4);
		painter.drawLine(W / 4, -W / 4, W / 4, W / 4);
		painter.drawLine(W / 4, W / 4, -W / 4, W / 4);
		painter.drawLine(-W / 4, W / 4, -W / 4, -W / 4);
		break;

	case FigureType::triangle:
		painter.drawLine(0, -W / 4, W / 4, W / 4);
		painter.drawLine(W / 4, W / 4, -W / 4, W / 4);
		painter.drawLine(-W / 4, W / 4, 0, -W / 4);
		break;
	}
}



void FigureWidget::mouseMoveEvent(QMouseEvent* event)
{
	// Позиция указателя мыши в системе координат виджета.
	QPointF pnt = event->position();

	// Центр виджета
	QPointF center{ size().width() / 2.0f, size().height() / 2.0f };

	// Смещение указателя мыши относительно центра.
	QPointF delta = pnt - center;

	// Расчет направления.
	double angleRad = qAtan2(-delta.y(), delta.x());
	double angleDeg = qRadiansToDegrees(angleRad);

	// Выдача отладочного сообщения с использованием перегруженных операций <<
	qDebug() << "Угол" << "angleRad = " << angleRad << " angleDeg = " << angleDeg;
	// Выдача отладочного сообщения с использованием формата в стиле Си/printf
	qDebug("Угол angleRad = %.1lf angleDeg = %.1lf", angleRad, angleDeg);

	if (angleDeg < 0)
		angleDeg = 360 + angleDeg;

	// Запоминание нового направления с помощью слота
	setAngle(angleDeg);
}

