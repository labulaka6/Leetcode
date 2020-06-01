static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 纯数组模拟栈实现

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
		vector<int> numStack (tokens.size()/2 + 1, 0);
		int index = 0;
		for (string s : tokens) {
            char t = s[0];
            // 负数的第一位为符号位，为了不混淆，如果s的长度大于1则用第二位做判断，虽然可能是两位以上整数，但是不影响下面判断
            if(s.length() > 1) t = s[1];
			switch (t) {
			case '+':
				numStack[index - 2] += numStack[index - 1];
                index--;
				break;
			case '-':
				numStack[index - 2] -= numStack[index - 1];
                index--;
				break;
			case '*':
				numStack[index - 2] *= numStack[index - 1];
                index--;
				break;
			case '/':
				numStack[index - 2] /= numStack[index - 1];
                index--;
				break;
			default:
				numStack[index++] = atoi(s.c_str());
				break;
			}
		}
		return numStack[0];
    }
};

// 栈实现

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
		stack<int> numStack;
		int op1, op2;
		for (string s : tokens) {
            char t = s[0];
            // 负数的第一位为符号位，为了不混淆，如果s的长度大于1则用第二位做判断，虽然可能是两位以上整数，但是不影响下面判断
            if(s.length() > 1) t = s[1];
			switch (t) {
			case '+':
				op2 = numStack.top();
                numStack.pop();
				op1 = numStack.top();
                numStack.pop();
				numStack.push(op1 + op2);
				break;
			case '-':
				op2 = numStack.top();
                numStack.pop();
				op1 = numStack.top();
                numStack.pop();
				numStack.push(op1 - op2);
				break;
			case '*':
				op2 = numStack.top();
                numStack.pop();
				op1 = numStack.top();
                numStack.pop();
				numStack.push(op1 * op2);
				break;
			case '/':
				op2 = numStack.top();
                numStack.pop();
				op1 = numStack.top();
                numStack.pop();
				numStack.push(op1 / op2);
				break;
			default:
				numStack.push(atoi(s.c_str()));
				break;
			}
		}
		return numStack.top();
    }
};