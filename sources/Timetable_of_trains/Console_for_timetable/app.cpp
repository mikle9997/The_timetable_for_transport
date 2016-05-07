#include "app.h"

// todo когда так много кода, разделяйте его на смысловые блоки пробельными строками
void ConsoleForTimetable::definitionOfAdministrator()
{
    char answer_about_rights;
    cout << " Are you the administrator? Y/N" << endl << endl << "-->";
    // todo во многих местах вы считываете символ. Выделить метод
    cin >> answer_about_rights;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');       /// Мешает считать кучу символов(ведь нам нужен один)
    if (answer_about_rights == 'Y' or answer_about_rights == 'y')
    {
        Core.issuanceOfRights(administrator);
        cout << endl << " You got administrator rights" << endl << endl;
    }
    else
    {
        Core.issuanceOfRights(usual_user);
        cout << endl << " You got rights as a usual user" << endl << endl;
    }
    cout << endl << " Press Enter..." << endl;
    cin.get();
}

void ConsoleForTimetable::routeInformation()
{
    unsigned how_many_routes;
    try
    {
        unsigned choice_of_the_route;
        how_many_routes = Core.howManyRoutes();
        cout << " What route are you interested in?  (Enter number: 1-" << how_many_routes << ')' << endl << endl << "-->";
        cin >> choice_of_the_route;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        vector<string> output_for_console = Core.getItinerary(choice_of_the_route);
        for(unsigned i = 0; i < output_for_console.size(); i++)
        {
            cout << ' ' << i+1 << '.' << output_for_console[i] << endl;  /// Выводится в виде: 1.Parnas
        }                                                               ///                    2.Prospekt Prosvescheniya
        cout << endl;
    }
    // todo ловить исключение по ссылке
    catch(RouteDoesNotExist)
    {
        cout << " The route does not exist" << endl
             << endl << " At the moment there are 1-" << how_many_routes << " routes" << endl
             << endl << " Enter number of the route, for example: 1" << endl;
    }
    catch(ThereAreNoRoutes)
    {
        cout << endl << " At the moment there are no routes, contact the administrator for help" << endl;
    }
    cout << endl << " Press Enter..." << endl << endl;
    cin.get();
}

void ConsoleForTimetable::findTheRoute()
{
    return;
}

void ConsoleForTimetable::informationAboutStation()
{
    unsigned how_many_routes = 0;
    try
    {
        how_many_routes = Core.howManyRoutes();
        cout << " What route are you interested in?  (Enter number: 1-" << how_many_routes << ')' << endl << endl << "-->";
        unsigned choice_of_the_route;
        cin >> choice_of_the_route;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        vector<string> output_for_console = Core.getItinerary(choice_of_the_route);
        for(unsigned i = 0; i < output_for_console.size(); i++)
        {
            cout << ' ' << i+1 << '.' << output_for_console[i] << endl;  /// Выводится в виде: 1.Parnas
        }                                                               ///                    2.Prospekt Prosvescheniya
        cout << endl;
        cout << " What station are you interested in?" << endl << endl << "-->";
        int choice_number_of_the_station;
        cin >> choice_number_of_the_station;
        choice_number_of_the_station--;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        string choice_name_of_the_station;
        // todo компилятор говорит что тут сравнение разных типов. Исправьте
        if (choice_number_of_the_station >= 0 && choice_number_of_the_station < output_for_console.size())
        {
            choice_name_of_the_station = output_for_console[choice_number_of_the_station];
        }
        else
        {
            choice_name_of_the_station = " ";
        }
        try
        {
            cout << endl << " Information about the station:" << endl << endl << ' ' << choice_name_of_the_station << " : "
                 << Core.getInformationAboutStation(choice_name_of_the_station) << endl;
        }
        catch(StationDoesNotExist)
        {
            cout << " The station does not exist";
        }

    }
    catch(RouteDoesNotExist)
    {
        cout << " The route does not exist" << endl
             << endl << " At the moment there are 1-" << how_many_routes << " routes" << endl
             << endl << " Enter number of the route, for example: 1" << endl;
    }
    catch(ThereAreNoRoutes)
    {
        cout << endl << " At the moment there are no routes, contact the administrator for help" << endl;
    }
    cout << endl << endl << " Press Enter..." << endl;
    cin.get();
}

