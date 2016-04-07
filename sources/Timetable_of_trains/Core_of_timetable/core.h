#ifndef CORE_OF_TIMETABLE_H
#define CORE_OF_TIMETABLE_H

#include <string>
#include <vector>
#include <file_route.h>
#include <file_timetable.h>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

enum what_rights{usual_user = 0, administrator = 1};

/**
 * @brief Класс в котором содержится бизнес-логика приложения
 */
class CoreOfTimetable
{

public:
    CoreOfTimetable();

    /**
     * @brief Выдача прав
     * @param Какие права нужно выдать
     */
    void issuanceOfRights(int const what_rights);

    /**
     * @return Информация о правах
     */
    bool informationOfTheRights() const;

    /**
     * @brief Используется для более удобного вывода в консоль
     * @param Номер маршрута
     * @return Маршрут поезда в формате vector<string>
     */
    vector<string> getRouteOfTrain(int const number_of_the_route);

    /**
     * @brief Используется для более удобного вывода в консоль
     * @param Название станции
     * @return Время начала движения в формате vector<string>
     */
    string getWhenStartMovementOnTheStation(string const name_of_the_station);

    /**
     * @param station - станция
     * @param time - время относительно которого делается вывод
     * @return время до прибытия следующего поезда
     */
    int whenWillTheTrainsArrive(string station, int time);

    /**
     * @brief Выставить максимально возможное количество строк в файле
     */
    void setMaxNumberStringInFile(int const new_max_quantity);

    /**
     * @brief Узнать максимально возможное количество строк в файле
     */
    int getMaxNumberStringInFile();

    /**
     * @brief Изменить маршрут поезда
     * @param номер маршрута, который нужно изменить
     */
    void changeRouteTable(int const  choice_route,int choice_station, string what_to_replace);

    /**
     * @brief Изменение станции в файле "Schedule.txt"
     * @param имя станции, которую нужно изменить или добавить
     * @param что поставить вместо
     */
    void changeTimetable(string const what_change, string const in_exchange);

    /**
     * @brief Удаление станции из файла "Schedule.txt"
     * @param имя станции, которую нужно удалить
     */
    void removeStationFromTimetalbe(string const what_remove);

    /**
     * @param departure - станция отправления
     * @param arrival  - станция назначения
     * @param time - время (возможно я уберу этот параметр во время реализации функции)
     * @return Возвращяет подходящий маршрут
     */
    string findSuitableRoute(string departure,string arrival,int time);

private:

    int right;

    FileRoute DataSetOfTheRoute;

    FileTimetable DataSetOfTimetable;
};

/**
 * @brief Недостаточно прав
 */
class InsufficientRights : public exception {};

/**
 * @brief Рекомендованые параметры функции
 */
class RecommendedSettings : public exception {};

#endif // CORE_OF_TIMETABLE_H
