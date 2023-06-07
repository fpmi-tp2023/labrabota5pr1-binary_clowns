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

TEST(CheckPasswordTest, TestPositive){
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkPassword("admin", "admin"));
}

TEST(CheckPasswordTest, TestNegative){
    controller c("greenhouse.db");
    EXPECT_FALSE(c.checkPassword("admin", "neAdmin"));
}

TEST(createUserTest, TestPositive){
    controller c("greenhouse.db");
    EXPECT_TRUE(c.createUser("UniqueUser", "123456789"));
}

TEST(createUserTest, TestNegative){
    controller c("greenhouse.db");
    EXPECT_FALSE(c.createUser("admin", "admin"));
}