#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

#include "FigureWidget.h"
#include "MainForm.h"
#include "LineDrawerWidget.h"

#define FIRSTCOLECTIONBUTTOMHEIGHT 120
#define FIRSTCOLECTIONBUTTOMWIDTH 150
#define INDENT 10

MainForm::MainForm(QWidget* parent) : QWidget(parent)
{
	// Виджет для отображения фигуры
	// (Координаты и размеры задаются явно)
	const int LEFT_OFS = 10, TOP_OFS = 10;
	const int IMG_W = 200, IMG_H = 200;
	m_figWidget = new FigureWidget(this);
	m_figWidget->setGeometry(LEFT_OFS, TOP_OFS, IMG_W, IMG_H);

	// Виджеты для задания толщины фигуры
	const int LINE_W_MIN = 1, LINE_W_MAX = 25;
	m_spinBoxWidth = new QSpinBox(this);
	m_spinBoxWidth->setGeometry(10, IMG_H + 20, 50, 30);
	m_spinBoxWidth->setRange(LINE_W_MIN, LINE_W_MAX);
	m_sliderWidth = new QSlider(Qt::Horizontal, this);
	m_sliderWidth->setGeometry(70, IMG_H + 20, 140, 30);
	m_sliderWidth->setRange(LINE_W_MIN, LINE_W_MAX);

	const int LINE_ANGLE_MIN = 0, LINE_ANGLE_MAX = 360;
	m_spinBoxAngle = new QSpinBox(this);
	m_spinBoxAngle->setGeometry(10, IMG_H + 50, 50, 30);
	m_spinBoxAngle->setRange(LINE_ANGLE_MIN, LINE_ANGLE_MAX);
	m_sliderAngle = new QSlider(Qt::Horizontal, this);
	m_sliderAngle->setGeometry(70, IMG_H + 50,140, 30);
	m_sliderAngle->setRange(LINE_ANGLE_MIN, LINE_ANGLE_MAX);

	// Группа виджетов для задания типа фигуры
	QGroupBox* gbFigType = new QGroupBox("Тип фигуры", this);
	gbFigType->setGeometry(LEFT_OFS + IMG_W + 20, TOP_OFS, FIRSTCOLECTIONBUTTOMWIDTH, FIRSTCOLECTIONBUTTOMHEIGHT);
	QRadioButton* radio1 = new QRadioButton("&Отрезок");
	QRadioButton* radio2 = new QRadioButton("&Прямоугольник");
	QRadioButton* radio3 = new QRadioButton("&Треугольник");
	radio1->setChecked(true); // Одна кнопка группы делается отмеченной

	// Объект-менеджер компоновки для автоматического расчета
	// положения и размеров виджетов.
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(radio1);
	vbox->addWidget(radio2);
	vbox->addWidget(radio3);
	gbFigType->setLayout(vbox);

	// Связывание виджетов-кнопок с виджетом m_lineWidget
	// посредством лямбда-функций.
	// По сигналу от каждой кнопки QRadioButton слот m_figWidget вызывается
	// из лямбда-функции с передачей конкретного значения стиля линии.
	connect(radio1, &QRadioButton::clicked,
		[this] { m_figWidget->setFigType(FigureType::line); });
	connect(radio2, &QRadioButton::clicked,
		[this] { m_figWidget->setFigType(FigureType::rectangle); });
	connect(radio3, &QRadioButton::clicked,
		[this] { m_figWidget->setFigType(FigureType::triangle); });

	// Группа виджетов для задания типа фигуры
	QGroupBox* gdLineType = new QGroupBox("Тип фигуры", this);
	gdLineType->setGeometry(LEFT_OFS + IMG_W + 20, TOP_OFS + FIRSTCOLECTIONBUTTOMHEIGHT + INDENT, FIRSTCOLECTIONBUTTOMWIDTH, FIRSTCOLECTIONBUTTOMHEIGHT);
	QRadioButton* radio4 = new QRadioButton("SolidLine");
	QRadioButton* radio5 = new QRadioButton("DashLine");
	QRadioButton* radio6 = new QRadioButton("DotLine");
	QRadioButton* radio7 = new QRadioButton("DashDotLine");
	radio4->setChecked(true); // Одна кнопка группы делается отмеченной
	QVBoxLayout* figureBox = new QVBoxLayout;
	figureBox->addWidget(radio4);
	figureBox->addWidget(radio5);
	figureBox->addWidget(radio6);
	figureBox->addWidget(radio7);
	gdLineType->setLayout(figureBox);

	connect(radio4, &QRadioButton::clicked,
		[this] { m_figWidget->setPenStyle(Qt::SolidLine); });
	connect(radio5, &QRadioButton::clicked,
		[this] { m_figWidget->setPenStyle(Qt::DashLine); });
	connect(radio6, &QRadioButton::clicked,
		[this] { m_figWidget->setPenStyle(Qt::DotLine); });
	connect(radio7, &QRadioButton::clicked,
		[this] { m_figWidget->setPenStyle(Qt::DashDotLine); });
	
	connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), m_sliderWidth, SLOT(setValue(int)));
	connect(m_sliderWidth, SIGNAL(valueChanged(int)), m_spinBoxWidth, SLOT(setValue(int)));
	connect(m_sliderWidth, SIGNAL(valueChanged(int)), m_figWidget, SLOT(setWidth(int)));
	connect(m_figWidget, SIGNAL(widthChanged(int)), m_sliderWidth, SLOT(setValue(int)));

	connect(m_spinBoxAngle, SIGNAL(valueChanged(int)), m_sliderAngle, SLOT(setValue(int)));
	connect(m_sliderAngle, SIGNAL(valueChanged(int)), m_spinBoxAngle, SLOT(setValue(int)));
	connect(m_sliderAngle, SIGNAL(valueChanged(int)), m_figWidget, SLOT(setAngle(int)));
	connect(m_figWidget, SIGNAL(angleChanged(int)), m_sliderAngle, SLOT(setValue(int)));

	// Указание текущих значений свойств отрезка - посредством сигналов от
	// FigWidget эти значения будут переданы в виджеты-ползунки, а от
	// них - в виджеты-счетчики.
	const int LINE_W = 5, LINE_ANGLE = 0;
	m_figWidget->setWidth(LINE_W);
	m_figWidget->setAngle(LINE_ANGLE);

	m_lineDrawerWidget = new LineDrawerWidget(this);
	m_lineDrawerWidget->setGeometry(LEFT_OFS + IMG_W + FIRSTCOLECTIONBUTTOMWIDTH + 3 * INDENT, TOP_OFS, IMG_W, IMG_H);

	QPushButton* radio8 = new QPushButton("Очистить", this);
	radio8->setGeometry(LEFT_OFS + IMG_W + FIRSTCOLECTIONBUTTOMWIDTH + 3 * INDENT, TOP_OFS + IMG_H + INDENT, IMG_W, 40);

	connect(radio8, &QPushButton::clicked, m_lineDrawerWidget, &LineDrawerWidget::clearLines);
}