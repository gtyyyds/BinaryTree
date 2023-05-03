#include<iostream>//输入输出流
#include<stack>//STL中的栈容器
#include<string>//STL中的字符串容器
#include<queue>//STL中的队列容器
typedef char ElemType;
using namespace std;//使用标准命名空间
struct BinTreeNode//二叉树结点类
{
    ElemType data;//数据域
    BinTreeNode* leftChild, * rightChild;//左孩子和右孩子
    BinTreeNode():leftChild(NULL), rightChild(NULL) {}//无参构造函数初始化列表（当无参构造二叉树结点类时，左孩子和右孩子默认指NULL）
    BinTreeNode(ElemType x, BinTreeNode* l = NULL, BinTreeNode* r = NULL):
        data(x), leftChild(l), rightChild(r) {}//有参构造函数初始化列表以及默认参数
    /*
    * 为什么使用初始化列表？这样可以在构造二叉树结点类时，构造类型更加丰富，我可以什么也不传参（默认构造），也可以只传数据域参数，
    * 在不指明左孩子和右孩子的情况下，默认为NULL，这样可以节省在下面对结点操作时，还要指定左右孩子NULL
    */
};
class BinaryTree//二叉树类（核心）
{
public://公共权限
    BinaryTree():root(NULL) {};//二叉树类无参构造，以及初始化列表默认根节点为NULL
    BinaryTree(ElemType value):root(NULL),RefValue(value) {}; //二叉树类有参构造函数，以及初始化列表，传入“数据结束输入的标志”
    BinaryTree(BinaryTree& s) {};//拷贝构造函数（复制二叉树）
    ~BinaryTree() {};//析构函数
    //创建
    void InitBinTree();//二叉树的初始化（类内声明）
    void CreateBinaryTree_GenTab(); //使用广义表的方法创建二叉树（类内声明）
    void CreateBinaryTree_PerOrder(BinTreeNode* &BTRoot);//使用前序遍历方法创建二叉树（类内声明）
    void CreateBinaryTree_Per_In(BinTreeNode*& BTRoot, const char* Pre, const char* In, int n);//使用前序遍历和中序遍历创建二叉树（类内声明）
    void CreateBinaryTree_In_Post(BinTreeNode*& BTRoot, const char* In, const char* Post, int n);//使用中序遍历和后序遍历创建二叉树(类内声明)
    //遍历
    void LevelOrder(BinTreeNode* BTRoot);//层序遍历（类内声明）
    void PreOrder(BinTreeNode* BTRoot);//前序遍历（类内声明）
    void InOrder(BinTreeNode* BTRoot);//中序遍历（类内声明）
    void PostOrder(BinTreeNode* BTRoot);//后序遍历（类内声明）
    //属性
    int Get_BinaryTreeNodeCount(BinTreeNode* BTRoot);//获取二叉树的节点个数（类内声明）
    int Get_BinaryTreeDegree(BinTreeNode* BTRoot);//获取二叉树的深度（类内声明）
    int Get_BinaryTreeLeafCount(BinTreeNode* BTRoot);//获取二叉树叶子结点数（类内声明）
    int Get_BinaryTreeSingleChildNodeCount(BinTreeNode* BTRoot);//获取二叉树单个孩子的结点数（度为1）（类内声明）
    int Get_BinaryTreeTwoChildNodeCount(BinTreeNode* BTRoot);//获取二叉树两个孩子结点数（度为2）（类内声明）

    //菜单
    void ShowMainMenu();//主要菜单（类内声明）
    void ShowCreateMenu();//创建菜单（类内声明）
    void ShowTraverMenu();//遍历菜单（类内声明）
    void ShowAttributeMenu();//属性菜单（类内声明）

