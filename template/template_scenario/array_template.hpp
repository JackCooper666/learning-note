/*
案例描述: 实现一个通用的数组类，要求如下：

可以对内置数据类型以及自定义数据类型的数据进行存储
将数组中的数据存储到堆区
构造函数中可以传入数组的容量
提供对应的拷贝构造函数以及operator=防止浅拷贝问题
提供尾插法和尾删法对数组中的数据进行增加和删除
可以通过下标的方式访问数组中的元素
可以获取数组中当前元素个数和数组的容量
*/

template <class T>
class MyArrary {
    public:
    MyArrary(int capacity){
        this->capacity = capacity;
        this->size = 0;
        this->Address = new T[this->capacity];
    }
    MyArrary(const MyArrary& other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->Address = new T[this->capacity];
        for (int i = 0; i < this->size; ++i) {
            //如果T为对象，而且还包含指针，必须需要重载 = 操作符，因为这个等号不是 构造 而是赋值，
			// 普通类型可以直接= 但是指针类型需要深拷贝
            this->Address[i] = other.Address[i]; // 深拷贝
        }
    }
    ~MyArrary() {
        if (this->Address != nullptr) {
            delete[] this->Address;
            this->Address = nullptr;
            this->size = 0;
            this->capacity = 0;
        }
    }
    void push_back(const T& value) {
        if (this->size >= this->capacity) {
            cout << "数组已满，无法添加新元素" << endl;
            return;
        }
        this->Address[this->size++] = value; // 添加新元素并增加大小
    }
    void pop_back() {
        if (this->size <= 0) {
            cout << "数组为空，无法删除元素" << endl;
            return;
        }
        --this->size; // 减少大小
    }
    void printsize() const {
        cout << "当前元素个数: " << this->size << endl;
    }
    void printcapacity() const {
        cout << "数组容量: " << this->capacity << endl;
    }
    MyArrary& operator=(const MyArrary& other) {
        if (this == &other){
            if (this->Address != nullptr) {
                delete[] this->Address; // 释放原有内存
                this->Address = nullptr; // 避免悬空指针
            }
            this->capacity = other.capacity;
            this->size = other.size;
            this->Address = new T[this->capacity]; // 分配新内存
            for (int i = 0; i < this->size; ++i) {
                this->Address[i] = other.Address[i]; // 深拷贝
            }
        }
        return *this; // 返回当前对象以支持链式赋值
    }
    T& operator[](int index) {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }
        return this->Address[index]; // 返回指定索引的元素
    }
    private:
    T* Address; // 存储数据的指针
    int size; // 当前元素个数
    int capacity; // 数组容量
};
