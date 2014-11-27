// ObjectTraits.h

#ifndef _JUST_AVBASE_OBJECT_OBJECT_TRAITS_H_
#define _JUST_AVBASE_OBJECT_OBJECT_TRAITS_H_

namespace just
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
            typedef void header_type; // �������¶���

            typedef void i_archive_t; // �������¶���

            typedef void o_archive_t; // �������¶���

            static size_t const max_size = 0; // �������¶���

            typedef ObjectHelper<ObjectTraits> helper_t;

            typedef ObjectDataHelper<ObjectTraits> data_helper_t;
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_OBJECT_OBJECT_TRAITS_H_
