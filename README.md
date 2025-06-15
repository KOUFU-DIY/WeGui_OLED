企鹅交流群787475855

为节省接线问题, 本源码配套有开发板, 已开源, Allegro格式, 已打包GERBER, 可直接发出打样, 在资料文件夹里获取
![image](https://github.com/user-attachments/assets/c0a6d7dc-1bec-4e88-a16e-cd656e62bb61)

接线参考:

SPI屏幕:

CS->A6
DC->B11
RES->B10
SDA->A7
SCL->A5

IIC屏幕:

SDA->B11
SCL->B10
        
按键(接地有效)

OK->A0
BACK->C15
UP->B13
DOWN->B14
LEFT->B15
RIGHT->B12

电位器(用于ADC参数展示DEMO)

RADC->A1

本程序使用了大量模拟io驱动, 暂不支持任意调换编译器版本, 请使用ARMV5编译器(默认)

本源码使用了大量的"UTF8"支持多国语言的编码, 为正常使用本程序, 需要对keil进行设置

1.Edit->Configuration->Encoding->"Encod in UTF8"

2.Project -> Oprions for Target-> C/C++ -> Misc Contiols -> 填入"--locale=english"

![image](https://github.com/user-attachments/assets/5462ea01-7397-4de6-859d-96fe33bee2a7)
![image](https://github.com/user-attachments/assets/87ab057c-e279-49fd-b616-b62acc55b7df)


