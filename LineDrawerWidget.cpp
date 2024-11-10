#include "LineDrawerWidget.h"
#include <QPainter>
#include <QMouseEvent>

LineDrawerWidget::LineDrawerWidget(QWidget* parent)
    : QWidget(parent), isDrawing(false)  // Инициализация виджета и установка флага isDrawing в false
{
}

// Очищает все отрезки и обновляет виджет для перерисовки
void LineDrawerWidget::clearLines()
{
    lines.clear();  // Очищаем вектор отрезков
    update();       // Запрашиваем перерисовку виджета
}

// Метод отрисовки, вызываемый при необходимости перерисовать виджет
void LineDrawerWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);  // Устанавливаем черный цвет для рисования линий

    // Отрисовываем все сохраненные отрезки
    for (const auto& line : lines)
    {
        painter.drawLine(line.first, line.second);  // Рисуем отрезок от начальной до конечной точки
    }

    // Отрисовываем текущий отрезок, если идет его рисование
    if (isDrawing)
    {
        painter.drawLine(startPoint, endPoint);  // Рисуем отрезок от начальной до конечной точки
    }
}

// Обрабатывает нажатие левой кнопки мыши
void LineDrawerWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  // Проверяем, что нажата именно левая кнопка
    {
        startPoint = event->pos();  // Устанавливаем начальную точку в текущую позицию мыши
        endPoint = startPoint;      // Инициализируем конечную точку как начальную
        isDrawing = true;           // Устанавливаем флаг, что идет рисование
    }
}

// Обрабатывает перемещение мыши с зажатой кнопкой
void LineDrawerWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isDrawing)  // Если идет рисование
    {
        endPoint = event->pos();  // Обновляем конечную точку в текущую позицию мыши
        update();                 // Запрашиваем перерисовку виджета
    }
}

// Обрабатывает отпускание левой кнопки мыши
void LineDrawerWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDrawing)  // Если отпущена левая кнопка и идет рисование
    {
        endPoint = event->pos();  // Фиксируем конечную точку
        lines.append(qMakePair(startPoint, endPoint));  // Сохраняем текущий отрезок в список
        isDrawing = false;  // Сбрасываем флаг рисования
        update();           // Запрашиваем перерисовку виджета для отображения нового отрезка
    }
}