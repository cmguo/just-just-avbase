// StreamInfo.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/StreamType.h"

namespace ppbox
{
    namespace avbase
    {

        boost::uint32_t StreamType::from_string(
            std::string const & str)
        {
            if (str.size() == 4) {
                boost::uint32_t e;
                memcpy(&e, str.c_str(), 4);
                return (Enum)e;
            }
            return NONE;
        }

        std::string StreamType::to_string(
            boost::uint32_t e)
        {
            char c[5] = {0};
            memcpy(c, &e, 4);
            c[4] = 0;
            return c;
        }

    } // namespace avbase
} // namespace ppbox
