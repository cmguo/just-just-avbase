// ObjectData.h

#ifndef _JUST_AVBASE_OBJECT_OBJECT_DATA_H_
#define _JUST_AVBASE_OBJECT_OBJECT_DATA_H_

#include "just/avbase/object/ObjectTraits.h"
#include "just/avbase/object/Object.h"

namespace just
{
    namespace avbase
    {

        template <
            typename ObjT, 
            typename T, 
            typename ObjT::header_type::id_type id
        >
        class ObjectData
            : ObjectDataBase
        {
        public:
            typedef typename ObjT::header_type::id_type id_type;

            static id_type const static_id;

            static ObjectDefine::ClassEnum const static_cls;

            static ObjectDefineT<ObjT, T> const obj_def;
        };

        template <
            typename ObjT, 
            typename T, 
            typename ObjT::header_type::id_type id
        >
        typename ObjT::header_type::id_type const ObjectData<ObjT, T, id>::static_id = id;

        template <
            typename ObjT, 
            typename T, 
            typename ObjT::header_type::id_type id
        >
        typename ObjectDefine::ClassEnum const ObjectData<ObjT, T, id>::static_cls = ObjectDefine::cls_meta;

        template <
            typename ObjT, 
            typename T, 
            typename ObjT::header_type::id_type id
        >
        ObjectDefineT<ObjT, T> const ObjectData<ObjT, T, id>::obj_def(T::static_cls);

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_OBJECT_OBJECT_DATA_H_