    //类内成员属性
    BinTreeNode* root;//根节点
    ElemType RefValue;//空字符'#',代表数据为空

};
void BinaryTree::InitBinTree()//二叉树的初始化
{
    if (this->root != NULL)//初始化，让二叉树的根节点置空
    {
        this->root = NULL;
    }
    cout << "初始化成功！" << endl;
}
void BinaryTree::CreateBinaryTree_GenTab()//使用广义表的方法创建二叉树
{
    stack<BinTreeNode*>s;//栈容器
    string BTstr;//字符串容器
    BinTreeNode* BTRoot = NULL;//根节点变量
    BinTreeNode* t = NULL;//记录当前创建的节点
    BinTreeNode* p = NULL;//记录栈顶元素
    int k = 0;//k是处理左孩子或者右孩子的标记
    cin >> BTstr;//输入广义表
    for (int i = 0; i < BTstr.size(); i++)//把广义表里每个数据存储
    {
        switch (BTstr[i])//判断输入的每个字符
        {
        case'(':
            s.push(p);//如果是‘(’，说明遇到了左孩子元素
            k = 1;//标记置1
            break;

        case')':
            s.pop();//如果遇到了')',说明该结点的元素已经入树，要退栈
            break;
        case',':
            k = 2;//如果是‘,’,说明遇到了右孩子元素
            break;
        default:
            p = new BinTreeNode(BTstr[i]);//向操作系统在堆区申请空间，并且利用有参构造函数，构造一个值为BTstr[i]的结点，并且把结点的首地址返回给p
            if (BTRoot == NULL)//初次建立，创建根结点
            {
                BTRoot = p;
            }
            else if (k == 1)//左孩子操作
            {
                t = s.top();
                t->leftChild= p;
            }
            else if (k == 2)//右孩子操作
            {
                t = s.top();
                t->rightChild = p;
            }
            break;
        }
    }
    this->root = BTRoot;//把根结点，赋值给类内的成员属性
    cout << "创建成功！" << endl;
}
void BinaryTree::CreateBinaryTree_PerOrder(BinTreeNode * &BTRoot)//使用先序遍历创建二叉树（递归）
{
    ElemType elem;//数据输入
    if (cin >> elem)
    {
        if (elem != this->RefValue)//这里的RefValue是'#'
        {       
            BTRoot = new BinTreeNode(elem);//有参构造
            CreateBinaryTree_PerOrder(BTRoot->leftChild);//访问左孩子
            CreateBinaryTree_PerOrder(BTRoot->rightChild);//访问右孩子
        }
    }
    else
    {
        BTRoot = NULL;//遇到‘#’，表示无数据，BTRoot直接为空
    }
}
void BinaryTree::CreateBinaryTree_Per_In(BinTreeNode*& BTRoot, const char* Pre, const char* In, int n)//使用先序和中序遍历创建二叉树
{
    if (n <= 0)//前序遍历的字符长度为0，代表已经无结点                                //第一个参数：要递归的对象
    {                                                                                 //第二个参数：前序遍历字符
        BTRoot = NULL;                                                                //第三个参数：中序遍历字符
        return;                                                                       //第四个参数：前序遍历字符长度
    }
    //根据前序遍历，先找到这棵树的根节点，也就是数组中第一个结点的位置，创建根节点，然后在中序遍历中找到根的值所在的下标，切出左右子树的前序和中序
    int k = 0;
    while (Pre[0] != In[k])//再中序中找到pre[0]的值
    {
        k++;
    }
    BTRoot = new BinTreeNode(In[k]);//创建结点
    CreateBinaryTree_Per_In(BTRoot->leftChild, Pre + 1, In, k);
    CreateBinaryTree_Per_In(BTRoot->rightChild, Pre + k + 1, In + k + 1, n - k - 1);
}
void BinaryTree::CreateBinaryTree_In_Post(BinTreeNode*& BTRoot, const char* In, const char* Post, int n)//使用中序遍历和后序遍历创建二叉树
{                                                                                                                                                  
    if (n == 0)                                             
    {                                                                             
        BTRoot == NULL;                                                       
        return;
    }
//根据后序遍历，先找到这棵树的根节点的值，也就是数组中最后一个节点（数组长度 - 1）的位置，由此创建根节点，然后在中序遍历中找到根的值所在的下标，切出左右子树的后续和中序
    char r = *(Post + n - 1);//根结点值
    BTRoot = new BinTreeNode(r);//构造当前结点
    int k = 0;
    const char* p = In;
    while (*p != r)
    {
        k++;
        p++;
    }
    CreateBinaryTree_In_Post(BTRoot->leftChild, In, Post, k);
    CreateBinaryTree_In_Post(BTRoot->rightChild, p + 1, Post + k, n - k - 1);
}

