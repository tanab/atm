#include <gmock/gmock.h>
#include <diacritics.hpp>

TEST(DiacriticsHandling, RemoveDiacriticsFromText) {
    auto no_diacritics = atm::util::removeDiacritics(L"حَدَّثَنَا");
    ASSERT_THAT(no_diacritics, testing::Eq(L"حدثنا"));
}

TEST(DiacriticsHandling, RemoveDiacriticsFromStringWithOnlySpacesDoesNothing) {
    auto outcome = atm::util::removeDiacritics(L"      ");
    ASSERT_THAT(outcome, testing::Eq(L"      "));
}
