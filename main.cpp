#include "FaceRecGUI.h"
#include "SF.h"
#include <QtWidgets/QApplication>





int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FaceRecGUI w;
	w.show();
	return a.exec();
}
