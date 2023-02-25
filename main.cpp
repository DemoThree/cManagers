#include <iostream>
#include <WinSock.h> //一定要包含这个
#include <time.h>
#include <string.h>
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"
using namespace std;
// #pragma comment(lib, "libmysql")
extern MYSQL my_sql;
extern char *service_name, *danpan_id, *man, *price, *time;

int main()
{
    int ting;

    // 定义一个mysql对象
    mysql_init(&my_sql); // 获得或初始化一个MYSQL结构。
    if (!mysql_real_connect(&my_sql, "localhost", "root", "root", "abc", 3306, NULL, 0))
    {
        cout << "error" << endl;
    }
    else
    {
        cout << "数据库连接:success" << endl;
        // 设置编码格式
        printf("设置编码格式\n");
        mysql_set_character_set(&my_sql, "utf-8");
        printf("欢迎进入索赔管理系统！！\n");
        printf("请输入一个数字  1:添加2:查询3:删除4:查询 输入：\n"); // 让用户输入一个数字
        scanf("%d", &ting);
        switch (ting)
        {

        case 1:
            printf("1.添加\n");
            insertDate();
            break;
        case 2:
            printf("Case 2\n");
            break;
        default:
            printf("Default case\n");
        }

        insertDate();
    }
    // 4. 关闭MySQL
    // free(result);
    printf("数据库关闭");
    mysql_close(&my_sql);
    return 0;
}

void insertDate()

{

    printf("insert:");

    string sql = "insert into suopei values(null,\'\',198791,  \' 王五\' , \'42352\', \'2020-06-12\')";
    int res = mysql_query(&my_sql, sql.c_str());
    if (res == 0)
    {
        cout << "insert succeeded" << endl;
    }
    else
    {
        cout << "insert false" << endl;
    }
}