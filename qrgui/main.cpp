#include <QtCore/QtPlugin>
#include <QtGui/QApplication>

#include "mainwindow/mainWindow.h"
#include "thirdparty/windowsmodernstyle.h"

using namespace qReal;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTranslator appTranslator;
	QTranslator qtTranslator;
	if (app.arguments().count() <= 1 || app.arguments().at(1) != "--no-locale") {
		appTranslator.load(":/qrgui_" + QLocale::system().name());
		qtTranslator.load(":/qt_" + QLocale::system().name());
		app.installTranslator(&appTranslator);
		app.installTranslator(&qtTranslator);
	}

	if (app.arguments().contains("--clear-conf")) {
		SettingsManager::clearSettings();
		SettingsManager::instance()->saveData();
		return 0;
	}

#ifndef NO_STYLE_WINDOWSMODERN
	app.setStyle(new WindowsModernStyle());
#endif

	MainWindow window;
	if (window.isVisible()) {
		return app.exec();
	} else {  // The window decided to not show itself, exiting now.
		return 0;
	}
}
