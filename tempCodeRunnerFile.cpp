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
        outtextxy(0, 100 + 40 * q, head[q - 1].id);

        // service_name
        outtextxy(50, 100 + 40 * q, head[q - 1].service_name);

        // danpan_id
        outtextxy(250, 100 + 40 * q, head[q - 1].danpan_id);

        // man
        outtextxy(400, 100 + 40 * q, head[q - 1].man);
        // price
        outtextxy(500, 100 + 40 * q, head[q - 1].price);
        // time
        outtextxy(600, 100 + 40 * q, head[q - 1].time);