static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution{
private:
    string str = "";
    unordered_map<char, int> m;
public:
    // Insert one char from stringstream
    void Insert(char ch){
        m[ch]++;
        str += ch;
    }
    // return the first appearence once char in current stringstream
    char FirstAppearingOnce(){
        for(char c : str){
            if(m[c] == 1) return c;
        }
        return '#';
    }

};