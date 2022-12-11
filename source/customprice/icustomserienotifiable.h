#ifndef ICUSTOMSERIENOTIFIABLE_H
#define ICUSTOMSERIENOTIFIABLE_H

#include <cstddef>
class ICustomSerieNotifiable{
public:
   virtual void OnNewData(size_t start) = 0;
};



#endif // ICUSTOMSERIENOTIFIABLE_H
