#include <iostream>
#include <cstdlib> 

/** recursively compute the n-th number of the sequence
 *  J(n) = 0                                      if n = 0
 *         1                                      if n = 1
 *         1                                      if n = 2
 *         J(n - 1) + 2 * J(n - 2) + 4 * J(n - 3) if n > 2
 * @param n - index
 * @return the n-th number of the sequence, 
 *         or -1 if invalid (negative index)
 */
long long seriesRecursive(int n)
{
    if (n < 0) //case for n < 0
        return -1;

    if (n == 0) //base case for n = 0
        return 0;

    if (n == 1 || n == 2) //base case for n = 1 and n = 2
        return 1;

    return (seriesRecursive(n - 1) + 2 * seriesRecursive(n - 2) + 4 * seriesRecursive(n - 3));
}


int main(int argc, char* argv[])
{
    // Read n from command line argument
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1; 
    }

    // Convert n to an integer
    int n = std::atoi(argv[1]); 

    // Compute series value of n
    long long result = seriesRecursive(n); 
    std::cout << "seriesRecursive(" << n << ") = " << result << std::endl;

    return 0; 
}
