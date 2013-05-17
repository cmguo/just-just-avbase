// Format.h

#ifndef _PPBOX_AVBASE_FORMAT_H_
#define _PPBOX_AVBASE_FORMAT_H_

#include <boost/detail/endian.hpp>

namespace ppbox
{
    namespace avbase
    {

#ifdef BOOST_BIG_ENDIAN
#define MAKE_FOURC_TYPE(c1, c2, c3, c4) \
    ((((boost::uint32_t)c1) << 24) | \
    (((boost::uint32_t)c2) << 16) | \
    (((boost::uint32_t)c3) << 8) | \
    (((boost::uint32_t)c4)))
#else
#define MAKE_FOURC_TYPE(c1, c2, c3, c4) \
    ((((boost::uint32_t)c1)) | \
    (((boost::uint32_t)c2) << 8) | \
    (((boost::uint32_t)c3)) << 16 | \
    (((boost::uint32_t)c4) << 24))
#endif

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

#endif // _PPBOX_AVBASE_FORMAT_H_