void BinaryTree::LevelOrder(BinTreeNode* BTRoot)//层序遍历（类外实现）
{
    queue<BinTreeNode*>Q;//队列容器
    Q.push(BTRoot);//根结点入队
    BinTreeNode* t = NULL;
    while (!Q.empty())
    {
        t = Q.front();//t先记住队头,再将队头出队
        Q.pop();
        cout << t->data; //访问队头元素的数据
        if (t->leftChild != NULL)
        {
            Q.push(t->leftChild);
        }
        if (t->rightChild != NULL)
        {
            Q.push(t->rightChild);
        }
    }
}
void BinaryTree::PreOrder(BinTreeNode *BTRoot)//前序遍历（类外实现）（递归）
{
    if (BTRoot != NULL)
    {
        cout << BTRoot->data;
        PreOrder(BTRoot->leftChild);
        PreOrder(BTRoot->rightChild);
    }
}
void BinaryTree::InOrder(BinTreeNode* BTRoot)//中序遍历（类外实现）（递归）
{
    if (BTRoot != NULL)
    {
        InOrder(BTRoot->leftChild);
        cout << BTRoot->data;
        InOrder(BTRoot->rightChild);
    }
}
void BinaryTree::PostOrder(BinTreeNode* BTRoot)//后序遍历（类外实现）（递归）
{
    if (BTRoot != NULL)
    {
        InOrder(BTRoot->leftChild);
        InOrder(BTRoot->rightChild);
        cout << BTRoot->data;
    }
}

int BinaryTree::Get_BinaryTreeNodeCount(BinTreeNode* BTRoot)//获取二叉树的结点个数（递归）
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    return Get_BinaryTreeNodeCount(BTRoot->leftChild) + Get_BinaryTreeNodeCount(BTRoot->rightChild) + 1;
}
int BinaryTree::Get_BinaryTreeDegree(BinTreeNode* BTRoot)//获取二叉树深度（递归）
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    int i = Get_BinaryTreeDegree(BTRoot->leftChild);
    int j = Get_BinaryTreeDegree(BTRoot->rightChild);
    return i < j ? j + 1 : i + 1;//取最大值
}
int BinaryTree::Get_BinaryTreeLeafCount(BinTreeNode* BTRoot)//获取二叉树的叶子数（递归）
{
    int LeafCount;
    if (BTRoot == NULL)
    {
        LeafCount = 0;
    }
    else if (BTRoot->leftChild == NULL && BTRoot->rightChild == NULL)//符合条件的结点
    {
        LeafCount = 1;
    }
    else
    {
        LeafCount = Get_BinaryTreeLeafCount(BTRoot->leftChild) + Get_BinaryTreeLeafCount(BTRoot->rightChild);//不符合接着递归
    }
    return LeafCount;
}
int BinaryTree::Get_BinaryTreeSingleChildNodeCount(BinTreeNode* BTRoot)//获取二叉树单个孩子数（递归）
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    else if ((BTRoot->rightChild != NULL && BTRoot->leftChild == NULL) || (BTRoot->rightChild == NULL && BTRoot->leftChild != NULL))//符合条件的结点
    {
        return Get_BinaryTreeSingleChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeTwoChildNodeCount(BTRoot->rightChild) + 1;
    }
    else
    {
       return Get_BinaryTreeSingleChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeSingleChildNodeCount(BTRoot->rightChild);//不符合接着递归
    }
    
}
int BinaryTree::Get_BinaryTreeTwoChildNodeCount(BinTreeNode* BTRoot)//获取二叉树度为2的结点数（递归）
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    else if (BTRoot->leftChild != NULL && BTRoot->rightChild != NULL)
    {
        return Get_BinaryTreeTwoChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeTwoChildNodeCount(BTRoot->rightChild) + 1;
    }
    else
    {
        return  Get_BinaryTreeTwoChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeTwoChildNodeCount(BTRoot->rightChild);
    }
}

