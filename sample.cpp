#include <iostream>

// Reference:
// https://qiita.com/yohhoy/items/f3d90c598348817cd29c

// Conversations with ChatGPT:
// https://chatgpt.com/share/679ffb96-50b8-800b-8bb1-d59e7102a392

#include <type_traits>

namespace sfinae1
{
    /*
    Define a function that returns twice of the input value.
    The functtion should return twice of the input value if the input value is a numeric type.
    If the input value is not a numeric type, the function should return "*".
    */

    // Function to check if the input value is a numeric type.
    template <typename T>
    struct is_number :
        std::integral_constant<
        bool,
        std::is_integral<T>::value || std::is_floating_point<T>::value
        > {};

    // Function to return twice of the input value for numeric type.
    template <typename T>
    typename std::enable_if<is_number<T>::value>::type
        twice(T x)
    {
        std::cout << (x * 2) << std::endl;
    }

    // Function to return "*" for non-numeric type.
    template <typename T>
    typename std::enable_if<!is_number<T>::value>::type
        twice(T x)
    {
        std::cout << "*" << std::endl;
    }
} // sfinae1

namespace sfinae2
{
    /*
    Define a function that returns twice of the input value.
    The functtion should return twice of the input value if the input value is a numeric type.
    Add "u" after the output value if the input value is an unsigned integer type.             <--- Added
    If the input value is not a numeric type, the function should return "*".
    */

    // Function to check if the input value is a numeric type.
    template <typename T>
    struct is_number :
        std::integral_constant<
        bool,
        std::is_integral<T>::value || std::is_floating_point<T>::value
        > {};

    // Function to return twice of the input value for numeric type.
    template <typename T>
    typename std::enable_if<is_number<T>::value && std::is_unsigned<T>::value>::type
        twice(T x)
    {
        std::cout << (x * 2) << "u" << std::endl;
    }

    template <typename T>
    typename std::enable_if<is_number<T>::value && !std::is_unsigned<T>::value>::type
        twice(T x)
    {
        std::cout << (x * 2) << std::endl;
    }

    // Function to return "*" for non-numeric type.
    template <typename T>
    typename std::enable_if<!is_number<T>::value>::type
        twice(T x)
    {
        std::cout << "*" << std::endl;
    }
} // sfinae2

namespace use_concept {
    /*
    Define a function that returns twice of the input value.
    The functtion should return twice of the input value if the input value is a numeric type.
    Add "u" after the output value if the input value is an unsigned integer type.
    If the input value is not a numeric type, the function should return "*".
    */

    // Concept to check if the input value is a numeric type.
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    // Primary template
    void twice(auto) {
        std::cout << "*" << std::endl;
    }

    // Specialization for numeric type
    void twice(Number auto x) {
        std::cout << (x * 2) << std::endl;
    }

    // Specialization for unsigned integer type
    void twice(std::unsigned_integral auto x) {
        std::cout << (x * 2) << "u" << std::endl;
    }

} // concept

// ----- Test -----
int main()
{
    std::cout << "sfinae1" << std::endl;
    sfinae1::twice(3); // 6
    sfinae1::twice(3u); // 6
    sfinae1::twice(3.14); // 6.28
    sfinae1::twice("Hello"); // *
    sfinae1::twice(std::string("Hello")); // *
    sfinae1::twice(char('A'));
    std::cout << std::endl;

    std::cout << "sfinae2" << std::endl;
    sfinae2::twice(3); // 6
    sfinae2::twice(3u); // 6u
    sfinae2::twice(3.14); // 6.28
    sfinae2::twice("Hello"); // *
    std::cout << std::endl;

    std::cout << "concept" << std::endl;
    use_concept::twice(3); // 6
    use_concept::twice(3u); // 6u
    use_concept::twice(3.14); // 6.28
    use_concept::twice("Hello"); // *
    std::cout << std::endl;

    return 0;
}
