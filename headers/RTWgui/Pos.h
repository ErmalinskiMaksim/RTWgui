#ifndef POS_H
#define POS_H

#include <functional>

// a class that is used internally in widgets to determine a descrete
// position of a widget component (e.g. a cell in a table)
struct Pos {
    size_t col;
    size_t row;
    bool operator==(const Pos&) const = default;
    inline bool operator<(const Pos& other) const {
        return (row < other.row) || (row == other.row && col < other.col);
    }
};

namespace std {
    template<>
    struct hash<Pos> {
        size_t operator() (const Pos& p) const {
		return std::rotl(hash<size_t>{}(p.col),1) ^
			   hash<size_t>{}(p.row);
	    }
    };
}

#endif
