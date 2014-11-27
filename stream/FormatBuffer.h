// FormatBuffer.h

#ifndef _JUST_AVBASE_STREAM_FORMAT_BUFFER_H_
#define _JUST_AVBASE_STREAM_FORMAT_BUFFER_H_

#include <util/archive/ArchiveBuffer.h>

namespace just
{
    namespace avbase
    {

        typedef util::archive::ArchiveBuffer<boost::uint8_t> FormatBuffer;

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_STREAM_FORMAT_BUFFER_H_
