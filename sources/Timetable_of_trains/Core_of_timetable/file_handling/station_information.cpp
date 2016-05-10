#include "station_information.h"

void FileStationInformation::readingFromFile() noexcept
{
    std::ifstream inputFile_for_reading("metro_Saint-Petersburg_station_info.txt");

    if (!inputFile_for_reading.is_open())        
    {
        return;
    }

    // todo может быть, бросать исключение
    /// Зачем бросать исключение? Ведь если файла нет, это не плохо. Мы просто считаем, что сохранённой информации нет.
    /// Раньше я бросал исключение, но в связи с тем, что оно никак не обрабатывалось, я отказался от этого.

    std::string LineFromFile;
    std::string PartOfTheLine;

    std::getline(inputFile_for_reading, LineFromFile);
    for (unsigned i = 0; i < LineFromFile.size(); i++)
    {
        if (LineFromFile[i] == '/')
        {
            FileData.push_back(PartOfTheLine);      /// Здесь происходят действия аналогичные тем, что происходили
            PartOfTheLine = "";                    ///  в route_information.cpp
                                                   // todo если это так, то, может быть, вынести отдельный метод
                                                   // в базовый класс.
                                                 /// Я ещё подумаю об этом
        }
        else
        {
            PartOfTheLine += LineFromFile[i];
        }
    }
    FileData.push_back(PartOfTheLine);
    inputFile_for_reading.close();
    std::string buffer;
    std::string name_of_buffer;
    std::string value_of_buffer;

    for(unsigned i = 0; i < FileData.size(); i++)
    {
        buffer = FileData[i];
        name_of_buffer = "";
        value_of_buffer = "";
        part_of_buffer what_part = part_of_buffer::name;
        for(unsigned j = 0; j < buffer.size(); j++)            /// Идёт заполение контейнера map
        {
            if (buffer[j] == '~')
            {
                what_part = part_of_buffer::value;                    ///  отделяются имя и значение
                j++;
            }
            if (what_part == part_of_buffer::name)
            {
                name_of_buffer += buffer[j];
            }
            else
            {
                value_of_buffer += buffer[j];
            }
        }
        Timetable[name_of_buffer] = value_of_buffer;
    }
}

std::string FileStationInformation::getFileData(const std::string &number_of_the_block)
{
    if(Timetable[number_of_the_block] == "")
    {
        throw ItemDoesNotExist();
    }
    return Timetable[number_of_the_block];
}

void FileStationInformation::deleteBlockFromLine(const std::string &by_what_name_to_delete)
{
    if(Timetable[by_what_name_to_delete] == "")
    {
        throw ItemDoesNotExist();
    }
    Timetable.erase(Timetable.find(by_what_name_to_delete));

    std::string buffer;
    std::string name_of_buffer;
    for(unsigned i = 0; i < FileData.size(); i++)       /// В FileData находятся и удаляются пустые "" элементы
    {
        buffer = FileData[i];
        name_of_buffer = "";
        part_of_buffer what_part = part_of_buffer::name;
        for(unsigned j = 0; j < buffer.size(); j++)
        {
            if (buffer[j] == '~')
            {
                what_part = part_of_buffer::value;
                j++;
            }
            if (what_part == part_of_buffer::name)
            {
                name_of_buffer += buffer[j];
            }
        }
        if (Timetable[name_of_buffer] == "" )
        {
            FileData.erase(FileData.begin() + i);
        }
    }
}

void FileStationInformation::addNewBlockOrChangeExisting(std::string &name_of_the_block, std::string &block_description)  noexcept
{
    Timetable[name_of_the_block] = block_description;

    std::string buffer;
    std::string name_of_buffer;
    int number_of_the_same = -1;
    for(unsigned i = 0; i < FileData.size(); i++)
    {                                                    /// Проверяется содерижтся ли такой элемент в FileData или нет
        buffer = FileData[i];
        name_of_buffer = "";
        part_of_buffer what_part = part_of_buffer::name;

        // todo этот цикл for встречается в нескольких методах, постараться выделить метод
        /// Там окончание каждый раз разное, например здесь мы смотрим встречался ли элемент раньше и запоминаем
        /// его номер, а до этого мы удаляли его, а самый первый раз мы записывали его в map, так что если и есть какой-то
        /// путь я его не вижу

        for(unsigned j = 0; j < buffer.size(); j++)
        {
            if (buffer[j] == '~')
            {
                what_part = part_of_buffer::value;
                j++;
            }
            if (what_part == part_of_buffer::name)
            {
                name_of_buffer += buffer[j];
            }
        }
        if (name_of_buffer == name_of_the_block)
        {
            number_of_the_same = i;
        }
    }
    if (number_of_the_same != -1)
    {
        FileData[number_of_the_same] = name_of_the_block + '~' + block_description;
    }
    else
    {
        FileData.push_back(name_of_the_block + '~' + block_description);
    }
}

void FileStationInformation::saveChanges() noexcept
{
    std::ofstream rewriteFileWithInformationAboutStation("metro_Saint-Petersburg_station_info.txt");

    rewriteFileWithInformationAboutStation << FileData[0];        /// В файл печатается первый элемент(он всегда есть),
                                                                 ///  а отдельно потому что перед ним не надо ставить '/'
    for(unsigned i = 1; i < FileData.size(); i++)
    {
        if (FileData[i] != "")
        {
            rewriteFileWithInformationAboutStation << '/' << FileData[i];
        }
        else
        {
            if (i == 0)
            {
                i++;
                rewriteFileWithInformationAboutStation << FileData[i];
            }
        }
    }
    rewriteFileWithInformationAboutStation.close();
}

std::vector<std::string> FileStationInformation::getAllElement() noexcept
{
    return FileData;
}
