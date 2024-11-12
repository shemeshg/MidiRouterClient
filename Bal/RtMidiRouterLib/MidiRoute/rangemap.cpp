#include "rangemap.h"
namespace MidiRoute {

RangeMap setRangeMapObject(std::vector<int> &jv, RangeMap &rm){
    if (jv.size() == 1){
        rm.set(jv[0]);
    } else if (jv.size() == 2){
        rm.set(jv[0], jv[1]);
    } else if (jv.size() == 3){
        rm.set(jv[0], jv[1], jv[2]);
    } else if (jv.size() == 4){
        rm.set(jv[0], jv[1], jv[2], jv[3]);
    }
    return rm;
}
}