void ConsoleForTimetable::changeItinerarys()
{
    if (Core.informationOfTheRights() == usual_user)  /// Пользователь не сможет вызвать метод, если он не админ
    {
        return;
    }
    int choice_action_with_route_table;
    cout << " What do you want to do with route table? ";
    try
    {
        unsigned how_many_routes = 0;
        how_many_routes = Core.howManyRoutes();
        cout << "(There are routes: 1-" << how_many_routes << ')' << endl;
    }
    catch(ThereAreNoRoutes)
    {
        cout << "(There are routes: 0)" << endl;
    }
    cout << " 1.Add route" << endl
         << " 2.Change route" << endl
         << " 3.Delete route" << endl << endl << "-->";
    cin >> choice_action_with_route_table;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(choice_action_with_route_table)
    {
    case 1:
    {
        addRoute();
        break;
    }
    case 2:
    {
        changeRoute();
        break;
    }
    case 3:
    {
        deleteRoute();
        break;
    }
    default:
    {
        cout << endl << " You have entered something unclear" << endl;
        break;
    }
    }
    cout << endl << " Press Enter..." << endl << endl;
    cin.get();
}

void ConsoleForTimetable::addRoute()
{
    cout << endl << " Was created the route " << Core.addRoute() << endl;
}

void ConsoleForTimetable::deleteRoute()
{
    unsigned choice_route;
    cout << endl << " Which route you want to delete" << endl << endl << "-->";
    cin >> choice_route;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    try
    {
        Core.deleteRoute(choice_route);
        cout << endl << " The route " << choice_route << " was successfully deleted" << endl;
    }
    catch(RouteDoesNotExist)
    {
        cout << endl << " The route does not exist" << endl;
    }
    cout << endl;
}

void ConsoleForTimetable::changeRoute()
{
    bool how_successful_changes = 1;
    cout << endl << " Which do route you want to change?" << endl << endl << "-->";
    unsigned choice_route;
    cin >> choice_route;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    try
    {
        cout << endl;
        vector<string> output_for_console = Core.getItinerary(choice_route);
        // todo даже по комментарию понятно, что это дублирование кода. Выделить метод, выводящий
        // в консоль станции заданного маршрута
        for(unsigned i = 0; i < output_for_console.size(); i++)
        {
            cout << ' ' << i+1 << '.' << output_for_console[i] << endl;  /// Выводится в виде: 1.Parnas
        }                                                               ///                    2.Prospekt Prosvescheniya
        cout << endl;
        cout << " What do you want?" << endl
             << " 1.Add station" << endl
             << " 2.Change station" << endl
             << " 3.Delete station" << endl
             << endl << "-->";
        int choice_action_with_rote;
        cin >> choice_action_with_rote;
        cout << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice_action_with_rote)
        {
        case 1:
        {
            cout << " What station do you want to add?" << endl
                 << "  (the station will be added to the end of the branch)" <<endl << endl << "-->";
            string what_to_add;
            getline(cin,what_to_add);
            cout << endl << endl;
            Core.addStationInItinerary(choice_route,what_to_add);
            break;
        }
        case 2:
        {
            cout << " What station do you want to change?" << endl << endl << "-->";
            unsigned choice_station;
            cin >> choice_station;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << " What do you want to put in replacement?" << endl << endl << "-->";
            string what_to_replace;
            getline(cin,what_to_replace);
            cout << endl << endl;
            Core.changeItinerary(choice_route,choice_station,what_to_replace);
            break;
        }
        case 3:
        {
            cout << " What station do you want to delete?" << endl << endl << "-->";
            unsigned choice_station;
            cin >> choice_station;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Core.deleteStationFromItinerary(choice_route,choice_station);
            break;
        }
        default:
        {
            cout << endl << " You have entered something unclear" << endl;
            how_successful_changes = 0;
            break;
        }
        }
    }
    catch(RouteDoesNotExist)
    {
        cout << " The route does not exist" << endl;
        how_successful_changes = 0;
    }
    catch(StationDoesNotExist)
    {
        cout << endl << " The station does not exist" << endl;
        how_successful_changes = 0;
    }
    if (how_successful_changes == 1)
    {
        cout << endl << " The changes have been well accepted" << endl;
    }
}

