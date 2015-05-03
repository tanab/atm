#include <gmock/gmock.h>
#include <diacritics.h>

TEST(DiacriticsHandling, RemoveDiacriticsFromText) {
    auto no_diacritics = removeDiacritics(L"حَدَّثَنَا");
    ASSERT_THAT(no_diacritics, testing::Eq(L"حدثنا"));
}
