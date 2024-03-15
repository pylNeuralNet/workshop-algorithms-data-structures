#include <iostream>
#include <unordered_map>
#include <string>

class Dictionary {
private:
    std::unordered_map<std::string, std::string> word_map;

public:
    void AddWord(std::string&& word, std::string&& definition) {
        word_map.emplace(std::move(word), std::move(definition));
    }

    void UpdateWord(const std::string& word, std::string&& definition) {
        auto it = word_map.find(word);
        if (it != word_map.end()) {
            it->second = std::move(definition);
        }
    }

    const std::string& GetDefinition(const std::string& word) const {
        if (auto it = word_map.find(word); it != word_map.end())
            return it->second;
        static std::string empty_string;
        return empty_string;
    }

    void PrintDictionary() const {
        for (const auto& [word, definition] : word_map) {
            std::cout << "Word: " << word << ", Definition: " << definition << "\n";
        }
    }
};

int main() {
    Dictionary dictionary;
    dictionary.AddWord("Apple", "A fruit that is red or green in color.");
    dictionary.UpdateWord("Apple", "A round fruit that is red, green, or yellow in color.");
    dictionary.PrintDictionary();

    std::cout << "Definition of Apple: " << dictionary.GetDefinition("Apple") << "\n";
    std::cout << "Definition of Banana: " << dictionary.GetDefinition("Banana") << "\n";

    return 0;
}