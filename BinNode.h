#pragma once

#include <algorithm>
#include <memory>

using std::max;
using std::min;
using std::swap;


#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色

template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
	T data; //数值
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
	int height; //高度（通用）
	int npl; //Null Path Length（左式堆，也可直接用height代替）
	RBColor color; //颜色（红黑树）
 // 构造函数
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
	// 操作接口
	int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T const&); //作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const&); //作为当前节点的右孩子插入新节点
	BinNodePosi(T) succ(); //取当前节点的直接后继
	BinNodePosi(T) pred(); //自己补充仿照的直接前驱
	template <typename VST> void travLevel(VST&); //子树层次遍历
	template <typename VST> void travPre(VST&); //子树先序遍历
	template <typename VST> void travIn(VST&); //子树中序遍历
	template <typename VST> void travPost(VST&); //子树后序遍历
 // 比较器、判等器（各列其一，其余自行补充）
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
	bool operator== (BinNode const& bn) { return data == bn.data; } //等于
	/*DSA*/
	/*DSA*/BinNodePosi(T) zig(); //顺时针旋转
	/*DSA*/BinNodePosi(T) zag(); //逆时针旋转
};

/*DSA*/#define HeightUpdated(x) /*高度更新常规条件*/ \
/*DSA*/        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件


/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

 /******************************************************************************************
  * 与BinNode具有特定关系的节点及指针
  ******************************************************************************************/
#define sibling(p) /*兄弟*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*叔叔*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);
} //将e作为当前节点的左孩子插入二叉树

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);
} //将e作为当前节点的右孩子插入二叉树

template <typename T> int BinNode<T>::size() //统计当前节点后代总数，即以其为根的子树规模
{ 
	int s = 1; //计入本身
	if (lc) s += lc->size(); //递归计入左子树规模
	if (rc) s += rc->size(); //递归计入右子树规模
	return s;
}

template <typename T> void stretchByZag(BinNodePosi(T) & x) {
	/*DSA*/   int c = 0; //记录旋转次数
	int h = 0;
	BinNodePosi(T) p = x; while (p->rc) p = p->rc; //最大节点，必是子树最终的根
	while (x->lc) x = x->lc; x->height = h++; //转至初始最左侧通路的末端
	for (; x != p; x = x->parent, x->height = h++) { //若x右子树已空，则上升一层
		while (x->rc) //否则，反复地
			/*DSA*/ {
			x->zag(); //以x为轴做zag旋转
			/*DSA*/c++;
			/*DSA*/
		}
	} //直到抵达子树的根
	/*DSA*/printf("\nh = %d, c = %d\n\n", h, c);
}

//通过zig旋转调整，将子树x拉伸成最右侧通路
template <typename T> void stretchByZig(BinNodePosi(T) & x, int h) {
	/*DSA*/   int c = 0;
	for (BinNodePosi(T) v = x; v; v = v->rc) {
		while (v->lc)
			/*DSA*/ {
			v = v->zig();
			/*DSA*/c++;
			/*DSA*/
		}
		v->height = --h;
	}
	while (x->parent) x = x->parent;
	/*DSA*/printf("\nh = %d, c = %d\n\n", h, c);
}

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //定位节点v的直接后继
	BinNodePosi(T) s = this; //记录后继的临时变量
	if (rc) { //若有右孩子，则直接后继必在右子树中，具体地就是
		s = rc; //右子树中
		while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
	}
	else //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
	{ 
		while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
		s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}

template <typename T>
BinNode<T>* BinNode<T>::pred()
{
	BinNodePosi(T) s = this; //记录前驱的历史变量
	if (lc) //如果存在左孩子，则前驱就是左孩子
	{
		s = lc;
		while (HasRChild(*s)) s = s->rc;
	}
	else if (IsRChild(*s)) //如果是右子树，则前驱是其父节点
	{
		s = s->parent;
	}
	else //是左孩子，且没有左子树
	{
		while (IsLChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}


template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST& visit) { //二叉树中序遍历算法统一入口
	//switch (rand() % 5) { //此处暂随机选择以做测试，共五种选择
	//case 1: travIn_I1(this, visit); break; //迭代版#1
	//case 2: travIn_I2(this, visit); break; //迭代版#2
	//case 3: travIn_I3(this, visit); break; //迭代版#3
	//case 4: travIn_I4(this, visit); break; //迭代版#4
	//default: travIn_R(this, visit); break; //递归版
	//}
	travIn_R(this, visit);
}

template <typename T, typename VST> //元素类型、操作器
void travIn_R(BinNodePosi(T) x, VST& visit) { //二叉树中序遍历算法（递归版）
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

//此处省略了一个travlevel算法，因为不需要进行层次遍历

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPost(VST& visit) { //二叉树后序遍历算法统一入口
	//switch (rand() % 2) { //此处暂随机选择以做测试，共两种选择
	//case 1: travPost_I(this, visit); break; //迭代版
	//default: travPost_R(this, visit); break; //递归版
	//}
	travPost_R(this, visit);
}

template <typename T, typename VST> //元素类型、操作器
void travPost_R(BinNodePosi(T) x, VST& visit) { //二叉树后序遍历算法（递归版）
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPre(VST& visit) { //二叉树先序遍历算法统一入口
	//switch (rand() % 3) { //此处暂随机选择以做测试，共三种选择
	//case 1: travPre_I1(this, visit); break; //迭代版#1
	//case 2: travPre_I2(this, visit); break; //迭代版#2
	//default: travPre_R(this, visit); break; //递归版
	//}
	travPre_R(this, visit);
}

template <typename T, typename VST> //元素类型、操作器
void travPre_R(BinNodePosi(T) x, VST& visit) { //二叉树先序遍历算法（递归版）
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

template <typename T> BinNodePosi(T) BinNode<T>::zag() 
{
	BinNodePosi(T) rChild = rc;
	rChild->parent = this->parent;
	if (rChild->parent)
		((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
	rc = rChild->lc; if (rc) rc->parent = this;
	rChild->lc = this; this->parent = rChild;
	return rChild;
}

template <typename T> BinNodePosi(T) BinNode<T>::zig() 
{
	BinNodePosi(T) lChild = lc;
	lChild->parent = this->parent;
	if (lChild->parent)
		((this == lChild->parent->rc) ? lChild->parent->rc : lChild->parent->lc) = lChild;
	lc = lChild->rc; if (lc) lc->parent = this;
	lChild->rc = this; this->parent = lChild;
	return lChild;
}