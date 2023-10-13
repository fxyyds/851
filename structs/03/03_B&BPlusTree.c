#include "../../main.h"

// B-树与B+树
// 演示网站：https://www.cs.usfca.edu/~galles/visualization/BTree.html

// B树(多路平衡查找树)
// 【终于把B树搞明白了(三)_B树的查找，B+树的引入】 https://www.bilibili.com/video/BV1yB4y1v7Jy/
/**
 * 一颗 m 阶的 B-树，或为空树，或为满足下列特性的 m 叉树
 * 1. 树中每个节点至多有 m 棵子树
 * 2. 若根节点不是叶子节点，则至少有两棵子树
 * 3. 除根节点之外的所有非终端节点至少有 [m/2]（向上取整） 棵子树
 * 4. 有 n 个子树的节点有 n-1 个关键字，这些关键字互不相等且按递增排序
 * 5. 所有的叶子节点都处于同一层，是查找失败到达的位置，可以为空
 * 6. 描述节点的结构：
 *      (n, P0, K1, P1, K2, P2, ..., Kn, Pn)
 * */
#define m 3 // 阶数
typedef struct BTNode {
    int n; // 当前节点关键字个数，最多为m-1
    int keys[m-1]; // 储存关键字的数组
    struct BTNode* child[m]; // 指向子节点
    int leaf; // 叶子节点标记，叶子节点 ? 1 : 0
} BTree;

// 搜索 —— 利用B树特性比较大小遍历递归查找即可

// 插入 —— 分裂操作
// https://juejin.cn/post/7102339835494400007#heading-6
// 定位到最底层的**非叶子节点**（叶子节点上一层），直接插入，判断关键字个数，若已满则从中间位置分裂，左半部分留原节点，
//      右半部分放中间节点，中间节点插入双亲（双亲为空则中间节点升为根节点）
// 重复上述操作，判断双亲节点是否需要分裂

// 删除 —— 合并操作(合并难度过大，较小几率作为考点，仅了解
// 仅讨论删除叶子节点的情况（非叶子节点删除可转换为叶子节点删除），有以下三种可能：
// 1. 节点内关键字数量充足，可直接删除
// 2. 不足，从兄弟节点中借，兄弟节点充足
// 3. 兄弟节点不充足，合并
// https://zhuanlan.zhihu.com/p/623572741

// B+树
/**
 * B+树与b-树的区别在于
 * 1. 有 n 个子树的节点有 n 个关键字，这些关键字互不相等且按递增排序
 * 2. 关键字信息与指向关键字的指针存放在所有的叶子节点中
 * 3. 所有的非叶子节点可以看成索引，其中并未储存数据
 * */