#pragma once
#include <string>

class Letter {
 private:
  char letter_;
  bool is_terminal_;
 public:
  Letter() {}
  Letter(const Letter& other_letter);
  Letter(char letter);
  bool GetIsTerminal() const;
  char GetLetter() const;
  void SetLetter(char letter);
};