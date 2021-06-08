#include <iostream>
#include <string>
#include <fstream>
#include <vector>


bool isOperator(std::string);
bool isOperand(std::string);

template <class T>
class stack //stack with templates
{
private:
    int p_t;
    T STACK[256];
public:
    stack()
    {
        p_t = -1;
    }
    T pop()
    {
        p_t--;
        return STACK[p_t + 1];
    }
    void push(T v)
    {
        p_t++;
        STACK[p_t] = v;
    }
    int check_pt()
    {
        return p_t;
    }
};

class Node
{
private:
    Node* left;
    Node* right;
    std::string inside;
    int counter;

public:
    Node()
    {
        left = nullptr;
        right = nullptr;
        inside = '\0';
        counter = 0;
    }
    Node(std::string ins)
    {
        left = nullptr;
        right = nullptr;
        inside = ins;
        if ((ins.length() > 2) or (isdigit(ins[0]) != 0))
            counter = 2;
        else
            counter = 0;
    }
    Node(Node* l, Node* r, std::string ins = "\0")
    {
        left = l;
        right = r;
        inside = ins;
        counter = 0;
    }

    Node* get_left(){ return left; }
    Node* get_right() { return right; }
    std::string get_inside() { return inside; }
    int get_counter() { return counter; }

    void set_left(Node* l) { left = l; }
    void set_right(Node* r) { right = r; }
    void set_inside(std::string ins) { inside = ins; }
    void set_counter(int a) { counter = a; }

};

class Constructor
{
private:
    Node* root;

    Node* add_new(std::string ins)
    {
        Node* temp = new Node(ins);
        return temp;
    }

    Node* construct_tree(std::string ins, Node* nova)
    {
        Node* temp;
        if (nova == nullptr)
        {
            temp = add_new(ins);
        }
        else
        {
            if (isOperator(ins))
            {
                if (nova->get_right() == nullptr)
                {
                    nova->set_right(construct_tree(ins, nova->get_right()));
                }
                else if (nova->get_right()->get_counter() < 2)
                {
                    nova->set_right(construct_tree(ins, nova->get_right()));
                }
                else if (nova->get_right()->get_counter() >= 2)
                {
                    nova->set_left(construct_tree(ins, nova->get_left()));
                }
                nova->set_counter(nova->get_counter()-1);
            }
            else
            {
                if (nova->get_right() == nullptr)
                {
                    nova->set_right(construct_tree(ins, nova->get_right()));
                }
                else if ((isOperator(nova->get_right()->get_inside())) and ((nova->get_right()->get_counter() < 2)))
                {
                    nova->set_right(construct_tree(ins, nova->get_right()));
                }
                else
                {
                    nova->set_left(construct_tree(ins, nova->get_left()));
                }
                nova->set_counter(nova->get_counter() + 1);
            }
            temp = nova;
        }
        return temp;
    }
public:
    Constructor()
    {
        root = nullptr;
    }
   

    Node* construct(std::string* out, int n)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            root = construct_tree(out[i], root);
        }
        return root;
    }

    

    void output_tree(Node* output)
    {
        if (output != nullptr)
        {
            std::cout << output->get_inside();
            std::cout << " ";
            output_tree(output->get_right());
            output_tree(output->get_left());
        }
    }

    Node* get_root() { return root; }
};

class Calculation
{
private:
    Node* root;
    double result;

    double pow(double a, double b)
    {
        if (b > 0)
        {
            return a*pow(a, b - 1);
        }
        else
        {
            return 1;
        }
    }

    double calculate(Node *n)
    {
        double a, b, c;
        if (n != nullptr)
        {
            if (isOperator(n->get_inside()))
            {
                a = calculate(n->get_left());
                b = calculate(n->get_right());
                switch (n->get_inside()[0])
                {
                case '+':
                    c = a + b;
                    break;
                case '-':
                    c = a - b;
                    break;
                case '*':
                    c = a * b;
                    break;
                case '/':
                    c = a / b;
                    break;
                case '^':
                    c = pow(a,b);
                    break;
                }
            }
            else
            {
                c = stod(n->get_inside());
            }
            return c;
        }
    }

public:
    Calculation(Node* r)
    {
        root = r;
        result = calculate(root);
    }

