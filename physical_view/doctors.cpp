#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define allvec(a) a.begin(), a.end()
#define curtime             chrono::high_resolution_clock::now()
#define timedif(start,end)  chrono::duration_cast<chrono::nanoseconds>(end - start).count()

using namespace std;

class Row
{
    // class for template of our row object
public:
    string dr_code, name, gender, address, designation;
    Row(string dr_code, string name, string gender, string address, string designation)
    {
        this->dr_code = dr_code;
        this->name = name;
        this->gender = gender;
        this->address = address;
        this->designation = designation;
    }
};
bool operator==(const Row &lhs, const Row &rhs)
{
    // operator overloading for == operator
    return (lhs.dr_code == rhs.dr_code && lhs.name == rhs.name && lhs.gender == rhs.gender && lhs.address == rhs.address && lhs.designation == rhs.designation);
}
bool operator!=(const Row &lhs, const Row &rhs)
{
    // operator overloading for != operator
    return !(lhs == rhs);
}
bool operator<(const Row &lhs, const Row &rhs)
{
    // operator overloading for < operator
    return (lhs.name < rhs.name);
}
bool operator>(const Row &lhs, const Row &rhs)
{
    // operator overloading for > operator
    return (lhs.name > rhs.name);
}
ostream &operator<<(ostream &os, const Row &r)
{
    os << "Dr. Code : " << r.dr_code << "\n";
    os << "Dr. Name : " << r.name << "\n";
    os << "Gender: " << r.gender << "\n";
    os << "Address : " << r.address << "\n";
    os << "Designation : " << r.designation << "\n";
    return os;
}

// empty row object
Row mt = Row("Empty", "Empty", "Empty", "Empty", "Empty");

int powerMod(int a, int b, int m)
{
    if (b == 0)
    {
        return (a % m);
    }
    int ans = powerMod(a, b >> 1, m);
    ans *= ans;
    ans %= m;
    if (b & 1)
    {
        ans *= a;
        ans %= m;
    }
    return ans;
}
int hashFunction(string s, int mod_1)
{
    int hashValue = 0;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        hashValue += ((i + 1) * powerMod((int)s[i], i + 1, mod_1)) % mod_1;
        hashValue %= mod_1;
    }
    return hashValue;
}

//---------------------------------------extendible hashing----------------------------------------------------//

class Extendible_Hashing
{
    map<string, vector<Row>> Table;
    map<string, int> mp;
    int MAX_BUCKET_SIZE = 4;

public:
    int cnt_splits;
    int insert(Row a)
    {
        string s = "";
        int val = hashFunction(a.dr_code, 1e5 + 3);
        //cout << "Hash Value for " << a.dr_code << " is " << val << "\n";
       // cout << "Hash Value : " << val << "\n";
        function<int(string)> split;
        split = [&](string in) -> int
        { 
            cnt_splits++;
            string s1 = "0" + in;
            string s2 = "1" + in;
            if (in.size() > 65)
                return -1;
            int bit = 1 << ((int)in.size());
            for (auto t : Table[in])
            {
                if (hashFunction(t.dr_code, 1e5 + 3) & bit)
                {
                    Table[s2].pb(t);
                }
                else
                {
                    Table[s1].pb(t);
                }
            }
            if (bit & val)
            {
                if (Table[s2].size() == MAX_BUCKET_SIZE)
                {

                    if (split(s2) == -1)
                        return -1;
                    Table[in].clear();
                    mp[in] = true;
                    return 0;
                }
                Table[s2].pb(a);
            }
            else
            {
                if (Table[s1].size() == MAX_BUCKET_SIZE)
                {

                    if (split(s1) == -1)
                        return -1;
                    Table[in].clear();
                    mp[in] = true;
                    return 0;
                }
                Table[s1].pb(a);
            }
            Table[in].clear();
            mp[in] = true;
            return 0;
        };
        for (int i = 1; 1 << i <= val; i++)
        {
            if (i & val)
            {
                s = "1" + s;
            }
            else
            {
                s = "0" + s;
            }
            if (!mp[s])
            {
                if (Table[s].size() == MAX_BUCKET_SIZE)
                {

                    return split(s);
                }
                Table[s].pb(a);
                return 0;
            }
        }
        return -1;
    }
    pair<bool,Row> find(Row a)
    {
        for(auto t: Table){
            for(auto tt: t.second){
                if(tt.dr_code==a.dr_code){
                    return make_pair(true,tt);
                }
            }
        }
        return make_pair(false,mt);
    }
    void print()
    {
        for (auto t : Table)
        {
            cout << t.first << " : \n";
            for (auto tt : t.second)
            {
                cout << tt;
            }
            cout << "\n";
        }
    }

