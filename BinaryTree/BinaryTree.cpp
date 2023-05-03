#include<iostream>//���������
#include<stack>//STL�е�ջ����
#include<string>//STL�е��ַ�������
#include<queue>//STL�еĶ�������
typedef char ElemType;
using namespace std;//ʹ�ñ�׼�����ռ�
struct BinTreeNode//�����������
{
    ElemType data;//������
    BinTreeNode* leftChild, * rightChild;//���Ӻ��Һ���
    BinTreeNode():leftChild(NULL), rightChild(NULL) {}//�޲ι��캯����ʼ���б����޲ι�������������ʱ�����Ӻ��Һ���Ĭ��ָNULL��
    BinTreeNode(ElemType x, BinTreeNode* l = NULL, BinTreeNode* r = NULL):
        data(x), leftChild(l), rightChild(r) {}//�вι��캯����ʼ���б��Լ�Ĭ�ϲ���
    /*
    * Ϊʲôʹ�ó�ʼ���б����������ڹ�������������ʱ���������͸��ӷḻ���ҿ���ʲôҲ�����Σ�Ĭ�Ϲ��죩��Ҳ����ֻ�������������
    * �ڲ�ָ�����Ӻ��Һ��ӵ�����£�Ĭ��ΪNULL���������Խ�ʡ������Խ�����ʱ����Ҫָ�����Һ���NULL
    */
};
class BinaryTree//�������ࣨ���ģ�
{
public://����Ȩ��
    BinaryTree():root(NULL) {};//���������޲ι��죬�Լ���ʼ���б�Ĭ�ϸ��ڵ�ΪNULL
    BinaryTree(ElemType value):root(NULL),RefValue(value) {}; //���������вι��캯�����Լ���ʼ���б����롰���ݽ�������ı�־��
    BinaryTree(BinaryTree& s) {};//�������캯�������ƶ�������
    ~BinaryTree() {};//��������
    //����
    void InitBinTree();//�������ĳ�ʼ��������������
    void CreateBinaryTree_GenTab(); //ʹ�ù����ķ�������������������������
    void CreateBinaryTree_PerOrder(BinTreeNode* &BTRoot);//ʹ��ǰ�������������������������������
    void CreateBinaryTree_Per_In(BinTreeNode*& BTRoot, const char* Pre, const char* In, int n);//ʹ��ǰ������������������������������������
    void CreateBinaryTree_In_Post(BinTreeNode*& BTRoot, const char* In, const char* Post, int n);//ʹ����������ͺ����������������(��������)
    //����
    void LevelOrder(BinTreeNode* BTRoot);//�������������������
    void PreOrder(BinTreeNode* BTRoot);//ǰ�����������������
    void InOrder(BinTreeNode* BTRoot);//�������������������
    void PostOrder(BinTreeNode* BTRoot);//�������������������
    //����
    int Get_BinaryTreeNodeCount(BinTreeNode* BTRoot);//��ȡ�������Ľڵ����������������
    int Get_BinaryTreeDegree(BinTreeNode* BTRoot);//��ȡ����������ȣ�����������
    int Get_BinaryTreeLeafCount(BinTreeNode* BTRoot);//��ȡ������Ҷ�ӽ����������������
    int Get_BinaryTreeSingleChildNodeCount(BinTreeNode* BTRoot);//��ȡ�������������ӵĽ��������Ϊ1��������������
    int Get_BinaryTreeTwoChildNodeCount(BinTreeNode* BTRoot);//��ȡ�������������ӽ��������Ϊ2��������������

    //�˵�
    void ShowMainMenu();//��Ҫ�˵�������������
    void ShowCreateMenu();//�����˵�������������
    void ShowTraverMenu();//�����˵�������������
    void ShowAttributeMenu();//���Բ˵�������������

