// FourCC.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/FourCC.h"

namespace ppbox
{
    namespace avbase
    {

        boost::uint32_t FourCC::from_string(
            std::string const & str)
        {
            if (str.size() <= 4) {
                boost::uint32_t e = 0;
                memcpy(&e, str.c_str(), str.size());
                return e;
            }
            return 0;
        }

        std::string FourCC::to_string(
            boost::uint32_t e)
        {
            char c[5] = {0};
            memcpy(c, &e, 4);
            c[4] = 0;
            return c;
        }

    } // namespace avbase
} // namespace ppbox
