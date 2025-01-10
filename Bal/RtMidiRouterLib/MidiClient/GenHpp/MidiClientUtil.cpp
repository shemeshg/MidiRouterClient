#include "MidiClientUtil.h"
#include <QUuid>
    QString getUuId() 
{
    return QUuid::createUuid().toString().replace("{", "").replace("}", "");
}

    template<typename T> void moveItem(std::vector<T> & vec, int intFrom, int intTo) 
{
    int size = vec.size();
    intTo = (intTo + size) % size;

    if (intFrom < 0 || intFrom >= size || intTo < 0 || intTo >= size) {
        throw std::out_of_range("Index out of range");
    }

    if (intFrom == intTo) {
        return; // No need to move if the positions are the same
    }

    if (intFrom < intTo) {
        std::rotate(vec.begin() + intFrom, vec.begin() + intFrom + 1, vec.begin() + intTo + 1);
    } else {
        std::rotate(vec.begin() + intTo, vec.begin() + intFrom, vec.begin() + intFrom + 1);
    }
}
