map/set，这些元素内部通过红黑树进行实现， 插入和搜索的平均复杂度均为 O(log(size))。
在插入元素时候，会根据 < 操作符比较元素大小并判断元素是否相同， 并选择合适的位置插入到容器中。
当对这个容器中的元素进行遍历时，输出结果会按照 < 操作符的顺序来逐个遍历。
而无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 O(constant)， 在不关心容器内部元素顺序时，能够获得显著的性能提升。

所以在使用上 如果不需要对元素进行排序则推荐用unordered_map;需要对元素进行排序则使用map
