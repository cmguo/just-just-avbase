// Format.h

#ifndef _JUST_AVBASE_FOUR_CC_H_
#define _JUST_AVBASE_FOUR_CC_H_

#include <boost/detail/endian.hpp>

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

namespace just
{
    namespace avbase
    {

        struct FourCC
        {
            static boost::uint32_t from_string(
                std::string const & str);

            static std::string to_string(
                boost::uint32_t e);
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_FOUR_CC_H_
