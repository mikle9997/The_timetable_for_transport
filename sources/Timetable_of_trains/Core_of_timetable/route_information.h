#ifndef FILETIMETABLE_H
#define FILETIMETABLE_H

#include "file_handling.h"

/**
 *  @brief Класс,для обработатки первой строчки файла, в которой находиться информация о маршрутах
 */
class FileRouteInformation : public FileHandling
{
public:

    void readingFromFile() override;

    /**
     * @brief Переписать часть строки
     * @param number_of_part - номер части строки, которую надо перезаписать
     * @param ToPrintToFile - что нужно написать на этом месте
     */
    void changeBlockFromLine(const int number_of_block,  string &InExchange);

    /**
     * @brief Удалить определённую часть отделёную знаками '/'
     * @param number_of_part номер части, которую нужно удалить
     */
    void deleteBlockFromLine(const int number_of_block);

    /**
     * @brief Добавляет блок с информацией в строчку (добавляется в конец)
     */
    void addNewBlock();

    /**
     * @return Количество частей, на которые разибвается строчка
     */
    unsigned getNumberOfBlocksInTheLine() const {return FileData.size();}

    void saveChanges() override;

    /**
     *  @param number_of_the_part - номер запрашиваемой части строки
     *  @return Строчка с необходимыми данными
     */
    string getFileData(int number_of_part) const;
};

#endif // FILETIMETABLE_H
