#pragma once

#include <QWidget>
#include "ui_RF.h"
#include <stdio.h>
#include<RFsource.h>

class RF : public QWidget
{
	Q_OBJECT

public:
	RF(QWidget *parent = Q_NULLPTR);
	~RF();

public slots:
	void filecsv();
	void RecFace();

private:
	Ui::RF ui;
	QString filePath;
	std::string filename;
};
