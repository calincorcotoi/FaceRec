#include "SF.h"
#include "FaceRecGUI.h"

#include <QtWidgets/QApplication>
#include<QFileDialog>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <filesystem>
#include <QMenuBar>
namespace fs = std::experimental::filesystem;
#include <iostream>
#include <stdio.h>
#include <QDir>
#include<QTextStream>
using namespace std;
using namespace cv;


/** Global variables */
String face_cascade_name = "c:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "c:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
static int indexcropp{ 0 };
static int indexcropp2{ 1 };



SF::SF(QWidget *parent)
	: QWidget(parent)
{
	 ui.setupUi(this);
	 connect(ui.btnOpenCamera, SIGNAL(clicked()), this, SLOT(opencamera()));
	 connect(ui.btnCloseCamera, SIGNAL(clicked()), this, SLOT(setFlagNOT()));
	 connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(setFlag()));
	 connect(ui.btnWrite, SIGNAL(clicked()), this, SLOT(makeCSVfile()));

}

SF::~SF()
{
}


void SF::makeCSVfile()
{
	std::string path = "c:\\Users\\CalinNUTU\\source\\repos\\FaceRecGUI\\images\\";
	
	QString filename = QFileDialog::getSaveFileName(this, "asd");// the file where we want to write 
	if (filename.isEmpty())
	{
		ui.textEdit->insertPlainText("CAN'T WRITE TO THE FILE!");
		return;
	}
	QFile file(filename);

	file.resize(0);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		return;

	QTextStream out(&file);
	int index{ 0 };
	int index2{ 1 };
	int index3{ 0 };
	for (const auto & entry : fs::directory_iterator(path))
	{
		if (index3 != 0)
		{
			if (index % 10 == 0 && index != 0)
			{
				index = 0;
				index2++;
			}
			string b = entry.path().string();
			QString qstr = QString::fromStdString(b);
			ui.textEdit->insertPlainText(qstr);
			ui.textEdit->insertPlainText("\n");
			out << qstr << ";" << index2 << "\n";
			index++;
		}
		
		index3++;
	}
}

void SF::setFlag()
{
	flag = 1;
	ui.textEdit->insertPlainText("CAMERA CAN BE USE AGAIN\n");
}


void SF::setFlagNOT()
{
	flag = 0;
	void destroyWindow(const String& window_name);
	ui.textEdit->insertPlainText("CAMERA STOPED\n");
	
}

void SF::opencamera()
{
	Mat frame;
	int alegecamera = ui.spinBox->value();
	VideoCapture cap(alegecamera); // open the default camera
	if (!cap.isOpened())
	{
		ui.textEdit->insertPlainText("open the camera NOT SUCCEEDED\n");
	}
	else
	{
		ui.textEdit->insertPlainText("open the camera SUCCEEDED\n");
	}

	//Load the cascades
	if (!face_cascade.load(face_cascade_name))
	{
		ui.textEdit->insertPlainText("Load the cascades face NOT SUCCEEDED\n");
	}
	else
	{
		ui.textEdit->insertPlainText("Load the cascades face  SUCCEEDED\n");
	}

	if (!eyes_cascade.load(eyes_cascade_name))
	{
		ui.textEdit->insertPlainText("Load the cascades eyes NOT SUCCEEDED\n");
	}
	else
	{
		ui.textEdit->insertPlainText("Load the cascades eyes SUCCEEDED\n");
	}
	

	while (true)
	{

		cap >> frame; // get a new frame from camera
		// Apply the classifier to the frame

		if (!frame.empty())
		{
			detectAndDisplay(frame);
		}
		else
		{
			cout << " --(!) No captured frame -- Break!"; break;
		}
		// pres btn closeCamera to exit
		QApplication::processEvents();
		if (!flag)
		{
			void  destroyAllWindows();
		}
		if (!flag) { break; }

	}


}

void SF::detectAndDisplay(Mat& frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	//equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	double t = (double)getTickCount();
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	//===============================
	
	if(ui.btnCaptura->isDown())
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			
			if (indexcropp % 10 == 0 && indexcropp!=0)
			{
				indexcropp2++;
				indexcropp = 0;
			}
				
			
			Mat face_roi;
			frame(faces[i]).copyTo(face_roi);
			CV_EXPORTS_W::resize(face_roi, face_roi, cv::Size(150, 150));
			char name[200];
			char name1[200];
		
			sprintf_s(name, "C:\\Users\\CalinNUTU\\source\\repos\\FaceRecGUI\\images\\face_%d%d.png", indexcropp2,indexcropp);
			sprintf_s(name1, "face_%d%d.png", indexcropp2, indexcropp);

			imwrite(string(name), face_roi);
			ui.textEdit->insertPlainText(name1); ui.textEdit->insertPlainText(" S-A FACUT O DECUPARE\n");
			indexcropp++;
		}
	}
	//===============================
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		t = (double)getTickCount() - t;
		cout << "detection time = " << t * 1000 / getTickFrequency() << endl;

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}

	//-- Show what you got
	imshow(window_name, frame);
	

}

