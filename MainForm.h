#ifndef _MAINFORM
#define _MAINFORM

#include <QWidget>

class QSpinBox;
class QSlider;
class FigureWidget;
class LineDrawerWidget;

class MainForm : public QWidget {
	Q_OBJECT

public:
	explicit MainForm(QWidget* parent = nullptr);

private:
	// Динамически создаваемые дочерние виджеты
	FigureWidget* m_figWidget{ nullptr };
	QSpinBox* m_spinBoxWidth{ nullptr };
	QSlider* m_sliderWidth{ nullptr };
	QSpinBox* m_spinBoxAngle{ nullptr };
	QSlider* m_sliderAngle{ nullptr };
	LineDrawerWidget* m_lineDrawerWidget{nullptr};
};

#endif