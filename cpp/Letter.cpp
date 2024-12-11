#include "../hpp/Letter.hpp"

Letter::Letter(char letter) {
  letter_ = letter;
  // Если буква большая, то терминал
  is_terminal_ = isupper(letter);
}

Letter::Letter(const Letter& other_letter) {
  letter_ = other_letter.letter_;
  is_terminal_ = other_letter.is_terminal_;
}

bool Letter::GetIsTerminal() const {
  return is_terminal_;
}

char Letter::GetLetter() const{
  return letter_;
}

void Letter::SetLetter(char letter) {
  letter_ = letter;
  is_terminal_ = isupper(letter);
}