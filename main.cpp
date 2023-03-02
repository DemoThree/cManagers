#include <iostream>
#include <WinSock.h> //一定要包含这个
#include <time.h>
#include <string.h>
#include "windows.h" //关键导包
#include <cstdio>
#include <graphics.h>
#include <conio.h>

#include <codecvt>
// #include "Gui.cpp"
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"

using namespace std;
// #pragma comment(lib, "libmysql")
// 显示全部数据的页面跳转标识
int FlagAI = -1;
// 查询找到页面跳转标识
int FlagFPT = -1;
int Nums = 0;
// char header[3] = {0xef, 0xbb, 0xbf};
void insertDate();

void deleteDate();

void updateDate();

void queryDate();

void Menu();

// 绘制菜单
void AdminPage();
void Page();
void ShowAllInfor();
void login();
void S1mplePrint();
char *timer(char str[]);

// 读写文操作
void files();
// 文件读取数据到链表
struct suopei2 *loadFile();
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
    char time[22];
    struct suopei *next;
};

struct suopei2 *head;
struct suopei2
{
    char id[20];
    // 数据库字段
    char service_name[40];
    char danpan_id[40];
    char man[40];
    char price[40];
    char time[42];
    struct suopei2 *next;
};

void login()
{

    cout << "请输入账号：" << endl;
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
    cout << "sql:" + sql << endl;

    int res = mysql_query(&my_sql, sql.c_str());
    if (res == 0)
    {
        cout << "update succeeded" << endl;
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
            fp2 = fopen("test.csv", "w");
            // 没有指定文件路径，则默认为当前工作目录

            for (int i = 0; i < colnum; ++i)
            {
                printf("%s", column[i]);
                fprintf(fp, "%s", column[i]);
                fprintf(fp2, "%s", column[i]);

                for (int z = 0; z < 21 - strlen(column[i]); z++)
                {
                    /* code */
                    fprintf(fp, " ");
                }
                if (i + 1 < colnum)
                {
                    /* code */
                    fprintf(fp2, ",");
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
                    fprintf(fp2, "%s", result_row[j]);
                    for (int z = 0; z < 21 - strlen(result_row[j]); z++)
                    {
                        /* code */
                        fprintf(fp, " ");
                    }
                    if (i + 1 < colnum)
                    {
                        /* code */
                        fprintf(fp2, ",");
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
    char FirstTitle[50] = {"汽车索赔管理系统"};
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
    char FirstSelect1[40] = {"管理员操作界面"};

    char FirstSelect2[40] = {"普通用户操作界面"};

    char FirstSelect3[40] = {"退出程序"};

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
                AdminPage();
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

// 管理员界面
void AdminPage()
{
    initgraph(760, 760);
    // 先清除一下
    cleardevice();
    // 定义第二个鼠标操作
    MOUSEMSG m2;

    cleardevice();
    IMAGE picture1;
    loadimage(&picture1, "./firstbc.jpg", 760, 760);
    putimage(0, 0, &picture1);
    setfillcolor(GREEN);
    setbkmode(TRANSPARENT);

    char SecondTitle1[5] = {"管"};
    char SecondTitle2[5] = {"理"};
    char SecondTitle3[5] = {"员"};
    char SecondTitle4[5] = {"操"};
    char SecondTitle5[5] = {"作"};
    char SecondTitle6[5] = {"界"};
    char SecondTitle7[5] = {"面"};

    settextstyle(50, 0, "黑体");
    outtextxy(50, 150, SecondTitle1);
    outtextxy(50, 210, SecondTitle2);
    outtextxy(50, 270, SecondTitle3);
    outtextxy(50, 330, SecondTitle4);
    outtextxy(50, 390, SecondTitle5);
    outtextxy(50, 450, SecondTitle6);
    outtextxy(50, 510, SecondTitle7);

    setbkmode(TRANSPARENT);

    // 三个选项的背景
    fillrectangle(230, 240, 560, 285);
    fillrectangle(230, 370, 560, 415);
    fillrectangle(230, 500, 560, 545);

    setbkmode(TRANSPARENT);

    // 三个选项的文字
    settextstyle(40, 0, "黑体");

    // 三个选项
    char SecondSelect1[20] = {"显示所有数据"};
    char SecondSelect2[20] = {"增删查改数据"};
    char SecondSelect3[20] = {"返回"};

    outtextxy(270, 240, SecondSelect1);
    outtextxy(270, 370, SecondSelect2);
    outtextxy(350, 500, SecondSelect3);

    // 进入主界面选项操作界面
    while (1)
    {
        m2 = GetMouseMsg(); // 获取鼠标操作
        if (m2.x >= 230 && m2.x <= 560 && m2.y >= 240 && m2.y <= 285)
        {
            setlinecolor(RED);
            rectangle(230, 240, 560, 285);
            if (m2.uMsg == WM_LBUTTONDOWN)
            {
                // 显示所有数据
                FlagAI = 1;
                cleardevice();
                ShowAllInfor();
            }
        }
        else if (m2.x >= 230 && m2.x <= 560 && m2.y >= 370 && m2.y <= 415)
        {
            setlinecolor(RED);
            rectangle(230, 370, 560, 415);
            if (m2.uMsg == WM_LBUTTONDOWN)
            {
                // 增删查改界面
                cleardevice();
                // AdDeSeMoPage();
            }
        }
        else if (m2.x >= 230 && m2.x <= 560 && m2.y >= 500 && m2.y <= 545)
        {
            setlinecolor(RED);
            rectangle(230, 500, 560, 545);
            if (m2.uMsg == WM_LBUTTONDOWN)
            {
                // 返回
                cleardevice();
                Page();
            }
        }
        // 鼠标不在上面悬停
        else
        {
            setlinecolor(WHITE);
            rectangle(230, 240, 560, 285);
            rectangle(230, 370, 560, 415);
            rectangle(230, 500, 560, 545);
        }
    }
}
// 显示所有数据-通用
void ShowAllInfor()
{

    // 鼠标操作
    MOUSEMSG SA;
    initgraph(860, 760);
    // 默认只是打印数据到屏幕上
    cleardevice();
    IMAGE picture2;
    loadimage(&picture2, "./secondbc.jpg", 860, 760);
    putimage(0, 0, &picture2);

    setfillcolor(GREEN);
    setbkmode(TRANSPARENT);

    // fillrectangle(690, 90, 850, 140);
    // fillrectangle(690, 190, 850, 240);
    fillrectangle(690, 290, 850, 340);
    fillrectangle(690, 390, 850, 440);
    fillrectangle(690, 590, 850, 640);

    // 表头文字部分
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "黑体");
    // outtextxy(0, 0, "id");
    // outtextxy(50, 0, "servise_name");
    // outtextxy(250, 0, "danpan_id");
    // outtextxy(400, 0, "man");
    // outtextxy(500, 0, "price");
    // outtextxy(600, 0, "time");

    outtextxy(700, 300, "排序方式");
    outtextxy(700, 400, "按金额排序");

    outtextxy(740, 600, "返回");

    S1mplePrint();

    while (1)
    {
        SA = GetMouseMsg();

        if (SA.x >= 690 && SA.x <= 850 && SA.y >= 390 && SA.y <= 440)
        {

            setlinecolor(RED);
            rectangle(690, 390, 850, 440);
            if (SA.uMsg == WM_LBUTTONDOWN)
            {
                // SortAcSumScore();
                // 刷新重新载入
                ShowAllInfor();
            }
        }
        else if (SA.x >= 690 && SA.x <= 850 && SA.y >= 590 && SA.y <= 640)
        {
            // 返回
            setlinecolor(RED);
            rectangle(690, 590, 850, 640);
            if (SA.uMsg == WM_LBUTTONDOWN)
            {
                cleardevice();
                // 判断从哪个窗口点进来的
                if (FlagAI == 1)
                {
                    AdminPage();
                }
                else if (FlagAI == -1)
                {
                    // CommonUserPage();
                }
            }
        }
        else
        {
            setlinecolor(WHITE);
            // rectangle(690, 90, 850, 140);
            // rectangle(690, 190, 850, 240);
            rectangle(690, 290, 850, 340);
            rectangle(690, 390, 850, 440);
            rectangle(690, 590, 850, 640);
        }
    }
}
// 读取文件内信息
struct suopei2 *loadFile()
{
    int i = 0;
    char id[20];

    // 数据库字段
    char service_name[40];
    char danpan_id[40];
    char man[40];
    char price[40];
    char time[40];
    FILE *fp;
    struct suopei2 *p1 = NULL;
    struct suopei2 *p2 = NULL;
    struct suopei2 *head = NULL;
    // 判断是否有文件

    if ((fp = fopen("test.csv", "r")) != NULL)
    {

        char row[80];
        char *tokens;
        int x = 1;
        // fget从csv文件读取一行
        while (fgets(row, 80, fp) != NULL)
        {
            p1 = (struct suopei2 *)malloc(sizeof(struct suopei2));
            p1->next = NULL;
            x = 1;

            // printf("Row: %s", row);
            // 通过“，”分割数据
            tokens = strtok(row, ",");

            while (tokens != NULL)
            {
                // printf("Token: %s%d\n", tokens, x);
                switch (x)
                {
                case 1:

                    strcpy(p1->id, tokens);
                    break;
                case 2:
                    strcpy(p1->service_name, tokens);
                    break;
                case 3:
                    strcpy(p1->danpan_id, tokens);
                    ;

                    break;
                case 4:
                    strcpy(p1->man, tokens);

                    break;
                case 5:
                    strcpy(p1->price, tokens);

                    break;
                case 6:
                    strcpy(p1->time, tokens);

                    break;
                default:
                    printf("%d", x);
                }
                tokens = strtok(NULL, ",");
                x++;
            }

            if (i == 0)
            {
                head = p1;
                p2 = p1;
                i = 1;
            }
            else
            {
                p2->next = p1;
                p2 = p1;
            }
            Nums++;
        }

        fclose(fp);
    }

    return head;
}

void S1mplePrint()
{

    head = loadFile();
    struct suopei2 *p3 = head;
    // while (p3 != NULL)
    // {
    //     printf("%s\t%s\n", p3->id, p3->service_name);
    //     p3 = p3->next;
    // }

    // // 如果为空就不往下执行;/
    if (Nums == 0)
    {

        settextstyle(50, 0, "黑体");
        outtextxy(200, 200, "当前记录为空!");
        return;
    }
    for (int q = 1; q <= Nums; q++)
    {

        // 顺序
        settextstyle(30, 0, "黑体");

        // id
        outtextxy(0, 100 + 40 * q, p3->id);

        // service_name.
        outtextxy(50, 100 + 40 * q, p3->service_name);

        // danpan_id
        outtextxy(250, 100 + 40 * q, p3->danpan_id);

        // man
        outtextxy(400, 100 + 40 * q, p3->man);
        // price
        outtextxy(500, 100 + 40 * q, p3->price);
        // time
        outtextxy(600, 100 + 40 * q, p3->time);
        p3 = p3->next;
        // if (strlen(StuArry[q - 1].s_Name) != 0)
        // {
        //     outtextxy(0, 40 + 40 * q, Nums);
        //     char SuSo[20];
        //     sprintf(SuSo, "%.2f", StuArry[q - 1].s_SumScore); // 小数点后保留两位
        //     outtextxy(600, 40 + 40 * q, SuSo);
        // }
    }
}
