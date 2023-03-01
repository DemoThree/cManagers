#include <iostream>
#include <WinSock.h> //一定要包含这个
#include <time.h>
#include <string.h>
#include "windows.h" //关键导包
#include <cstdio>
#include <graphics.h>
#include <conio.h>

// #include "Gui.cpp"
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
FILE *fp2 = NULL;
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
        case 5:

            printf("5.GUI界面\n");
            Page();
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
        cout << "是否导入excel:y/n" << endl;
        cin >> s;
        if (/* condition */ s == "y")
        {
            printf("导入中....\n");
            Sleep(1000); // 休眠100毫秒
            /* code */
            fp = fopen("test.txt", "w");
            fp2 = fopen("test.xls", "w");
            // 没有指定文件路径，则默认为当前工作目录

            for (int i = 0; i < colnum; ++i)
            {
                printf("%s", column[i]);
                fprintf(fp, "%s", column[i]);
                fprintf(fp2, "%s\t", column[i]);

                for (int z = 0; z < 21 - strlen(column[i]); z++)
                {
                    /* code */
                    fprintf(fp, " ");
                }
            }
            fprintf(fp, "\n");
            fprintf(fp2, "\n");
            string sql = "select * from suopei";
            mysql_query(&my_sql, sql.c_str());
            // 获取查询结果集
            res = mysql_store_result(&my_sql);
            row = mysql_num_rows(res);
            colnum = mysql_num_fields(res);
            for (int i = 1; i < row + 1; i++)
            {
                // 一行数据
                result_row = mysql_fetch_row(res);
                for (int j = 0; j < colnum; j++)
                {
                    fprintf(fp, "%s", result_row[j]);
                    fprintf(fp2, "%s\t", result_row[j]);
                    for (int z = 0; z < 21 - strlen(result_row[j]); z++)
                    {
                        /* code */
                        fprintf(fp, " ");
                    }
                }
                fprintf(fp, "\n");
                fprintf(fp2, "\n");
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
    fclose(fp2);
    mysql_free_result(res); // 释放结果集
}
void Page()
{
    // 窗口大小
    initgraph(760, 760);
    // 鼠标操作1
    MOUSEMSG m1;

    cleardevice();
    IMAGE picture1;
    loadimage(&picture1, "./firstbc.jpg", 760, 760);
    putimage(0, 0, &picture1);
    setbkmode(TRANSPARENT);

    setfillcolor(GREEN);

    // 大标题
    char FirstTitle[20] = {"汽车索赔管理系统"};
    settextstyle(60, 0, "黑体");
    outtextxy(150, 100, FirstTitle);

    // 三个选项的背景
    fillrectangle(230, 445, 560, 490);
    fillrectangle(230, 505, 560, 550);
    fillrectangle(230, 565, 560, 610);

    setbkmode(TRANSPARENT);

    // 三个选项的文字
    settextstyle(40, 0, "黑体");

    // 三个选项
    char FirstSelect1[20] = {"管理员操作界面"};
    char FirstSelect2[20] = {"普通用户操作界面"};
    char FirstSelect3[20] = {"退出程序"};
    outtextxy(240, 450, FirstSelect1);
    outtextxy(240, 510, FirstSelect2);
    outtextxy(240, 570, FirstSelect3);
    // 进入主界面选项操作界面
    while (1)
    {
        m1 = GetMouseMsg();                                           // 获取鼠标操作
        if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490) // 管理员界面
        {
            setlinecolor(RED);
            rectangle(230, 445, 560, 490);
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                // 加入管理员登录
                // AdminSignIn();
            }
        }
        else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550) // 普通用户界面
        {
            setlinecolor(RED);
            rectangle(230, 505, 560, 550);
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                cleardevice();
                        }
        }
        else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610) // 退出
        {
            setlinecolor(RED);
            rectangle(230, 565, 560, 610);
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                exit(0);
            }
        }
        // 鼠标不在上面悬停
        else
        {
            setlinecolor(WHITE);
            rectangle(230, 445, 560, 490);
            rectangle(230, 505, 560, 550);
            rectangle(230, 565, 560, 610);
        }
    }
}