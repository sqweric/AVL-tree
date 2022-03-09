#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template<class T>
class TreeNode
{
public:
    T val;
    TreeNode<T>* lc;
    TreeNode<T>* rc;
    int height;
public:
    TreeNode(T _val=0,TreeNode<T> *_lc= nullptr,TreeNode<T>* _rc= nullptr,int _height=0):val(_val),
    lc(_lc),rc(_rc),height(_height)
    {

    }
    ~TreeNode()
    {}
    TreeNode<T>*Getlc()const{
        return lc;
    }
    // void CreateNode(TreeNode)
    void Setlc(TreeNode<T>* _lc);
    TreeNode<T>* Getrc() const;
    void Setrc(TreeNode<T>* _rc);
    void SetVal(T _val);
    T GetVal() const
    {
        return val;
    }
    bool IsLeaf();
    static TreeNode<T>*CreateNode();
};
template<class T>
TreeNode<T>* TreeNode<T>::CreateNode()
{
    cout<<"请输入当前节点的值：";
    T n;
    cin>>n;
    if(n<0)
    {
        return;
    }
    TreeNode<T> *Node_ptr=new TreeNode<T>(n);
    Node_ptr->lc=TreeNode<T>::CreateNode();
    Node_ptr->rc=TreeNode<T>::CreateNode();
    return Node_ptr;

}
template<class T>
void TreeNode<T>::SetVal(T _val)
{
    val=_val;
}
template<class T>
void TreeNode<T>::Setlc(TreeNode<T>* _lc)
{
    lc=_lc;
}
template<class T>
void TreeNode<T>::Setrc(TreeNode<T>* _rc)
{
    rc=_rc;
}
template<class T>
TreeNode<T>* TreeNode<T>::Getrc() const
{
    return rc;
}
//创建平衡二叉树
//平衡二叉树概念：平衡二叉树的跟节点，一定比他的左子树大，并且比它的右子树小，且每个根节点的左子树与右子树的高度相差不超过1.
template <class T>
class BalancedBinaryTree
{
private:
    TreeNode<T>*subroot;
    TreeNode<T>* InsertNode(TreeNode<T>* &_root,T _val);//插入节点
    TreeNode<T>* RightHand(TreeNode<T>* &_root);          //右旋
    TreeNode<T>* LeftHand(TreeNode<T>* &_root);           //左旋
    TreeNode<T>* RightLeftHand(TreeNode<T>* &_root);      //右左
    TreeNode<T>* LeftRightHand(TreeNode<T>* &_root);      //右左
    TreeNode<T>* RemoveNode(TreeNode<T>* _root,T _val);   //删除值为_val的节点,返回值是删除后的根节点
    TreeNode<T>* MinNode(TreeNode<T>* _root) const;       //获取树中的最小值,一直返回左子树的值，直到左子树为空
    TreeNode<T>* MaxNode(TreeNode<T>* _root) const;       //获取树中的最大值
    TreeNode<T>* FindNode(TreeNode<T>*_root,T key) const; //查找值为Key的节点
    void DestroyNode(TreeNode<T>* &_root);                       //销毁树
    void TravelPreorderNode(TreeNode<T>* _root) const;           //前序遍历-》深度优先遍历
public:
    BalancedBinaryTree(TreeNode<T>* _subroot=NULL):subroot(_subroot)
    {}
    BalancedBinaryTree(BalancedBinaryTree<T> *Tree)
    {
        subroot=Tree->GetRoot();
    }
    ~BalancedBinaryTree()
    {}
    TreeNode<T>* GetRoot() const
    {
        return subroot;
    }
    inline int getheight(TreeNode<T> *_Node) const
    {
        if(NULL==_Node)
        {
            return 0;
        }
        return _Node->height;
    }
    void InsertKey(T _val);
    void RemoveKey(T _val);
    void DestroyTree();      //销毁树
    void TravelPreorderTree() const;
    TreeNode<T> * FindKey(T _key);
    int TreeHeight() const;                                                //获取树的高度

