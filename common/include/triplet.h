#pragma once

///
/// \brief The Triplet struct defines a class of triplets with types of those triplets being
/// templates.
///
template <class T1, class T2, class T3>
struct Triplet {
    Triplet() : first(T1()), second(T2()), third(T3()) {}
    Triplet(const T1 &t1, const T2 &t2, const T3 &t3) : first(t1), second(t2), third(t3) {}
    Triplet(const Triplet<T1, T2, T3> &other)
        : first(other.first), second(other.second), third(other.third) {}
    Triplet<T1, T2, T3> &operator=(const Triplet<T1, T2, T3> &other) {
        first = other.first;
        second = other.second;
        third = other.third;
        return *this;
    }

    T1 first;
    T2 second;
    T3 third;
};

template <class T1, class T2, class T3>
bool operator==(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return t1.first == t2.first && t1.second == t2.second && t1.third == t2.third;
}

template <class T1, class T2, class T3>
bool operator!=(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return !(t1 == t2);
}

template <class T1, class T2, class T3>
bool operator<(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return t1.first < t2.first || (!(t2.first < t1.first) && t1.second < t2.second) ||
           (!(t2.first < t1.first) && !(t1.second < t2.second) && t1.third < t2.third);
}

template <class T1, class T2, class T3>
bool operator>(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return t2 < t1;
}

template <class T1, class T2, class T3>
bool operator<=(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return !(t2 < t1);
}

template <class T1, class T2, class T3>
bool operator>=(const Triplet<T1, T2, T3> &t1, const Triplet<T1, T2, T3> &t2) {
    return !(t1 < t2);
}