void BinaryTree::ShowMainMenu()//主要菜单（类外实现）
{
    cout << "     ****************" << endl;
    cout << "     *  二叉树操作  *" << endl;
    cout << "     ****************" << endl;
    cout << "     * 1、创    建  *" << endl;
    cout << "     * 2、遍    历  *" << endl;
    cout << "     * 3、属    性  *" << endl;
    cout << "     * 0、退    出  *" << endl;
    cout << "     ****************" << endl;
    cout << "请输入您的选项：";
}
void BinaryTree::ShowCreateMenu()//主要菜单（类外实现）
{
    cout << "     ******************" << endl;
    cout << "     *   二叉树创建   *" << endl;
    cout << "     ******************" << endl;
    cout << "     * 1、广  义  表  *" << endl;
    cout << "     * 2、前      序  *" << endl;
    cout << "     * 3、前序和中序  *" << endl;
    cout << "     * 4、后序和中序  *" << endl;
    cout << "     * 5、初  始  化  *" << endl;
    cout << "     * 0、返      回  *" << endl;
    cout << "     ******************" << endl;
    cout << "请输入您的选项：" ;
}
void BinaryTree::ShowTraverMenu()//遍历菜单（类外实现）
{
    cout << "     ****************" << endl;
    cout << "     *  二叉树遍历  *" << endl;
    cout << "     ****************" << endl;
    cout << "     * 1、层    序  *" << endl;
    cout << "     * 2、先    序  *" << endl;
    cout << "     * 3、中    序  *" << endl;
    cout << "     * 4、后    序  *" << endl;
    cout << "     * 0、返    回  *" << endl;
    cout << "     ****************" << endl;
    cout << "请输入您的选项：";
}
void BinaryTree::ShowAttributeMenu()//属性菜单（类外实现）
{
    cout << "     ********************" << endl;
    cout << "     *     二叉树属性   *" << endl;
    cout << "     ********************" << endl;
    cout << "     * 1、 结点个数     *" << endl;
    cout << "     * 2、 树的深度     *" << endl;
    cout << "     * 3、叶子节点数    *" << endl;
    cout << "     * 4、单孩子节点数  *" << endl;
    cout << "     * 5、度为二节点数  *" << endl;
    cout << "     * 0、返        回  *" << endl;
    cout << "     ********************" << endl;
    cout << "请输入您的选项：";
}


