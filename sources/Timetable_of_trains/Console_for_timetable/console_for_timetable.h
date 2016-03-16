#ifndef CONSOLE_FOR_TIMETABLE_H
#define CONSOLE_FOR_TIMETABLE_H

#include <core_of_timetable.h>
#include <string>
#include <vector>

using namespace std;

/**
* Класс служащий для работы с "Core_of_timetable" через консоль
*/
class Console_for_timetable
{
public:
    Console_for_timetable();

private:
    void theDefinitionOfAdministrator(); /*Выдача прав администратору*/

    void  seeTheTimetable(int number_of_the_train); /*Посмотерть расписание*/

    void findTheRoute(string departure,string arrival,int time); /*Найти нужный маршрут*/

    void toEditTheTimetable(); /*Добавить расписание*/

    void menu(); /*Вызов меню*/

    Core_of_timetable Core;
};

#endif // CONSOLE_FOR_TIMETABLE_H
