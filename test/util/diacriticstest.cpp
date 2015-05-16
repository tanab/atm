#include <gmock/gmock.h>
#include <diacritics.hpp>

using namespace atm::util;

TEST(DiacriticsHandling, RemoveDiacriticsFromText) {
    auto no_diacritics = removeDiacritics(L"حَدَّثَنَا");
    ASSERT_THAT(no_diacritics, testing::Eq(L"حدثنا"));
}

TEST(DiacriticsHandling, RemoveDiacriticsFromStringWithOnlySpacesDoesNothing) {
    auto outcome = removeDiacritics(L"      ");
    ASSERT_THAT(outcome, testing::Eq(L"      "));
}

TEST(DiacriticsHandling, RemovesLastNonDiacriticLetterFromWord) {
    // atm::util::removeLastLetter
    ASSERT_FALSE(true);
}

TEST(DiacriticsHandling, RemovesTrailingDiacritics) {
    // atm::util::removeTrailingDiacritics
    ASSERT_FALSE(true);
}

TEST(DiacriticConversion, ReturnProperCharacterForDiacritic) {
    auto diacritic = Diacritic::FATHA;
    auto letter = interpret(diacritic);
    ASSERT_THAT(letter, testing::Eq(fatha));
}

TEST(DiacriticConversion, ReturnProperDiacriticForTheCharacter) {
    auto diacritic = interpret(sukun);
    ASSERT_THAT(diacritic, testing::Eq(Diacritic::SUKUN));
}

TEST(DiacriticConversion, ReturnUndefinedDiacriticForNonDiacriticCharacter) {
    auto diacritic = interpret(alef);
    ASSERT_THAT(diacritic, testing::Eq(Diacritic::UNDEFINED_DIACRITIC));
}

TEST(DiacriticsSearch, RetursCorrectoPositionOfTheLastNonDiacriticLetter) {
    // atm::util::lastLetterIndex
    ASSERT_FALSE(true);
}

TEST(DiacriticsSearch, ReturnsMinusOneIfTheWordHasOnlyDiacritics) {
    auto all_diacritics = diacritics;
    ASSERT_THAT(atm::util::lastLetterIndex(all_diacritics), testing::Eq(-1));
}

TEST(DiacriticsSearch, ReturnsLastNonDiacriticLetter) {
    // atm::util::lastLetter
    ASSERT_FALSE(true);
}

TEST(DiacriticsSearch, ReturnsNullCharacterIfWordHasNoDiacritics) {
    auto all_diacritics = diacritics;
    ASSERT_THAT(atm::util::lastLetter(diacritics), testing::Eq(L'\0'));
}
