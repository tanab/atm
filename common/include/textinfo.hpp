#ifndef TEXTINFO_HPP
#define TEXTINFO_HPP

#include <string>

template <class STRING_TYPE>
class TextInfo {
    public:
        explicit TextInfo(const STRING_TYPE &text, size_t start, size_t finish) :
            m_text(text), m_start(start), m_finish(finish) {
        }
        virtual ~TextInfo() {}

        // TODO: Check the behavior when diacritics are present.
        STRING_TYPE getString() const {
            m_text.substr(m_start, m_finish - m_start + 1);
        }

    private:
        STRING_TYPE m_text;
        std::size_t m_start;
        std::size_t m_finish;
};

#endif // TEXTINFO_HPP

