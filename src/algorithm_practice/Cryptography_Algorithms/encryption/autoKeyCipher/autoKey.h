#ifndef AUTO_KEY_H
#define AUTO_KEY_H

std::string updateText(const std::string&, std::function<char(char,int)>);

std::string encrypt(const std::string&, const std::string&);

std::string decrypt(const std::string&, const std::string&);

#endif /* AUTO_KEY_H */
