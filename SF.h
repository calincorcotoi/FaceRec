#pragma once

#include <QWidget>
#include "ui_SF.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

class SF : public QWidget
{
	Q_OBJECT

public:
	SF(QWidget *parent = Q_NULLPTR);
	~SF();


private slots:
	void opencamera();
	void setFlag();
	void setFlagNOT();
	void makeCSVfile();
	

private:
	Ui::SF ui;
	bool flag{1};
	void SF::detectAndDisplay(Mat& frame);
};
