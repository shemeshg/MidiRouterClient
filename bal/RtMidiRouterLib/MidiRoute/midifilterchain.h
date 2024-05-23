#pragma once

#include "RoutFiltersChainClass.h"


namespace MidiRoute {



class MidiFilterChain
{
public:
    std::vector<std::unique_ptr<RoutFiltersChainClass>> chains;

    MidiFilterChain(){
    };
    int addChain(){
        chains.push_back(std::unique_ptr<RoutFiltersChainClass>(new RoutFiltersChainClass()));
        return (int)chains.size() -1;
    }


};

}

