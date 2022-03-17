#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define N 40
int find_set(int *set, int);

int main()
{
    // read the file, generate the graph
    // ifstream file("example.txt");
    ifstream file("p107_network.txt");
    string str;
    int weight[N][N] = {0};
    if (!file)
    {
        cout << "Error: no input file" << endl;
    }
    else
    {
        int i = 0;
        while (getline(file, str))
        {
            stringstream ss(str);
            int j = 0;
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                if (substr != "-")
                {
                    weight[i][j] = stoi(substr);
                }
                else
                {
                    weight[i][j] = 0; // INT_MAX
                }
                j += 1;
            }
            i += 1;
        }
    }

    int original_sum = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            original_sum += weight[i][j];
            // cout << weight[i][j] << " ";
        }
        // cout << endl;
    }
    original_sum /= 2;

    int res = 0;
    int set[N] = {0};
    for (int i = 0; i < N; i++)
    {
        set[i] = i;
    }

    for (int edges = 0; edges < N - 1; edges++)
    {
        int x = 0, y = 0;
        int min = 2147483647; // INT_MAX

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                // find minimum, check sets are different
                if ((find_set(set, i) != find_set(set, j)) &&
                    weight[i][j] && min > weight[i][j])
                {
                    min = weight[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        // union
        int x_set = find_set(set, x);
        int y_set = find_set(set, y);
        set[y_set] = x_set; // same: set[x_set]=y_set

        res += weight[x][y];
    }
    cout << res << endl;
    // cout << original_sum - res << endl;
    return 0;
}

int find_set(int *set, int i)
{
    while (set[i] != i)
    {
        i = set[i];
    }
    return i;
}