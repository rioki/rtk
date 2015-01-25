
#ifndef _RTK_SIZE_H_
#define _RTK_SIZE_H_

#include "config.h"

namespace rtk
{
    class RTK_EXPORT Size
    {
    public:
        
        int w;
        int h;

        Size();

        Size(int w, int h);
        
    };

}

#endif
