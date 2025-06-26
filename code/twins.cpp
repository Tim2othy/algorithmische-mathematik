# include <iostream>
# include <vector>

void print(int n)
{
    std::cout << " " << n;
}

void twins(int n, int d)
{
    std::vector<bool> is_prime(n + 1, true);

    for (int i = 2; i <= n; ++i)
    {
        if (is_prime[i])
        {
            if (i >= (d + 2) && is_prime[i - d]) /* Checks if i is already large enough, so you don't accedintally leave the vector, and then checks if i-d is prime */
            {
                std::cout << "One pair is: ";
                print(i - d);
                std::cout << " and";
                print(i);
                std::cout << ".\n";
            }
            for (int j = i; j <= n / i; ++j) /* This is just the Sieb des Eratosthenes)*/
            {
                is_prime[i * j] = false;
            }
        }
    }
}


int get_input_n()
{
    int n;
    std::cout << "This program lists all pairs of primes up to a given integer n, with difference of a given integer d.\n"
        << "(For this exersise set n = 1000000 and d = 2.)\n"
        << "Enter an integer for n: \n";

    std::cin >> n;
    return n;
}

int get_input_d()
{
    int d;
    std::cout << "Enter an integer for d: ";
    std::cin >> d;
    return d;
}

int main()
{
    int n = get_input_n();
    int d = get_input_d();

    if ((n < 2) || (d < 0))
    {
        std::cout << "Larger number please.\n";
    }
    else
    {
        std::cout << "The pairs of twin primes up to " << n << " of difference " << d << " are:" << "\n";
        twins(n, d);
    }
}