#include "timetablegui.h"

TimetableGUI::TimetableGUI(int argc, char *argv[]) : argc(argc), argv(argv)
{
    core = new CoreOfInfoAboutMetro;
}

int TimetableGUI::startGUI()
{
    QApplication app(argc, argv);

    MainWindow window(core);
    window.show();

    return app.exec();
}

TimetableGUI::~TimetableGUI()
{
    delete core;
}