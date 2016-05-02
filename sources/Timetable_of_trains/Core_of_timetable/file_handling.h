#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

/**
 *  @brief Абстрактный класс объединяющий взаимодействие с файлами
 */
class FileHandling
{
public:

    /**
     * @brief Читает файл и помещает информацию из него в удобный для вывода контейрнер
     */
    virtual void readingFromFile() = 0;

    /**
     * @brief Сохранить изменения в файле
     */
    virtual void saveChanges() = 0;

    virtual ~FileHandling(){}

protected:

    /**
     *  @brief Сюда записываются данные извлечённые из файла
     */
    vector<string> FileData;
};

class ItemDoesNotExist : public exception {};


#endif // FILE_H
