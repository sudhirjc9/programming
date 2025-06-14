#include <iostream>
#include <memory>

using namespace std;


class points{

	int x, y;

	public:
	points():x(0), y(0){
	
	}
	
	points(int a, int b):x(a), y(b){
		cout<<"points value is: ("<<x<<","<<y<<")"<<endl;
	}

};

int main(){
	
	unique_ptr<int> ptr1(new int(100));
	unique_ptr<int> ptr2(new int(200));
//	ptr2 = ptr1;
	unique_ptr<int> ptr3 = move(ptr1);

	cout<<"ptr2: "<<*ptr2<<endl;
	cout<<"ptr3: "<<*ptr3<<endl;

	shared_ptr<points> p1(new points());
	shared_ptr<points> p2(p1);
	cout<<"shared_count: "<<p1.use_count()<<endl;
}
