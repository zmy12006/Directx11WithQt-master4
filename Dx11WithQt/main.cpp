#include "mainwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	//w.setFixedSize(QSize(1024, 768));//size can't be changed anymore...
	//w.setSizeIncrement(QSize(1024, 768));
	w.show();
	return a.exec();
}
