#include <iostream> 
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std; 

void func(string x, string y, int pxy, int pgap);
  
int main(int argc, char* argv[]) {
    //copying sequence 1 in a string
    ifstream f1;
    f1.open(argv[1]);
    if(f1.fail()){
        cout << "File 1 does not exist";
        return 1;
    }
    stringstream buf1;
    buf1 <<f1.rdbuf();
    string seq_1 = buf1.str();
    cout << "Sequence 1 : " << seq_1 <<endl;

    //copying sequence 2 in a string
    ifstream f2;
    f2.open(argv[2]);
    if(f2.fail()){
        cout << "File 2 does not exist";
        return 1;
    }
    stringstream buf2;
    buf2 <<f2.rdbuf();
    string seq_2 = buf2.str();
    cout << "Sequence 2 : " << seq_2 << "\n" << endl;

    //  program works on the logic of minimizing penalty, so penalty values are positive and match score is 0
    int misMatchPenalty = 3;
    int gapPenalty = 2;

    cout << "Scoring scheme: ";
    cout << "Match = 0, Mis-match Penalty = 3, Gap penalty = 2\n" << endl; 
 
    // calling the function to calculate the result
    func(seq_1, seq_2, 
        misMatchPenalty, gapPenalty);

    
    return 0; 
}

void func(string x, string y, int pxy, int pgap){
    int i, j; // initialising variables
     
    int m = x.length(); // length of gene1
    int n = y.length(); // length of gene2
     
    // table for storing optimal substructure answers
    int dp[n+m+1][n+m+1] = {0};
 
    // initialising the table 
    for (i = 0; i <= (n+m); i++)
    {
        dp[i][0] = i * pgap;
        dp[0][i] = i * pgap;
    }    
 
    // calculating the minimum penalty
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i - 1][j - 1] + pxy , 
                                dp[i - 1][j] + pgap    , 
                                dp[i][j - 1] + pgap    });
            }
        }
    }
 
    // Reconstructing the solution
    int l = n + m; // maximum possible length
     
    i = m; j = n;
     
    int xpos = l;
    int ypos = l;
 
    // Final answers for the respective strings
    int xans[l+1], yans[l+1];
     
    while ( !(i == 0 || j == 0))
    {
        if (x[i - 1] == y[j - 1])
        {
            xans[xpos--] = (int)x[i - 1];
            yans[ypos--] = (int)y[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j - 1] + pxy == dp[i][j])
        {
            xans[xpos--] = (int)x[i - 1];
            yans[ypos--] = (int)y[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j] + pgap == dp[i][j])
        {
            xans[xpos--] = (int)x[i - 1];
            yans[ypos--] = (int)'_';
            i--;
        }
        else if (dp[i][j - 1] + pgap == dp[i][j])
        {
            xans[xpos--] = (int)'_';
            yans[ypos--] = (int)y[j - 1];
            j--;
        }
    }
    while (xpos > 0)
    {
        if (i > 0) xans[xpos--] = (int)x[--i];
        else xans[xpos--] = (int)'_';
    }
    while (ypos > 0)
    {
        if (j > 0) yans[ypos--] = (int)y[--j];
        else yans[ypos--] = (int)'_';
    }
 
    // Since we have assumed the answer to be n+m long, 
    // we need to remove the extra gaps in the starting 
    // id represents the index from which the arrays
    // xans, yans are useful
    int id = 1;
    for (i = l; i >= 1; i--)
    {
        if ((char)yans[i] == '_' && (char)xans[i] == '_')
        {
            id = i + 1;
            break;
        }
    }
 
    // Printing the final answer
    cout << "Minimum Penalty in aligning the genes = ";
    cout << dp[m][n] << "\n\n";
    cout << "The aligned genes are :\n";
    for (i = id; i <= l; i++)
    {
        cout<<(char)xans[i];
    }
    cout << "\n";
    for (i = id; i <= l; i++)
    {
        cout << (char)yans[i];
    }
    cout << "\n\n";
    return;
}