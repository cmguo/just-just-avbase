// ObjectBase.h

#ifndef _JUST_AVBASE_OBJECT_OBJECT_BASE_H_
#define _JUST_AVBASE_OBJECT_OBJECT_BASE_H_

#include "just/avbase/object/ObjectDefine.h"

namespace just
{
    namespace avbase
    {

        class ObjectBase
        {
        public:
            ObjectBase();

            ~ObjectBase();

        public:
            ObjectBase(
                ObjectBase const & r);

            ObjectBase & operator=(
                ObjectBase const & r);

        public:
            bool empty() const
            {
                return def_ == NULL;
            }

            ObjectDefine::ClassEnum cls() const
            {
                return def_ ? def_->cls : ObjectDefine::cls_meta;
            }

            bool is_cls_meta() const
            {
                return def_ == NULL || def_->cls == ObjectDefine::cls_meta;
            }

            bool is_cls_data() const
            {
                return def_ && def_->cls == ObjectDefine::cls_data;
            }

        protected:
            void load(
                void *);

            void save(
                void *) const;

            void reset();

            void reset(
                ObjectDefine const * def);

        protected:
            ObjectDefine const * def_;
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_OBJECT_OBJECT_BASE_H_
