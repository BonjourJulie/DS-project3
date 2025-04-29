//#include<iostream>
//#include<vector>
//using namespace std;
//
//class Error {
//private:
//	string message;
//public:
//	Error() :message("发生错误") {}
//	Error(string message) {
//		this->message = message;
//	}
//	void show()const {
//		cout << message << endl;
//	}
//};
//
//
//
//vector<int> SearchSmallestSameElement(vector<int>& a, vector<int>& b, vector<int>& c,int aNum,int bNum,int cNum) {
//	//进行查找
//	int i = 0, j = 0, k = 0,f = 0;
//
//	while (i < aNum && j < bNum && k < cNum) {
//		if (a[i] == b[j] && b[j] == c[k]) {
//			f = 1;
//			break;
//		}
//		int minX = min(a[i], min(b[j], c[k]));
//		if (minX == a[i]) i++;
//		if (minX == b[j]) j++;
//		if (minX == c[k]) k++;
//	}
//
//	if (f) {
//		return { a[i],i+1,j+1,k+1  };
//	}
//	else {
//		throw Error("NOT FOUND");
//	}
//
//}
//
//int FindMid01(int n, vector<int>& a, vector<int>& b) {
//	vector<int> mix;
//	int i = 0, j = 0;
//	while (i < n && j < n) {
//		if (a[i] > b[j]) {
//			mix.push_back(b[j]);
//			j++;
//		}
//		else {
//			mix.push_back(a[i]);
//			i++;
//		}
//	}
//	while (j < n) { mix.push_back(b[j++]); }
//	while (i < n) { mix.push_back(a[i++]); }
//
//	i = 0;
//	while (i < n-1) i++;
//	return mix[i];
//	
//}
///*
//找中位数，就是找第n小的数，比较2/n，舍弃较小数组的前2/n。
//*/
//int FindKth(vector<int>& a, vector<int>& b, int aStart, int bStart, int k, int n) {
//	if (aStart >= n) return b[bStart + k - 1];
//	if (bStart >= n) return a[aStart + k - 1];
//	if (k == 1)return min(a[aStart], b[bStart]);
//
//	//防止溢出
//	int aMid = (aStart + k / 2 - 1 < n) ? a[aStart + k / 2 - 1] : n+1;
//	int bMid = (bStart + k / 2 - 1 < n) ? b[bStart + k / 2 - 1] : n+1;
//
//	if (aMid < bMid) return FindKth(a, b, aStart + k / 2, bStart, k - k / 2, n);
//	else return FindKth(a, b, aStart, bStart + k / 2, k - k / 2, n);
//
//}
//int FindMid02(int n,vector<int>& a, vector<int>& b) {
//	return FindKth(a, b, 0, 0, n, n);
//}
//
//int main() {
//	try {
//		//得到三个数组
//		
//		cout << "请输入三个数组的大小：";
//		int aNum, bNum, cNum;
//		cin >> aNum >> bNum >> cNum;
//
//		vector<int> a(aNum), b(bNum), c(cNum);
//		cout << "请输入第一个数组：";
//		for (int i = 0; i < aNum; i++) cin >> a[i];
//		cout << "请输入第二个数组：";
//		for (int i = 0; i < bNum; i++) cin >> b[i];
//		cout << "请输入第三个数组：";
//		for (int i = 0; i < cNum; i++) cin >> c[i];
//		
//		
//
//		vector<int> ans = SearchSmallestSameElement(a,b,c,aNum,bNum,cNum);
//		for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
//			cout << *it << " ";
//		}
//		cout << endl;
//
//		cout << "请输入数组大小：";
//		int Num;
//		cin >> Num;
//
//		vector<int> d(Num), e(Num);
//		cout << "请输入第一个数组：";
//		for (int i = 0; i < Num; i++) cin >> d[i];
//		cout << "请输入第二个数组：";
//		for (int i = 0; i < Num; i++) cin >> e[i];
//
//
//		cout <<"第一种方式查找中位数的结果" << FindMid01(Num, d, e) << endl;
//		cout << "第二种方式查找中位数的结果" << FindMid02(Num, d, e) << endl;
//	}	
//	catch (Error e) {
//		e.show();
//	}
//
//}