    Extendible_Hashing(vector<Row> in, int MAX_BUCKET_SIZE)
    {
        for(auto t: in){
         //   cout << "Inserting : " << t.dr_code << "\n";
        }
        this->MAX_BUCKET_SIZE = MAX_BUCKET_SIZE;
        cnt_splits = 0;
        for (auto t : in)
        {
            //cout << "Inserting " << t.dr_code << "\n";
            if (insert(t) == -1)
                cout << "Table Full Cannot Insert\n";
        }
    }
};

int32_t main()
{

    vector<Row> input{
       Row("D2AT6Y","Dr. A.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT6Z","Dr. B.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT70","Dr. C.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT71","Dr. D.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT72","Dr. E.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT73","Dr. F.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT74","Dr. G.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT75","Dr. H.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT76","Dr. I.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT77","Dr. J.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT78","Dr. K.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT79","Dr. L.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT7A","Dr. M.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
        Row("D2AT7B","Dr. N.Mishra","M","B-1/2, Sector-5, Noida","Consultant"),
    };

    int choice;
    cout << "Choose 1 if you want to analyse hashing for differnt bucket sizes\n";
    cout << "Choose 2 if you want to simulate extendible hashing\n";
    cin >> choice;

    if(choice==2){

    



    int max_bucket_size;
    cout << "Enter the maximum bucket size : ";
    cin >> max_bucket_size;

    Extendible_Hashing E(input, max_bucket_size);
    // build a simulation for inserting deleting and searching
    while (1)
    {
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Print\n";
        cout << "4. Exit\n";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            string dr_code, name, gender, address, designation;
            cout << "Enter the details of the doctor\n";
            cout << "Dr. Code : ";
            cin >> dr_code;
            cout << "Dr. Name : ";
            cin >> name;
            cout << "Gender :";
            cin >> gender;
            cout << "Address : ";
            cin >> address;
            cout << "Designation : ";
            cin >> designation;

            Row r = Row(dr_code, name, gender, address, designation);
            if (E.insert(r) == -1)
                cout << "Table Full Cannot Insert\n";
        }
        else if (choice == 2)
        {
            string dr_code;
            cout << "Enter the dr_code to search : ";
            cin >> dr_code;
            Row r = Row(dr_code, "", "", "", "");
            if (E.find(r).first)
            {
               cout << "Found\n";
               cout << "Details : \n";
                cout << E.find(r).second;
            }
            else
            {
                cout << "Not Found\n";
            }
        }
        else if (choice == 3)
        {
            E.print();
        }
        else
        {
            break;
        }
    }
    }
    else{
        int no_of_instances;
        cout << "Enter the number of instances : ";
        cin >> no_of_instances;
        vector<int> bucket_sizes;
        
        for(int i=0;i<no_of_instances;i++){
            cout << "Enter the bucket size : ";
            int x;
            cin >> x;
            bucket_sizes.pb(x);
        }
        vector<int> cnt_splits;
        for(auto t: bucket_sizes){
            Extendible_Hashing E(input, t);
            cnt_splits.pb(E.cnt_splits);
        }
        for(int i=0;i<bucket_sizes.size();i++){
            cout << "Bucket Size : " << bucket_sizes[i] << " Number of Splits : " << cnt_splits[i] << "\n";
        }
    }
    return -1;
}