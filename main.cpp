// 
// Qt - лекция 2, задание 1
// Автор - Аминев Илья
//
#include <iostream>
#include <QtWidgets>
#include "MainForm.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	QApplication app(argc, argv);

	app.setStyle(QStyleFactory::create("Fusion"));
	app.setApplicationName("Line Example app");

	// Виджет верхнего уровня (parent == nullptr).
	// Отображается в отдельном окне и на панели задач.
	MainForm* mainForm = new MainForm;
	mainForm->show();

	return app.exec();
}