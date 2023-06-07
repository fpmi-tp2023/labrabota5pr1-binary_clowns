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

TEST(createUserTest, TestPositiveWithDeleting){
    controller c("greenhouse.db");
    EXPECT_TRUE(c.createUser("UniqueUser", "123456789"));
    EXPECT_TRUE(c.deleteOperatin("Customer", "Login = 'UniqueUser'"));
    EXPECT_TRUE(c.updateSQLSequence("Customer", "ID"));
}

TEST(createUserTest, TestNegative){
    controller c("greenhouse.db");
    EXPECT_FALSE(c.createUser("admin", "admin"));
}

TEST(md5Test, TestPositive){
    controller c("greenhouse.db");
    EXPECT_EQ(c.md5("123456"), "e10adc3949ba59abbe56e057f20f883e");
}

TEST(TestPasswordMatch, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.isAdmin("admin"));
    EXPECT_FALSE(c.isAdmin("Vantuzz"));
}