    //���ڳ�Ա����
    BinTreeNode* root;//���ڵ�
    ElemType RefValue;//���ַ�'#',��������Ϊ��

};
void BinaryTree::InitBinTree()//�������ĳ�ʼ��
{
    if (this->root != NULL)//��ʼ�����ö������ĸ��ڵ��ÿ�
    {
        this->root = NULL;
    }
    cout << "��ʼ���ɹ���" << endl;
}
void BinaryTree::CreateBinaryTree_GenTab()//ʹ�ù����ķ�������������
{
    stack<BinTreeNode*>s;//ջ����
    string BTstr;//�ַ�������
    BinTreeNode* BTRoot = NULL;//���ڵ����
    BinTreeNode* t = NULL;//��¼��ǰ�����Ľڵ�
    BinTreeNode* p = NULL;//��¼ջ��Ԫ��
    int k = 0;//k�Ǵ������ӻ����Һ��ӵı��
    cin >> BTstr;//��������
    for (int i = 0; i < BTstr.size(); i++)//�ѹ������ÿ�����ݴ洢
    {
        switch (BTstr[i])//�ж������ÿ���ַ�
        {
        case'(':
            s.push(p);//����ǡ�(����˵������������Ԫ��
            k = 1;//�����1
            break;

        case')':
            s.pop();//���������')',˵���ý���Ԫ���Ѿ�������Ҫ��ջ
            break;
        case',':
            k = 2;//����ǡ�,��,˵���������Һ���Ԫ��
            break;
        default:
            p = new BinTreeNode(BTstr[i]);//�����ϵͳ�ڶ�������ռ䣬���������вι��캯��������һ��ֵΪBTstr[i]�Ľ�㣬���Ұѽ����׵�ַ���ظ�p
            if (BTRoot == NULL)//���ν��������������
            {
                BTRoot = p;
            }
            else if (k == 1)//���Ӳ���
            {
                t = s.top();
                t->leftChild= p;
            }
            else if (k == 2)//�Һ��Ӳ���
            {
                t = s.top();
                t->rightChild = p;
            }
            break;
        }
    }
    this->root = BTRoot;//�Ѹ���㣬��ֵ�����ڵĳ�Ա����
    cout << "�����ɹ���" << endl;
}
void BinaryTree::CreateBinaryTree_PerOrder(BinTreeNode * &BTRoot)//ʹ����������������������ݹ飩
{
    ElemType elem;//��������
    if (cin >> elem)
    {
        if (elem != this->RefValue)//�����RefValue��'#'
        {       
            BTRoot = new BinTreeNode(elem);//�вι���
            CreateBinaryTree_PerOrder(BTRoot->leftChild);//��������
            CreateBinaryTree_PerOrder(BTRoot->rightChild);//�����Һ���
        }
    }
    else
    {
        BTRoot = NULL;//������#������ʾ�����ݣ�BTRootֱ��Ϊ��
    }
}
void BinaryTree::CreateBinaryTree_Per_In(BinTreeNode*& BTRoot, const char* Pre, const char* In, int n)//ʹ������������������������
{
    if (n <= 0)//ǰ��������ַ�����Ϊ0�������Ѿ��޽��                                //��һ��������Ҫ�ݹ�Ķ���
    {                                                                                 //�ڶ���������ǰ������ַ�
        BTRoot = NULL;                                                                //��������������������ַ�
        return;                                                                       //���ĸ�������ǰ������ַ�����
    }
    //����ǰ����������ҵ�������ĸ��ڵ㣬Ҳ���������е�һ������λ�ã��������ڵ㣬Ȼ��������������ҵ�����ֵ���ڵ��±꣬�г�����������ǰ�������
    int k = 0;
    while (Pre[0] != In[k])//���������ҵ�pre[0]��ֵ
    {
        k++;
    }
    BTRoot = new BinTreeNode(In[k]);//�������
    CreateBinaryTree_Per_In(BTRoot->leftChild, Pre + 1, In, k);
    CreateBinaryTree_Per_In(BTRoot->rightChild, Pre + k + 1, In + k + 1, n - k - 1);
}
void BinaryTree::CreateBinaryTree_In_Post(BinTreeNode*& BTRoot, const char* In, const char* Post, int n)//ʹ����������ͺ����������������
{                                                                                                                                                  
    if (n == 0)                                             
    {                                                                             
        BTRoot == NULL;                                                       
        return;
    }
//���ݺ�����������ҵ�������ĸ��ڵ��ֵ��Ҳ�������������һ���ڵ㣨���鳤�� - 1����λ�ã��ɴ˴������ڵ㣬Ȼ��������������ҵ�����ֵ���ڵ��±꣬�г����������ĺ���������
    char r = *(Post + n - 1);//�����ֵ
    BTRoot = new BinTreeNode(r);//���쵱ǰ���
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

void BinaryTree::LevelOrder(BinTreeNode* BTRoot)//�������������ʵ�֣�
{
    queue<BinTreeNode*>Q;//��������
    Q.push(BTRoot);//��������
    BinTreeNode* t = NULL;
    while (!Q.empty())
    {
        t = Q.front();//t�ȼ�ס��ͷ,�ٽ���ͷ����
        Q.pop();
        cout << t->data; //���ʶ�ͷԪ�ص�����
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
void BinaryTree::PreOrder(BinTreeNode *BTRoot)//ǰ�����������ʵ�֣����ݹ飩
{
    if (BTRoot != NULL)
    {
        cout << BTRoot->data;
        PreOrder(BTRoot->leftChild);
        PreOrder(BTRoot->rightChild);
    }
}
void BinaryTree::InOrder(BinTreeNode* BTRoot)//�������������ʵ�֣����ݹ飩
{
    if (BTRoot != NULL)
    {
        InOrder(BTRoot->leftChild);
        cout << BTRoot->data;
        InOrder(BTRoot->rightChild);
    }
}
void BinaryTree::PostOrder(BinTreeNode* BTRoot)//�������������ʵ�֣����ݹ飩
{
    if (BTRoot != NULL)
    {
        InOrder(BTRoot->leftChild);
        InOrder(BTRoot->rightChild);
        cout << BTRoot->data;
    }
}

int BinaryTree::Get_BinaryTreeNodeCount(BinTreeNode* BTRoot)//��ȡ�������Ľ��������ݹ飩
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    return Get_BinaryTreeNodeCount(BTRoot->leftChild) + Get_BinaryTreeNodeCount(BTRoot->rightChild) + 1;
}
int BinaryTree::Get_BinaryTreeDegree(BinTreeNode* BTRoot)//��ȡ��������ȣ��ݹ飩
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    int i = Get_BinaryTreeDegree(BTRoot->leftChild);
    int j = Get_BinaryTreeDegree(BTRoot->rightChild);
    return i < j ? j + 1 : i + 1;//ȡ���ֵ
}
int BinaryTree::Get_BinaryTreeLeafCount(BinTreeNode* BTRoot)//��ȡ��������Ҷ�������ݹ飩
{
    int LeafCount;
    if (BTRoot == NULL)
    {
        LeafCount = 0;
    }
    else if (BTRoot->leftChild == NULL && BTRoot->rightChild == NULL)//���������Ľ��
    {
        LeafCount = 1;
    }
    else
    {
        LeafCount = Get_BinaryTreeLeafCount(BTRoot->leftChild) + Get_BinaryTreeLeafCount(BTRoot->rightChild);//�����Ͻ��ŵݹ�
    }
    return LeafCount;
}
int BinaryTree::Get_BinaryTreeSingleChildNodeCount(BinTreeNode* BTRoot)//��ȡ�������������������ݹ飩
{
    if (BTRoot == NULL)
    {
        return 0;
    }
    else if ((BTRoot->rightChild != NULL && BTRoot->leftChild == NULL) || (BTRoot->rightChild == NULL && BTRoot->leftChild != NULL))//���������Ľ��
    {
        return Get_BinaryTreeSingleChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeTwoChildNodeCount(BTRoot->rightChild) + 1;
    }
    else
    {
       return Get_BinaryTreeSingleChildNodeCount(BTRoot->leftChild) + Get_BinaryTreeSingleChildNodeCount(BTRoot->rightChild);//�����Ͻ��ŵݹ�
    }
    
}
int BinaryTree::Get_BinaryTreeTwoChildNodeCount(BinTreeNode* BTRoot)//��ȡ��������Ϊ2�Ľ�������ݹ飩
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

void BinaryTree::ShowMainMenu()//��Ҫ�˵�������ʵ�֣�
{
    cout << "     ****************" << endl;
    cout << "     *  ����������  *" << endl;
    cout << "     ****************" << endl;
    cout << "     * 1����    ��  *" << endl;
    cout << "     * 2����    ��  *" << endl;
    cout << "     * 3����    ��  *" << endl;
    cout << "     * 0����    ��  *" << endl;
    cout << "     ****************" << endl;
    cout << "����������ѡ�";
}
void BinaryTree::ShowCreateMenu()//��Ҫ�˵�������ʵ�֣�
{
    cout << "     ******************" << endl;
    cout << "     *   ����������   *" << endl;
    cout << "     ******************" << endl;
    cout << "     * 1����  ��  ��  *" << endl;
    cout << "     * 2��ǰ      ��  *" << endl;
    cout << "     * 3��ǰ�������  *" << endl;
    cout << "     * 4�����������  *" << endl;
    cout << "     * 5����  ʼ  ��  *" << endl;
    cout << "     * 0����      ��  *" << endl;
    cout << "     ******************" << endl;
    cout << "����������ѡ�" ;
}
void BinaryTree::ShowTraverMenu()//�����˵�������ʵ�֣�
{
    cout << "     ****************" << endl;
    cout << "     *  ����������  *" << endl;
    cout << "     ****************" << endl;
    cout << "     * 1����    ��  *" << endl;
    cout << "     * 2����    ��  *" << endl;
    cout << "     * 3����    ��  *" << endl;
    cout << "     * 4����    ��  *" << endl;
    cout << "     * 0����    ��  *" << endl;
    cout << "     ****************" << endl;
    cout << "����������ѡ�";
}
void BinaryTree::ShowAttributeMenu()//���Բ˵�������ʵ�֣�
{
    cout << "     ********************" << endl;
    cout << "     *     ����������   *" << endl;
    cout << "     ********************" << endl;
    cout << "     * 1�� ������     *" << endl;
    cout << "     * 2�� �������     *" << endl;
    cout << "     * 3��Ҷ�ӽڵ���    *" << endl;
    cout << "     * 4�������ӽڵ���  *" << endl;
    cout << "     * 5����Ϊ���ڵ���  *" << endl;
    cout << "     * 0����        ��  *" << endl;
    cout << "     ********************" << endl;
    cout << "����������ѡ�";
}


void BinTreeCreate(BinaryTree& BT)//����������
{
    system("cls");
    int select;
    while (true)
    {
        BT.ShowCreateMenu();
        cin >> select;
        switch (select)
        {
        case 1://���ݹ����ʽ����
            BT.InitBinTree();
            cout << "���ù����ķ�ʽ����������" << endl << "���磺A(B(D,E(G,)),C(,F))" << endl << "ע��ʹ��Ӣ�ķ��ţ�" << endl;
            BT.CreateBinaryTree_GenTab();
            return;
        case 2://����ǰ�������ʽ����
            BT.InitBinTree();
            cout << "����ǰ������ķ�ʽ����������" << endl << "���磺ABC##DE#G##F###" << endl << "ע��ʹ��Ӣ�ķ��ţ�" << endl;
            BT.CreateBinaryTree_PerOrder(BT.root);
            cout << "�����ɹ���" << endl;
            return;
        case 3://����ǰ�������ʽ����
        {
            BT.InitBinTree();
            string Pre_str, In_str;
            cout << "��ʹ��ǰ������������������������" <<endl<< "���磺" << endl << "ǰ�������ABDEGCF" << endl << "���������DBGEACF" << endl << "ע��ʹ��Ӣ�ķ��ţ�" << endl;
            cout << "������ǰ�������" << endl;
            cin >> Pre_str;
            cout << "���������������" << endl;
            cin >> In_str;
            BT.CreateBinaryTree_Per_In(BT.root,(const char*)Pre_str.c_str(),(const char*)In_str.c_str(),Pre_str.size());//��STL�е�string����ת����C���Է����ַ�������.c_str,��const char*
            cout << "�����ɹ���" << endl;
        }
            return;
        case 4://���ݺ����ǰ��ʽ����
        {
            BT.InitBinTree();
            string In_str, Post_str;
            cout << "��ʹ����������ͺ����������������" << "���磺" << endl << "���������DBGEACF" << endl << "���������DGEBFCA" << endl << "ע��ʹ��Ӣ�ķ��ţ�" << endl;
            cout << "���������������" << endl;
            cin >> In_str;
            cout << "��������������" << endl;
            cin >> Post_str;
            BT.CreateBinaryTree_In_Post(BT.root, (const char*)In_str.c_str(), (const char*)In_str.c_str(), Post_str.size());
            cout << "�����ɹ���" << endl;
        }
            return;
        case 5://��������ʼ��
            BT.InitBinTree();
            return;
        default://�˳��ú���
            return;
        }
    }
}
void BinTreeTraver(BinaryTree& BT)//����������
{
    system("cls");//����
    int select;
    while (true)
    {
        BT.ShowTraverMenu();
        cin >> select;
        switch (select)
        {
        case 1://�������
            BT.LevelOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 2://�������
            BT.PreOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 3://�������
            BT.InOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;;
        case 4://�������
            BT.PostOrder(BT.root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        default://�˳��ú���
            return;
        }
    }
}
void BinTreeAttribute(BinaryTree& BT)//��ȡ������������
{
    system("cls");//����
    int select;
    while (true)
    {
        BT.ShowAttributeMenu();
        cin >> select;
        switch (select)
        {
        case 1://��ȡ�ڵ����
            cout << "�ö������Ľ�������" << endl << BT.Get_BinaryTreeNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 2://��ȡ�������
            cout << "�ö���������ȣ�" << endl << BT.Get_BinaryTreeDegree(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 3://��ȡҶ�ӽڵ���
            cout << "�ö�������Ҷ�ӽ�������" << endl << BT.Get_BinaryTreeLeafCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 4://��ȡ�����ӽڵ���
            cout << "�ö������ĵ������ӽ����(��Ϊһ�Ľ��)��" << endl << BT.Get_BinaryTreeSingleChildNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        case 5://��ȡ��Ϊ���ڵ���
            cout << "�ö�������Ϊ���Ľ������˫���ӽ�㣩��" << endl << BT.Get_BinaryTreeTwoChildNodeCount(BT.root) << endl;
            system("pause");
            system("cls");
            break;
        default://�˳��ú���
            return;
        }
    }
}
int main()
{
    BinaryTree BT('#');//�����вι��촴�����󣬿������ַ�Ϊ��#��
    int select;//�û�ѡ��
    while (true)
    {
        BT.ShowMainMenu();//�������˵�
        cin >> select;
        switch (select)
        {
        case 1://����������
            BinTreeCreate(BT);//���봴���˵�
            system("pause");
            system("cls");
            break;
        case 2://����������
            if (BT.root != NULL)//�Ƚ��봴���˵������Ҵ��������������ܽ�������˵�
            {
                BinTreeTraver(BT);//�����˵�
            }
            else
            {
                cout << "���ȴ�����������" << endl;
            }
            system("pause");
            system("cls");
            break;
        case 3://��ȡ������������
            if (BT.root != NULL)//�Ƚ��봴���˵������Ҵ��������������ܽ������Բ˵�
            {
                BinTreeAttribute(BT);//���Բ˵�
            }
            else
            {
                cout << "���ȴ�����������" << endl;
            }
            system("pause");
            system("cls");
            break;
        default://��������
            cout << "��ӭ�´�ʹ�ã�" << endl;
            system("pause");
            return 0;
        }
    }

}