    double get_calculation()
    {
        return result;
    }
};

class Parser
{
private:

public:

};
class FileRead
{
private:
    std::fstream pFile;
    std::string buffer;
    std::vector<std::string> input_from_file;
    std::vector<std::pair< std::string, std::string>> pairs;
    int elnum;

    void normalize()
    {
        for (int i = 0; i < elnum-1; i++)
        {
            buffer = input_from_file[i].substr(0, input_from_file[i].find(' ', 0));
            buffer += input_from_file[i].substr(input_from_file[i].find_last_of(' '));
            buffer.erase(buffer.length() - 1);
            input_from_file[i] = buffer;
        }
        input_from_file[elnum - 1].erase(input_from_file[elnum - 1].length() - 1);
        std::string a, b;
        for (int i = 0; i < elnum - 1; i++)
        {
            a = input_from_file[i].substr(0, input_from_file[i].find(' '));
            b = input_from_file[i].substr(input_from_file[i].find(' ') + 1);
            pairs.push_back(std::make_pair(a, b));
        }
    }
public:
    FileRead(std::string name)
    {
        pFile.open(name, std::ios::in);
        int i = 0;
        while (!pFile.eof())
        {
            getline(pFile, buffer);
            input_from_file.push_back(buffer);
            std::cout << buffer << std::endl;
        }
        pFile.close();
        elnum = input_from_file.size();
        normalize();
    }

    void output()
    {
        for (int i = 0; i < elnum; i++)
        {
            std::cout << input_from_file[i] << std::endl;
        }
        for (int i = 0; i < elnum-1; i++)
        {
            std::cout << pairs[i].first << " " << pairs[i].second << std::endl;
        }
    }
    


    std::string get_statement() { return input_from_file[elnum - 1]; }
    std::vector<std::pair<std::string, std::string>> get_pairs() { return pairs; }



};


//class Node //допоміжний класс дерева
//{
//private:
//    int inside;
//    Node* left;
//    Node* right;
//public:
//    Node()
//    {
//        inside = 0;
//        left = NULL;
//        right = NULL;
//    }
//    Node* new_node(int ins) //створення нової ноди
//    {
//        Node* temp = new Node;
//        temp->inside = ins;
//        temp->left = temp->right = NULL;
//        return temp;
//    }
//
//    Node* add_node(int ins, Node* tree) //додавання нової ноди
//    {
//        Node* temp;
//        if (tree == NULL)
//        {
//            temp = new_node(ins);
//        }
//        else
//        {
//            if (ins < tree->inside)
//            {
//                tree->left = add_node(ins, tree->left);
//            }
//            else
//            {
//                tree->right = add_node(ins, tree->right);
//            }
//            temp = tree;
//        }
//        return temp;
//    }
//
//    Node* get_left() { return left; } //геттери
//    Node* get_right() { return right; }
//    int get_inside() { return inside; }
//
//    ~Node() //рекурсивний деструктор
//    {
//        if (this != NULL)
//        {
//            delete right;
//            delete left;
//        }
//    }
//};

std::string console_interp(int, char* []);
int num_of_elements(std::string);
std::string* divide_into_elements(std::string, int);
std::string* replace_variables(std::string*, std::vector<std::pair<std::string, std::string>>, int);
std::string* sort_station(std::string*, int*);
char priority(char, char);
//int get_through(std::string*, int);
//int pow(int, int);

