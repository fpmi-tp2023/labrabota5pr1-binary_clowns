#include <gtest/gtest.h>
#include "controller.h"
#include <sstream>

TEST(CheckLoginTest, TestPositive){
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkLogin("admin"));
}

TEST(CheckLoginTest, TestNegative){
    controller c("greenhouse.db");
    EXPECT_FALSE(c.checkLogin("ADMIN"));
}