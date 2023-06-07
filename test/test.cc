#include <gtest/gtest.h>
#include "controller.h"
#include <sstream>

TEST(CheckLoginTest, TestPositive)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkLogin("admin"));
}

TEST(CheckLoginTest, TestNegative)
{
    controller c("greenhouse.db");
    EXPECT_FALSE(c.checkLogin("ADMIN"));
}

TEST(CheckPasswordTest, TestPositive)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkPassword("admin", "admin"));
}

TEST(CheckPasswordTest, TestNegative)
{
    controller c("greenhouse.db");
    EXPECT_FALSE(c.checkPassword("admin", "neAdmin"));
}

TEST(createUserTest, TestPositiveWithDeleting)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.createUser("UniqueUser", "123456789"));
    EXPECT_TRUE(c.deleteOperatin("Customer", "Login = 'UniqueUser'"));
    EXPECT_TRUE(c.updateSQLSequence("Customer", "ID"));
}

TEST(createUserTest, TestNegative)
{
    controller c("greenhouse.db");
    EXPECT_FALSE(c.createUser("admin", "admin"));
}

TEST(md5Test, TestPositive)
{
    controller c("greenhouse.db");
    EXPECT_EQ(c.md5("123456"), "e10adc3949ba59abbe56e057f20f883e");
}

TEST(isAdminTest, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.isAdmin("admin"));
    EXPECT_FALSE(c.isAdmin("Vantuzz"));
}

TEST(getFullTableTest, TestPositive)
{
    controller c("greenhouse.db");
    EXPECT_EQ(c.getFullTable("Customer"), "ID : 0\nLogin : admin\nPassword : 21232f297a57a5a743894a0e4a801fc3\nAdmin : 1\n\n"
                                          "ID : 1\nLogin : Vantuzz\nPassword : 81dc9bdb52d04dc20036dbd8313ed055\nAdmin : 0\n\n"
                                          "ID : 2\nLogin : abc\nPassword : 900150983cd24fb0d6963f7d28e17f72\nAdmin : 0\n\n"
                                          "ID : 3\nLogin : nikita\nPassword : 81dc9bdb52d04dc20036dbd8313ed055\nAdmin : 0\n\n");
}

TEST(checkTableTest, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkTable("Customer"));
    EXPECT_FALSE(c.checkTable("UnCustomer"));
}

TEST(checkColumnTest, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.checkColumn("Customer", "ID"));
    EXPECT_FALSE(c.checkColumn("Customer", "Surname"));
}

TEST(getNumOfColumnsTest, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_EQ(c.getNumOfColumns("Customer"), 4);
}

TEST(getNumOfRowsTest, TestWhole)
{
    controller c("greenhouse.db");
    EXPECT_EQ(c.getNumOfRows("Flower"), 25);
}

TEST(updateOperationTest, TestWhole)
{
    controller c("greenhouse.db");
    std::vector<std::string> setColumns;
    setColumns.push_back("Admin = '1'");
    EXPECT_TRUE(c.updateOperation("Customer", setColumns, "Login = 'admin'"));
}