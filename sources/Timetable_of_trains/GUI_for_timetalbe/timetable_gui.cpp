#include "timetable_gui.h"

TimetableGUI::TimetableGUI(int argc, char *argv[]) : argc(argc), argv(argv)
{
    core = new CoreOfInfoAboutMetro;
//    core->loadInfoFromFile("metro_Saint-Petersburg_route_info.txt", "metro_Saint-Petersburg_station_info.txt");
}

int TimetableGUI::startGUI()
{
    QApplication app(argc, argv);

    MainWindow window(nullptr, core);
    window.show();

    return app.exec();
}

TimetableGUI::~TimetableGUI()
{
    delete core;
}