#include "./hpp/Grammar.hpp"
#include "./hpp/Parser.hpp"
#include <gtest/gtest.h>
#include <random>

std::string CreateBracketSequence(size_t size, bool* coorect) {
	std::string result;
	*coorect = true;
	int count = 0;
	result.resize(size);
	for (int i = 0; i < size; i++) {
		if (random() % 2 == 0) {
			result[i] = '(';
			count += 1;
		} else {
			result[i] = ')';
			count -= 1;
		}
		if (count < 0) {
			*coorect = false;
		}
	}
	if (count > 0) {
		*coorect = false;
	}
	return result;
}

std::string CreateATranB(size_t size, bool* coorect) {
	std::string result;
	*coorect = true;
	bool exit_b = false;
	size_t count_a = 0;
	size_t count_b = 0;
	result.resize(size);
	for (int i = 0; i < size; i++) {
		if (random() % 2 == 0) {
			result[i] = 'a';
			count_a++;
			if (exit_b) {
				*coorect = false;
			}
		} else {
			result[i] = 'b';
			count_b++;
			exit_b = true;
		}
	}
	if (count_b !=  count_a) {
		*coorect = false;
	}
	return result;
}

TEST(СorrectBracketSequence, SmallTrue) {
	Grammar grammar;
	grammar.SetRule("S->");
	grammar.SetRule("S->(S)");
	grammar.SetRule("S->SS");
	ParserEarley parser;
	EXPECT_TRUE(parser.Earley("()", grammar));
	EXPECT_TRUE(parser.Earley("()()", grammar));
	EXPECT_TRUE(parser.Earley("()()()", grammar));
	EXPECT_TRUE(parser.Earley("(())", grammar));
	EXPECT_TRUE(parser.Earley("((()))", grammar));
	EXPECT_TRUE(parser.Earley("", grammar));
}

TEST(СorrectBracketSequence, SmallFalse) {
	Grammar grammar;
	grammar.SetRule("S->");
	grammar.SetRule("S->(S)");
	grammar.SetRule("S->SS");
	ParserEarley parser;
	EXPECT_FALSE(parser.Earley("(", grammar));
	EXPECT_FALSE(parser.Earley("(()", grammar));
	EXPECT_FALSE(parser.Earley("))", grammar));
	EXPECT_FALSE(parser.Earley("())", grammar));
	EXPECT_FALSE(parser.Earley(")()()(", grammar));
}

TEST(СorrectBracketSequence, BIGTEST) {
	Grammar grammar;
	grammar.SetRule("S->");
	grammar.SetRule("S->(S)");
	grammar.SetRule("S->SS");
	ParserEarley parser;
	for (size_t i = 0; i < 100; i++) {
		bool coorect = true;
		std::string str = CreateATranB(i*4, &coorect);
		if (coorect) {
			EXPECT_TRUE(parser.Earley(str, grammar));
		} else {
			EXPECT_FALSE(parser.Earley(str, grammar));
		}
	}
}

TEST(AThanB, SmallTrue) {
	Grammar grammar;
	grammar.SetRule("S->ASB");
	grammar.SetRule("S->");
	grammar.SetRule("A->a");
	grammar.SetRule("B->b");
	ParserEarley parser;
	EXPECT_TRUE(parser.Earley("ab", grammar));
	EXPECT_TRUE(parser.Earley("aabb", grammar));
	EXPECT_TRUE(parser.Earley("aaaabbbb", grammar));
	EXPECT_TRUE(parser.Earley("", grammar));
}

TEST(AThanB, SmallFalse) {
	Grammar grammar;
	grammar.SetRule("S->ASB");
	grammar.SetRule("S->");
	grammar.SetRule("A->a");
	grammar.SetRule("B->b");
	ParserEarley parser;
	EXPECT_FALSE(parser.Earley("abababab", grammar));
	EXPECT_FALSE(parser.Earley("bbbaaa", grammar));
	EXPECT_FALSE(parser.Earley("baabba", grammar));
	EXPECT_FALSE(parser.Earley("ba", grammar));
	EXPECT_FALSE(parser.Earley("cccc", grammar));
}


TEST(AThanB, BIGTEST) {
	Grammar grammar;
	grammar.SetRule("S->ASB");
	grammar.SetRule("S->");
	grammar.SetRule("A->a");
	grammar.SetRule("B->b");
	ParserEarley parser;
	for (size_t i = 0; i < 100; i++) {
		bool coorect = true;
		std::string str = CreateBracketSequence(i*5, &coorect);
		if (coorect) {
			EXPECT_TRUE(parser.Earley(str, grammar));
		} else {
			EXPECT_FALSE(parser.Earley(str, grammar));
		}
	}
}

