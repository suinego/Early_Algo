
#include "../hpp/Grammar.hpp"
#include <tuple>

class Situation {
 public:
  Situation(const Rule& rule, int parent_index, int index);
  Situation(const Situation& other_sim);
  
  bool operator<(const Situation& other) const;

  Rule GetRule() const;
  int GetIndex() const;
  int GetParentIndex() const;

  bool IndexIsTerminal() const;
  bool IsEnd() const;
  char NextLetter() const;

private:
  Rule rule_;
  int parent_index_;
  int index_;
};