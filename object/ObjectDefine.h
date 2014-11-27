// ObjectTraits.h

#ifndef _JUST_AVBASE_OBJECT_OBJECT_DEFINE_H_
#define _JUST_AVBASE_OBJECT_OBJECT_DEFINE_H_

#include <util/buffers/StreamBuffer.h>

namespace just
{
    namespace avbase
    {

        class ObjectBase;

        typedef util::buffers::StreamBuffer<boost::uint8_t> StreamBuffer;

        struct ObjectDefine
        {
            enum ClassEnum
            {
                cls_meta, 
                cls_data, 
            };

            typedef void (* constuct_t)(
                ObjectBase *);
            typedef void (* copy_t)(
                ObjectBase *, 
                ObjectBase const *);
            typedef void (* load_t)(
                ObjectBase *, 
                void *);
            typedef void (* save_t)(
                ObjectBase const *, 
                void *);
            typedef void (* destroy_t)(
                ObjectBase *);

            ObjectDefine(
                ClassEnum cls = cls_meta)
                : cls(cls)
                , construct(NULL)
                , copy(NULL)
                , load(NULL)
                , save(NULL)
                , destroy(NULL)
            {
            }

            ClassEnum cls;
            constuct_t construct;
            copy_t copy;
            load_t load;
            save_t save;
            destroy_t destroy;
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_OBJECT_OBJECT_DEFINE_H_