int main(int _argc, char* _argv[])
{
    ////std::string infix = console_interp(_argc, _argv);
    //std::string infix;                            //debug testing
    //getline(std::cin, infix);

    std::string infix;
    FileRead fromfile("test.txt");
    fromfile.output();
    infix = fromfile.get_statement();
    std::cout << isalpha('b') << std::endl;

    int n = num_of_elements(infix);
    std::string* infix_alg = divide_into_elements(infix, n);
    infix_alg = replace_variables(infix_alg, fromfile.get_pairs(), n);
    for (int i = 0; i < n; i++)
    {
        std::cout << infix_alg[i] << std::endl;
    }

    std::string* out_temp = sort_station(infix_alg, &n);

    

    std::string* out = new std::string[n];
    out = out_temp;
    for (int i = 0; i < n; i++)
    {
        std::cout << out[i] << " ";
    }
    std::cout << std::endl;

    //int sum = get_through(out, n);
    //std::cout << "Result: " << sum << std::endl;

    //Node_c b('*');
    //Constructor a(b);
    //std::string out[2] = { "heh" , "mda" };
    //a.construct(out, 7);

    
        
    Constructor constr;
    constr.construct(out, n);
    constr.output_tree(constr.get_root());
    Calculation calculated(constr.get_root());
    std::cout << std::endl;
    std::cout << calculated.get_calculation() << std::endl;
    
}

bool isOperator(std::string ch)
{
    if ((ch.length() < 2) and ((isdigit(ch[0]) == 0) and (isalpha(ch[0]) == 0)))
        return true;
    else
        return false;
}

bool isOperand(std::string ch)
{
    if ((ch.length() > 1) or (isdigit(ch[0]) != 0) or (isalpha(ch[0]) != 0))
        return true;
    else
        return false;
}

std::string console_interp(int argc, char* argv[]) //interpreting console input
{
    std::string L = "";
    for (int i = 1; i < argc; i++)
    {
        L += argv[i];
    }
    return L;
}

int num_of_elements(std::string S) //getting number of elements
{
    int count_el = 0;
    bool flag = true;
    for (int i = 0; i < S.length(); i++)
    {
        switch (S[i])
        {
        case '+':
        case '/':
        case '^':
        case '*':
        case '(':
        case ')':
            flag = true;
            count_el++;
            break;
        case '-':
            if (i == 0)
                ;
            else if (S[i - 1] == '(')
                ;
            else
            {
                count_el++;

            }
            flag = true;
            break;
        default:
            if (flag)
            {
                count_el++;
                flag = false;
            }
        }
    }
    return count_el;
}

std::string* divide_into_elements(std::string D, int n) //dividing into operators and operands
{
    std::string* L = new std::string[n];
    int i = 0;
    int k = 0;
    int j = 0;
    if (D[0] == '-')
    {
        j = 1;
    }
    while (j < D.length())
    {
        if (((isdigit(D[j]) == 0) and ((isalpha(D[j])) == 0)) and (k - j == 0) and ((isdigit(D[j + 1]) != 0) or (isalpha(D[j+1]) != 0)))
        {
            L[i] = D.substr(j, 1);
            k++;
            i++;
        }
        else if (((isdigit(D[j]) == 0) and (isalpha(D[j])==0)) and (D[j] == '(') and (D[j + 1] == '-'))
        {
            k = j;
            j += 2;
            L[i] = D.substr(k, 1);
            i++;
            k++;
            while ((isdigit(D[j]) != 0) or (isalpha(D[j]) != 0))
            {
                j++;
            }
            L[i] = D.substr(k, j - k);
            i++;
            k = j;
            if (D[j] == ')')
            {
                L[i] = D.substr(k, 1);
                j++;
                k++;
                i++;
            }
            if (j >= D.length())
            {
                return L;
            }

            L[i] = D.substr(k, 1);
            k++;
            i++;
        }
        else if ((isdigit(D[j]) == 0) and (isalpha(D[j]) == 0))
        {
            L[i] = D.substr(k, j - k);
            k = j;
            i++;
            L[i] = D.substr(k, 1);
            i++;
            k++;
        }
        j++;
    }
    if (i < n)
    {
        L[i] = D.substr(k, j - k);
    }
    return L;
}

