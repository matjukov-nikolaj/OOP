#pragma once

bool ReadObsceneWordsFromFile(std::istream &input, std::set<std::string> &obsceneWords);
std::string RemoveObsceneWords(std::string &str);
