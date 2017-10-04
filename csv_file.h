#ifndef CSV_FILE_H
#define CSV_FILE_H
#include <QString>
#include <fstream>
#include "array.h"
#include <string>
#include "qdebug.h"
#include "vector_list.h"
class CSV_File
{
public:
    CSV_File();
    loadCSV();
    void load_into_CSV();
    void saveCSV();

    Vector_list getList() const;

private:
    Vector_list *list;
};

#endif // CSV_FILE_H
