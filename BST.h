#pragma once

#include "BinTree.h" //引入BinTree

template <typename T> class BST : public BinTree<T> { //由BinTree派生BST模板类
public:
	BinNodePosi(T) _hot; //“命中”节点的父亲
protected:
	BinNodePosi(T) connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x); //对x及其父亲、祖父做统一旋转调整
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
	virtual BinNodePosi(T) & search(const T& e); //查找
	virtual BinNodePosi(T) insert(const T& e); //插入
	virtual bool remove(const T& e); //删除
};


#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //节点v（或假想的通配哨兵）的关键码等于e


template <typename T> BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
	//*DSA*/print(a); print(b); print(c); printf("\n");
	a->lc = T0; if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateHeight(b);
	return b; //该子树新的根节点
}

template <typename T> BinNodePosi(T) BST<T>::insert(const T& e)
{ //将关键码e插入BST树中
	//cout << "WHAT" << endl;
	BinNodePosi(T) & x = search(e);
	if (x)
	{
		//NEW 更新，此处需要在列表中增加一个位置
		//cout<<"HERE"<<endl;
		x->data.Add(e._index[0]);
		return x; //确认目标不存在（留意对_hot的设置）
	}
	x = new BinNode<T>(e, _hot); //创建新节点x：以e为关键码，以_hot为父
	_size++; //更新全树规模
	updateHeightAbove(x); //更新x及其历代祖先的高度
	return x; //新插入的节点，必为叶子
} //无论e是否存在于原树中，返回时总有x->data == e

template <typename T> bool BST<T>::remove(const T& e) { //从BST树中删除关键码e
	BinNodePosi(T) & x = search(e); if (!x) return false; //确认目标存在（留意_hot的设置）
	removeAt(x, _hot); _size--; //实施删除
	updateHeightAbove(_hot); //更新_hot及其历代祖先的高度
	return true;
} //删除成功与否，由返回值指示

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) {
	BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
	BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
	if (!HasLChild(*x)) //若*x的左子树为空，则可
		succ = x = x->rc; //直接将*x替换为其右子树
	else if (!HasRChild(*x)) //若右子树为空，则可
		succ = x = x->lc; //对称地处理——注意：此时succ != NULL
	else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
		w = w->succ(); //（在右子树中）找到*x的直接后继*w
		swap(x->data, w->data); //交换*x和*w的数据元素
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
	}
	hot = w->parent; //记录实际被删除节点的父亲
	if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
	//release(w->data); release(w); 
	delete w;
	return succ; //释放被摘除节点，返回接替者
}

template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) { //v为非空孙辈节点
	/*DSA*/if (!v) { printf("\a\nFail to rotate a null node\n"); exit(-1); }
	BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
	if (IsLChild(*p)) /* zig */
		if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
			p->parent = g->parent; //向上联接
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
			v->parent = g->parent; //向上联接
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	else  /* zag */
		if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
			p->parent = g->parent; //向上联接
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
			v->parent = g->parent; //向上联接
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
}

template <typename T> BinNodePosi(T) & BST<T>::search(const T& e) //在BST中查找关键码e
{
	return searchIn(_root, e, _hot = NULL);
} //返回目标节点位置的引用，以便后续插入、删除操作


//template <typename T> //在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
//static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) {
//	if (EQUAL(e, v)) return v; hot = v; //退化情况：在子树根节点v处命中
//	while (1) { //一般地，反复不断地
//		BinNodePosi(T) & c = (e < hot->data) ? hot->lc : hot->rc; //确定深入方向
//		if (EQUAL(e, c)) return c; hot = c; //命中返回，或者深入一层
//	} //hot始终指向最后一个失败节点
//} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）

template <typename T> //在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) {
	if (!v || (e == v->data)) return v; //递归基：在节点v（或假想的通配节点）处命中
	hot = v; //一般情况：先记下当前节点，然后再
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot); //深入一层，递归查找
} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）

