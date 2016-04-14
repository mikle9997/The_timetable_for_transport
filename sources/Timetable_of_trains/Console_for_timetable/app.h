#ifndef CONSOLE_FOR_TIMETABLE_H
#define CONSOLE_FOR_TIMETABLE_H

#include <core.h>
#include <string>
#include <exception>
#include <vector>

using namespace std;

/**
 * @brief Класс служащий для работы с ядром через консоль
 */
class ConsoleForTimetable
{
public:
    ConsoleForTimetable();

private:

    /**
     * @brief Выводи в консоль меню с предоставляемыми возможностями
     */
    void menu();

    /**
     * @brief В зависимости от запрашиваемой станции, печатает время начала и окончания её работы
     */
    void whenBeginsAndEndsMovementOfTheTrainAtTheStation();

    /**
     * @brief Выдача прав или администратора, или обычного юзера
     */
    void definitionOfAdministrator();

    /**
     * @brief Предоставляет информация о запрашиваемом маршруте
     */
    void routeInformation();

    /**
     * @brief Удобный вывод маршрута в консоль
     * @param Номер маршрута
     * Сделан, чтобы избежать копипаста, но я не уверен стоило ли это того
     */
    void convenientOutputInTheConsoleForRouteTable(int const choice_of_the_route);

    /**
     * @brief Печатает в консоль проложеный маршрут от одной станции до другой
     */
    void findTheRoute();


    /// Методы для администратора:

    /**
     * @brief Изменить маршруты поездов
     */
    void changeRouteTable();

    /**
     * @brief Изменить расписание
     */
    void changeTimetable();

    CoreOfTimetable Core;
};

/**
 * @brief Ошибка ввода  (не уверен в его необходимости)
 */
class InputError : public exception {};

#endif // CONSOLE_FOR_TIMETABLE_H
