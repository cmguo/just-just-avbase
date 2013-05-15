// StreamInfo.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/StreamInfo.h"
#include "ppbox/avbase/Format.h"

namespace ppbox
{
    namespace avbase
    {

        StreamInfoBase::StreamInfoBase()
            : type(StreamType::NONE)
            , sub_type(0)
            , time_scale(0)
            , bitrate(0)
            , start_time(0)
            , duration(0)
        {
        }

        StreamInfo::StreamInfo()
            : format_type(0)
        {
        }

    } // namespace avbase
} // namespace ppbox