TEST(Arifmetics, TestTrue) {
	Grammar grammar;
	grammar.SetRule("S->a");
	grammar.SetRule("S->b");
	grammar.SetRule("S->S+S");
	grammar.SetRule("S->SS");
	grammar.SetRule("S->S*S");
	grammar.SetRule("S->(S)");
	ParserEarley parser;
	EXPECT_TRUE(parser.Earley("a+b", grammar));
	EXPECT_TRUE(parser.Earley("a*b", grammar));
	EXPECT_TRUE(parser.Earley("b*a", grammar));
	EXPECT_TRUE(parser.Earley("a*a", grammar));
	EXPECT_TRUE(parser.Earley("(a+b)*a", grammar));
	EXPECT_TRUE(parser.Earley("b*(b+a)*a", grammar));
	EXPECT_TRUE(parser.Earley("(b+a)(b+a)", grammar));
}


TEST(Arifmetics, TestFalse) {
	Grammar grammar;
	grammar.SetRule("S->a");
	grammar.SetRule("S->b");
	grammar.SetRule("S->S+S");
	grammar.SetRule("S->SS");
	grammar.SetRule("S->S*S");
	grammar.SetRule("S->(S)");
	ParserEarley parser;
	EXPECT_FALSE(parser.Earley("a+(", grammar));
	EXPECT_FALSE(parser.Earley("(a*b", grammar));
	EXPECT_FALSE(parser.Earley("b*+a", grammar));
	EXPECT_FALSE(parser.Earley("a*", grammar));
	EXPECT_FALSE(parser.Earley("(+b)*a", grammar));
	EXPECT_FALSE(parser.Earley("*(b+a)*a", grammar));
	EXPECT_FALSE(parser.Earley("(b+a))(b+a)", grammar));
	EXPECT_FALSE(parser.Earley("", grammar));
}

/*
{w ∈ {a, b}∗ | |w|a − 2|w|b = −1}

	S →S0aS0bS0
	S →S0bS0aS0
	S0 →ε
	S0 →S0aS0aS0bS0
	S0 →S0bS0aS0aS0
	S0 →S0aS0bS0aS0
*/


TEST(Teor5, TestTrue) {
	Grammar grammar;
	grammar.SetRule("S->TaTbT");
	grammar.SetRule("S->TbTaT");
	grammar.SetRule("T->");
	grammar.SetRule("T->TaTaTbT");
	grammar.SetRule("T->TbTaTaT");
	grammar.SetRule("T->TaTbTaT");
	ParserEarley parser;
	EXPECT_TRUE(parser.Earley("ab", grammar));
	EXPECT_TRUE(parser.Earley("ba", grammar));
	EXPECT_TRUE(parser.Earley("babaa", grammar));
	EXPECT_TRUE(parser.Earley("baaba", grammar));
	EXPECT_TRUE(parser.Earley("abaab", grammar));
	EXPECT_TRUE(parser.Earley("aaabb", grammar));
	EXPECT_TRUE(parser.Earley("bababaaa", grammar));
	EXPECT_TRUE(parser.Earley("baaaabba", grammar));
	EXPECT_TRUE(parser.Earley("abaaabab", grammar));
	EXPECT_TRUE(parser.Earley("aaababab", grammar));
	EXPECT_TRUE(parser.Earley("bababbaaaaa", grammar));
	EXPECT_TRUE(parser.Earley("baaaabaabba", grammar));
	EXPECT_TRUE(parser.Earley("abaaaaabbab", grammar));
	EXPECT_TRUE(parser.Earley("aaabaababab", grammar));
}

TEST(Teor5, TestFalse) {
	Grammar grammar;
	grammar.SetRule("S->TaTbT");
	grammar.SetRule("S->TbTaT");
	grammar.SetRule("T->");
	grammar.SetRule("T->TaTaTbT");
	grammar.SetRule("T->TbTaTaT");
	grammar.SetRule("T->TaTbTaT");
	ParserEarley parser;
	EXPECT_FALSE(parser.Earley("b", grammar));
	EXPECT_FALSE(parser.Earley("a", grammar));
	EXPECT_FALSE(parser.Earley("abaa", grammar));
	EXPECT_FALSE(parser.Earley("baba", grammar));
	EXPECT_FALSE(parser.Earley("aaab", grammar));
	EXPECT_FALSE(parser.Earley("aabb", grammar));
	EXPECT_FALSE(parser.Earley("baabaaa", grammar));
	EXPECT_FALSE(parser.Earley("baaabba", grammar));
	EXPECT_FALSE(parser.Earley("aaaabab", grammar));
	EXPECT_FALSE(parser.Earley("aababab", grammar));
	EXPECT_FALSE(parser.Earley("ababbaaaaa", grammar));
	EXPECT_FALSE(parser.Earley("baaabaabba", grammar));
	EXPECT_FALSE(parser.Earley("aaaaaabbab", grammar));
	EXPECT_FALSE(parser.Earley("aabaababab", grammar));
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
