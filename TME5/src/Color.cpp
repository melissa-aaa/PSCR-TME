#include "Color.h"
#include <iostream>
#include <vector>

namespace pr {

const Color white = Color(255,255,255);
const Color red = Color(255,0,0);
const Color blue = Color(0,0,255);
const Color black = Color(0,0,0);


std::ostream & operator<<(std::ostream & os, const Color & col) {
	os << int(col.r) << ' ' << int(col.g) << ' ' << int(col.b) << '\n' ;
	return os;
}

} /* namespace pr */
