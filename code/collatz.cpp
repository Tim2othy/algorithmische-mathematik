# include <iostream>
# include <vector>
# include <string>

void print(int n)
{
    std::cout << n << "\n";
}

void print_s(std::string s)
{
    std::cout << s;
}

//Die funktion macht die eigentlichen collatz Schritte
// Und gibt die Laenge der folge für ein n aus

int collatz(long long n, std::vector<bool>& could_max)
{
    int length;
    length = 0;

    while (n > 1) {

        length = length + 1;

        if (n < 1000000)
        {
            could_max[n] = false; // Wenn man wirklich will, dass für jeden n die Folge berechnet wird kann man einfach diese
            // Zeile rausnehmen, dann wird es nur etwas laenger dauern.
            // Wobei es glaube ich gar nicht so viel Zeit spart, vielleicht macht es auch alles viel langsamer, weil man diesen vector braucht.
            //Die idee ist wie beim Priemzahl Sieb die zahlen die nicht mehr in frage kommen rauszusortieren.
        }

        if (n % 2 == 0) {
            n = n / 2;
        }
        else {

            if (n > 3606775569372413952) //Falls n größer als diese Zahl ist und mit 3 multipliziert wird gibt es einen overflow
            {
                print_s("Achtung Zahl zu groß");
                break;
            }

            n = 3 * n + 1;
        }
    }
    return length;
}

// Die funktion macht alles andere drumherum.
std::vector<int> calc(int n)
{
    std::vector<bool> could_max(n + 1, true);

    int length;
    int max_length = 0;
    int n_star = 0;

    for (int i = 1; i <= n; ++i) {

        if (could_max[i]) {

            length = collatz(i, could_max);

            if (max_length < length)
            {
                n_star = i;
                max_length = length;
            }
        }
    }
    std::vector<int> output(2);
    output[0] = n_star;
    output[1] = max_length;
    return(output);
}

int main()
{
    int n = 1000000;
    std::vector<int> output = calc(n);

    print_s("Das ist n_star, das n mit der laengsten Folge: ");
    print(output[0]);
    print_s("Das ist die laenge der von n_star ausgehenden Folge: ");
    print(output[1]);
}
