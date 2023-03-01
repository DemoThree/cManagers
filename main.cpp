#include <iostream>
#include <WinSock.h> //一定要包含这个
#include <time.h>
#include <string.h>
#include "windows.h" //关键导包
#include <cstdio>
#include <graphics.h>
#include <conio.h>
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"
using namespace std;
// #pragma comment(lib, "libmysql")

void insertDate();

void deleteDate();

void updateDate();

void queryDate();

void Menu();

// 绘制菜单

void Page();

void login();

char *timer(char str[]);

// 读写文操作
void files();

int token = 0;

// 初始化文件指针

FILE *fp = NULL;

string s;

// 登陆时的账号

string username;
// 登陆时的密码
string password;
time_t timep;
MYSQL my_sql;
MYSQL_RES *res;                            // 查询结果集
MYSQL_ROW row;                             // 二维数组，存放数据
MYSQL_ROW result_row; /*按行返回查询信息*/ // typedef char** MYSQL_ROW
char column[30][40];
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
void login()
{

    cout << "请输入账号:" << endl;
    cin >> username;
    cout << "请输入密码:" << endl;
    cin >> password;
    token += 1;
    Menu();
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
    if (token == 0)
    {
        /* code */
        cout << "初次登录请输入密码" << endl;
        login();
    }

    int ting;
    // 定义一个mysql对象
    mysql_init(&my_sql); // 获得或初始化一个MYSQL结构。
    if (!mysql_real_connect(&my_sql, "localhost", username.c_str(), password.c_str(), "abc", 3306, NULL, 0))
    {
        if (token == 0)
        {
            /* code */
            cout << "初次登录请输入密码" << endl;
            login();
        }
        else
        {
            cout << "账号或者密码错误" << endl;
            if (token >= 3)
            {
                /* code */
                cout << "错误次数太多啦休眠3秒" << endl;
                Sleep(3000);
            }

            /* code */

            login();
        }
    }
    else
    {

        cout << "数据库连接:success" << endl;
        // 设置编码格式
        printf("设置编码格式\n");
        mysql_set_character_set(&my_sql, "GBK");

        printf("欢迎进入索赔管理系统！！\n");
        cout << "账号：" + username << endl;
        printf("请输入一个数字  1:添加2:更改3:删除4:查询\n"); // 让用户输入一个数字
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
        row = mysql_num_rows(res);
        colnum = mysql_num_fields(res);
        // 执行输出结果,从第二行开始循环（第一行是字段名）
        // 6.保存字段

        for (int i = 0; i < colnum; ++i)
        {
            strcpy(column[i], mysql_fetch_field(res)->name);
            printf("%s", column[i]);
            for (int j = 0; j < 21 - strlen(column[i]); j++)
            {
                /* code */
                printf(" ");
            }
        }
        printf("\n");

        for (int i = 1; i < row + 1; i++)
        {
            // 一行数据
            result_row = mysql_fetch_row(res);
            for (int j = 0; j < colnum; j++)
            {
                printf("%s", result_row[j]);
                for (int z = 0; z < 21 - strlen(result_row[j]); z++)
                {
                    /* code */
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("是否导出数据到excel? y/n:");
        cin >> s;
        if (/* condition */ s == "y")
        {
            printf("导入中....\n");
            Sleep(1000); // 休眠100毫秒
            /* code */
            fp = fopen("test.txt", "w");
            // 没有指定文件路径，则默认为当前工作目录

            for (int i = 0; i < colnum; ++i)
            {
                printf("%s", column[i]);
                fprintf(fp, "%s\t", column[i]);
            }

            cout << "导入成功！！！！！" << endl;
        }
        else
        {
            printf("no\n");
        }
    }
    else
    {
        printf("未获取到数据：%s \n", mysql_error(&my_sql));
    }

    // fp 为文件指针，关闭文件代码如下：
    fclose(fp);

    mysql_free_result(res); // 释放结果集
}
