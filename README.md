# Math-Express
一个由C-Lang驱动的数学处理&amp;运算器



##### 与 `Math-calculator` 的关系

1. `Math-calculator` 由 PHP 进行驱动,而 `Math-Express` 由 C-Lang 驱动
2. `Math-calculator` 将会提供更多实验性功能，`Math-Express` 提供基础结构的功能



#### 原理层

- 词法核心由 `单Token扫描` 实现

- 语法核心由 `AST抽象语法树` 实现

#### 实现的功能:

- [x] 基础四则运算
- [x] 小数计算
- [x] 乘方
- [x] 求余
- [ ] 括号运算
- [ ] 完整错误控制 (目前大部分情况都已支持)