    void TravelInfixorder(TreeNode<T>* _root) const;          //中序遍历-》深度优先遍历
    void ExtentTravel(TreeNode<T>* _root) const;              //广度优先遍历
};
template<class T>
void BalancedBinaryTree<T>::TravelPreorderTree() const
{
    TravelPreorderNode(subroot);
}
template<class T>
void BalancedBinaryTree<T>::DestroyTree()
{
    DestroyNode(subroot);
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::FindKey(T _key)
{
    return FindNode(subroot,_key);
}
template<class T>
void BalancedBinaryTree<T>::RemoveKey(T _val)
{
    subroot=RemoveNode(subroot,_val);
}
template<class T>
void BalancedBinaryTree<T>::InsertKey(T _val)
{
    subroot=InsertNode(subroot,_val);
}
template<class T>
void BalancedBinaryTree<T>::DestroyNode(TreeNode<T> *&_root)
{
    if(NULL!=_root)
    {
        DestroyNode(_root->lc);
        DestroyNode(_root->rc);
        delete _root;
        _root=NULL;
    }
}
template<class T>
int BalancedBinaryTree<T>::TreeHeight() const
{
    return subroot->height;
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::FindNode(TreeNode<T>*_root,T key) const
{
    if(NULL==_root)
    {
        return NULL;
    }
    if(_root->val==key)
    {
        return _root;
    }
    else if(key<_root->val)
    {
        return FindNode(_root->lc,key);
    }
    else
    {
        return FindNode(_root->rc,key);
    }
}
template<class T>
void BalancedBinaryTree<T>::TravelPreorderNode(TreeNode<T> *_root) const
{
    if(NULL==_root)
    {
        return;
    }
    cout<<_root->val<<" ";
    TravelPreorderNode(_root->lc);
    TravelPreorderNode(_root->rc);
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::MaxNode(TreeNode<T> *_root) const
{
    if(NULL==_root)
    {
        return NULL;
    }
    while(NULL!=_root->rc)
    {
        _root=_root->rc;
    }
    return _root;
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::MinNode(TreeNode<T> *_root) const
{
    if(NULL==_root)
    {
        return NULL;
    }
    while(NULL!=_root->lc)
    {

        _root=_root->lc;
    }
    return _root;
}
// 如果要删除的子树左右节点都为空，那么就用左节点的最大值或者右节点的最小值进行替换，这样不会破坏二叉树的平衡性
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::RemoveNode(TreeNode<T> *_root, T _val)
{
    if(NULL==_root)
    {
        return NULL;
    }
    if(_val<_root->val)
    {
        _root->lc=RemoveNode(_root->lc,_val);
        //删除左子树上的节点相当于在右子树上插入节点
        if(getheight(_root->rc)-getheight(_root->lc)==2)
        {
            //相当于在右子树上插入左节点造成的失衡（情况四）
            if (getheight(_root->rc->lc)>getheight(_root->rc->rc))
            {
                //相当与插入的右左
                _root=RightLeftHand(_root);

            }
            else
            {
                //相当于插入的右右
                _root=LeftHand(_root);
            }
        }
    }
    else if(_val>_root->val)
    {
        _root->rc=RemoveNode(_root->rc,_val);
        if(getheight(_root->lc)-getheight(_root->rc)==2)
        {
            //删除右子树的节点相当与在左子树上插入节点，下面就判断是在左子树的右子树插入还是左子树的左子树插入的
            if(getheight(_root->lc->lc)>getheight(_root->lc->rc))//左左
            {
                _root=RightHand(_root);

            }
            else
            {
                _root=LeftRightHand(_root);
            }

        }
    }
    else
    {
        //删除过程要判断：
        //1 当前节点是不是叶节点
        //2 删除之后还要看看是否破坏了平衡性

        if(NULL!=_root->lc&&NULL!=_root->rc)
        {
            //从左右子树中较高的子树中找到对应的最大最小的点来替换，如果是左子树就用最大值，如果是右子树就用最小值
            if(getheight(_root->lc)>getheight(_root->rc))//左边子树高度大
            {
                //获取左边节点最大值
                TreeNode<T>* _MaxNode=MaxNode(_root->lc);
                _root->val=_MaxNode->val;
                _root->lc=RemoveNode(_root->lc,_MaxNode->val);

            }
            else
            {
                TreeNode<T>* _MinNode=MinNode(_root->rc);
                _root->val=_MinNode->val;
                _root->rc=RemoveNode(_root->rc,_MinNode->val);
            }
        }
        else//只有一个为NULL
        {
            TreeNode<T> *NowNode=_root;
            if(NULL!=_root->lc)
            {
                _root=_root->lc;
            }
            else if(NULL!=_root->rc)
            {
                _root=_root->rc;
            }
            else
            {
                _root=NULL;// 当前节点是叶节点没有子节点
            }
            delete NowNode;
        }


    }
    return _root;//把删除的节点返回
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::LeftHand(TreeNode<T> *&_root)
{
    TreeNode<T>* _rootrc=_root->rc;
    _root->rc=_rootrc->lc;
    _rootrc->lc=_root;
    _rootrc->height=getheight(_rootrc->lc)>getheight(_rootrc->rc)?getheight(_rootrc->lc)+1:getheight(_rootrc->rc)+1;
    _root->height=getheight(_root->lc)>getheight(_root->rc)?getheight(_root->lc)+1:getheight(_root->rc)+1;
    return _rootrc;
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::RightHand(TreeNode<T> *&_root)
{
    TreeNode<T> * _rootlc=_root->lc;
    _root->lc=_rootlc->rc;
    _rootlc->rc=_root;
    _rootlc->height=getheight(_rootlc->lc)>getheight(_rootlc->rc)?getheight(_rootlc->lc)+1:getheight(_rootlc->rc)+1;
    _root->height=getheight(_root->lc)>getheight(_root->rc)?getheight(_root->lc)+1:getheight(_root->rc)+1;
    return _rootlc;//返回的就是作为参数传过来的节点在树中的位置
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::RightLeftHand(TreeNode<T> *&_root)
{
    _root->lc=LeftHand(_root->lc);
    return RightHand(_root);
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::LeftRightHand(TreeNode<T> *&_root)
{
    _root->rc=RightHand(_root->rc);
    return LeftHand(_root);
}
template<class T>
TreeNode<T>* BalancedBinaryTree<T>::InsertNode(TreeNode<T> *&_root,T _val)
{
    if(NULL==_root)
    {
        _root=new TreeNode<T>(_val);
        _root->height=getheight(_root->lc)>getheight(_root->rc)?getheight(_root->lc)+1:getheight(_root->rc)+1;
    }
        //判断当前节点应该插入根节点的左子树还是右子树
    else if(_val<_root->val)
    {
        _root->lc=InsertNode(_root->lc,_val);
        if(getheight(_root->lc)-getheight(_root->rc)==2)//插入后失衡
        {
            if(_val<_root->lc->val)
            {
                _root=RightHand(_root);//左左的旋转
            }
            else
            {
                _root=LeftRightHand(_root);//左右的旋转
            }
        }
    }
    else
    {
        _root->rc=InsertNode(_root->rc,_val);
        if(getheight(_root->rc)-getheight(_root->lc)==2)// 右插后失衡
        {
            if(_val<_root->rc->val)
            {
                _root=RightLeftHand(_root);//右左
            }
            else
            {
                _root=LeftHand(_root); //右右
            }
        }
    }
    _root->height=getheight(_root->lc)>getheight(_root->rc)?getheight(_root->lc)+1:getheight(_root->rc)+1;
    return _root;//返回插入的这个值
}
int main(int argc,char **argv)
{
    BalancedBinaryTree<int>* root=new BalancedBinaryTree<int>();
    for(int i=1;i<10;i++)
    {
        root->InsertKey(i);
    }
    root->RemoveKey(2);
    root->RemoveKey(8);
    root->TravelPreorderTree();
    return 0;
}


