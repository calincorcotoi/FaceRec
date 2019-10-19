#include "RF.h"
#include<QFileDialog>
#include<QDebug>
#include<iostream>


RF::RF(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btnCSV, SIGNAL(clicked()), this, SLOT(filecsv()));
	connect(ui.btnRec, SIGNAL(clicked()), this, SLOT(RecFace()));
}

RF::~RF()
{
}

void RF::filecsv()
{

 filePath = QFileDialog::getOpenFileName(this, "Get Any File");
  filename = filePath.toLocal8Bit().constData();
 
}

void RF::RecFace()
{
	 recunoastere(filename);
}