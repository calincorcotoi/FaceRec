#include "FaceRecGUI.h"

FaceRecGUI::FaceRecGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.btnSF, SIGNAL(clicked(bool)), this, SLOT(openSF()));
	connect(ui.btnRF, SIGNAL(clicked(bool)), this, SLOT(openRF()));
}

void FaceRecGUI::openRF()
{ 
	windowRF = new RF();
	windowRF->show();
}

void FaceRecGUI::openSF()
{
	windowSF = new SF();
	windowSF->show();
}