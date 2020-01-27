#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwidget.h"
#include "DX11Render.h"
class MainWidget : public QMainWindow
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = 0);
	~MainWidget();

private:
	Ui::MainWidgetClass ui;
	DX11Render mScene;
};

#endif // MAINWIDGET_H
