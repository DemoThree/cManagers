#include <iostream>
#include <WinSock.h> //一定要包含这个
#include <time.h>
#include <string.h>
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"
using namespace std;
// #pragma comment(lib, "libmysql")
void insertDate();

void deleteDate();

void updateDate();

void queryDate();

void Menu();

char *timer(char str[]);

string s;

time_t timep;

MYSQL my_sql;
MYSQL_RES *res;       // 查询结果集
MYSQL_ROW row;        // 二维数组，存放数据
MYSQL_ROW result_row; /*按行返回查询信息*/
// char *service_name, *danpan_id, *man, *price, *time;
// 时间结构体
// struct tm
// {
//     int tm_sec;   // 秒（0~61）
//     int tm_min;   // 分（0~59）
//     int tm_hour;  // 小时（0~23)
//     int tm_mday;  // 日(1~31)
//     int tm_mon;   // 月份(0~11)
//     int tm_year;  // 年，从1970年至今经过的年数
//     int tm_wday;  // 星期:(0~6)
//     int tm_yday;  // 天数(0~365)
//     int tm_isdst; // 夏令时 daylight-saving time
// };

struct suopei
{
    int id;
    // 数据库字段
    char service_name[20];
    char danpan_id[20];
    char man[20];
    char price[20];
    char time[20];
};

int main(int argc, char *argv[])
{
    Menu();

    return 0;
};

char *timer(char str[])
{
    time(&timep);

    struct tm *p;
    p = gmtime(&timep);

    snprintf(str, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);

    printf("\n%s\n", str);
    return str;
};

void Menu()
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
        mysql_set_character_set(&my_sql, "GBK");
        printf("欢迎进入索赔管理系统！！\n");
        printf("请输入一个数字  1:添加2:更改3:删除4:查询 输入：\n"); // 让用户输入一个数字
        scanf("%d", &ting);
        switch (ting)
        {

        case 1:
            printf("1.添加\n");
            insertDate();
            Menu();
            break;
        case 2:
            printf("2.更改\n");
            updateDate();
            Menu();
            break;
        case 3:
            printf("3.删除\n");
            deleteDate();
            Menu();
            break;
        case 4:
            printf("4.查询\n");
            queryDate();
            Menu();
            break;
        default:
            printf("Default case\n");
        }
    }
    // 4. 关闭MySQL
    // free(result);
    printf("数据库关闭");
    mysql_close(&my_sql);
};
;
void insertDate()

{
    printf("insert:\n");
    struct suopei sp;
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
    timer(sp.time);
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
void deleteDate()
{
    printf("delete:\n");
    printf("根据id删除,请输入对应的编号id:\n");
    string sql = "DELETE FROM suopei WHERE id = ";
    cin >> s;
    cout << s << endl;
    sql = sql + "'" + s + "'";
    cout << sql << endl;
    int res = mysql_query(&my_sql, sql.c_str());
    if (res == 0)
    {
        cout << "delete succeeded" << endl;
    }
    else
    {
        cout << "delete false" + mysql_errno(&my_sql) << endl;
    }
}
void updateDate()
{
    printf("update:\n");
    printf("请输入需要修改的字段:\n");
    string sql = "update suopei set ";
    cin >> s;
    sql = sql + s + "=";
    printf("请输入需要修改的值:\n");
    cin >> s;
    cout << "输入的值为：" + s << endl;
    sql = sql + "'" + s + "'";
    printf("请输入修改的id数据具体到某行:\n");
    cin >> s;
    cout << "输入的值为：" + s << endl;
    sql = sql + " where id = '" + s + "'";
    cout << sql << endl;

    int res = mysql_query(&my_sql, sql.c_str());
    if (res == 0)
    {
        cout << "delete succeeded" << endl;
    }
    else
    {
        cout << "delete false" + mysql_errno(&my_sql) << endl;
    }
}
void queryDate()
{
    int row, colnum;
    printf("query:\n");
    string sql = "select * from suopei";

    if (mysql_query(&my_sql, sql.c_str()))
    {
        cout << "query false" + mysql_errno(&my_sql) << endl;
    }
    else
    {

        cout << "query succeeded" << endl;
    }
    // 获取查询结果集
    res = mysql_store_result(&my_sql);
    if (res)
    {
        printf("获取到数据\n");
    }
    else
    {
        printf("未获取到数据：%s \n", mysql_error(&my_sql));
    }
    // 打印获取到的数据
    // while (row = mysql_fetch_row(res))
    // {
    //     // printf("%s\t%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    //     cout << row << endl;
    // }
    // 释放资源
    // 获取行数，列数
    row = mysql_num_rows(res);
    colnum = mysql_num_fields(res);
    // 执行输出结果,从第二行开始循环（第一行是字段名）
    for (int i = 1; i < row + 1; i++)
    {
        // 一行数据
        result_row = mysql_fetch_row(res);
        for (int j = 0; j < colnum; j++)
        {
            printf("\t%s", result_row[j]);
        }
        printf("\n");
    }
    mysql_free_result(res); // 释放结果集
}
