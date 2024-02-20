#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out | std::ios::binary);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //读出第 n 个 int 的值赋给 tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return ;
        /* your code here */
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekg((n - 1) * sizeof(int), std::ios::beg);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
        file.close();
        return ;
    }

    //将 tmp 写入第 n 个 int 的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return ;
        /* your code here */
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekp((n - 1) * sizeof(int), std::ios::beg);
        file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
        file.close();
        return ;
    }

    //在文件合适位置写入类对象 t，并返回写入的位置索引 index
    //位置索引意味着当输入正确的位置索引 index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引 index 可以取为对象写入的起始位置
     int write(T &t) {
         /* your code here */
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekp(0, std::ios::end);
        int len = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
        return len;
     }

     //用 t 的值更新位置索引 index 对应的对象，保证调用的 index 都是由 write 函数产生
     void update(T &t, const int index) {
         /* your code here */
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekp(index, std::ios::beg);
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
        return ;
     }

     //读出位置索引 index 对应的 T 对象的值并赋值给 t，保证调用的 index 都是由 write 函数产生
     void read(T &t, const int index) {
         /* your code here */
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekg(index, std::ios::beg);
        file.read(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
        return ;
     }

    // //删除位置索引 index 对应的对象 (不涉及空间回收时，可忽略此函数)，保证调用的 index 都是由 write 函数产生
    // void Delete(int index) {
    //     /* your code here */
    // }
    //  int write(T &t) {
    //     file.open(file_name, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
    //     int index = file.tellp(); // get current write position as index
    //     file.write(reinterpret_cast<char *>(&t), sizeof(T));
    //     file.close();
    //     return index;
    // }

    // void update(T &t, const int index) {
    //     file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
    //     file.seekp(index);
    //     file.write(reinterpret_cast<char *>(&t), sizeof(T));
    //     file.close();
    // }

    // void read(T &t, const int index) {
    //     file.open(file_name, std::ios::in | std::ios::binary);
    //     file.seekg(index);
    //     file.read(reinterpret_cast<char *>(&t), sizeof(T));
    //     file.close();
    // }

    void Delete(int index) {
        
    }
};


#endif //BPT_MEMORYRIVER_HPP