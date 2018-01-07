#pragma once
#include <algorithm>
template <typename T>
struct node
{
	T inf;
	node<T> *left, *right;
};

template <typename T>
class BinTree
{
private:
	node<T>* root;

	void DeleteBinTree(node<T> * &) const;
	void Copy(node<T>* &, node<T>* const &) const;
	void CopyBinTree(BinTree<T> const &);
	void pr(const node<T> *) const;
	void CreateBinTree(node<T> * &) const;

public:
	BinTree();
	~BinTree();
	BinTree(BinTree<T> const &);
	BinTree& operator= (BinTree<T> const &);

	T RootBinTree() const;
	BinTree<T>& LeftBinTree() const;
	BinTree<T>& RightBinTree() const;
	node<T>* GetRoot();
	bool empty() const;
	void print() const;
	void Create();
	void Create3(T, BinTree<T>, BinTree<T>);
	int getHeight(node<T>*);
	void printCurrentLevel(node<T>*, int);
	void levelOrderTraversal(node<T>*);
	node<T>* LCA(node<T>*, T, T);
};

template<typename T>
BinTree<T>::BinTree()
{
	root = NULL;
}

template <typename T>
BinTree<T>::~BinTree()
{
	DeleteBinTree(root);
}

template <typename T>
BinTree<T>::BinTree(BinTree<T> const & r)
{
	CopyBinTree(r);
}

template <typename T>
BinTree<T>& BinTree<T>::operator= (BinTree<T> const & r)
{
	if (this != &r)
	{
		DeleteBinTree(root);
		CopyBinTree(r);
	}
	return *this;
}

template<typename T>
void BinTree<T>::DeleteBinTree(node<T>* & p) const
{
	if (p)
	{
		DeleteBinTree(p->left);
		DeleteBinTree(p->right);
		delete p;
		p = NULL;
	}
}

template <typename T>
void BinTree<T>::Copy(node<T>* & pos, node<T>* const & r) const
{
	pos = NULL;
	if (r)
	{
		pos = new node<T>;
		pos->inf = r->inf;
		Copy(pos->left, r->left);
		Copy(pos->right, r->right);
	}
}

template <typename T>
void BinTree<T>::CopyBinTree(BinTree<T> const & r)
{
	Copy(root, r.root);
}

template <typename T>
bool BinTree<T>::empty() const
{
	return root == NULL;
}

template <typename T>
T BinTree<T>::RootBinTree() const
{
	return root->inf;
}

template <typename T>
node<T>* BinTree<T>::GetRoot()
{
	return root;
}

template <typename T>
BinTree<T>& BinTree<T>::LeftBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->left);
	return t;
}


template <typename T>
BinTree<T>& BinTree<T>::RightBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->right);
	return t;
}

template <typename T>
void BinTree<T>::pr(const node<T>* p) const
{
	if (p)
	{
		pr(p->left);
		std::cout << p->inf << " ";
		pr(p->right);
	}
}

template <typename T>
void BinTree<T>::print() const
{
	pr(root);
}

template <typename T>
void BinTree<T>::Create3(T x, BinTree<T> l, BinTree<T> r)
{
	root = new node<T>;
	root->inf = x;
	Copy(root->left, l.root);
	Copy(root->right, r.root);
}

template <typename T>
void BinTree<T>::CreateBinTree(node<T>* & pos) const
{
	T x;
	char c;
	std::cout << "root: ";
	std::cin >> x;

	pos = new node<T>;
	pos->inf = x;
	pos->left = NULL;
	pos->right = NULL;

	std::cout << "left BinTree of: " << x << " y/n ? ";
	std::cin >> c;
	if (c == 'y')
		CreateBinTree(pos->left);

	std::cout << "right BinTree of: " << x << " y/n ? ";
	std::cin >> c;
	if (c == 'y')
		CreateBinTree(pos->right);
}

template <typename T>
void BinTree<T>::Create()
{
	CreateBinTree(root);
}

template <typename T>
int BinTree<T>::getHeight(node<T>* r)
{
	if (!r)
		return -1;
	return 1 + max(getHeight(r->left), getHeight(r->right));
}

template <typename T>
void BinTree<T>::printCurrentLevel(node<T>* r, int level)
{
	if (r == NULL)
		return;
	if (level == 0)
	{
		cout << r->inf << " ";
	}
	else if(level > 0)
	{
		printCurrentLevel(r->left, level - 1);
		printCurrentLevel(r->right, level - 1);
	}
}

template <typename T>
void BinTree<T>::levelOrderTraversal(node<T>* r)
{
	for (int i = 0; i <= getHeight(r); i++)
	{
		printCurrentLevel(r, i);
	}
}

template <typename T>
node<T>* BinTree<T>::LCA(node<T>* r, T v1, T v2)
{
	if (r == NULL)
		return NULL;

	if (r->inf == v1 || r->inf == v2)		//if the root is v1 or v2 then the root is LCA
		return r;

	node<T>* leftLCA = LCA(r->left, v1, v2);
	node<T>* rightLCA = LCA(r->right, v1, v2);

	if (leftLCA && rightLCA)	
		return r;

	return (leftLCA != NULL) ? leftLCA : rightLCA;
}
