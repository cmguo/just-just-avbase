// StreamType.h

#ifndef _JUST_AVBASE_STREAM_TYPE_H_
#define _JUST_AVBASE_STREAM_TYPE_H_

#include "just/avbase/FourCC.h"

namespace just
{
    namespace avbase
    {

        struct StreamType
        {
            enum Enum
            {
                NONE = 0, 
                VIDE = MAKE_FOURC_TYPE('V', 'I', 'D', 'E'), 
                AUDI = MAKE_FOURC_TYPE('A', 'U', 'D', 'I'), 
                SUBS = MAKE_FOURC_TYPE('S', 'U', 'B', 'S'), 
            };
        };

        struct StreamSubType
        {
            enum Enum
            {
                NONE = 0, 
            };
        };

        struct StreamFormatType
        {
            enum Enum
            {
                none = 0, 
            };
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_STREAM_TYPE_H_