void BinTreeCreate(BinaryTree& BT)//二叉树创建
{
    system("cls");
    int select;
    while (true)
    {
        BT.ShowCreateMenu();
        cin >> select;
        switch (select)
        {
        case 1://根据广义表方式创建
            BT.InitBinTree();
            cout << "请用广义表的方式创建二叉树" << endl << "例如：A(B(D,E(G,)),C(,F))" << endl << "注意使用英文符号！" << endl;
            BT.CreateBinaryTree_GenTab();
            return;
        case 2://根据前序遍历方式创建
            BT.InitBinTree();
            cout << "请用前序遍历的方式创建二叉树" << endl << "例如：ABC##DE#G##F###" << endl << "注意使用英文符号！" << endl;
            BT.CreateBinaryTree_PerOrder(BT.root);
            cout << "创建成功！" << endl;
            return;
        case 3://根据前序和中序方式创建
        {
            BT.InitBinTree();
            string Pre_str, In_str;
            cout << "请使用前序遍历和中序遍历创建二叉树" <<endl<< "例如：" << endl << "前序遍历：ABDEGCF" << endl << "中序遍历：DBGEACF" << endl << "注意使用英文符号！" << endl;
            cout << "请输入前序遍历：" << endl;
            cin >> Pre_str;
            cout << "请输入中序遍历：" << endl;
            cin >> In_str;
            BT.CreateBinaryTree_Per_In(BT.root,(const char*)Pre_str.c_str(),(const char*)In_str.c_str(),Pre_str.size());//把STL中的string容器转换成C语言风格的字符串：先.c_str,再const char*
            cout << "创建成功！" << endl;
        }
            return;
        case 4://根据后序和前序方式创建
        {
            BT.InitBinTree();
            string In_str, Post_str;
            cout << "请使用中序遍历和后序遍历创建二叉树" << "例如：" << endl << "中序遍历：DBGEACF" << endl << "后序遍历：DGEBFCA" << endl << "注意使用英文符号！" << endl;
            cout << "请输入中序遍历：" << endl;
            cin >> In_str;
            cout << "请输入后序遍历：" << endl;
            cin >> Post_str;
            BT.CreateBinaryTree_In_Post(BT.root, (const char*)In_str.c_str(), (const char*)In_str.c_str(), Post_str.size());
            cout << "创建成功！" << endl;
        }
            return;
        case 5://二叉树初始化
            BT.InitBinTree();
            return;
        default://退出该函数
            return;
        }
    }
}
void BinTreeTraver(BinaryTree& BT)//遍历二叉树
{
    system("cls");//清屏
    int select;
    while (true)
    {
        BT.ShowTraverMenu();
        cin >> select;
        switch (select)
        {
        case 1://层序遍历
            BT.LevelOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 2://先序遍历
            BT.PreOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 3://中序遍历
            BT.InOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 4://后序遍历
            BT.PostOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        default://退出该函数
            return;
        }
    }
}
void BinTreeAttribute(BinaryTree& BT)//获取二叉树的属性
{
    system("cls");//清屏
    int select;
    while (true)
    {
        BT.ShowAttributeMenu();
        cin >> select;
        switch (select)
        {
        case 1://获取节点个数
            cout << "该二叉树的结点个数：" << endl << BT.Get_BinaryTreeNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 2://获取树的深度
            cout << "该二叉树的深度：" << endl << BT.Get_BinaryTreeDegree(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 3://获取叶子节点数
            cout << "该二叉树的叶子结点个数：" << endl << BT.Get_BinaryTreeLeafCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 4://获取单孩子节点数
            cout << "该二叉树的单个孩子结点数(度为一的结点)：" << endl << BT.Get_BinaryTreeSingleChildNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 5://获取度为二节点数
            cout << "该二叉树度为二的结点数（双孩子结点）：" << endl << BT.Get_BinaryTreeTwoChildNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        default://退出该函数
            return;
        }
    }
}
int main()
{
    BinaryTree BT('#');//利用有参构造创建对象，空数据字符为‘#’
    int select;//用户选择
    while (true)
    {
        BT.ShowMainMenu();//调用主菜单
        cin >> select;
        switch (select)
        {
        case 1://创建二叉树
            BinTreeCreate(BT);//进入创建菜单
            system("pause");
            system("cls");
            break;
        case 2://遍历二叉树
            if (BT.root != NULL)//先进入创建菜单，并且创建二叉树，才能进入遍历菜单
            {
                BinTreeTraver(BT);//遍历菜单
            }
            else
            {
                cout << "请先创建二叉树！" << endl;
            }
            system("pause");
            system("cls");
            break;
        case 3://获取二叉树的属性
            if (BT.root != NULL)//先进入创建菜单，并且创建二叉树，才能进入属性菜单
            {
                BinTreeAttribute(BT);//属性菜单
            }
            else
            {
                cout << "请先创建二叉树！" << endl;
            }
            system("pause");
            system("cls");
            break;
        default://结束程序
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return 0;
        }
    }

}