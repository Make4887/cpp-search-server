#pragma once
#include <iostream>
#include <vector>

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : begin_(begin)
        , end_(end)
    {
    }

    Iterator begin() {
        return begin_;
    }

    Iterator end() {
        return end_;
    }

private:
    Iterator begin_;
    Iterator end_;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator range_begin, Iterator range_end, size_t page_size) {
        for (; static_cast<size_t>(range_end - range_begin) >= page_size; range_begin = range_begin + page_size) {
            pages_.push_back({ range_begin, range_begin + page_size });
        }
        if (range_begin < range_end) {
            pages_.push_back({ range_begin, range_end });
        }
    }


    auto begin() const {
        return pages_.begin();
    }
    auto end() const {
        return pages_.end();
    }
private:
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& out, IteratorRange<Iterator> range) {
    for (auto it = range.begin(); it != range.end(); ++it) {
        out << *it;
    }
    return out;
}