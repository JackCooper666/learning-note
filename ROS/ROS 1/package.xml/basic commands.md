refer to CSDN博主「西红柿打卤面Love」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/cynalfly/article/details/125714149

# 1. 概述
  软件包（package）清单（manifest）是一个名为 package.xml 2 的 XML 文件，必须包含在任何兼容 catkin 的软件包的根文件夹中。该文件定义了有关软件包的属性，例如软件包名称、版本号、作者、维护者以及对其他catkin软件包的依赖关系。

# 2. package.xml文件

## 2.1 遵循的格式
`package.xml`遵循XML（可扩展标记语言）标签的写法，包含的标签有：
编号 | 标签 | 功能 | 备注
1	<package>	根标签，所有其他标签都嵌套在它下面	Required
2	<name>	软件包的名称	Required
3	<version>	软件包的版本号（必须是3个点分隔的整数）	Required
4	<description>	软件包的内容描述	Required
5	<maintainer>	软件包的维护者	Required
6	<license>	发布代码的软件许可证（例如 GPL、BSD、ASL）	Required
7	<buildtool_depend>	编译系统工具，通常为catkin	–
8	<depend>	指定依赖项为编译、导出、运行需要的依赖，最常用	–
9	<build_depend>	编译依赖项	–
10	<build_export_depend>	编译导出依赖项	–
11	<exec_depend>	执行依赖项	–
12	<test_depend>	测试用例依赖项	–
13	<doc_depend>	文档工具依赖项	–