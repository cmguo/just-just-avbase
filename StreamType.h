// StreamType.h

#ifndef _PPBOX_AVBASE_STREAM_TYPE_H_
#define _PPBOX_AVBASE_STREAM_TYPE_H_

#include "ppbox/avbase/FourCC.h"

namespace ppbox
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
} // namespace ppbox

#endif // _PPBOX_AVBASE_STREAM_TYPE_H_
