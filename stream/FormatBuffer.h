// FormatBuffer.h

#ifndef _PPBOX_AVBASE_STREAM_FORMAT_BUFFER_H_
#define _PPBOX_AVBASE_STREAM_FORMAT_BUFFER_H_

#include <util/archive/ArchiveBuffer.h>

namespace ppbox
{
    namespace avbase
    {

        typedef util::archive::ArchiveBuffer<boost::uint8_t> FormatBuffer;

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_STREAM_FORMAT_BUFFER_H_
