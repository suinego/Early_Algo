#include "../hpp/Parser.hpp"

bool ParserEarley::Earley(const std::string &word, Grammar grammar) {
  grammar_ = grammar;
  word_ = word;

  // очищаем на случай, если уже использовати
  situations_.clear();
  situations_.resize(word.size() + 1);

  // вводим дополнительное состояние, которое
  // характеризует начало
  grammar_.SetRule(Rule("~->S"));
  Situation dop_start = Situation(Rule("~->S"), 0, 0);
  situations_[0].insert(dop_start);

  for (int index = 0; index < word.size() + 1; index++) {
    // занесли первую итерациб в цикл for
    Scan(index);
    int old_value = situations_[index].size();

    Complete(index);
    Predict(index);

    while (situations_[index].size() != old_value) {
      old_value = situations_[index].size();
      Complete(index);
      Predict(index);
    }
  }
  return (situations_[word.size()].find(Situation(
              dop_start.GetRule(), dop_start.GetParentIndex(),
              dop_start.GetIndex() + 1)) != situations_[word.size()].end());
}

void ParserEarley::Scan(int index) {
  if (index == 0) {
    return;
  }
  for (std::set<Situation>::iterator it = situations_[index - 1].begin();
       it != situations_[index - 1].end(); ++it) {
    if (it->IndexIsTerminal()) {
      continue;
    }
    if (word_[index - 1] != it->NextLetter()) {
      continue;
    }
    situations_[index].insert(
        Situation(it->GetRule(), it->GetParentIndex(), it->GetIndex() + 1));
  }
}

void ParserEarley::Predict(int index) {
  for (std::set<Situation>::iterator it = situations_[index].begin();
       it != situations_[index].end(); ++it) {
    if (it->IsEnd()) {
      continue;
    }
    if (!it->IndexIsTerminal()) {
      continue;
    }
    for (int i = 0; i < grammar_.rules_.size(); i++) {
      if (it->NextLetter() == grammar_.rules_[i].GetTerminal()) {
        situations_[index].emplace(grammar_.rules_[i], index, 0);
      }
    }
  }
}

void ParserEarley::Complete(int index) {
  for (std::set<Situation>::iterator it = situations_[index].begin();
       it != situations_[index].end(); ++it) {
    if (it->GetIndex() != it->GetRule().GetSizeRule()) {
      continue;
    }
    for (std::set<Situation>::iterator parent_it =
             situations_[it->GetParentIndex()].begin();
         parent_it != situations_[it->GetParentIndex()].end(); ++parent_it) {
      if (parent_it->IsEnd()) {
        continue;
      }
      if (parent_it->NextLetter() != it->GetRule().GetTerminal()) {
        continue;
      }
      situations_[index].insert(Situation(parent_it->GetRule(),
                                          parent_it->GetParentIndex(),
                                          parent_it->GetIndex() + 1));
    }
  }
}