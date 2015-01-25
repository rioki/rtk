
#ifndef _RTK_POINT_H_
#define _RTK_POINT_H_

#include "config.h"

namespace rtk
{
    class RTK_EXPORT Point
    {
    public:
        
        unsigned int x;
        unsigned int y;

        Point();

        Point(unsigned int x, unsigned int y);
        
    };

}

#endif
