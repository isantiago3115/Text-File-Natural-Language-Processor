// Syllabizer.hpp	Creed Jones	VT ECE 3574	Feb 4 2026
// This class implements methods to break an English word (string) into syllables
#include <string>
#include <vector>

class Syllabizer {
public:
	static const std::string vowels; /*!Upper and lowercase vowels as string*/
	static const std::string consonants; /*!Upper and lowercase consonants as string*/
	static const std::string prefixes[]; /*! Array of all prefixes*/
	static const std::string suffixes[]; /*! Array of all suffixes*/
	// these are defined in the cpp, so the function can be called at class level
private:
	static bool isvowel(char c); 
	static bool isconsonant(char c);
	static std::string getvcpattern(std::string&);
public:
	static std::vector<int> syllabize(std::string&); /*! Returns the start of each syllable in a given words represetned as a vector of ints*/
};
