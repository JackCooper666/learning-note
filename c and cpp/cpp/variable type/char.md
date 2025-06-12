# isalnum()
The `isalnum()` function is a **character classification function** from the C++ Standard Library (`<cctype>` header). It checks whether a given character is **alphanumeric**, meaning it is either:
- A **letter** (`'A'-'Z'`, `'a'-'z'`), or
- A **digit** (`'0'-'9'`).
  
```cpp
#include <cctype>  // Required header

int isalnum(int c);
```

- **Parameter (`c`)**: The character to check (passed as an `int` or `char`).
- **Return Value**:
    - **Non-zero (true)**: If `c` is alphanumeric.
    - **0 (false)**: If `c` is **not** alphanumeric (e.g., spaces, symbols like `'@'`, `'#'`).

## **Example Usage**

### **1. Basic Check**
```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char c1 = 'A', c2 = '5', c3 = '@';
    cout << isalnum(c1) << endl;  // Output: 1 (true)
    cout << isalnum(c2) << endl;  // Output: 1 (true)
    cout << isalnum(c3) << endl;  // Output: 0 (false)
    return 0;
}
```
### **2. Filtering Alphanumeric Characters**
```cpp
string s = "Hello123!";
for (char c : s) {
    if (isalnum(c)) {
        cout << c;  // Output: "Hello123" (ignores '!')
    }
}
```

# tolower()
In C++, the `tolower()` function is used to **convert an uppercase character to its lowercase equivalent**.
## ✅ Function Signature
```cpp
int tolower(int ch);
```
- **Header**: `<cctype>` (or `<ctype.h>` in C-style)
- **Parameter**: `ch` — a character (as `int`) to be converted
- **Return**: If `ch` is an uppercase alphabet (like `'A'`), it returns its lowercase version (like `'a'`); otherwise, it returns the original character.
