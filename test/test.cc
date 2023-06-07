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

TEST(updateOperationTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> setColumns;
    setColumns.push_back("Admin = '1'");
    EXPECT_TRUE(c.updateOperation("Customer", setColumns, "Login = 'admin'"));
}

TEST(getColumnsNamesTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> columns;
    columns.push_back("ID");
    columns.push_back("Name");
    EXPECT_EQ(c.getColumnsNames("Composition"), columns);
}

TEST(getPrymaryKeysTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> columns;
    columns.push_back("ID");
    EXPECT_EQ(c.getPrymaryKeys("Composition"), columns);
}

TEST(lookInVectorTest, TestWhole)
{
    controller c("greenhouse.db");
    std::vector<std::string> columns;
    columns.push_back("ID");
    columns.push_back("Name");
    EXPECT_TRUE(c.lookInVector("ID", columns));
    EXPECT_FALSE(c.lookInVector("info", columns));
}

TEST(insertOperationTest, TestPositiveWithDeleting)
{
    controller c("greenhouse.db");
    std::vector<std::string> columns;
    columns.push_back("Name");
    std::vector<std::string> values;
    values.push_back("NewComp");
    EXPECT_TRUE(c.insertOperation("Composition", values, columns));
    EXPECT_TRUE(c.deleteOperatin("Composition", "Name = 'NewComp'"));
    EXPECT_TRUE(c.updateSQLSequence("Composition", "ID"));
}

TEST(deleteUserTest, TestPositiveWithDeleting)
{
    controller c("greenhouse.db");
    EXPECT_TRUE(c.createUser("NewUser", "NewPassword"));
    EXPECT_TRUE(c.deleteUser("NewUser"));
    EXPECT_TRUE(c.updateSQLSequence("Customer", "ID"));
}

TEST(mostPopularComposeTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> answer;
    answer.push_back("FlowerID : 21\nName : Narcissus\nFlowersAmount : 15\nPrice : 9.99\nCompositionID : 2\nCompositionName : Golden Fields\n");
    answer.push_back("FlowerID : 22\nName : Petunia\nFlowersAmount : 11\nPrice : 4.44\nCompositionID : 2\nCompositionName : Golden Fields\n");
    answer.push_back("FlowerID : 23\nName : Poppy\nFlowersAmount : 17\nPrice : 3.33\nCompositionID : 2\nCompositionName : Golden Fields\n");
    EXPECT_EQ(c.mostPopularCompose(), answer);
}

TEST(urgentOrdersTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> answer;
    answer.push_back("Amount : 4\nDays : 1\n");
    answer.push_back("Amount : 3\nDays : 2\n");
    answer.push_back("Amount : 2\nDays : 3\n");
    answer.push_back("Amount : 1\nDays : 4\n");
    EXPECT_EQ(c.urgentOrders(), answer);
}

TEST(flowersInfoTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> answer;
    answer.push_back("Kind : Annual\nTotalAmount : 302\n");
    answer.push_back("Kind : Biennial\nTotalAmount : 26\n");
    answer.push_back("Kind : Bulb\nTotalAmount : 211\n");
    answer.push_back("Kind : Herb\nTotalAmount : 9\n");
    answer.push_back("Kind : Perennial\nTotalAmount : 46\n");
    answer.push_back("Kind : Shrub\nTotalAmount : 57\n");
    EXPECT_EQ(c.flowersInfo("2022-03-12","2023-06-08"), answer);
}

TEST(soldComposeTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> answer;
    answer.push_back("CompositionID : 1\nName : Summer Sunset\nAmount : 4\nCompPrice : 162.32\nTotalPrice : 649.28\n");
    answer.push_back("CompositionID : 2\nName : Golden Fields\nAmount : 4\nCompPrice : 255.3\nTotalPrice : 1021.2\n");
    answer.push_back("CompositionID : 3\nName : Meadow Breeze\nAmount : 2\nCompPrice : 123.85\nTotalPrice : 247.7\n");
    answer.push_back("CompositionID : 4\nName : Autumn Harvest\nAmount : 1\nCompPrice : 161.31\nTotalPrice : 161.31\n");
    answer.push_back("CompositionID : 6\nName : Snowy Mountains\nAmount : 1\nCompPrice : 348.85\nTotalPrice : 348.85\n");
    answer.push_back("CompositionID : 8\nName : Garden Party\nAmount : 3\nCompPrice : 209.31\nTotalPrice : 627.93\n");
    answer.push_back("CompositionID : 9\nName : Butterfly Garden\nAmount : 3\nCompPrice : 84.12\nTotalPrice : 252.36\n");
    answer.push_back("CompositionID : 10\nName : Rose Garden\nAmount : 3\nCompPrice : 235.14\nTotalPrice : 705.42\n");
    answer.push_back("CompositionID : 11\nName : Tropical Paradise\nAmount : 1\nCompPrice : 232.1\nTotalPrice : 232.1\n");
    answer.push_back("CompositionID : 12\nName : Sunny Day\nAmount : 2\nCompPrice : 102.36\nTotalPrice : 204.72\n");
    answer.push_back("CompositionID : 15\nName : Wildflower Fields\nAmount : 1\nCompPrice : 230.61\nTotalPrice : 230.61\n");
    EXPECT_EQ(c.soldCompose(), answer);
}

TEST(ordersByDateTest, TestPositive)
{
    controller c("greenhouse.db");
    std::vector<std::string> answer;
    answer.push_back("ID : 1\nAcceptance : 2023-01-02\nCompletion : 2023-01-04\nCustomerID : 1\n");
    EXPECT_EQ(c.ordersByDate("2023-01-02"), answer);
}
