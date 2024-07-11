# `Mini-Lisp` 解释器
这是软件设计实践课程（24春）的大作业，在课程团队的[框架与指南](https://pku-software.github.io/project-doc/)下实现了一个`Mini_Lisp`解释器。

**未来选课同学完成大作业时请独立完成，不要（也不必）参考本人的代码。**

下面是解释器的使用说明：
使用命令行进行控制
文本模式: `\.mini_lisp -f filename`
REPL模式: `\.mini_lisp -r`

在REPL模式当中, 我们支持多行输入, 当逐行输入输入的内容满足左括号和右括号数目匹配时，视为一次输入,这里我们要求每一行必须打印完整.

增加了内置过程`int?`,`num?`检测一列值是否都为数/整数.修改`-`的输入标准,支持多个参数,参数>1时返回第一个参数依次减去后面的参数
