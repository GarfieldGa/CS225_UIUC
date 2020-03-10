#include <string>
#include <stack>
#include <iostream>
using namespace std;

bool isValid(string input) {
    stack<char> st;
    for (unsigned int i = 0; i < input.length(); i++) {
      if (input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']' || input[i] == '{' || input[i] == '}') {
        st.push(input[i]);
      }
    }
    char tmp1 = ' ';
    char tmp2 = ' ';
    char tmp3 = ' ';
    while (!st.empty()) {
      if (tmp1 == ' ' && (tmp2 != ' ' || tmp3 != ' ')) {
        return false;
      }
      if (tmp2 == ' ' && tmp3 != ' ') {
        return false;
      }
      if (tmp1 == ' ') {
        tmp1 = st.top();
        st.pop();
        continue;
      }
      if (tmp1 == ')' && st.top() == '(') {
        tmp1 = ' ';
        st.pop();
        continue;
      }
      if (tmp1 == ']' && st.top() == '[') {
        tmp1 = ' ';
        st.pop();
        continue;
      }
      if (tmp1 == '}' && st.top() == '{') {
        tmp1 = ' ';
        st.pop();
        continue;
      }
      if (tmp2 == ' ') {
        tmp2 = st.top();
        st.pop();
        continue;
      }
      if (tmp2 == ')' && st.top() == '(') {
        tmp2 = ' ';
        st.pop();
        continue;
      }
      if (tmp2 == ']' && st.top() == '[') {
        tmp2 = ' ';
        st.pop();
        continue;
      }
      if (tmp2 == '}' && st.top() == '{') {
        tmp2 = ' ';
        st.pop();
        continue;
      }
      if (tmp3 == ' ') {
        tmp3 = st.top();
        st.pop();
        continue;
      }
      if (tmp3 == ')' && st.top() == '(') {
        tmp3 = ' ';
        st.pop();
        continue;
      }
      if (tmp3 == ']' && st.top() == '[') {
        tmp3 = ' ';
        st.pop();
        continue;
      }
      if (tmp3 == '}' && st.top() == '{') {
        tmp3 = ' ';
        st.pop();
        continue;
      }
    }
    if (tmp1 != ' ' || tmp2 != ' ' || tmp3 != ' ') {
      return false;
    }
    return true;    // modify this!
}
