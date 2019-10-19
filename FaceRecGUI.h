#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FaceRecGUI.h"
#include "SF.h"
#include "RF.h"
class FaceRecGUI : public QMainWindow
{
	Q_OBJECT

public:
	FaceRecGUI(QWidget *parent = Q_NULLPTR);

	private slots:
	void openSF();
	void openRF();


private:
	Ui::FaceRecGUIClass ui;
	SF *windowSF;
	RF *windowRF;

};
