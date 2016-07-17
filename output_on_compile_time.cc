// file: output_on_compile_time.cc

template<int N>
struct print_size_as_warning
{
    char operator()() {return N + 256;} // always cause overflow
};

int main()
{
    // prove that "sizeof" is running on compile time
    print_size_as_warning<sizeof(int)>()();
    return 0;
}