// todo очень длинный метод. Попробуйте разбить
void ConsoleForTimetable::changeInfoAboutStation()
{
    if (Core.informationOfTheRights() == usual_user)
    {
        return;
    }
    unsigned how_many_routes = 0;
    try
    {
        cout << " 1.Add or change information about station" << endl
             << " 2.Remove information about station" << endl << endl << "-->";
        int choice_of_action;
        cin >> choice_of_action;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        switch(choice_of_action)
        {
        case 1:
        {
            how_many_routes = Core.howManyRoutes();
            cout << " What route are you interested in?  (Enter number: 1-"
                 << how_many_routes << ')' << endl << endl << "-->";
            unsigned choice_of_the_route;
            cin >> choice_of_the_route;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            vector<string> output_for_console = Core.getItinerary(choice_of_the_route);
            for(unsigned i = 0; i < output_for_console.size(); i++)
            {
                cout << ' ' << i+1 << '.' << output_for_console[i] << endl;
            }
            cout << endl;
            string name_of_the_route;
            int choice_number_of_the_station;
            cout << endl << " Which information about station do you want to change?" << endl << endl << "-->";
            cin >> choice_number_of_the_station;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice_number_of_the_station--;
            // todo компилятор говорит что тут сравнение разных типов. Исправьте
            if (choice_number_of_the_station >= 0 && choice_number_of_the_station < output_for_console.size())
            {
                name_of_the_route = output_for_console[choice_number_of_the_station];
            }
            else
            {
                name_of_the_route = " ";
            }
            cout << endl << " What is known about the station?" << endl << endl << "-->";
            string station_description;
            getline(cin, station_description);
            Core.addInformationAboutStation(name_of_the_route, station_description);
            break;

        }
        case 2:
        {
            vector<string> AllItemFromTimetable = Core.getAllItemWhichHaveDescription();
            for(unsigned i = 0; i < AllItemFromTimetable.size(); i++)
            {
                cout << ' ' << i+1 << '.' << AllItemFromTimetable[i] << endl;
            }
            int number_of_what_remove;
            string what_remove;
            cout << endl << " What do you want to remove?" << endl << endl << "-->";
            cin >> number_of_what_remove;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            number_of_what_remove--;
            // todo компилятор говорит что тут сравнение разных типов. Исправьте
            if (number_of_what_remove >= 0 && number_of_what_remove < AllItemFromTimetable.size())
            {
                what_remove = AllItemFromTimetable[number_of_what_remove];
            }
            else
            {
                what_remove = " ";
            }
            try
            {
                Core.removeInformationAboutStation(what_remove);
            }
            catch(StationDoesNotExist)
            {
                cout << endl << " The station does not exist" << endl;
            }
            break;
        }
        default:
        {
            cout << " You have entered something unclear" << endl;
            break;
        }
        }
        cout << endl << " The changes have been well accepted" << endl;
    }
    catch(RouteDoesNotExist)
    {
        cout << " The route does not exist" << endl
             << endl << " At the moment there are 1-" << how_many_routes << " routes" << endl
             << endl << " Enter number of the route, for example: 1" << endl;
    }
    catch(ThereAreNoRoutes)
    {
        cout << endl << " At the moment there are no routes, contact the administrator for help" << endl;
    }
    cout << endl << endl << " Press Enter..." << endl << endl;
    cin.get();
}

void ConsoleForTimetable::saveChanges()
{
    if (Core.informationOfTheRights() == usual_user)
    {
        return;
    }
    cout << endl << " Do you want to save changes? (Y/N)" << endl << endl << "-->";
    char answer_about_save;
    cin >> answer_about_save;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (answer_about_save == 'Y' || answer_about_save == 'y')
    {
        Core.saveChanges();
        cout << endl << " The information was saved successfully" << endl << endl;
    }
    else
    {
         cout << endl << " You refused to save" << endl << endl;
    }
    cout << " Press Enter..." << endl;
    cin.get();
}

bool ConsoleForTimetable::menu()
{
    cout << " 1. The route table for trains" << endl
         << " 2. Information about station" << endl
         << " 3. Get administrator rights" << endl;
    if (Core.informationOfTheRights() == administrator)
    {
        cout << " 4. Change route table for the train" << endl
             << " 5. Change information about station" << endl
             << " 6. Save Changes" << endl;
    }
    cout << " 0. Exit" << endl << endl;
    char choice_in_menu;
    cout << "-->";
    cin >> choice_in_menu;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  /// Мешает считать кучу символов(ведь нам нужен один)
    cout << endl;
    switch(choice_in_menu)
    {
    case '1':
    {
        routeInformation();
        break;
    }
    case '2':
    {
        informationAboutStation();
        break;
    }
    case '3':
    {
        definitionOfAdministrator();
        break;
    }
    case '4':
    {
        changeItinerarys();
        break;
    }
    case '5':
    {
        changeInfoAboutStation();
        break;
    }
    case '6':
    {
        saveChanges();
        break;
    }
    case '0':
    {
        saveChanges();
        return false;
    }
    }
    return true;
}
