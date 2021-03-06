#include "work_with_stations.h"

void WorkWithStations::informationAboutStation(CoreOfInfoAboutMetro &core)
{
    unsigned how_many_routes = 0;
    try
    {
        how_many_routes = core.howManyRoutes();

        if(how_many_routes == 0)
        {
            std::cout << std::endl << " At the moment there are no routes, contact the administrator for help" << std::endl;
            std::cout << std::endl << " Press Enter..." << std::endl << std::endl;
            std::cin.get();
            return;
        }


        std::cout << " What route are you interested in?  (Enter number: 1-" << how_many_routes << ')' << std::endl << std::endl << "-->";
        int choice_of_the_route = getIntFromConsole();
        std::cout << std::endl;

        std::vector<std::string> output_for_console = core.getRoute(choice_of_the_route);

        displayRoute(output_for_console);

        std::cout << " What station are you interested in?" << std::endl << std::endl << "-->";
        int choice_number_of_the_station = getIntFromConsole();
        std::cout << std::endl;

        try
        {
            std::cout << std::endl << " Information about the station:" << std::endl << std::endl << ' '
                      << core.getInfoAboutStation(choice_of_the_route, choice_number_of_the_station) << std::endl;
        }
        catch(StationDoesNotExist& exception)
        {
            std::cout << " The station " << '"' << exception.getWhatRequested() << '"' << " does not exist";
        }
    }
    catch(RouteDoesNotExist& exception)
    {
        std::cout << " The route "
                  << '"' << exception.getWhatRequested() << '"' << " does not exist" << std::endl
                  << std::endl << " At the moment there are 1-" << how_many_routes << " routes" << std::endl
                  << std::endl << " Enter number of the route, for example: 1" << std::endl;
    }
    std::cout << std::endl << std::endl << " Press Enter..." << std::endl;
    std::cin.get();
}

void WorkWithStations::changeInfoAboutStation(CoreOfInfoAboutMetro &core)
{
    if (core.getInformationOfTheRights() == Rights_of_customers::user)
    {
        return;
    }
    try
    {
        std::cout << " 1.Add or change information about station" << std::endl
             << " 2.Remove information about station" << std::endl << std::endl << "-->";

        int choice_of_action = getIntFromConsole();

        std::cout << std::endl;

        switch(choice_of_action)
        {
        case 1:
        {
            addOrChangeInformationAboutStation(core);
            break;
        }
        case 2:
        {
            removeInformationAboutStation(core);
            break;
        }
        default:
        {
            std::cout << " You have entered something unclear" << std::endl;
            break;
        }
        }
        std::cout << std::endl << " The changes have been well accepted" << std::endl;
    }
    catch(StationDoesNotExist& exception)
    {
        std::cout << std::endl << " The station with number "
                  << '"' << exception.getWhatRequested() << '"' << " does not exist" << std::endl;
    }
    catch(RouteDoesNotExist& exception)
    {
        if(core.howManyRoutes() == 0)
        {
            std::cout << std::endl << " At the moment there are no routes, contact the administrator for help" << std::endl;
            std::cout << std::endl << " Press Enter..." << std::endl << std::endl;
            std::cin.get();
            return;
        }

        std::cout << " The route "
                  << '"' << exception.getWhatRequested() << '"' << " does not exist" << std::endl
                  << std::endl << " At the moment there are 1-" << core.howManyRoutes() << " routes" << std::endl
                  << std::endl << " Enter number of the route, for example: 1" << std::endl;
    }

    std::cout << std::endl << std::endl << " Press Enter..." << std::endl << std::endl;
    std::cin.get();
}

void WorkWithStations::addOrChangeInformationAboutStation(CoreOfInfoAboutMetro &core)
{
    if(core.howManyRoutes() == 0)
    {
        std::cout << std::endl << " At the moment there are no routes, contact the administrator for help" << std::endl;
        std::cout << std::endl << " Press Enter..." << std::endl << std::endl;
        std::cin.get();
        return;
    }


    std::cout << " What route are you interested in?  (Enter number: 1-"
         << core.howManyRoutes() << ')' << std::endl << std::endl << "-->";

    int choice_of_the_route = getIntFromConsole();

    std::cout << std::endl;

    std::vector<std::string> output_for_console = core.getRoute(choice_of_the_route);

    displayRoute(output_for_console);

    std::cout << std::endl << " Which information about station do you want to change?" << std::endl << std::endl << "-->";

    int choice_number_of_the_station = getIntFromConsole();

    std::cout << std::endl << " What is known about the station?" << std::endl << std::endl << "-->";
    std::string station_description;
    std::getline(std::cin, station_description);

    core.addInfoAboutStation(choice_of_the_route, choice_number_of_the_station, station_description);
}

void WorkWithStations::removeInformationAboutStation(CoreOfInfoAboutMetro &core)
{
    auto AllItemFromTimetable = core.getAllStationsWhichHaveDescription();
    for(unsigned i = 0; i < AllItemFromTimetable.size(); i++)
    {
        std::cout << ' ' << i+1 << '.' << (AllItemFromTimetable[i]).first << " : " <<
                     (AllItemFromTimetable[i]).second << std::endl;
    }

    std::cout << std::endl << " What do you want to remove?" << std::endl << std::endl << "-->";

    int number_of_what_remove = getIntFromConsole();

    try
    {
        core.removeInfoAboutStation(number_of_what_remove);
    }
    catch(StationDoesNotExist& exception)
    {
        std::cout << std::endl << " The station with number "
                  << '"' << exception.getWhatRequested() << '"' << " does not exist" << std::endl;
    }
}
