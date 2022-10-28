#include <iostream>
using namespace std;


int test(string s)
        {
            int ctr_aa = 0;
            for (int i = 0; i < s.length() - 1; i++)
            {
                if (s.substr(i, 2) == "aa")
                {
                    ctr_aa++;
                }
            }
            return ctr_aa;
        }
        
int main() 
 {
  cout << test("bbaaccaag") << endl;  
  cout << test("jjkiaaasew") << endl;  
  cout << test("JSaaakoiaa") << endl;  
  return 0;    
}
