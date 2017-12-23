#include "mainwidget.h"
#include "d3d11renderwidget.h"
#include "GraphicViewer.h"
#include <QDockWidget>
#include <QTextEdit>
#include <qboxlayout.h>

MainWidget::MainWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mScene.InitialDevice();

	QVBoxLayout* vlayout = new QVBoxLayout();
	QHBoxLayout* hlayout = new QHBoxLayout;
	QHBoxLayout* hlayout1 = new QHBoxLayout;

	//Ìí¼ÓD3D×Ó´°¿Ú
// 	D3d11RenderWidget *widget = new D3d11RenderWidget(this);
// 	D3d11RenderWidget *widget1 = new D3d11RenderWidget(this);
// 	D3d11RenderWidget *widget2 = new D3d11RenderWidget(this);
// 	D3d11RenderWidget *widget3 = new D3d11RenderWidget(this);

	GraphicViewer* widget = new GraphicViewer(this);
	GraphicViewer* widget1 = new GraphicViewer(this);
	GraphicViewer* widget2 = new GraphicViewer(this);
	GraphicViewer* widget3 = new GraphicViewer(this);

	widget->Initial(&mScene);
	widget1->Initial(&mScene);
	widget2->Initial(&mScene);
	widget3->Initial(&mScene);

	
	hlayout->addWidget(widget);
	hlayout->addWidget(widget1);
	hlayout1->addWidget(widget2);
	hlayout1->addWidget(widget3);
	

	vlayout->addLayout(hlayout);
	vlayout->addLayout(hlayout1);

	QWidget* view = new QWidget();
	view->setLayout(vlayout);
	

	setCentralWidget(view);

	//=================test dock
//http://blog.csdn.net/x_iya/article/details/17200887
//http://blog.csdn.net/x_iya/article/details/17253403
	QDockWidget *dock = new QDockWidget("Dock Window1", this);
	dock->setFeatures(QDockWidget::DockWidgetMovable);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QTextEdit *te1 = new QTextEdit;
	te1->setText("Dock Window1");
	dock->setWidget(te1);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	dock = new QDockWidget("Dock Window2", this);
	dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
	QTextEdit *te2 = new QTextEdit;
	te2->setText("Dock Window2");
	dock->setWidget(te2);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	dock = new QDockWidget("Dock Window3", this);
	dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	QTextEdit *te3 = new QTextEdit;
	te3->setText("Dock Windo3");
	dock->setWidget(te3);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	this->resize(QSize(1024, 768));
}

MainWidget::~MainWidget()
{

}
