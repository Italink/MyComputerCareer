#include <QWidget>
#include <QPainter>
#include <QStringList>
#include <QRect>
#include <QDebug>
#include <windows.h>
#include "View/QKeyboardWidget.h"
#include "MyComputerCareerApplication.h"

int main(int argc, char* argv[]) {
	QMyComputerCareerApplication app(argc, argv);
	if (app.isAppRunning()) {
		QMessageBox::information(nullptr, "My Computer Career", "The application is already running.");
		return 0;
	}
	app.initialize();
	return app.exec();
}