CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #Cmake最低版本需求,不加入此行会受到警告信息

PROJECT(BattleShip)  #项目名称

AUX_SOURCE_DIRECTORY(. SRC_LIST) #把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST

#AUX_SOURCE_DIRECTORY(<dir> <variable>)函数接受两个参数，收集指定目录中所有源文件的名称，并将列表存储在提供
#的<variable>中.

ADD_EXECUTABLE(BattleShip ${SRC_LIST}) #//自动生成可执行文件Hello,ADD函数将所有源代码文件进行编译