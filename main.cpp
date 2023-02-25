#include <iostream>
#include <WinSock.h> //一定要包含这个
// #include <time.h>
#include <string.h>
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"
using namespace std;
// #pragma comment(lib, "libmysql")
void insertDate();
MYSQL my_sql;
// char *service_name, *danpan_id, *man, *price, *time;
struct suopei
{
    char service_name[20];
    char danpan_id[20];
    char man[20];
    char price[20];
    char time[20];
};

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
    }
    // 4. 关闭MySQL
    // free(result);
    printf("数据库关闭");
    mysql_close(&my_sql);
    return 0;
}

void insertDate()

{

    printf("insert:\n");
    struct suopei sp;
    // 1
    printf("服务站名称:");
    scanf("%s", sp.service_name);
    printf("\n");
    printf("底盘号:");
    scanf("%s", sp.danpan_id);
    printf("\n");
    printf("审核人:");
    scanf("%s", sp.man);
    printf("\n");
    printf("索赔金额:");
    scanf("%s", sp.price);
    printf("\n");
    printf("索赔日期:");
    scanf("%s", sp.time);
    printf("服务站名称:%s 底盘号:%s 审核人:%s 索赔金额:%s 索赔日期:%s\n", sp.service_name, sp.danpan_id, sp.man, sp.price, sp.time);
    string s(sp.service_name);
    cout << s << endl;
    string sql = "insert into suopei values(null,";
    sql = sql + "'" + s + "',";
    s = sp.danpan_id;
    sql = sql + "'" + s + "',";
    s = sp.man;
    sql = sql + "'" + s + "',";
    s = sp.price;
    sql = sql + "'" + s + "',";
    s = sp.time;
    sql = sql + "'" + s + "'";
    sql += ")";
    cout << sql << endl;
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