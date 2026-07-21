#include <string>
#include <unordered_map>

enum class PARTS_OF_SPEECH {
UNKNOWN, ADJECTIVE, ADVERB, ARTICLE, CONJUNCTION,
DETERMINER, INTERJECTION, LETTER, NAME,
NOT, NOUN, NUMBER, PREPOSITION, PRONOUN, VERB };

struct WordInfo {
    bool isStop;
    PARTS_OF_SPEECH pos;
};

class Lexicon {
    public:
        static Lexicon& getInstance();
        Lexicon(); /*! Default constructor for lexicon class*/
        ~Lexicon(); /*! Default destructor for lexicon class*/
        int loadcsv(std::string); /*! Load csv file with proper format into lexicon class*/
// loads from a file in the right format
// returns the number of words (rows) loaded
        bool addWord(std::string, bool, PARTS_OF_SPEECH); /*! Add a word into lexicon class given word, stopword, and part of speech*/
// add a single word to the Lexicon, with the attributes from the file
// params are: word: std::string (the text ONLY of the word to add)
// isstop: bool (true if the file said it’s a stopword)
// wordtype: PARTS_OF_SPEECH (from string in file)
// if the word was added, return true
// if the word exists or any other error, make no change and return false
        bool isStopWord(std::string); /*! Returns true if word is a stopword*/
// true if the word passed in is a stopword
        PARTS_OF_SPEECH gettype(std::string); /*! Returns part of speech*/
// returns the parts of speech for a word – defined as an enum
    private:
        std::unordered_map<std::string, WordInfo> lex; /*! Map for storing words in lexicon*/
        PARTS_OF_SPEECH stringToPOS(const std::string& str); /*! Converts string to PARTS_OF_SPEECH*/
};