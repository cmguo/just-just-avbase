// ObjectBase.h

#ifndef _PPBOX_AVBASE_OBJECT_OBJECT_BASE_H_
#define _PPBOX_AVBASE_OBJECT_OBJECT_BASE_H_

#include "ppbox/avbase/object/ObjectDefine.h"

namespace ppbox
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
            bool empty() const;

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
} // namespace ppbox

#endif // _PPBOX_AVBASE_OBJECT_OBJECT_BASE_H_
