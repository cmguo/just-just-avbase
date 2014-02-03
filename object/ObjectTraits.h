// ObjectTraits.h

#ifndef _PPBOX_AVBASE_OBJECT_OBJECT_TRAITS_H_
#define _PPBOX_AVBASE_OBJECT_OBJECT_TRAITS_H_

namespace ppbox
{
    namespace avbase
    {

        template <
            typename ObjT
        >
        class ObjectHelper;

        template <
            typename ObjT
        >
        class ObjectDataHelper;

        class ObjectTraits
        {
        public:
            typedef void header_type; // 必须重新定义

            typedef void i_archive_t; // 必须重新定义

            typedef void o_archive_t; // 必须重新定义

            static size_t const max_size = 0; // 必须重新定义

            typedef ObjectHelper<ObjectTraits> helper_t;

            typedef ObjectDataHelper<ObjectTraits> data_helper_t;
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_OBJECT_OBJECT_TRAITS_H_
