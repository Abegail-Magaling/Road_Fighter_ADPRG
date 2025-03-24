#include "GD_AtlasParserM.h"

bool comparePrefix(std::string word, std::string prefix){
    int wordLen = word.length();
    int prefixLen = prefix.length();

    if(wordLen<prefixLen) return false;

    return word.substr(0, prefixLen) == prefix;
}

bool containsChar(std::string word, char character){
    return std::find(word.begin(), word.end(), character) != word.end();
}

std::unordered_map<std::string,sf::IntRect>* createDictionary(std::string atlasFile){
    std::ifstream file(atlasFile);
    if(!file) {
        std::cerr << "Error opening file!" << std::endl;
        return nullptr;
    }

    std::string imageName;
    std::getline(file, imageName);

    std::string line, imgName, bounds;

    std::unordered_map<std::string,sf::IntRect>* dictionary = new std::unordered_map<std::string,sf::IntRect>();

    while(std::getline(file, line)){
        if(comparePrefix(line,"size:")){
            continue;
        }else if(comparePrefix(line,"repeat:")){
            continue;
        }else if(comparePrefix(line,"format:")){
            continue;
        }else if(!containsChar(line,':')){
            imgName = line;
            std::getline(file, line);
            
            if(!comparePrefix(line,"bounds:")) return nullptr;
            bounds = line.substr(7, line.length());

            std::istringstream stream(bounds);
            std::string part;
            std::vector<std::string> segments;

            while (std::getline(stream, part, ','))
                segments.push_back(part);
            
            if(segments.size()!=4) return nullptr;

            int x = std::atoi(segments[0].c_str());
            int y = std::atoi(segments[1].c_str());
            int width = std::atoi(segments[2].c_str());
            int height = std::atoi(segments[3].c_str());

            (*dictionary)[imgName] = sf::IntRect({x,y},{width,height});
        }
    }
    file.close();
    return dictionary;
}
