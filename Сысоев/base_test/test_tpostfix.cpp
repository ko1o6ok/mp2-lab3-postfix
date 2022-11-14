#include "postfix.h"
#include <gtest/gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, to_inverse_polish_correctly){
    TPostfix a("3+5/(1-2)");
    ASSERT_EQ(a.ToPostfix(),"3 5 1 2 -/+");
}
TEST(TPostfix,can_calculate_correctly){
    TPostfix a("4+9*(3-1)");
    ASSERT_EQ(a.Calculate(),22);
}
TEST(TPostfix,result_is_independent_of_the_order_commutative_ops){
    TPostfix a1("(3+2)*7/3");
    TPostfix a2("7*(2+3)/3");
    ASSERT_EQ(a1.Calculate(),a2.Calculate());
}
TEST(TPostfix,result_is_dependent_of_the_order_non_commutative_ops){
    TPostfix a1("(6-5)/3");
    TPostfix a2("(5-6)/3");
    ASSERT_NE(a1.Calculate(),a2.Calculate());
}

TEST(TPostfix,result_is_the_same_before_and_after_the_calculation){
    TPostfix a("2*(3+6-11)");
    TPostfix b("2*(3+6-11)/4");
    ASSERT_EQ(a.Calculate()/4,b.Calculate());
}
TEST(TPostfix,calculate_throw_unknown_symbol){
    TPostfix a("3+2&5");
    ASSERT_ANY_THROW(a.Calculate());
}
TEST(TPostfix,postfix_throw_unknown_symbol){
    TPostfix a("3+2&5*6");
    ASSERT_ANY_THROW(a.ToPostfix());
}

TEST(TPostfix,postfix_throw_double){
    TPostfix a("3++2");
    ASSERT_ANY_THROW(a.ToPostfix());
}
TEST(TPostfix,postfix_correct_length){
    TPostfix a("(3+6)*9+3/(2-5)");

    ASSERT_EQ(a.ToPostfix().length(),17);
}

TEST(TPostfix,cannot_divide_by_zero){
    TPostfix a("3+6/(3-3)");
    ASSERT_ANY_THROW(a.Calculate());
}

TEST(TPostfix,priority_is_correct){
    ASSERT_EQ(TPostfix::Priority('+'),TPostfix::Priority('-'));
}

TEST(TPostfix, applying_inverse_to_itself_gives_id){
    TPostfix a("1/(1/5)");
    ASSERT_EQ(a.Calculate(),5);
}
TEST(TPostfix, applying_negative_to_itself_gives_id){
    TPostfix a("0-(0-5)");
    ASSERT_EQ(a.Calculate(),5);
}
TEST(TPostfix,distributive_law_works){
    TPostfix a("(3-6)/7");
    TPostfix b("3/7-6/7");
    ASSERT_EQ(a.Calculate(),b.Calculate());
}