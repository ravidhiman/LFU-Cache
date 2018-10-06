#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

class Product
{
	int id;
	string name;
public:
	Product(int id, string name) :id(id), name(name) {}
	int getId() const
	{
		return id;
	}
	string getName() const
	{
		return name;
	}
};

ostream& operator<<(ostream& out,const Product& p)
{
	out << p.getId() << " " << p.getName().c_str();
	return out;
}

class DB
{
	vector<Product> records = { Product(1,"abc"),Product(2,"def"),Product(3,"xxx"),Product(4,"yyy"),Product(5,"zzz") };
public:
	Product getProduct(int productId)
	{
		for (int i = 0;i < records.size();i++)
		{
			if (records[i].getId() == productId)
				return records[i];
		}
	}
};

class LFU
{
	unordered_map<int, int> myMap;
	vector<pair<int, Product>> pq;
	int capacity;
	void heapify(int i);
	void insertKey(int i);
	void swap(pair<int, Product> &p1, pair<int, Product> &p2)
	{
		pair<int, Product> temp = p1;
		p1 = p2;
		p2 = temp;
	}
public:
	LFU(int N) :capacity(N) {}
	//void refer(Product p);
	void setProduct(Product p);
	Product getProduct(int productID);
	void displayCache()
	{
		for (auto i = 0;i <pq.size();i++)
		{
			cout << pq[i].first << " " << pq[i].second << ";";
		}
		cout << endl;
	}
};
void LFU::heapify(int i)
{
	int n = pq.size();
	int minima = i;
	int l = i*2 + 1;
	if (l < n)
	{
		minima = pq[l].first < pq[i].first ? l : i;
	}
	int r = i*2 + 2;
	if (r < n)
	{
		minima = pq[r].first < pq[minima].first ? r : minima;
	}
	if (i != minima)
	{
		myMap[pq[i].second.getId()] = minima;
		myMap[pq[minima].second.getId()] = i;
		swap(pq[i], pq[minima]);
		heapify(minima);
	}
}
void LFU::insertKey(int i)
{
	int parent = (i - 1) / 2;
	while (i && pq[parent].first > pq[i].first)
	{
		myMap[pq[i].second.getId()] = parent;
		myMap[pq[parent].second.getId()] = i;
		swap(pq[i], pq[parent]);
		i = parent;
		parent = (i - 2) / 2;
	}
}

//void LFU::refer(Product p)
//{
//	if (myMap.find(p.getId()) != myMap.end())
//	{
//		pq[myMap[p.getId()]].first++;
//		heapify(myMap[p.getId()]);
//	}
//	else
//	{
//		if (pq.size() == capacity)
//		{
//			pq[0] = pq[pq.size() - 1];
//			pq.pop_back();
//			myMap.erase(pq[0].second.getId());
//			heapify(0);
//		}
//		pq.push_back(make_pair(1, p));
//		myMap[p.getId()] = pq.size() - 1;
//		insertKey(pq.size() - 1);
//	}
//}

void LFU::setProduct(Product p)
{
	if (pq.size() == capacity)
	{
		pq[0] = pq[pq.size() - 1];
		pq.pop_back();
		myMap.erase(pq[0].second.getId());
		heapify(0);
	}
	pq.push_back(make_pair(1, p));
	myMap[p.getId()] = pq.size() - 1;
	insertKey(pq.size() - 1);
}

Product LFU::getProduct(int productID)
{
	Product p(-1, "no found");
	if (myMap.find(productID) != myMap.end())
	{

		pq[myMap[productID]].first++;
		heapify(myMap[productID]);
		p =  pq[myMap[productID]].second;
	}
	return p;
}

int main()
{
	LFU cache(4);
	DB db;

	if (cache.getProduct(1).getId() == -1)
	{
		Product p = db.getProduct(1);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(2).getId() == -1)
	{
		Product p = db.getProduct(2);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(1).getId() == -1)
	{
		Product p = db.getProduct(1);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(3).getId() == -1)
	{
		Product p = db.getProduct(3);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(2).getId() == -1)
	{
		Product p = db.getProduct(2);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(4).getId() == -1)
	{
		Product p = db.getProduct(4);
		cache.setProduct(p);
	}
	cache.displayCache();

	if (cache.getProduct(5).getId() == -1)
	{
		Product p = db.getProduct(5);
		cache.setProduct(p);
	}
	cache.displayCache();

	return 0;
}
