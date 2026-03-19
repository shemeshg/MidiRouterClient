#pragma once
#include <vector>
#include <map>
#include <math.h>

namespace MidiRoute {

class RangeDefinition {
public:
    int fromLBound = 0;
    int fromHBound = 0;
    int toLBound = 0;
    int toHBound = 0;
};

class RangeMap{
public:

    std::vector<RangeDefinition> rangeDefinitions;
    bool defaultAllMaped = true;
    //default all allowed 1==1 2==3 etc...
   RangeMap(){
   }





   void set(int i){
       set(i, i, i, i);
   }

   void set(int from, int to){
        set(from, from, to, to);
   }

  void set(int fromLBount, int fromHBound, int toLBound){
      set(fromLBount, fromHBound, toLBound, toLBound + (fromHBound - fromLBount));
  }

  void set(int fromLBount, int fromHBound, int toLBound, int toHBound){
      RangeDefinition r;
      r.fromLBound = fromLBount;
      r.fromHBound = fromHBound;
      r.toLBound = toLBound;
      r.toHBound =  toHBound;
      rangeDefinitions.push_back(std::move(r));
  }

   void clear(){
       rangeDefinitions.clear();
       defaultAllMaped = false;

   }

   int getVal(float i){
       int ret_val = -1;
       if (defaultAllMaped) {ret_val = (int)i;}


       for (RangeDefinition &rd : rangeDefinitions) {
           if (floor(i) == (float)rd.fromHBound && i > (float)rd.fromHBound ) {
               i = floor(i);
           }
           if (i <(float)rd.fromLBound || i  > (float)rd.fromHBound ) {
               continue;
           }
           float pctOfFrom  = 0;
           if (rd.fromHBound-rd.fromLBound > 0) {
               float f1 = ( i - (float)rd.fromLBound);
               float f2 = (float)(rd.fromHBound-rd.fromLBound);
               pctOfFrom = f1/f2;
           }
           ret_val  = (int)( pctOfFrom * (float)(rd.toHBound-rd.toLBound)+(float)rd.toLBound);

       }


       return ret_val;
   }

   bool isInRange(int i){
       return getVal((float)i) != -1;
   }


};

RangeMap setRangeMapObject(std::vector<int> &jv, RangeMap &rm);

}