std::string* replace_variables(std::string* B, std::vector<std::pair<std::string, std::string>> pairs, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (isalpha(B[i][0]) != 0)
        {
            for (int j=0; j<pairs.size(); j++)
            {
                if (B[i] == pairs[j].first)
                {
                    B[i] = pairs[j].second;
                }
            }
        }
    }
    return B;
}

std::string* sort_station(std::string* L, int* n_ext) //Shunting-Yard algorithm
{
    int n = *n_ext;
    stack<char> ST;
    char l;
    std::string* out = new std::string[n];
    int i = 0;
    int j = 0;
    bool flag;
    while (j < n)
    {
        if ((L[j].length() > 1) or (isdigit(L[j][0]) != 0))
        {
            out[i] = L[j];
            i++;
        }
        else
        {
            if ((L[j][0] != ')') and (L[j][0] != '('))
            {
                while (ST.check_pt() > -1)
                {
                    l = ST.pop();
                    if (l == '(')
                    {
                        ST.push(l);
                        break;
                    }
                    else if (priority(l, L[j][0]) == l)
                    {
                        out[i] = l;
                        i++;
                    }
                    else
                    {
                        ST.push(l);
                        break;
                    }
                }
                ST.push(L[j][0]);
            }
            else if (L[j][0] == '(')
            {
                ST.push(L[j][0]);
            }
            else if (L[j][0] == ')')
            {
                while (ST.check_pt() > -1)
                {
                    l = ST.pop();
                    if (l == '(')
                    {
                        *n_ext -= 2;
                        break;
                    }
                    out[i] = l;
                    i++;
                }
            }
        }
        j++;
    }
    while (ST.check_pt() > -1)
    {
        out[i] = ST.pop();
        i++;
    }
    return out;
}

char priority(char a, char b) //priority check
{
    char a_n = ' ';
    char b_n = ' ';
    char PRIORITY_LIST[10] = { '^','2','*','1','/','1','+','0','-','0' };
    for (int i = 0; i < 10; i += 2)
    {
        if (a == PRIORITY_LIST[i])
        {
            a_n = PRIORITY_LIST[i + 1];
        }
        if (b == PRIORITY_LIST[i])
        {
            b_n = PRIORITY_LIST[i + 1];
        }
    }
    if (a_n > b_n)
    {
        return a;
    }
    else if ((a_n < b_n) or ((a_n == b_n) and (a == '^')))
    {
        return b;
    }
    else
    {
        return a;
    }
}

//int get_through(std::string* L, int n) //getting through recieved postfix form
//{
//    stack<int> ST;
//    for (int i = 0; i < n; i++)
//    {
//        if ((L[i].length() > 1) or ((isdigit(L[i][0])) != 0))
//        {
//            ST.push(stoi(L[i]));
//        }
//        else
//        {
//            switch (L[i][0])
//            {
//            case '+':
//            {
//                int A, B;
//                A = ST.pop();
//                B = ST.pop();
//                ST.push(B + A);
//                break;
//            }
//            case '-':
//            {
//                int A, B;
//                A = ST.pop();
//                B = ST.pop();
//                ST.push(B - A);
//                break;
//            }
//            case '*':
//            {
//                int A, B;
//                A = ST.pop();
//                B = ST.pop();
//                ST.push(B * A);
//                break;
//            }
//            case '/':
//            {
//                int A, B;
//                A = ST.pop();
//                B = ST.pop();
//                ST.push(B / A);
//                break;
//            }
//            case '^':
//            {
//                int A, B;
//                A = ST.pop();
//                B = ST.pop();
//                if (A >= 0)
//                {
//                    ST.push(pow(B, A));
//                }
//                else
//                {
//                    ST.push(1 / pow(B, A));
//                }
//                break;
//            }
//            }
//        }
//    }
//    return ST.pop();
//}

//int pow(int a, int b) //recursive power function
//{
//    if (b > 0)
//    {
//        return a * pow(a, b - 1);
//    }
//    else
//    {
//        return 1;
//    }
//}