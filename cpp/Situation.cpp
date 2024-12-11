#include "../hpp/Situation.hpp"


Situation::Situation(const Rule& rule, int parent_index, int index) {
  rule_ = rule;
  parent_index_ = parent_index;
  index_ = index;
}

Situation::Situation(const Situation& other_sim) {
  rule_ = other_sim.rule_;
  parent_index_ = other_sim.parent_index_;
  index_ = other_sim.index_;
}

bool Situation::IndexIsTerminal() const {
  if (index_ == rule_.GetSizeRule()) {
    return true;
  }

  return rule_.GetLetterRight(index_).GetIsTerminal();
}

bool Situation::IsEnd() const {
  if (index_ == rule_.GetSizeRule()) {
    return true;
  }
  return false;
}

char Situation::NextLetter() const {
  return rule_.GetLetterRight(index_).GetLetter();
}

Rule Situation::GetRule() const {
  return rule_;
}

int Situation::GetIndex() const {
  return index_;
}

int Situation::GetParentIndex() const {
  return parent_index_;
}

bool Situation::operator<(const Situation& other) const {
  return std::make_tuple(rule_, parent_index_, index_)
      < std::make_tuple(other.rule_, other.parent_index_, other.index_);
}