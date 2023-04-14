#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


#define  MAX_DISKS_CNT         (10)
#define  RODS_CNT              (4)
#define  MAX_CNFG_CNT          (1 << (MAX_DISKS_CNT << 1))
#define  CNFG_CNT(disksCnt)    (1 << ((disksCnt) << 1))


int hashCode(vector<int> cnfg)
{
    int code = 0;
    int base = 1;
    
    for (int i = 0; i < cnfg.size(); i++) {
        code += (cnfg[i] - 1) * base;
        base <<= 2;     // base *= 4
    }
    
    return code;
}


vector<int> reveseHashCode(int code, int size) {
    vector<int> cnfg;
    
    for (int i = 0; i < size; i++) {
        cnfg.push_back(code % 4 + 1);
        code >>= 2;     // / 4
    }
    
    return cnfg;
}


void initMovesCnt(int* movesCnt, vector<int> posts, int val) {
    int idx = hashCode(posts);
    
    if (movesCnt[idx] <= val)
        return;
    
    movesCnt[idx] = val;
    
    /*
     * topOfRodSize[i] holds size of the top most disk
     * of rod i (1 indexed)
     */
    int topOfRodSize[RODS_CNT + 1];
    for (int i = 1; i <= RODS_CNT; i++) {
        topOfRodSize[i] = -1;    // initailly empty
    }
    
    for (int i = 0; i < posts.size(); i++) {
        int rod = posts[i];
        
        if (topOfRodSize[rod] != -1) // there's already a top disk
            continue;
        
        topOfRodSize[rod] = i;
        
        for (int destRod = 1; destRod <= RODS_CNT; destRod++) {
            if (topOfRodSize[destRod] == -1) {
                posts[i] = destRod;
                initMovesCnt(movesCnt, posts, val + 1);
                posts[i] = rod;
            }
        }
    }
}


/*
 * Complete the 'hanoi' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY posts as parameter.
 */

int hanoi(vector<int> posts) {
    
    int cnfgCnt = CNFG_CNT(posts.size());
    int movesCnt[MAX_CNFG_CNT];
    
    for (int i = 0; i < MAX_CNFG_CNT; i++) 
        movesCnt[i] = INT32_MAX;
    
    vector<int> initGame;
    // stask all in rod 1 in initial game
    for (int i = 0; i < posts.size(); i++) 
        initGame.push_back(1);
    
    int idx = hashCode(initGame);
    movesCnt[idx] = 0;
    queue<int> initializedIdxs;
    initializedIdxs.push(idx);
    
    while (initializedIdxs.size() > 0) {
        int srcIdx = initializedIdxs.front();
        initializedIdxs.pop();
        vector<int> src = reveseHashCode(srcIdx, posts.size());
        
        int desMoves = movesCnt[srcIdx] + 1;
        
        /*
        * topOfRodSize[i] holds size of the top most disk
        * of rod i (1 indexed) in src game configuration
        */
        int topOfRodSize[RODS_CNT + 1];
        for (int i = 1; i <= RODS_CNT; i++) {
            topOfRodSize[i] = -1;    // initailly empty
        }
        
        for (int i = 0; i < src.size(); i++) {
            int rod = src[i];
            
            if (topOfRodSize[rod] != -1) // there's already a top disk
                continue;
            
            topOfRodSize[rod] = i;
            
            for (int destRod = 1; destRod <= RODS_CNT; destRod++) {
                if (topOfRodSize[destRod] == -1) {
                    src[i] = destRod;
                    
                    int desIdx = hashCode(src);
                    if (movesCnt[desIdx] > desMoves) {
                        movesCnt[desIdx] = desMoves;
                        initializedIdxs.push(desIdx);
                    }
                    
                    src[i] = rod;
                }
            }
        }
    }
    
    idx = hashCode(posts);
    return movesCnt[idx];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string loc_temp_temp;
    getline(cin, loc_temp_temp);

    vector<string> loc_temp = split(rtrim(loc_temp_temp));

    vector<int> loc(n);

    for (int i = 0; i < n; i++) {
        int loc_item = stoi(loc_temp[i]);

        loc[i] = loc_item;
    }

    int res = hanoi(loc);

    fout << res << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
