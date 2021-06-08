#include <iostream>
#include <string>
#include <fstream>
#include <vector>




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
    std::string* parsed_statement;
    int num_of_tokens;

    void Copy(std::string*);

    std::string* parse(std::string);

    int num_of_elements(std::string);
    void sort_station(std::string*);
    void replace_variables(std::vector < std::pair < std::string, std::string>>, std::string*);

    char priority(char, char);
public:
    Parser(std::string statement, std::vector<std::pair<std::string, std::string>> variables)
    {
        num_of_tokens = num_of_elements(statement);
        std::string* A = parse(statement);
        replace_variables(variables, A);
        sort_station(A);
        
        delete[] A;
    }

    std::string* get_parsed_statement() { return parsed_statement; }
    int get_num() { return num_of_tokens; }

    ~Parser()
    {
        delete[] parsed_statement;
    }
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

int main(int _argc, char* _argv[])
{
    std::string infix;
    FileRead fromfile("test.txt");
    Parser parced(fromfile.get_statement(), fromfile.get_pairs());    
    Constructor constr;
    constr.construct(parced.get_parsed_statement(), parced.get_num());
    Calculation calculated(constr.get_root());
    std::cout << "Result = " << calculated.get_calculation() << std::endl;
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

int Parser::num_of_elements(std::string S) //getting number of elements
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

std::string* Parser::parse(std::string D) //dividing into operators and operands
{
    std::string* L = new std::string[num_of_tokens];
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
    if (i < num_of_tokens)
    {
        L[i] = D.substr(k, j - k);
    }
    return L;
}

void Parser::replace_variables(std::vector<std::pair<std::string, std::string>> pairs, std::string* B)
{
    for (int i = 0; i < num_of_tokens; i++)
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
}

void Parser::sort_station(std::string* L) //Shunting-Yard algorithm
{
    int n = num_of_tokens;
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
                        num_of_tokens -= 2;
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
    std::string* parsed_statement = new std::string[num_of_tokens];
    Copy(out);
    delete[] out;
}

void Parser::Copy(std::string* out)
{
    parsed_statement = new std::string[num_of_tokens];
    for (int i = 0; i < num_of_tokens; i++)
    {
        parsed_statement[i] = out[i];
    }
}

char Parser::priority(char a, char b) //priority check
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