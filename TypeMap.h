// TypeMap.h

#ifndef _JUST_AVBASE_TYPE_MAP_H_
#define _JUST_AVBASE_TYPE_MAP_H_

namespace just
{
    namespace avbase
    {

        template <
            typename T, 
            typename MT1
        >
        struct type_map_finder_t1
        {
            type_map_finder_t1(
                MT1 T::* m1, 
                MT1 f1)
                : m1_(m1)
                , f1_(f1)
            {
            }

            bool operator()(
                T const & e) const
            {
                return e.*m1_ == f1_;
            }
        private:
            MT1 T::* m1_;
            MT1 f1_;
        };

        template <
            typename T, 
            typename MT1, 
            typename MT2
        >
        struct type_map_finder_t2
        {
            type_map_finder_t2(
                MT1 T::* m1, 
                MT1 f1, 
                MT2 T::* m2, 
                MT2 f2) 
                : m1_(m1)
                , f1_(f1)
                , m2_(m2)
                , f2_(f2)
            {
            }

            bool operator()(
                T const & e) const
            {
                return e.*m1_ == f1_ && e.*m2_ == f2_;
            }
        private:
            MT1 T::* m1_;
            MT1 f1_;
            MT2 T::* m2_;
            MT2 f2_;
        };

        template <
            typename T, 
            typename MT1, 
            typename MT2, 
            typename MT3
        >
        struct type_map_finder_t3
        {
            type_map_finder_t3(
                MT1 T::* m1, 
                MT1 f1, 
                MT2 T::* m2, 
                MT2 f2, 
                MT3 T::* m3, 
                MT3 f3) 
                : m1_(m1)
                , f1_(f1)
                , m2_(m2)
                , f2_(f2)
                , m3_(m3)
                , f3_(f3)
            {
            }

            bool operator()(
                T const & e) const
            {
                return e.*m1_ == f1_ 
                    && e.*m2_ == f2_ 
                    && e.*m3_ == f3_;
            }
        private:
            MT1 T::* m1_;
            MT1 f1_;
            MT2 T::* m2_;
            MT2 f2_;
            MT3 T::* m3_;
            MT3 f3_;
        };

        template <
            typename T, 
            size_t n, 
            typename MT1
        >
        T const * type_map_find(
            T const (& table)[n], 
            MT1 T::* m1, 
            MT1 f1)
        {
            type_map_finder_t1<T, MT1> finder(m1, f1);
            T const * i = std::find_if(
                &table[0], &table[n], finder);
            if (i == &table[n])
                i = NULL;
            return i;
        }

        template <
            typename T, 
            typename MT1
        >
        T const * type_map_find(
            T const * table, 
            size_t n, 
            MT1 T::* m1, 
            MT1 f1)
        {
            type_map_finder_t1<T, MT1> finder(m1, f1);
            T const * i = std::find_if(
                table, table + n, finder);
            if (i == table + n)
                i = NULL;
            return i;
        }

        template <
            typename T, 
            size_t n, 
            typename MT1, 
            typename MT2
        >
        T const * type_map_find(
            T const (& table)[n], 
            MT1 T::* m1, 
            MT1 f1, 
            MT2 T::* m2, 
            MT2 f2)
        {
            type_map_finder_t2<T, MT1, MT2> finder(m1, f1, m2, f2);
            T const * i = std::find_if(
                &table[0], &table[n], finder);
            if (i == &table[n])
                i = NULL;
            return i;
        }

        template <
            typename T, 
            typename MT1, 
            typename MT2
        >
        T const * type_map_find(
            T const * table, 
            size_t n, 
            MT1 T::* m1, 
            MT1 f1, 
            MT2 T::* m2, 
            MT2 f2)
        {
            type_map_finder_t2<T, MT1, MT2> finder(m1, f1, m2, f2);
            T const * i = std::find_if(
                table, table + n, finder);
            if (i == table + n)
                i = NULL;
            return i;
        }

        template <
            typename T, 
            size_t n, 
            typename MT1, 
            typename MT2, 
            typename MT3
        >
        T const * type_map_find(
            T const (& table)[n], 
            MT1 T::* m1, 
            MT1 f1, 
            MT2 T::* m2, 
            MT2 f2, 
            MT3 T::* m3, 
            MT3 f3)
        {
            type_map_finder_t3<T, MT1, MT2, MT3> finder(m1, f1, m2, f2, m3, f3);
            T const * i = std::find_if(
                &table[0], &table[n], finder);
            if (i == &table[n])
                i = NULL;
            return i;
        }

        template <
            typename T, 
            typename MT1, 
            typename MT2, 
            typename MT3
        >
        T const * type_map_find(
            T const * table, 
            size_t n, 
            MT1 T::* m1, 
            MT1 f1, 
            MT2 T::* m2, 
            MT2 f2, 
            MT3 T::* m3, 
            MT3 f3)
        {
            type_map_finder_t3<T, MT1, MT2, MT3> finder(m1, f1, m2, f2, m3, f3);
            T const * i = std::find_if(
                table, table + n, finder);
            if (i == table + n)
                i = NULL;
            return i;
        }

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_TYPE_MAP_H_
