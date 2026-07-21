// testproject.cpp : Catch2 test executable for the ECE3574 project - SP26
// Creed Jones VT ECE - Feb 2, 2026
// updated for milestone 03 - Feb 15, 2026
#include <iostream>
#include <map>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Document.hpp"
#include "Syllabizer.hpp"
using namespace std;
unordered_map<string, string> testwords = {
{ "mango", "man-go" },
{ "poke", "poke" },
{ "poker", "pok-er"},
{ "cabin", "cab-in" },
{ "napkin", "nap-kin" },
{ "boat", "boat" },
{ "review", "re-view" },
{ "working", "work-ing" },
{ "rabbit", "rab-bit" },
{ "parrot", "par-rot" },
{ "opening", "o-pen-ing"},
{ "open", "o-pen" },
{ "ope", "ope"},
{ "computer", "com-put-er" },
{ "emit", "e-mit" },
{ "nation", "na-tion" },
{ "disturb", "dis-turb" },
{ "recalling", "re-call-ing" },
{ "working", "work-ing" },
{ "convention", "con-ven-tion" },
{ "undeniable", "un-de-ni-able" },
 };
// a function to show syllable breaks as dashes in the word
// for display or for checking syllabization results
string syllabizedstring(string input, vector<int> breaks) {
string result = input;
for (vector<int>::reverse_iterator it = breaks.rbegin(); it != breaks.rend(); ++it) {
if (*it > 0) { // don't insert a dash for the start of the word
result.insert(*it, "-");
}
}
return result;
}
TEST_CASE("Syllabizer testing", "") {
for (auto wordpair : testwords) {
string word = wordpair.first;
string answer = wordpair.second;
string testanswer = syllabizedstring(word, Syllabizer::syllabize(word));
REQUIRE(testanswer == answer);
}
}