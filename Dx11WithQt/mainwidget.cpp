#include "mainwidget.h"
#include "d3d11renderwidget.h"
#include "GraphicViewer.h"
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
}

MainWidget::~MainWidget()
{

}
