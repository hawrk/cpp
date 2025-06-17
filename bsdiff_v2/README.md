
使用 bsdiff 第三方库对文件进行差分操作

1. 修改了库源代码，增加对bsdiff, bspatch的封装，更易于调用

2. 对bsdiff直接编译生成so库，放在lib目录下

3. 生成demo需要信赖libbz2库， 示例以bsdiff_offical　bspatch_offical为准