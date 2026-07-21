#include "Lexicon.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

Lexicon& Lexicon::getInstance(){
    static Lexicon instance;
    return instance;
}

Lexicon::Lexicon() {}

Lexicon::~Lexicon() {}

int Lexicon::loadcsv(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return 0;

    std::string line;
    int count = 0;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string word, stopStr, freqStr, posStr;

        std::getline(ss, word, ',');
        std::getline(ss, stopStr, ',');
        std::getline(ss, freqStr, ',');
        std::getline(ss, posStr, ',');

        if (word.empty()) continue;

        bool isStop = (stopStr == "1");
        PARTS_OF_SPEECH pos = stringToPOS(posStr);

        if (addWord(word, isStop, pos)) {
            count++;
        }
    }
    return count;
}

bool Lexicon::addWord(std::string word, bool isstop, PARTS_OF_SPEECH wordtype) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    if (lex.find(word) != lex.end()) {
        return false;
    }

    lex[word] = {isstop, wordtype};
    return true;
}

bool Lexicon::isStopWord(std::string word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    auto it = lex.find(word);
    if (it == lex.end()) return false;

    return it->second.isStop;
}

PARTS_OF_SPEECH Lexicon::gettype(std::string word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    auto it = lex.find(word);
    if (it == lex.end()) return PARTS_OF_SPEECH::UNKNOWN;

    return it->second.pos;
}

PARTS_OF_SPEECH Lexicon::stringToPOS(const std::string& str) {
    if (str == "Adjective") return PARTS_OF_SPEECH::ADJECTIVE;
    if (str == "Adverb") return PARTS_OF_SPEECH::ADVERB;
    if (str == "Article") return PARTS_OF_SPEECH::ARTICLE;
    if (str == "Conjunction") return PARTS_OF_SPEECH::CONJUNCTION;
    if (str == "Determiner") return PARTS_OF_SPEECH::DETERMINER;
    if (str == "Interjection") return PARTS_OF_SPEECH::INTERJECTION;
    if (str == "Letter") return PARTS_OF_SPEECH::LETTER;
    if (str == "Name") return PARTS_OF_SPEECH::NAME;
    if (str == "Not") return PARTS_OF_SPEECH::NOT;
    if (str == "Noun") return PARTS_OF_SPEECH::NOUN;
    if (str == "Number") return PARTS_OF_SPEECH::NUMBER;
    if (str == "Preposition") return PARTS_OF_SPEECH::PREPOSITION;
    if (str == "Pronoun") return PARTS_OF_SPEECH::PRONOUN;
    if (str == "Verb") return PARTS_OF_SPEECH::VERB;

    return PARTS_OF_SPEECH::UNKNOWN;
}