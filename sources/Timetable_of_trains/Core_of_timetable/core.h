#ifndef CORE_OF_TIMETABLE_H
#define CORE_OF_TIMETABLE_H

#include "api.h"

enum what_rights{usual_user = 0, administrator = 1};

/**
 * @brief Класс в котором содержится основная бизнес-логика приложения
 */
class CoreOfTimetable : public API
{

public:
    CoreOfTimetable();

    void issuanceOfRights(const int what_rights) override;

    bool informationOfTheRights() const override;

    vector<string> getRouteOfTrain(unsigned number_of_the_route) override;

    string getInformationAboutStation(const string &name_of_the_station) override;

    void changeRouteTable(unsigned choice_route, unsigned choice_station, string &what_to_replace) override;

    void deleteStationFromRouteTable(unsigned choice_route, unsigned choice_station) override;

    void addStationInRouteTable(unsigned choice_route, string &what_to_add) override;

    void addStationInTimetable(string &name_of_the_route, string &route_description) override;

    void removeStationFromTimetalbe(const string &what_remove) override;

    string findSuitableRoute(string &departure, string &arrival) override;

    vector<string> getAllItemFromTimetable() override;

    unsigned addRoute() override;

    void deleteRoute(unsigned choice_route) override;

    void saveChanges() override;

    unsigned howManyRoutes() override;

private:

    int right;

    FileRoute DataSetOfTheRoute;

    FileTimetable DataSetOfTimetable;
};


class ThereAreNoRoutes : public exception {};

class NotSuitableInquiry : public exception {};

#endif // CORE_OF_TIMETABLE_H
