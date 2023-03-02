# ClaimsMmanagement

#### 介绍

一个基于 c++的索赔管理系统
数据库 mysql
前端页面 GUI

#### 软件架构

软件架构说明

#### 安装教程

#### 使用说明

1.本项目使用 vscode 开发
因此注意在导入 mysql 的依赖时注意导入文件路径
如果是使用 code Runner 插件右击运行
可参考配置以下 setting.json
"code-runner.executorMap"：{
"cpp": "cd $dir && g++ $fileName -I \"C:/Program Files/MySQL/MySQL Server 5.7/include\" -L \"C:/Program Files/MySQL/MySQL Server 5.7/lib\" -l mysql  -o  $fileNameWithoutExt && $dir$fileNameWithoutExt",
"objective-c": "cd $dir && gcc -framework Cocoa $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",}
以上配置为重点部分(文件路径请写自己 mysql 安装路径下的文件)其他省略
注意由于本项目是 c++因此 main.cpp 后缀是.cpp 结尾
因此请注意 c++语法
taks.json 配置可参考我的
配置

#### 参与贡献

DemoTreeIdea 肖灿

#### 特技
