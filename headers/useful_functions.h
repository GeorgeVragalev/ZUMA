#include "main.h"

using std::cout;
using std::cin;

long power2(int n) {
    if (n == 0)
        return 1;
    else return power2(n - 1) * 2;
}

long x_to_power_n(int x, int n) {
    if (n == 0) return 1;
    else return x_to_power_n(x, n - 1) * x;
}

int GCD(int x, int y)
{
    int r = x % y;
    while (r != 0)
    {
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

void show_binary(int u)
{
    while(u > 1){
        if((u % 2) == 0){
            cout << "0";
        }else{
            cout << "1";
        }
        u = u >> 1;
    }
    cout << "1\n";
}

void ten_to_bin(int n, int p){
    int k;
    if (p==1) cout << n;
    else {
        k=n%2;
        ten_to_bin(n/2,p-1);
        cout << k;
    }
}

int max_of_array (int a, int *ar[])
{

    int count = 0;
    int max = *ar[0];
    for (count ; count < a; count++) {
        if( *ar[count] > max){
            max = *ar[count];
        }
    }

    return max;
}
//////////////////////////Big num sum////////////////////////
//Reverse string
void reverseS(string& str)
{
    int n = str.length();

    // Swap character starting from two ends
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}


// Function for finding sum of larger numbers
//Input 2 string with digits
string findSum(string str1, string str2)
{
    // Before proceeding further, make sure length
    // of str2 is larger.
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverseS(str1);
    reverseS(str2);

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');

        // Calculate carry for next step
        carry = sum/10;
    }

    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');

    // reverse resultant string
    reverseS(str);
    return str;
}
//////////////////////////Big num sum////////////////////////

//////////////Convert from any bas to base 10//////////////////////
//returning values of a character
int val(char c) {
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}
//converting number to decimal equivalent
int convert_decimal(char *str, int base) {
    int len = strlen(str);
    int power = 1;
    int num = 0;
    int i;
    for (i = len - 1; i >= 0; i--) {
        if (val(str[i]) >= base) {
            printf("Invalid Number");
            return -1;
        }
        num += val(str[i]) * power;
        power = power * base;
    }
    return num;
}
//////////////Convert from any bas to base 10//////////////////////