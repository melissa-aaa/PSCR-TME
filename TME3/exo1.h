#ifndef EXO1_H_
#define EXO1_H_

#include <string>

namespace pr {

    template<typename iterator>
    size_t count (iterator begin, iterator end) {
        size_t cpt = 0;
        while (begin != end) {
            begin++;
            cpt++;
        }

        return cpt;
    }

    template<typename iterator, typename T>
    size_t count_if_equal(iterator begin, iterator end, const T& valeur) {
        size_t cpt = 0;
        while (begin != end ) {
            if (*begin == valeur) {
                cpt++;
            }
            begin++;
        }
        return cpt;
    }

}

#endif