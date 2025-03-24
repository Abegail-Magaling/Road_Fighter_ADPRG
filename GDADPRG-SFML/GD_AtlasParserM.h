#pragma once
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include <SFML/Graphics.hpp>
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>

bool comparePrefix(std::string word, std::string prefix);
bool containsChar(std::string word, char character);
std::unordered_map<std::string,sf::IntRect>* createDictionary(std::string atlasFile);
